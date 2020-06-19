#include <cassert>
#include <thread>

#include <Timer.hpp>

using namespace std::chrono_literals;


void copy()
{
	{
		Timer::AdvancedClock ac1;
		std::this_thread::sleep_for(20ms);
		ac1.pause();
		std::this_thread::sleep_for(20ms);

		Timer::AdvancedClock ac2(ac1);
		assert(ac1.get_duration_as<std::chrono::milliseconds>().count() == ac2.get_duration_as<std::chrono::milliseconds>().count());
	}

	{
		Timer::AdvancedClock ac1;
		std::this_thread::sleep_for(20ms);

		Timer::AdvancedClock ac2;
		ac2.pause();
		std::this_thread::sleep_for(20ms);
		ac2 = ac1;
		assert(ac1.get_duration_as<std::chrono::milliseconds>().count() == ac2.get_duration_as<std::chrono::milliseconds>().count());
	}
	
}

int main()
{
	copy();
}