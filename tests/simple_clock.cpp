#include <cassert>
#include <thread>

#include <Timer.hpp>

using namespace std::chrono_literals;

void copy()
{
	{
		Timer::SimpleClock sc1;
		std::this_thread::sleep_for(20ms);

		Timer::SimpleClock sc2(sc1);
		assert(sc1.get_duration_as<std::chrono::milliseconds>().count() == sc2.get_duration_as<std::chrono::milliseconds>().count());
	}

	{
		Timer::SimpleClock sc1;
		std::this_thread::sleep_for(20ms);

		Timer::SimpleClock sc2;
		std::this_thread::sleep_for(20ms);
		sc2 = sc1;
		assert(sc1.get_duration_as<std::chrono::milliseconds>().count() == sc2.get_duration_as<std::chrono::milliseconds>().count());
	}
	
}

int main()
{
	copy();
}