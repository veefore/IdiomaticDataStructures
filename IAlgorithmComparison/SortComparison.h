#include "stdafx.h"
#include <fstream>
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ListSequence.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ArraySequence.h"
#include "Sorts.h"
#include "CompareRuntime.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\output_reader.h"


#ifndef __SORTCOMPARISON__H__
#define __SORTCOMPARISON__H__

#define rssq run_sequence_sort_comparison

class SortComparison {

	template <typename TObject>
	static ISorter<TObject> **declare_sorts();

	template <typename TObject, template <typename T> typename TArr>
	static void sort_comparison_add_functions(CompareRuntime &sort_comparison, TArr<TObject> **data_arr, ISorter<TObject> **sorters_arr);


	template <typename TObject, template <class T> typename TSeq>
	static void run_seq_sort_comparison(const string &comparison_name, Sequence<TObject> *arr, bool(*lessThan)(const TObject &el1, const TObject &el2)
		= [](const TObject &el1, const TObject &el2) {
		return el1 < el2;
	});

public:

	static void run_sort_comparison();

	static void clear_default_comparison_results();


};

#endif 
