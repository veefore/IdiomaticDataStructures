
#include "ArraySequence.h"
#include "ListSequence.h"
#include <iostream>
#include "Test.h"


int main() {
	cout << "Running tests on ArraySequence" << endl;
	run_test([]() {
		return (Sequence<int> *)new ArraySequence<int>();
	}
	);

	cout << endl << "Running tests on ListSequence." << endl;
	run_test([]() {
		return (Sequence<int> *)new ListSequence<int>();
	});
	return 0;
}