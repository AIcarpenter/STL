#include"moonvector.h"
#include<vector>
#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<allocators>
#include"heap.h"
using namespace std;

class A {
private:
	int a;
public:
	A() {}
	A(int x) :a(x) {}
	~A() {}
	A(const A& other) { cout << "copy-constructor invocated." << endl; }
	A& operator=(const A& other) { cout << "copy-assignment constructor invocated" << endl; return *this; }
};

int main()
{
	int ia[9] = { 5,2,5,-2,4,5,1,23,-9 };
	vector<int> ivec(ia, ia + 9);
	moon::make_heap(ivec.begin(), ivec.end()-1);
	moon::sort_heap(ivec.begin(), ivec.end());
	getchar();


}