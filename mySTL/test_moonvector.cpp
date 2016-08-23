#include"moonvector.h"
#include"C:\Users\moon\Desktop\cghSTL\cghSTL\cghVector.h"
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class myself {
private:
	string a;
public:
	string b;
	myself() : a("hello"), b("world") {}
	
};
int main()
{
	moon::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.insert(vec.begin()+1, 3);
	sort(vec.begin(), vec.end());
	vec.erase(vec.begin()); cout << vec.size() << endl;
}