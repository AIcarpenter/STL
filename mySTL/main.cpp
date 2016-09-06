#include "moon_binary_serach_tree.h"
#include<iostream>

using namespace std;
int main()
{
	{
		moon::binary_search_tree<int> col;
		col.insert(1);
		col.insert(3);
		col.insert(-2);
		col.insert(10);
		col.insert(-111);
		for (auto& ite = col.begin(); ite != col.end(); ++ite)
			cout << *ite << endl;
		auto x = col.find(-2);
		col.erase(x);
		cout << "-------------" << endl;
		for (auto ite = col.begin(); ite != col.end(); ++ite)
			cout << *ite << endl;
		x = col.find(10);
		col.erase(x);
		cout << "-------------" << endl;
		for (auto ite = col.begin(); ite != col.end(); ++ite)
			cout << *ite << endl;
	}
	_CrtDumpMemoryLeaks();
}