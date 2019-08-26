#include "C:\Users\nolme\Repositories\vigilant-potato\unit_test.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\SortedSequence.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ListSequence.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ArraySequence.h"

//SORTED SEQUENCE TESTING UNIT

#ifndef __UNIT1__H__
#define __UNIT1__H__

namespace sequence_ut {

	void unit1_run() {
		
		unit_test ut("SortedSequence");
		
		//SORTED SEQUENCE CONSTRUCTOR TEST GROUP
		unit_test ss_constructor("SortedSequence::constructor()");
		
		//empty listseq
		ss_constructor.add_test([]() {
			Sequence<double> *seq = new ListSequence<double>();
			SortedSequence<double> ss(seq);
			bool flag = true;
			if (seq->getLength() != ss.getLength())
				flag = false;
			
			return flag;
		});

		//empty arrseq
		ss_constructor.add_test([]() {
			Sequence<double> *seq = new ArraySequence<double>();
			SortedSequence<double> ss(seq);
			bool flag = true;
			if (seq->getLength() != ss.getLength())
				flag = false;
			
			return flag;
		});

		//non-empty listseq
		ss_constructor.add_test([]() {
			Sequence<double> *seq = new ListSequence<double>();
			srand((unsigned)time(0));
			vector<double> vec;
			int size = 10000;
			for (int i = 0; i < size; i++) {
				int value = rand();
				vec.push_back(value);
			}
			seq->FillWithData(vec);
			SortedSequence<double> ss(seq);
			bool flag = true;
			for (int i = 0; i < 10 && flag; i++) 
				if (seq->Get(i) != ss.Get(i))
					flag = false;
			if (ss.getLength() != seq->getLength())
				flag = false;
			
			return flag;
		});

		//non-empty arrseq
		ss_constructor.add_test([]() {
			Sequence<double> *seq = new ArraySequence<double>();
			srand((unsigned)time(0));
			vector<double> vec;
			int size = 10000;
			for (int i = 0; i < size; i++) {
				int value = rand();
				vec.push_back(value);
			}
			seq->FillWithData(vec);
			SortedSequence<double> ss(seq);
			bool flag = true;
			for (int i = 0; i < 10 && flag; i++)
				if (seq->Get(i) != ss.Get(i))
					flag = false;
			if (ss.getLength() != seq->getLength())
				flag = false;
			
			return flag;
		});

		ut.add_group_test(ss_constructor);

		
		unit_test ss_add("void Add(const TElement &element);");
		
		//add in the middle
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(2.5);
			if (ss.Get(3) != 2.5 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});
		
		//add in the middle
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(2.5);
			if (ss.Get(3) != 2.5 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});

		//add in the beginning
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(0);
			if (ss.Get(0) != 0 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});

		//add in the beginning
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(0);
			if (ss.Get(0) != 0 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});

		//add in the end
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(11);
			if (ss.Get(length) != 11 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});

		//add in the end
		ss_add.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			seq->Append(3);
			seq->Append(3.3);
			seq->Append(3.9);
			seq->Append(4);
			seq->Append(5);
			if (!seq->isSorted())
				flag = false;
			SortedSequence<double> ss(seq);
			int length = seq->getLength();
			if (ss.getLength() != length)
				flag = false;
			ss.Add(11);
			if (ss.Get(length) != 11 || ss.getLength() != length + 1)
				flag = false;
			return flag;
		});

		ut.add_group_test(ss_add);


		unit_test ss_removefrom("void RemoveFrom(int index);");

		//index is valid
		ss_removefrom.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.RemoveFrom(1);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 2)
				flag = false;
			if (ss.getLength() != 2)
				flag = false;
			return flag;
		});

		//index is valid
		ss_removefrom.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.RemoveFrom(1);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 2)
				flag = false;
			if (ss.getLength() != 2)
				flag = false;
			return flag;
		});

		//index is invalid
		ss_removefrom.add_test([]() {
			bool flag = false;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			try {
				ss.RemoveFrom(7);
			}
			catch (IndexException e) {
				flag = true;
			}
			return flag;
		});

		//index is invalid
		ss_removefrom.add_test([]() {
			bool flag = false;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			try {
				ss.RemoveFrom(7);
			}
			catch (IndexException e) {
				flag = true;
			}
			return flag;
		});

		ut.add_group_test(ss_removefrom);


		unit_test ss_remove("void Remove(const TElement &item);");

		//seq contains such item
		ss_remove.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.Remove(1.7);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 2)
				flag = false;
			if (ss.getLength() != 2)
				flag = false;
			return flag;
		});

		//seq contains such item
		ss_remove.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.Remove(1.7);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 2)
				flag = false;
			if (ss.getLength() != 2)
				flag = false;
			return flag;
		});

		//seq doesn't contain such an item
		ss_remove.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.Remove(3);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 1.7)
				flag = false;
			if (ss.Get(2) != 2)
				flag = false;
			if (ss.getLength() != 3)
				flag = false;
			return flag;
		});

		//seq doesn't contain such an item
		ss_remove.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			ss.Remove(3);
			if (ss.Get(0) != 1)
				flag = false;
			if (ss.Get(1) != 1.7)
				flag = false;
			if (ss.Get(2) != 2)
				flag = false;
			if (ss.getLength() != 3)
				flag = false;
			return flag;
		});

		ut.add_group_test(ss_remove);

		
		unit_test ss_indexof("int IndexOf(const TElement &element);");

		//seq contains such element
		ss_indexof.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			int index = ss.IndexOf(1.7);
			if (index != 1)
				flag = false;
			return flag;
		});

		//seq contains such element
		ss_indexof.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			int index = ss.IndexOf(1.7);
			if (index != 1)
				flag = false;
			return flag;
		});

		//seq doesn't contain such element
		ss_indexof.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ListSequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			int index = ss.IndexOf(7);
			if (index != -1)
				flag = false;
			return flag;
		});

		//seq doesn't contain such element
		ss_indexof.add_test([]() {
			bool flag = true;
			Sequence<double> *seq = new ArraySequence<double>();
			seq->Append(1);
			seq->Append(1.7);
			seq->Append(2);
			SortedSequence<double> ss(seq);
			int index = ss.IndexOf(7);
			if (index != -1)
				flag = false;
			return flag;
		});

		ut.add_group_test(ss_indexof);

		ut.run();
	}

} 

#endif