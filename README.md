# Timer

## Description
A simple C++ header-only library to use cross-platform timer functionnalities using only the standard library.

## How to use it?
There is 2 types of class in this library:
* the __clocks__
* the __timers__

### The clocks
A clock allow you to have a duration between now and the last reset of the clock.
Each clock have a method to have this duration in the format of the std::chrono::system_clock, you can also have this value in any duration defined with std::chrono::duration or as the number of nanoseconds.

There is 2 clocks, __SimpleClock__ with only this functionnalities, and __AdvancedClock__ which can be paused.

In the file __src/main.cpp__ you can see examples to see how to use them.

### The timers
A timer allow you to start an action at the end of a duration.

If you want to run a function asynchronously in 3 seconds automatically while the main thread is doing something else, a __ThreadTimer__ is what you need.

If you want to run a function asynchronously every 3 seconds while the main thread is doing something else, a __LoopThreadTimer__ is what you need.

In the file __src/main.cpp__ you can see examples to see how to use them.

## How to install it?
It is a header only library, so you just need to have the header __Timer.hpp__ in your path.