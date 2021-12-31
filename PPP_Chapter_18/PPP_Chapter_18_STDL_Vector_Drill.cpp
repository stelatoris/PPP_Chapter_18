// PPP_Chapter_18.cpp
// Standard library vector Drill


#include "std_lib_facilities.h"

void print_vector(vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size()-1) cout << ',';
	}
	cout << '\n';
}

vector<int>gv(10);

//2
void int_vector(vector<int>& v)
{
	//3.a
	vector<int>lv(v.size());
	//3.b
	for (int i = 0; i < v.size(); ++i) {
		lv[i] = v[i];
	}
	//3.c
	cout << "lv: ";
	print_vector(lv);

	//3.d
	vector<int>lv2{ v };
	//3.e
	cout << "lv2: ";
	print_vector(lv2);
}

void factorial(vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i) {
		v[i] = pow(2, i);
	}
}

int main()
{
	//1
	factorial(gv);

	//4.a
	cout << "gv:- \n";
	int_vector(gv);
	cout << '\n';

	//4.b
	vector<int>vv(10);
	factorial(vv);

	//4.c
	cout << "vv:- \n";
	int_vector(vv);
	cout << '\n';
}
