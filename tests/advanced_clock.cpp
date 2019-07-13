#include <cassert>
#include <thread>

#include "Timer.hpp"

using namespace std::chrono_literals;


// Helper(s)
namespace
{

int64_t nanoToMilli(int64_t nano)
{
	return nano / 1000000;
}

}

// Tests

void basic_usage()
{

	Timer::AdvancedClock ac;
	std::this_thread::sleep_for(10ms);
	assert(nanoToMilli(ac.getTimeNanoCount()) == 10);

	ac.pause();
	std::this_thread::sleep_for(10ms);
	assert(ac.getDuractionAs<std::chrono::milliseconds>().count() == 10);

	ac.start();
	std::this_thread::sleep_for(10ms);
	assert(ac.getDuractionAs<std::chrono::milliseconds>().count() == 20);

	ac.pause();
	std::this_thread::sleep_for(10ms);
	assert(ac.getDuractionAs<std::chrono::milliseconds>().count() == 20);
	ac.start();
	assert(ac.getDuractionAs<std::chrono::milliseconds>().count() == 20);
}

void copy()
{
	{
		Timer::AdvancedClock ac1;
		std::this_thread::sleep_for(20ms);
		ac1.pause();
		std::this_thread::sleep_for(20ms);

		Timer::AdvancedClock ac2(ac1);
		assert(ac1.getDuractionAs<std::chrono::milliseconds>().count() == ac2.getDuractionAs<std::chrono::milliseconds>().count());
	}

	{
		Timer::AdvancedClock ac1;
		std::this_thread::sleep_for(20ms);

		Timer::AdvancedClock ac2;
		ac2.pause();
		std::this_thread::sleep_for(20ms);
		ac2 = ac1;
		assert(ac1.getDuractionAs<std::chrono::milliseconds>().count() == ac2.getDuractionAs<std::chrono::milliseconds>().count());
	}
	
}

int main()
{
	basic_usage();
	copy();
}