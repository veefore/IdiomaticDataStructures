#include "stdafx.h"
#include <chrono>

#ifndef __DURATIONCOUNTER__H__
#define __DURATIONCOUNTER__H__

class DurationCounter {
	double dur;
	std::chrono::time_point<std::chrono::steady_clock> start, end;

public: 
	DurationCounter() : dur(0) {};

	void start_now() {
		start = std::chrono::high_resolution_clock::now();
	}

	void end_now() {
		end = std::chrono::high_resolution_clock::now();
	}
	
	double get_duration() {
		std::chrono::duration<double> elapsed = end - start;
		//std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		dur = elapsed.count();
		return dur;
	}
};

#endif 