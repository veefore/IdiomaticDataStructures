#include "stdafx.h"
#include "SortComparison.h"
#include <iostream>


#ifndef __ALG_COMP_USERINTERFACE__H__
#define __ALG_COMP_USERINTERFACE__H__

using namespace std;

class AlgCompUI {

	static void show_menu() {
		cout << "Command menu: \n";
		cout << "1. Run default all algorithms time comparison.\n";
		cout << "2. Check for correctness of a particular algorithm.\n";
		cout << "3. Quit.\n";
		cout << "To perform any command, type the corresponding number and press ENTER." << endl;
	}

	static void run_default_time_comparison() {
		cout << "\nConduct a new comparison (it will take up to 5 minutes) instead of showing precalculated results? (Y/N):";
		char input;
	start:
		cin >> input;
		if (input == 'Y' || input == 'y') {
			SortComparison::clear_default_comparison_results();
		}
		else if (input == 'N' || input == 'n') {}
		else {
			cout << "\nInvalid input. (Y/N):";
			goto start;
		}
		SortComparison::run_sort_comparison();
	}

	static void run_check_single_alg() {
		ISorter<int> *sorter;
		char input;
		cout << "Choose a sorting algorithm by writing the correspondent number and then pressing enter.\n";
		cout << "1. QuickSort.\n2. MergeSort.\n3. ShellSort.\n4. BubbleSort.\n5. ShakerSort.\n6. InsertionSort.\n7. BinaryInsertionSort.\n8. SelectionSort.\n";
	start:
		cin >> input;
		if (input < '1' || input > '8') {
			cout << "\nInvalid input. Try again.\n";
			goto start;
		}
		if (input == '1')
			sorter = new QuickSort<int>();
		else if (input == '2')
			sorter = new MergeSort<int>();
		else if (input == '3') 
			sorter = new ShellSort<int>();
		else if (input == '4')
			sorter = new BubbleSort<int>();
		else if (input == '5')
			sorter = new ShakerSort<int>();
		else if (input == '6')
			sorter = new InsertionSort<int>();
		else if (input == '7')
			sorter = new BinaryInsertionSort<int>();
		else
			sorter = new SelectionSort<int>();
		
		bool input_data_flag;
		cout << "\nDo you want to fill the sequence to be sorted with elements yourself? Otherwise it will be filled automatically. (Y/N):";
	id_flag_start:
		cin >> input;
		if (input == 'Y' || input == 'y') 
			input_data_flag = true;
		else if (input == 'N' || input == 'n')
			input_data_flag = false;
		else {
			cout << "\nInvalid input. Try again. (Y/N):" << flush;
			goto id_flag_start;
		}


		cout << "Enter sequence size:";
		int size;
		cin >> size;
		
		Sequence<int> *base_sequence = new ArraySequence<int>();
		if (input_data_flag) {
			cout << "\nPlease enter " << size << " elements separated by whitespace.";
			for (int i = 0, temp; i < size; i++) {
				cin >> temp;
				base_sequence->Append(temp);
			}
		}
		else {
			base_sequence->FillWithRandom(size, 10000);
			bool sorted_flag;
			cout << "Do you want the sequence to be sorted? (Y/N):";
		sorted_flag_start:
			cin >> input;
			if (input == 'Y' || input == 'y')
				sorted_flag = true;
			else if (input == 'N' || input == 'n')
				sorted_flag = false;
			else {
				cout << "\nInvalid input. Try again. (Y/N):" << flush;
				goto sorted_flag_start;
			}
		
			if (sorted_flag) {
				QuickSort<int> qs;
				qs.Sort(base_sequence);
			}
		}	
	
		ListSequence<int> *resultant_list_seq = new ListSequence<int>(base_sequence);
		ArraySequence<int> *resultant_arr_seq = new ArraySequence<int>(base_sequence);
		sorter->Sort(resultant_arr_seq);
		sorter->Sort(resultant_list_seq);

		cout << "Resultant ArraySequence is ";
		if (resultant_arr_seq->isSorted())
			cout << "sorted.\n";
		else
			cout << "not sorted. Fail.\n";

		cout << "Resultant ListSequence is ";
		if (resultant_list_seq->isSorted())
			cout << "sorted.\n";
		else
			cout << "not sorted. Fail.\n";
		cout << flush;

		bool manual_check_flag;
		cout << "Do you want to check the results manually? (Y/N):";
	m_c_flag_start:
		cin >> input;
		if (input == 'Y' || input == 'y')
			manual_check_flag = true;
		else if (input == 'N' || input == 'n')
			manual_check_flag = false;
		else {
			cout << "\nInvalid input. Try again. (Y/N):" << flush;
			goto m_c_flag_start;
		}

		if (manual_check_flag) {
			cout << "The base sequence is:\n";
			base_sequence->Print();
			cout << "\nThe resultant ArraySequence is:\n";
			resultant_arr_seq->Print();
			cout << "\nThe resultant ListSequence is:\n";
			resultant_list_seq->Print();
		}
	}

public:
	static void launch() {
		char input;
	start:
		show_menu();
		cin >> input;
		while (input < '1' || input > '3') {
			cout << "\nIncorrect input. Please write a valid number from the numeration above.\n";
			cin >> input;
		}
		if (input == '1') 
			run_default_time_comparison();
		if (input == '2') 
			run_check_single_alg();
		if (input == '3') 
			exit(EXIT_SUCCESS);
		
		goto start;
	}

};


#endif