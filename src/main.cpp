#include <iostream>

#include "Timer.hpp"

using namespace Timer;
using namespace std::chrono_literals;

int64_t nano_to_milli(int64_t nano)
{
	return nano / 1000000;
}

void exampleSimpleClock()
{
	std::cout << "SimpleClock" << std::endl;

	SimpleClock sc;
	std::this_thread::sleep_for(1s);
	std::cout << nano_to_milli(sc.get_time_nano_count()) << " milliseconds" << std::endl;

	sc.reset();
	std::cout << nano_to_milli(sc.get_time_nano_count()) << " milliseconds" << std::endl;

	std::cout << "End" << std::endl << std::endl;
}

void exampleAdvancedClock()
{
	std::cout << "AdvancedClock" << std::endl;

	AdvancedClock ac;
	std::this_thread::sleep_for(1s);
	std::cout << nano_to_milli(ac.get_time_nano_count()) << " milliseconds" << std::endl;

	ac.pause();
	std::this_thread::sleep_for(1s);
	std::cout << nano_to_milli(ac.get_time_nano_count()) << " milliseconds" << std::endl;

	ac.start();
	std::this_thread::sleep_for(1s);
	std::cout << nano_to_milli(ac.get_time_nano_count()) << " milliseconds" << std::endl;

	std::cout << "End" << std::endl << std::endl;
}

void exampleSleeper()
{
	std::cout << "Sleeper" << std::endl;

	SimpleClock sc;
	Sleeper	sleeper(1s);
	std::cout << nano_to_milli(sc.get_time_nano_count()) << " milliseconds" << std::endl;

	std::thread thread(
		[&]
		{
			std::this_thread::sleep_for(500ms);
			sleeper.cancel_one();
		}
	);
	sc.reset();
	sleeper(1s);
	std::cout << nano_to_milli(sc.get_time_nano_count()) << " milliseconds" << std::endl;
	thread.join();


	std::cout << "End" << std::endl << std::endl;
}

void exampleThreadTimer()
{
	std::cout << "ThreadTimer" << std::endl;

	ThreadTimer tt;
	auto future_result = tt.start(2s,
		[]()
		{
			std::cout << "At the end of the world;" << std::endl;
			return 5;
		}
	);
	auto waited_result = future_result.get();
	std::cout << waited_result << std::endl;

	ThreadTimer ttt(1s,
		[]()
		{
			std::cout << "Hello from the other side." << std::endl;
		}
	);
	std::this_thread::sleep_for(1.2s);

	std::cout << "End" << std::endl << std::endl;
}

void exampleLoopThreadTimer()
{
	std::cout << "LoopThreadTimer" << std::endl;

	LoopThreadTimer ltt(0.3s,
		[]()
		{
			std::cout << "At the end of the world;" << std::endl;
		}
	);
	std::this_thread::sleep_for(1s);

	std::cout << "End" << std::endl;
}

int	main()
{
	exampleSimpleClock();
	exampleAdvancedClock();
	exampleSleeper();
	exampleThreadTimer();
	exampleLoopThreadTimer();
	return 0;
}
