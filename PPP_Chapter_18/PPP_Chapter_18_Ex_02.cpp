// PPP_Chapter_18.cpp
// 
// Exercise solutions from the book:
// ************************************************************************************
// * Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
// ************************************************************************************
//	2. Write a function, char* findx(const char* s, const char* x), that finds the
//	first occurrence of the C - style string x in s.Do not use any standard library
//	functions.Do not use subscripting; use the dereference operator * instead.


#include "std_lib_facilities.h"

const char* findx(const char* s, const char* x)
{
	//find x in s
	if (!s || !x) return nullptr;

	int si{ 0 };	// s array size counter
	int xi{ 0 };	// x array size counter
	for (int i{}; *s!=0; ++i) {
		if (*s == *x) {
			while (*x) {
				if (*s != *x) break;
				++s;
				++x;
				++si;
				++xi;
			}

			if (*x == '\0') {
				s -= xi;
				return s;
			}				
		}
		++s;
		++si;
	}

	return nullptr;
}

int main()
{
	char my_string_s[] = { "C++ is hard to understand, but fun to learn." };
	char my_string_x[] = { "hard to understand, but fun to learn." };
	
	cout << findx(my_string_s, my_string_x) << '\n';
}
