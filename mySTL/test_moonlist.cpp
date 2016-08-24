#include"moonlist.h"
#include<list>
#include<algorithm>
#include<iostream>
#include<string>
using namespace std;



int main()
{
	moon::list<string> container;
	container.push_back("hello world");
	container.push_back("i am robot");
	container.push_back("hello kitty");
	sort(container.begin(), container.end());
	//cout << *x << endl;
}