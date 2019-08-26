#include "stdafx.h"
#include "SortComparison.h"

#include <cstdio>
#include <vector>

#ifndef __SORTCOMPARISON__CPP__
#define __SORTCOMPARISON__CPP__

using namespace std;

template <typename TObject>
ISorter<TObject> **SortComparison::declare_sorts() {
	ISorter<TObject> **sorters_arr = new ISorter<TObject> *[8];

	QuickSort<TObject> *quicksort = new QuickSort<TObject>;
	MergeSort<TObject> *mergesort = new MergeSort<TObject>();
	ShellSort<TObject> *shell_sort = new ShellSort<TObject>();
	ShakerSort<TObject> *shaker_sort = new ShakerSort<TObject>();
	BubbleSort<TObject> *bubble_sort = new BubbleSort<TObject>();
	BinaryInsertionSort<TObject> *bin_insertion_sort = new BinaryInsertionSort<TObject>();
	InsertionSort<TObject> *insertion_sort = new InsertionSort<TObject>();
	SelectionSort<TObject> *selection_sort = new SelectionSort<TObject>();

	sorters_arr[0] = quicksort;
	sorters_arr[1] = mergesort;
	sorters_arr[2] = shell_sort;
	sorters_arr[3] = shaker_sort;
	sorters_arr[4] = bubble_sort;
	sorters_arr[5] = bin_insertion_sort;
	sorters_arr[6] = insertion_sort;
	sorters_arr[7] = selection_sort;

	return sorters_arr;
}

template <typename TObject, template <typename T> typename TArr>
void SortComparison::sort_comparison_add_functions(CompareRuntime &sort_comparison, TArr<TObject> **data_arr, ISorter<TObject> **sorters_arr) {

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[0]->Sort(data_arr[0]);
	}, "QuickSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[1]->Sort(data_arr[1]);
	}, "MergeSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[2]->Sort(data_arr[2]);
	}, "ShellSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[3]->Sort(data_arr[3]);
	}, "ShakerSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[4]->Sort(data_arr[4]);
	}, "BubbleSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[5]->Sort(data_arr[5]);
	}, "BinaryInsertionSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[6]->Sort(data_arr[6]);
	}, "InsertionSort");

	sort_comparison.add_function([data_arr, sorters_arr]() {
		sorters_arr[7]->Sort(data_arr[7]);
	}, "SelectionSort");
}


template <typename TObject, template <class T> typename TSeq>
void SortComparison::run_seq_sort_comparison(const string &comparison_name, Sequence<TObject> *arr, bool(*lessThan)(const TObject &el1, const TObject &el2)) {

	ISorter<TObject> **sorters_arr = declare_sorts<TObject>();

	Sequence<TObject> **data_arr = new Sequence<TObject> *[8];
	for (int i = 0; i < 8; i++)
		data_arr[i] = new TSeq<TObject>(arr);

	CompareRuntime sort_comparison(comparison_name);
	sort_comparison_add_functions<TObject, Sequence>(sort_comparison, data_arr, sorters_arr);
	sort_comparison.print_result();
}

void remove_file(const string &str) {
	ifstream ifstr;
	ifstr.open(str);
	if (ifstr.good()) {
		ifstr.close();
		remove(str.c_str());
	}
	else
		ifstr.close();
}

void SortComparison::run_sort_comparison() {
	cout << endl << "Default sorting algorithms comparison on sequences of size 1000 in 3 different cases: \n1) Not sorted. 2) Sorted. 3) Sorted in reverse order." << endl;
	//ARRSEQ, RANDOM DATA
	ifstream in_arr_comp_res_file("rd_arrseq_sort_comparison_result.txt");
	if (in_arr_comp_res_file.is_open()) {
		cout << in_arr_comp_res_file.rdbuf() << flush;
		in_arr_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *arr_seq = new ArraySequence<int>();
		arr_seq->FillWithRandom(1000, 1000);
		run_seq_sort_comparison<int, ArraySequence>("ArraySequence, random data", arr_seq);
		reader.stop();

		ofstream out_arr_comp_res_file("rd_arrseq_sort_comparison_result.txt");
		out_arr_comp_res_file << reader.str();
		reader.clear_buffer();
		out_arr_comp_res_file.close();

		in_arr_comp_res_file.open("rd_arrseq_sort_comparison_result.txt");
		cout << in_arr_comp_res_file.rdbuf();
		in_arr_comp_res_file.close();
	}

	//LISTSEQ, RANDOM DATA
	ifstream in_list_comp_res_file("rd_listseq_sort_comparison_result.txt");
	if (in_list_comp_res_file.is_open()) {
		cout << in_list_comp_res_file.rdbuf() << flush;
		in_list_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *list_seq = new ListSequence<int>();
		list_seq->FillWithRandom(1000, 1000);
		run_seq_sort_comparison<int, ListSequence>("ListSequence, random data", list_seq);
		reader.stop();

		ofstream out_list_comp_res_file("rd_listseq_sort_comparison_result.txt");
		out_list_comp_res_file << reader.str();
		reader.clear_buffer();
		out_list_comp_res_file.close();

		in_list_comp_res_file.open("rd_listseq_sort_comparison_result.txt");
		cout << in_list_comp_res_file.rdbuf();
		in_list_comp_res_file.close();
	}

	//ARRSEQ, SORTED DATA
	in_arr_comp_res_file.open("sd_arrseq_sort_comparison_result.txt");
	if (in_arr_comp_res_file.is_open()) {
		cout << in_arr_comp_res_file.rdbuf() << flush;
		in_arr_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *arr_seq = new ArraySequence<int>();
		arr_seq->FillWithRandom(1000, 10000);
		QuickSort<int> qsort;
		qsort.Sort(arr_seq);
		run_seq_sort_comparison<int, ArraySequence>("ArraySequence, sorted data", arr_seq);
		reader.stop();

		ofstream out_arr_comp_res_file("sd_arrseq_sort_comparison_result.txt");
		out_arr_comp_res_file << reader.str();
		reader.clear_buffer();
		out_arr_comp_res_file.close();

		in_arr_comp_res_file.open("sd_arrseq_sort_comparison_result.txt");
		cout << in_arr_comp_res_file.rdbuf();
		in_arr_comp_res_file.close();
	}

	//LISTSEQ, SORTED DATA
	in_list_comp_res_file.open("sd_listseq_sort_comparison_result.txt");
	if (in_list_comp_res_file.is_open()) {
		cout << in_list_comp_res_file.rdbuf() << flush;
		in_list_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *list_seq = new ListSequence<int>();
		list_seq->FillWithRandom(1000, 10000);
		QuickSort<int> qsort;
		qsort.Sort(list_seq);
		run_seq_sort_comparison<int, ListSequence>("ListSequence, sorted data", list_seq);
		reader.stop();

		ofstream out_list_comp_res_file("sd_listseq_sort_comparison_result.txt");
		out_list_comp_res_file << reader.str();
		reader.clear_buffer();
		out_list_comp_res_file.close();

		in_list_comp_res_file.open("sd_listseq_sort_comparison_result.txt");
		cout << in_list_comp_res_file.rdbuf();
		in_list_comp_res_file.close();
	}

	//ARRSEQ, SORTED IN REVERSE ORDER DATA
	in_arr_comp_res_file.open("srod_arrseq_sort_comparison_result.txt");
	if (in_arr_comp_res_file.is_open()) {
		cout << in_arr_comp_res_file.rdbuf() << flush;
		in_arr_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *arr_seq = new ArraySequence<int>();
		arr_seq->FillWithRandom(1000, 10000);
		QuickSort<int> qsort;
		qsort.Sort(arr_seq, [](const int &value1, const int &value2) {
			return value2 < value1;
		});
		run_seq_sort_comparison<int, ArraySequence>("ArraySequence, sorted in reverse order data", arr_seq);
		reader.stop();

		ofstream out_arr_comp_res_file("srod_arrseq_sort_comparison_result.txt");
		out_arr_comp_res_file << reader.str();
		reader.clear_buffer();
		out_arr_comp_res_file.close();

		in_arr_comp_res_file.open("srod_arrseq_sort_comparison_result.txt");
		cout << in_arr_comp_res_file.rdbuf();
		in_arr_comp_res_file.close();
	}

	//LISTSEQ, SORTED IN REVERSE ORDER DATA
	in_list_comp_res_file.open("srod_listseq_sort_comparison_result.txt");
	if (in_list_comp_res_file.is_open()) {
		cout << in_list_comp_res_file.rdbuf() << flush;
		in_list_comp_res_file.close();
	}
	else {
		output_reader reader;
		reader.start();
		Sequence<int> *list_seq = new ListSequence<int>();
		list_seq->FillWithRandom(1000, 10000);
		QuickSort<int> qsort;
		qsort.Sort(list_seq, [](const int &value1, const int &value2) {
			return value2 < value1;
		});
		run_seq_sort_comparison<int, ListSequence>("ListSequence, sorted in reverse order data", list_seq);
		reader.stop();

		ofstream out_list_comp_res_file("srod_listseq_sort_comparison_result.txt");
		out_list_comp_res_file << reader.str();
		reader.clear_buffer();
		out_list_comp_res_file.close();

		in_list_comp_res_file.open("srod_listseq_sort_comparison_result.txt");
		cout << in_list_comp_res_file.rdbuf();
		in_list_comp_res_file.close();
	}
}

	void SortComparison::clear_default_comparison_results() {
		remove_file("rd_arrseq_sort_comparison_result.txt");
		remove_file("rd_listseq_sort_comparison_result.txt");
		remove_file("sd_arrseq_sort_comparison_result.txt");
		remove_file("sd_listseq_sort_comparison_result.txt");
		remove_file("srod_arrseq_sort_comparison_result.txt");
		remove_file("srod_listseq_sort_comparison_result.txt");
	}



#endif