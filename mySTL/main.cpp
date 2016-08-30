#include"moonvector.h"
#include<vector>
#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<allocators>
#include"moonheap.h"
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
	priority_queue<int> col;
	col.push(1);
	col.push(12);
	col.push(-11);
	col.push(-1);


	
	cout << endl;
	getchar();
}