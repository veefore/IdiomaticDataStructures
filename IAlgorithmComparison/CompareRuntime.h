#include "stdafx.h"
#include "DurationCounter.h"
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <iostream>

#ifndef __COMPARERUNTIME__H__
#define __COMPARERUNTIME__H__

using namespace std;

struct ComparationElement {
	string name;

	double time_s;

	function<void()> function;
	
	ComparationElement(const std::function<void()> &function, const string &name, double time_s) : function(function), time_s(time_s), name(name) {}

	void print() {
		cout << name << " ran in " << time_s << "s." << endl;
	}
};



class CompareRuntime {
	bool sorted;
	vector<ComparationElement> functions;
	string name;

public:
	CompareRuntime(const string &str) : sorted(false), name(str) {}

	void add_function(const function<void()> &func, const string &name) {
		DurationCounter counter;
		double time = 0;
		for (int i = 0; i < 10; i++) {
			counter.start_now();
			func();
			counter.end_now();
			time += counter.get_duration();
		}
		time /= 10;
		functions.push_back(ComparationElement(func, name, time));
	}

	vector<ComparationElement> &result() {
		sort(functions.begin(), functions.end(), 
			[](const ComparationElement &element1, const ComparationElement &element2) {
			return element1.time_s < element2.time_s;
		});
		sorted = true;
		return functions;
	}

	void print_result() {
		if (!sorted)
			result();
		cout << endl << name << " comparison result:" << endl;
		int i = 1;
		for (ComparationElement &el : functions) {
			cout << "#" << i << ". ";
			el.print();
			i++;
		}
	}


};







#endif
