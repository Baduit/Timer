#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <condition_variable>

namespace Timer
{

using Duration = decltype(std::chrono::system_clock::now() - std::chrono::system_clock::now());

/*
** You can have the duration between now and the last reset of the clock. 
** It can't be paused.
*/
class SimpleClock
{
	public:
		SimpleClock() { reset(); };

		void		reset() { _first = std::chrono::system_clock::now(); }
		
		Duration	getTimeDuration() { return std::chrono::system_clock::now() - _first; }

		template<typename T>
		auto		getDuractionAs() { return std::chrono::duration_cast<T>(getTimeDuration()); }

		int64_t		getTimeNanoCount() { return getDuractionAs<std::chrono::nanoseconds>().count(); }

	private:
		std::chrono::system_clock::time_point _first;
};

/*
** You can have the duration between now and the last reset of the clock. 
** It can be paused.
** Default status at construction: started.
*/
class AdvancedClock
{
	public:
		AdvancedClock() { reset(); }

		void		reset()
		{
			_run_timer.reset();
			_pause_timer.reset();
			_paused_time = {};
		}
		
		auto		getTimeDuration()
		{
			return _run_timer.getTimeDuration() - getTotalPauseTime();
		}

		template<typename T>
		auto		getDuractionAs()
		{
			return _run_timer.getDuractionAs<T>() - getTotalPauseTimeAs<T>();
		}

		int64_t		getTimeNanoCount()
		{
			return _run_timer.getTimeNanoCount() - getTotalPauseTimeNanoCount();
		}

		void		pause()
		{
			if (!_pause_timer.has_value())
				_pause_timer.emplace();
		}

		void		start()
		{
			if (_pause_timer.has_value())
			{
				_paused_time += _pause_timer->getTimeDuration();
				_pause_timer.reset();
			}
		}

		Duration	getTotalPauseTime()
		{
			return (_pause_timer.has_value()) ? _paused_time + _pause_timer->getTimeDuration() : _paused_time;
		}

		template<typename T>
		auto 	getTotalPauseTimeAs() { return std::chrono::duration_cast<T>(getTotalPauseTime()); }


		int64_t	getTotalPauseTimeNanoCount() { return getTotalPauseTimeAs<std::chrono::nanoseconds>().count(); }

	private:
		SimpleClock							_run_timer;
		std::optional<SimpleClock>			_pause_timer;
		Duration							_paused_time;
};

/*
** Make a thread sleep, same as std::this_thread::sleep_for but cancelable
*/
class Sleeper
{
	public:
		template<typename D>
		Sleeper(const D& duration)
		{
			sleep(duration);
		}

		template<typename D>
		void	operator()(const D& duration)
		{
			sleep(duration);
		}

		template<typename D>
		void	sleep(const D& duration)
		{
			std::unique_lock lock(_mutex);
			_cv.wait_for(lock, duration);
		}

		// Use it if you want to awake only one thread sleeping
		void	cancel_one()
		{
			_cv.notify_one();
		}

		// Use it if you cant to awake all the sleeping threads (one or more)
		void	cancel_all()
		{
			_cv.notify_all();
		}

	private:
		std::mutex				_mutex;
		std::condition_variable	_cv;
};

/*
** Execute an action at the end of the choosed duration.
** For the moment it can't be paused.
*/
class ThreadTimer
{
	public:
		ThreadTimer() = default;

		template<typename D, typename Cb>
		ThreadTimer(const D& duration, Cb&& cb)
		{
			start(duration, std::move(cb));
		}

		virtual ~ThreadTimer()
		{
			stop();
		}

		template<typename D, typename Cb>
		auto	start(const D& duration, Cb&& cb)
		{
			auto thread_cb = 
				[this, duration, cb]()
				{
					auto moved_cb = std::move(cb);
					std::this_thread::sleep_for(duration);
					if (!_stop)
						return moved_cb();
					else
						return decltype(moved_cb())();
				};
			auto task = std::packaged_task<decltype(thread_cb())()>(std::forward<decltype(thread_cb)>(thread_cb));
    		auto future = task.get_future();
		
			_thread = std::thread(std::move(task));
			return future;
		}

		// by calling this function while the timer is started, future used as result for the callback is unitialized
		void	stop()
		{
			_stop = true;
			if (_thread.joinable())
				_thread.join();
		}

	private:
		std::thread			_thread;
		std::atomic<bool>	_stop = false;
};

/*
** Execute an action at the end of the choosed duration in a loop.
** For the moment it can't be paused.
*/
class LoopThreadTimer
{
	public:
		LoopThreadTimer() = default;

		template<typename D, typename Cb>
		LoopThreadTimer(const D& duration, Cb&& cb)
		{
			start(duration, std::move(cb));
		}

		virtual ~LoopThreadTimer()
		{
			hard_stop();
		}

		template<typename D, typename Cb>
		void	start(const D& duration, Cb&& cb)
		{
			auto thread_cb = 
				[this, duration, cb]()
				{
					auto moved_cb = std::move(cb);
					while (!_soft_stop)
					{
						std::this_thread::sleep_for(duration);
						if (!_hard_stop)
							moved_cb();
						else
							break;
					}
				};
			auto task = std::packaged_task<decltype(thread_cb())()>(std::forward<decltype(thread_cb)>(thread_cb));
		
			_thread = std::thread(std::move(task));
		}

		// call the callback a last time
		void	soft_stop()
		{
			_soft_stop = true;
			if (_thread.joinable())
				_thread.join();
		}

		// does call the callback a last time
		void	hard_stop()
		{
			_hard_stop = true;
			if (_thread.joinable())
				_thread.join();
		}

	private:
		std::thread			_thread;
		std::atomic<bool>	_soft_stop = false;
		std::atomic<bool>	_hard_stop = false;
};

}
