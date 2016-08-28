//#include"moondeque.h"
//#include<iostream>
//#include<string>
//#include<deque>
//#include<Windows.h>
//using namespace std;
//#define SIZE 10000000
//void mooncase1()
//{
//	auto start = GetTickCount();
//	moon:: deque<string> col;
//	auto x = col.begin();
//	int count = SIZE;
//	for (int i = 1; i < count; ++i)
//	{
//		col.push_front("hello wolrd");
//		//cout << col.size() << "--" << i << "--" << col._mapsize() << endl;
//	}
//	cout << "moon--" << GetTickCount() - start << "ms	" << col.size() << "	"<< col._mapsize() << endl;
//}
//
//void stdcase1()
//{
//	auto start = GetTickCount();
//	deque<string> col;
//	auto x = col.begin();
//	int count = SIZE;
//	for (int i = 1; i < count; ++i)
//	{
//		col.push_front("hello world");
//		//cout << col.size() << "--" << i << "--" << col._Mapsize() << endl;
//	}
//	cout << "std---"<<GetTickCount() - start <<"ms	"<<col.size()<<"	"<<col._Mapsize()<< endl;
//}
//
//class test {
//private:
//	int count;
//public:
//	test() { cout << "hello world" << endl; }
//	test(const test& other) { cout << "are you ok?" << endl; }
//};
//
//
//int main()
//{
//	deque<test> col1;
//	test a;
//	col1.push_back(a);
//
//
//
//
//
//	getchar();
//	_CrtDumpMemoryLeaks();
//}