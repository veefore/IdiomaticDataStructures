#include "BinarySearch.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\unit_test.h"
#include <functional>

//BINARY SEARCH TESTING UNIT

#ifndef __UNIT2__H__
#define __UNIT2__H__

namespace sequence_ut {

	void unit2_run() {
		unit_test unit2("Binary Search");

		//All tests are performed on a user-defined type template parameter.
		
		//CREATION
		//Test #1. BinSearch obj is uninitialized.
		//Test #2. BinSearch obj is partly initialized.
		//Test #3. BinSearch obj is default-initialized.
		//Test #4. BinSearch obj is user-initialized throught constructor.
		//Test #5. BinSearch obj is user-initialized through separate set() functions.

		//SEARCH WITH DEFAULT PARTITION
		//Test #1. No such element.
		//Test #2. Such element is the first one.
		//Test #3. Such element is the last one.
		//Test #4. Such element is somewhere near the middle.
		//Test #5. Two such elements and they are adjacent.
		//Test #6. Two such elements and they're placed far from one another.
		//Test #7. All of the elements are such.
		//Test #8. BinSearch obj is not initialized.

		//SEARCH WITH CUSTOM PARTITION
		//Test #1. One of proportion params is 0.
		//Test #2. The proportion params are fine.
		//Test #3. Search with fib partition.


		struct userdeftype {
			double value;

			userdeftype(double value = 0) : value(value){}
		
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

			
		};

		
		
		//CREATION
		unit_test bs_constructor("BinarySearch::BinarySearch()");

		struct g1 {
			static userdeftype get(int index) {
				return userdeftype(-3.5);
			}
		};

		//Test #1. BinSearch obj is uninitialized.
		bs_constructor.add_test([]() {
			BinarySearch<userdeftype> *bs = new BinarySearch<userdeftype>();
			
			bool flag = true;
			if (bs == nullptr)
				return false;
			if (bs->GetSize() != -1)
				flag = false;
			if (flag)
				delete bs;
			return flag;
		});
		
		//Test #2. BinSearch obj is partly initialized.
		bs_constructor.add_test([]() {
			BinarySearch<userdeftype> bs(1, &g1::get, &userdeftype::areEqual);

			bool flag = true;
			if (bs.GetSize() != 1 || !bs.IsInitialized())
				flag = false;
			return flag;
		});

		//Test #3. BinSearch obj is default-initialized.
		bs_constructor.add_test([]() {
			BinarySearch<userdeftype> bs(1, &g1::get);

			bool flag = true;
			if (bs.GetSize() != 1 || !bs.IsInitialized())
				flag = false;
			return flag;
		});

		//Test #4. BinSearch obj is user-initialized through constructor.
		bs_constructor.add_test([]() {
			BinarySearch<userdeftype> bs(1, &g1::get, &userdeftype::areEqual, &userdeftype::lessThan);

			bool flag = true;
			if (bs.GetSize() != 1 || !bs.IsInitialized())
				flag = false;
			return flag;
		});

		//Test #5. BinSearch obj is user-initialized through separate set() functions.
		bs_constructor.add_test([]() {
			BinarySearch<userdeftype> bs;
			bs.SetSize(1);
			bs.SetAreEqual(&userdeftype::areEqual);
			bs.SetLessThan(&userdeftype::lessThan);
			bs.SetGet(&g1::get);

			bool flag = true;
			if (bs.GetSize() != 1 || !bs.IsInitialized())
				flag = false;
			return flag;
		});

		unit2.add_group_test(bs_constructor);


		//SEARCH WITH DEFAULT PARTITION
		unit_test bs_default_search("int Search(const TObject &value)");

		//Test #1. No such element.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(100000) };
			int size = 5;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);

			int index = bs.Search(userdeftype(3));
			return index == -1;
		});

		//Test #2. Such element is the first one.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(100000) };
			int size = 5;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(-11));
			return index == 0;
		});

		//Test #3. Such element is the last one.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(100000) };
			int size = 5;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(100000));
			return index == 4;
		});

		//Test #4. Such element is somewhere near the middle.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(100000) };
			int size = 5;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(137));
			return index == 3;
		});

		//Test #5. Two such elements and they are adjacent.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(137), userdeftype(100000) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(137));
			return (index == 3 || index == 4);
		});

		//Test #6. Two such elements and they're placed far from one another.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(100000), userdeftype(2.3) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(2.3));
			return (index == 1 || index == 5);
		});

		//Test #7. All of the elements are such.
		bs_default_search.add_test([]() {
			userdeftype arr[] = { userdeftype(2.8488), userdeftype(2.8488), userdeftype(2.8488), userdeftype(2.8488), userdeftype(2.8488), userdeftype(2.8488) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);
			int index = bs.Search(userdeftype(2.8488));
			return index != -1;
		});

		//Test #8. BinSearch obj is not initialized.
		bs_default_search.add_test([]() {
			BinarySearch<userdeftype> bs;

			bool flag = false;
			int index;
			try {
				index = bs.Search(userdeftype(2.8488));
			}
			catch (BadExecutionException e) {
				flag = true;
			}
			return flag;
		});

		unit2.add_group_test(bs_default_search);


		//SEARCH WITH CUSTOM PARTITION
		unit_test bs_custom_search("int Search(const TObject &value, unsigned int proportion_el1, unsigned int proportion_el2)");

		//Test #1. One of proportion params is 0.
		bs_custom_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(137), userdeftype(100000) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);

			bool flag = false;
			try {
				int index = bs.Search(userdeftype(137), 0, 17);
			}
			catch (InvalidArgumentException e) {
				flag = true;
			}
			return flag;
		});

		//Test #2. The proportion params are fine.
		bs_custom_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(137), userdeftype(100000) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);

			bool flag = true;
			int index;
			try {
				index = bs.Search(userdeftype(137), 14, 17);
			}
			catch (InvalidArgumentException e) {
				flag = false;
			}
			if (index != 3)
				flag = false;
			
			return flag;
		});

		//Test #3. Search with fib partition.
		bs_custom_search.add_test([]() {
			userdeftype arr[] = { userdeftype(-11), userdeftype(2.3), userdeftype(2.8488), userdeftype(137), userdeftype(137), userdeftype(100000) };
			int size = 6;
			BinarySearch<userdeftype> bs(size, [arr](int index) {
				return arr[index];
			}, &userdeftype::areEqual, &userdeftype::lessThan);

			bool flag = true;
			int index;
			try {
				index = bs.Search(userdeftype(137), 3);
			}
			catch (Exception e) {
				flag = false;
			}
			if (index != 3)
				flag = false;
			
			return flag;
		});

		unit2.add_group_test(bs_custom_search);

		unit2.run();
	}

}
#endif