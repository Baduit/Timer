#include <iostream>

#include "Timer.hpp"

using namespace Timer;
using namespace std::chrono_literals;

uint64_t nanoToMilli(uint64_t nano)
{
	return nano / 1000000;
}

int	main()
{
	std::cout << "SimpleClock" << std::endl;
	SimpleClock sc;
	std::this_thread::sleep_for(1s);
	std::cout << nanoToMilli(sc.getTimeNanoCount()) << " milliseconds" << std::endl;
	sc.reset();
	std::cout << nanoToMilli(sc.getTimeNanoCount()) << " milliseconds" << std::endl;
	std::cout << "End" << std::endl << std::endl;

	std::cout << "AdvancedClock" << std::endl;
	AdvancedClock ac;
	std::this_thread::sleep_for(1s);
	std::cout << nanoToMilli(ac.getTimeNanoCount()) << " milliseconds" << std::endl;
	ac.pause();
	std::this_thread::sleep_for(1s);
	std::cout << nanoToMilli(ac.getTimeNanoCount()) << " milliseconds" << std::endl;
	ac.start();
	std::this_thread::sleep_for(1s);
	std::cout << nanoToMilli(ac.getTimeNanoCount()) << " milliseconds" << std::endl;
	std::cout << "End" << std::endl << std::endl;

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

	std::cout << "LoopThreadTimer" << std::endl;
	LoopThreadTimer ltt(0.3s,
		[]()
		{
			std::cout << "At the end of the world;" << std::endl;
		}
	);
	std::this_thread::sleep_for(1s);
	std::cout << "End" << std::endl;

	return 0;
}
