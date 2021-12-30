// PPP_Chapter_18.cpp
// Array Drill


#include "std_lib_facilities.h"

void print_array(int a[], int n)
{
	for (int i = 0; i < 10; ++i) {
		cout << a[i];
		if (i < 9) cout << ',';
	}
	cout << '\n';
}

// 1.
int ga[10];

//2.
void int_array(int a[], int n) 
{
	//3.a
	int la[10];	
	for (int i = 0; i < 10; ++i) {
		la[i] = a[i];
	}
	cout << "la: ";
	print_array(la, n);

	//3.d/e/f
	int* p = new int[n];	
	for (int i = 0; i < n; ++i) {
		p[i] = a[i];
	}

	cout << "p: ";
	print_array(p, n);

	//3.g
	delete[] p;
}

int main()
{
	const int n{ 10 };
	
	for (int i = 0; i < n; ++i) {
		ga[i] = pow(2, i);
	}	

	//4.a
	int_array(ga, n);

	//4.b
	int aa[n] = { 1 };
	int sum{1};
	for (int i = 1; i < n; ++i) {
		sum *= (i+1);
		aa[i] = sum;
	}

	//print aa
	cout << "aa: ";
	print_array(aa, n);

	//4.c
	int_array(aa, n);
}
