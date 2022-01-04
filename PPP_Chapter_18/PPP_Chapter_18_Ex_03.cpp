//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	3. Write a function, int strcmp(const char* s1, const char* s2), that compares
//	C - style strings.Let it return a negative number if s1 is lexicographically
//	before s2, zero if s1 equals s2, and a positive number if s1 is lexicographically
//	after s2.Do not use any standard library functions.Do not use
//	subscripting; use the dereference operator * instead.


#include "std_lib_facilities.h"

int strcmp(const char* s1, const char* s2)
{
	if (!s1 || !s2) error("C-style string argument is nullptr!");
	if(*s1==0||*s2==0) error("C-style string argument is empty!");
	
	int ns1{};
	int ns2{};

	while (*s1 != 0) {	// find size of s1
		++ns1;
		++s1;
	}

	while (*s2 != 0) {	// find size of s2
		++ns2;
		++s2;
	}

	s1 -= ns1;			// go back to s1[0]
	s2 -= ns2;			// go back to s2[0]

	while (*s1 == *s2) {
		++s1;
		++s2;
		if (*s1 == 0 || *s2 == 0) break;
	}
	if (*s1 == *s2) return 0;
	else if (*s1 < *s2) return -1;
	else return 1;	
}


int main()
try
{
	char my_string1[] = { "aa" };
	char my_string2[] = { "aaa" };

	cout << strcmp(my_string1, my_string2);
}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
	return 1;
}
catch (...) {
	std::cerr << "exception\n";
	return 2;
}