#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

#ifndef __ISEARCHER_UNITTESTS__CPP__
#define __ISEARCHER_UNITTESTS__CPP__

namespace sequence_ut {
	void run() {
		using namespace sequence_ut;
		//unit1_run();
		//unit2_run();
		unit3_run();
	}


}

int main() {
	sequence_ut::run();
	cin.get();
	cin.get();
	return 0;
}

#endif
