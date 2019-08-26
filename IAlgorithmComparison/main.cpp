#include "stdafx.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include "SortComparison.h"
#include "UserInterface.h"

using namespace std;

void Sleep(unsigned int ms) {
	clock_t wait_ms = (clock_t)ms;
	clock_t start_time = clock();
	while (clock() != start_time + wait_ms);
	return;
}





int main() {
	AlgCompUI::launch();
	

	cin.get();
	return 0;
}
