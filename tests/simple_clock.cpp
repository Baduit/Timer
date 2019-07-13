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

	Timer::SimpleClock sc;
	std::this_thread::sleep_for(10ms);
	assert(nanoToMilli(sc.getTimeNanoCount()) == 10);

	sc.reset();
	assert(sc.getDuractionAs<std::chrono::milliseconds>().count() == 0);
}

void copy()
{
	{
		Timer::SimpleClock sc1;
		std::this_thread::sleep_for(20ms);

		Timer::SimpleClock sc2(sc1);
		assert(sc1.getDuractionAs<std::chrono::milliseconds>().count() == sc2.getDuractionAs<std::chrono::milliseconds>().count());
	}

	{
		Timer::SimpleClock sc1;
		std::this_thread::sleep_for(20ms);

		Timer::SimpleClock sc2;
		std::this_thread::sleep_for(20ms);
		sc2 = sc1;
		assert(sc1.getDuractionAs<std::chrono::milliseconds>().count() == sc2.getDuractionAs<std::chrono::milliseconds>().count());
	}
	
}

int main()
{
	basic_usage();
	copy();
}