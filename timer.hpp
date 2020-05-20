#ifndef TIMER_CORE_H
#define TIMER_CORE_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
public:
	Timer();
	void restart();
	float current();
};

#endif // TIMER_CORE_H