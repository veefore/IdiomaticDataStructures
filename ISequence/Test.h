
#include "Sequence.h"
#include <iostream>
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\IndexException.h"


#ifndef __TEST__H__
#define __TEST__H__



void end_test() {
	std::cout << "Quitting testing interface." << std::endl;
}



void test_length(int length, double test, Sequence<int> *seq) {
	if (seq->getLength() != length) {
		cout << "Test 1." << test << " failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1." << test << " passed." << endl;
}

void test_catching_get(int index, int test, int step, Sequence<int> *seq) {
	bool caught_an_exception = false;
	try {
		seq->Get(index);
	}
	catch (IndexException excp) {
		caught_an_exception = true;
		cout << "Test 1." << test << ", step " << step << " passed." << endl;
	}
	catch (...) {
		cout << "Test 1." << test << ", step " << step << " passed incorrectly." << endl;
		end_test();
		return;
	}
	if (caught_an_exception != true) {
		cout << "Test 1." << test << ", step " << step << " passed." << endl;
		end_test();
		return;
	}
}

void run_test(Sequence<int> *(*constructor)()) {
	using namespace std;
	cout << "Performing tests..." << endl;
	Sequence<int> *seq = constructor();
	cout << "Test 1.1 passed." << endl;

	test_length(0, 2, seq);

	seq->Append(23);
	cout << "Test 1.3 passed." << endl;

	test_length(1, 4, seq);


	if (seq->GetFirst() != 23) {
		cout << "Test 1.5 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.5 passed." << endl;

	if (seq->GetLast() != 23) {
		cout << "Test 1.6 failed" << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.6 passed" << endl;

	if (seq->Get(0) != 23) {
		cout << "Test 1.7 failed at first step." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.7, step 1 passed." << endl;
	
	test_catching_get(-1, 7, 2, seq);
	
	test_catching_get(1, 7, 3, seq);

	seq->Append(43);
	cout << "Test 1.8 passed." << endl;

	test_length(2, 9, seq);

	if (seq->GetFirst() != 23) {
		cout << "Test 1.10 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.10 passed." << endl;

	if (seq->GetLast() != 43) {
		cout << "Test 1.11 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.11 passed." << endl;

	
	if (seq->Get(0) != 23) {
		cout << "Test 1.12, step 1 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.12, step 1 passed." << endl;

	if (seq->Get(1) != 43) {
		cout << "Test 1.12, step 2 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.12, step 2 passed." << endl;

	test_catching_get(-1, 12, 3, seq);

	test_catching_get(2, 12, 4, seq);


	seq->Prepend(53);
	cout << "Test 1.13 passed." << endl;

	test_length(3, 14, seq);

	if (seq->GetFirst() != 53) {
		cout << "Test 1.15 failed." << endl;
		end_test();
		return;
	} 
	else
		cout << "Test 1.15 passed." << endl;

	if (seq->GetLast() != 43) {
		cout << "Test 1.16 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.16 passed." << endl;

	if (seq->Get(0) != 53) {
		cout << "Test 1.17, step 1 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.17, step 1 passed." << endl;

	if (seq->Get(1) != 23) {
		cout << "Test 1.17, step 2 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.17, step 2 passed." << endl;

	test_catching_get(-1, 17, 3, seq);

	test_catching_get(3, 17, 4, seq);

	Sequence<int> *seq2 = seq->GetSubsequence(1, 1);
	test_length(1, 18.1, seq2);

	if (seq2->GetFirst() != 23 || seq2->GetLast() != 23) {
		cout << "Test 1.18.2 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.18.2 passed." << endl;

	seq->InsertAt(63, 1);
	cout << "Test 1.19.1 passed." << endl;

	test_length(4, 19.2, seq);

	if (seq->Get(2) != 23) {
		cout << "Test 1.19.3 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.19.3 passed." << endl;

	try {
		seq->InsertAt(33, -1);
	}
	catch (IndexException excp) {
		cout << "Test 1.20 passed." << endl;
	} 
	catch (...) {
		cout << "Test 1.20 failed." << endl;
	}

	seq->Remove(53);
	cout << "Test 1.21.1 passed." << endl;

	test_length(3, 21.2, seq);

	if (seq->Get(0) != 63) {
		cout << "Test 1.21.3 failed." << endl;
		end_test();
		return;
	}
	else
		cout << "Test 1.21.3 passed." << endl;

	

	cout << "All tests passed." << endl;
}

#endif
