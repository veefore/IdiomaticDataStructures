#include "C:\Users\nolme\Repositories\vigilant-potato\unit_test.h"
#include "BTree.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ListSequence.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\ArraySequence.h"

#ifndef __UNIT3__H__
#define __UNIT3__H__

namespace sequence_ut {

	void unit3_run() {

		unit_test ut("BTree");

		//All tests are performed on a user-defined type template parameter

		//CONSTRUCTOR
		//Test #1. No parameters.
		//Test #2. Both parameters.
		//Test #3. No parameters and setting attributes separately.
		//Test #3. Create from empty sequence.
		//Test #4. Create from non-empty sequence.
		//Test #5. Create from sequence with elements of the same value.

		//INSERTION
		//Test #1. Tree is empty.
		//Test #2. Tree isn't empty.
		//Test #3. Tree is default-constructed and isn't initialized.
		//Test #4. Invalid arguments
		//Test #5. Tree is really big.

		//SEARCHING
		//Test #1. Empty tree.
		//Test #2. No such element.
		//Test #3. 1 such element.
		//Test #4. 2 such elements.
		//Test #5. All elements are such.

		//DELETION
		//Test #1. Empty tree.
		//Test #2. No such element.
		//Test #3. 1 such element.
		//Test #4. 2 such elements.
		//Test #5. All elements are such.


		struct userdeftype {
			double value;

			userdeftype(double value = 0) : value(value) {}

			bool operator<(const userdeftype &obj) const {
				return this->value < obj.value;
			}

			bool operator==(const userdeftype &obj) const {
				return this->value == obj.value;
			}

			static bool areEqual(const userdeftype &obj1, const userdeftype &obj2) {
				return obj1.operator==(obj2);
			};

			static bool lessThan(const userdeftype &obj1, const userdeftype &obj2) {
				return obj1.operator<(obj2);
			};

			bool operator>(const userdeftype &obj) const {
				return this->value > obj.value;
			}

			bool operator>=(const userdeftype &obj) const {
				return this->value >= obj.value;
			}
		};

		struct TEl {
			int value;

			TEl(int value = 0) : value(value) {}

			bool operator==(const TEl &obj) const {
				return this->value == obj.value;
			}

			bool operator!=(const TEl &obj) const {
				return this->value != obj.value;
			}
		};

		/*function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
			return new ListSequence<KeyNode<userdeftype, TEl> *>();
		};

		function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
			return new ListSequence<BTreeNode<userdeftype, TEl> *>();
		};

		function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
			return new ArraySequence<KeyNode<userdeftype, TEl> *>();
		};

		function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
			return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
		};
*/


		//CONSTRUCTOR
		//Test #1. No parameters.
		//Test #2. Both parameters.
		//Test #3. No parameters and setting attributes separately.
		//Test #3. Create from empty sequence.
		//Test #4. Create from non-empty sequence.
		//Test #5. Create from sequence with elements of the same value.

		unit_test btree_constructor("BTree::BTree()");

		//Test #1. No parameters.
		btree_constructor.add_test([]() {
			BTree<userdeftype, TEl> btree;
			if (btree.getSize() == 0 && !btree.isReady())
				return true;
			else
				return false;
		});

		//Test #2. Both parameters.
		btree_constructor.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};


			BTree<userdeftype, TEl> btree(keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			if (btree.getSize() == 0 && btree.isReady())
				return true;
			else
				return false;
		});

		//Test #3. Create from empty sequence.
		btree_constructor.add_test([]() {
			ArraySequence<KeyNode<userdeftype, TEl> *> seq;
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};
			BTree<userdeftype, TEl> btree(&seq, keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			if (btree.getSize() == 0 && btree.isReady())
				return true;
			else
				return false;
		});

		//Test #4. Create from non-empty sequence.
		btree_constructor.add_test([]() {
			ArraySequence<KeyNode<userdeftype, TEl> *> seq;
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};
			KeyNode<userdeftype, TEl> *kn = new KeyNode<userdeftype, TEl>(userdeftype(-27.33), TEl(11));

			seq.Append(kn);
			BTree<userdeftype, TEl> btree(&seq, keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);

			bool flag = false;
			if (btree.getSize() == 1 && btree.isReady() && btree.find(userdeftype(-27.33), TEl(0)) == TEl(11))
				flag = true;

			delete kn;
			return flag;
		});

		//Test #5. Create from sequence with elements of the same value.
		btree_constructor.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};

			ArraySequence<KeyNode<userdeftype, TEl> *>seq;

			KeyNode<userdeftype, TEl> **kn_array = new KeyNode<userdeftype, TEl> *[100];
			for (int i = 0; i < 100; i++) {
				kn_array[i] = new KeyNode<userdeftype, TEl>(userdeftype(11.1), TEl(33));
			}
			seq.FillWithData(kn_array, 100);

			BTree<userdeftype, TEl> btree(&seq, keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			bool flag = false;
			if (btree.getSize() == 100 && btree.isReady() && btree.find(userdeftype(11.1), TEl(0)) == TEl(33))
				flag = true;

			delete kn_array;
			return flag;
		});

		ut.add_group_test(btree_constructor);


		//INSERTION
		//Test #1. Tree is empty.
		//Test #2. Tree isn't empty.
		//Test #3. Tree is default-constructed and isn't initialized.
		//Test #4. Tree is really big.

		unit_test btree_insertion("BTree::insert(const TKey &key, const TElement &element)");

		//Test #1. Tree is empty.
		btree_insertion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));
			bool flag = false;
			if (btree.getSize() == 1 && btree.find(userdeftype(1), TEl(0)) == TEl(23))
				flag = true;
			return flag;
		});

		//Test #2. Tree isn't empty.
		btree_insertion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};


			ArraySequence<KeyNode<userdeftype, TEl> *> seq;
			KeyNode<userdeftype, TEl> *kn = new KeyNode<userdeftype, TEl>(userdeftype(-27.33), TEl(11));
			seq.Append(kn);
			BTree<userdeftype, TEl> btree(&seq, keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);

			btree.insert(userdeftype(1), TEl(23));

			bool flag = false;
			if (btree.getSize() == 2 && btree.find(userdeftype(1), TEl(0)) == TEl(23))
				flag = true;
			delete kn;
			return flag;
		});

		//Test #3. Tree is default-constructed and isn't initialized.
		btree_insertion.add_test([]() {
			BTree<userdeftype, TEl> btree;

			bool flag = false;
			try {
				btree.insert(userdeftype(1), TEl(23));
			}
			catch (BadExecutionException e) {
				flag = true;
			}

			return flag;
		});

		//Test #4. Tree is really big.
		btree_insertion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};

			ArraySequence<KeyNode<userdeftype, TEl> *>seq;
			int size = 1000;
			KeyNode<userdeftype, TEl> **kn_array = new KeyNode<userdeftype, TEl> *[100];

			srand((unsigned)time(0));
			for (int i = 0; i < size; i++) {
				kn_array[i] = new KeyNode<userdeftype, TEl>(userdeftype(rand()), TEl(rand()));
			}
			seq.FillWithData(kn_array, size);

			BTree<userdeftype, TEl> btree(&seq, keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			btree.insert(userdeftype(11.3), TEl(-11));

			bool flag = false;
			if (btree.getSize() == size + 1 && btree.isReady() && btree.find(userdeftype(11.3), TEl(0)) == TEl(-11))
				flag = true;

			delete kn_array[100];
			return flag;
		});

		ut.add_group_test(btree_insertion);


		//SEARCHING
		//Test #1. Empty tree.
		//Test #2. No such element.
		//Test #3. 1 such element.
		//Test #4. 2 such elements.
		//Test #5. All elements are such.

		unit_test btree_find("BTree::find(const TKey &key)");

		//Test #1. Empty tree.
		btree_find.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};


			BTree<userdeftype, TEl> btree(keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			bool flag = false;
			try {
				btree.find(userdeftype(11.3), TEl(0)) == TEl(0);
			}
			catch (BadExecutionException e) {
				flag = true;
			}
			return flag;
		});

		//Test #2. No such element.
		btree_find.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));

			return btree.find(userdeftype(0), TEl(0)) == TEl(0);
		});

		//Test #3. 1 such element.
		btree_find.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));
			btree.insert(userdeftype(32.2), TEl(11));
			btree.insert(userdeftype(17.388), TEl(2));

			return btree.find(userdeftype(17.388), TEl(0)) == TEl(2);
		});

		//Test #4. 2 such elements.
		btree_find.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));
			btree.insert(userdeftype(32.2), TEl(11));
			btree.insert(userdeftype(17.388), TEl(2));
			btree.insert(userdeftype(23899), TEl(11));
			btree.insert(userdeftype(3899), TEl(-7));
			btree.insert(userdeftype(32.2), TEl(38));

			TEl result = btree.find(userdeftype(32.2), TEl(0));
			return result == TEl(11) || result == TEl(38);
		});

		//Test #5. All elements are such.
		btree_find.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);

			for (int i = 0; i < 100; i++)
				btree.insert(userdeftype(-777.7), TEl(i + 1));

			TEl result = btree.find(userdeftype(-777.7), TEl(0));
			return result != TEl(0);
		});

		ut.add_group_test(btree_find);


		//DELETION
		//Test #1. Empty tree.
		//Test #2. No such element.
		//Test #3. 1 such element.
		//Test #4. 2 such elements.
		//Test #5. All elements are such.

		unit_test btree_deletion("BTree::remove()");

		//Test #1. Empty tree.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};


			BTree<userdeftype, TEl> btree(keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			bool flag = false;
			try {
				btree.remove(userdeftype(11));
			} 
			catch (BadExecutionException e) {
				flag = true;
			}
			return flag && btree.getSize() == 0;
		});

		//Test #2. No such element.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));

			btree.remove(userdeftype(-723.22));
			return btree.find(userdeftype(1), TEl(0)) == TEl(23);
		});

		//Test #3. 1 such element.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));
			btree.insert(userdeftype(32.2), TEl(11));
			btree.insert(userdeftype(17.388), TEl(2));

			btree.remove(userdeftype(32.2));
			return btree.find(userdeftype(32.2), TEl(0)) == TEl(0) && btree.getSize() == 2;
		});

		//Test #4. 2 such elements.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);
			btree.insert(userdeftype(1), TEl(23));
			btree.insert(userdeftype(32.2), TEl(11));
			btree.insert(userdeftype(17.388), TEl(2));
			btree.insert(userdeftype(23899), TEl(11));
			btree.insert(userdeftype(3899), TEl(-7));
			btree.insert(userdeftype(32.2), TEl(38));

			btree.remove(userdeftype(32.2));
			return btree.getSize() == 5;
		});

		//Test #5. All elements are such.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeListSeqConstructor = []() {
				return new ListSequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeListSeqConstructor = []() {
				return new ListSequence<BTreeNode<userdeftype, TEl> *>();
			};

			BTree<userdeftype, TEl> btree(keyNodeListSeqConstructor, BTreeNodeListSeqConstructor);

			for (int i = 0; i < 100; i++)
				btree.insert(userdeftype(-777.7), TEl(i + 1));

			btree.remove(userdeftype(-777.7));
			return btree.getSize() == 99;
		});

		/*
		//Test #6. Random elements, at least one is such.
		btree_deletion.add_test([]() {
			function<Sequence<KeyNode<userdeftype, TEl> *> *()> keyNodeArrSeqConstructor = []() {
				return new ArraySequence<KeyNode<userdeftype, TEl> *>();
			};

			function<Sequence<BTreeNode<userdeftype, TEl, 2> *> *()> BTreeNodeArrSeqConstructor = []() {
				return new ArraySequence<BTreeNode<userdeftype, TEl> *>();
			};

			ArraySequence<KeyNode<userdeftype, TEl> *>seq;
			int size = 1000;
			KeyNode<userdeftype, TEl> **kn_array = new KeyNode<userdeftype, TEl> *[100];

			srand((unsigned)time(0));
			for (int i = 0; i < size; i++) {
				kn_array[i] = new KeyNode<userdeftype, TEl>(userdeftype(rand()), TEl(rand()));
			}
			seq.FillWithData(kn_array, size);

			BTree<userdeftype, TEl> btree(&seq, keyNodeArrSeqConstructor, BTreeNodeArrSeqConstructor);
			btree.insert(userdeftype(11.3), TEl(-11));
			btree.remove(userdeftype(11.3));

			bool flag = false;
			if (btree.getSize() == size && btree.isReady() && btree.find(userdeftype(11.3), TEl(0)) == TEl(0))
				flag = true;

			delete kn_array[100];
			return flag;
		}); */

		ut.add_group_test(btree_deletion);

		ut.run();
	}

}

#endif
