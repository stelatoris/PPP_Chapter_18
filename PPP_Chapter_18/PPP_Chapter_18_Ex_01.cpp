// PPP_Chapter_18.cpp
// 
// Exercise solutions from the book:
// ************************************************************************************
// * Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
// ************************************************************************************
//	1. Write a function, char* strdup(const char*), that copies a C - style string
//	into memory it allocates on the free store.Do not use any standard library
//	functions.Do not use subscripting; use the dereference operator * instead.


#include "std_lib_facilities.h"

char* my_strdup(const char* cs)
{
	// find size of cs array
	int n{};
	while (*cs != 0) {
		++cs;
		++n;
	}
	cs -= n;		//go back to [0]

	// copy array
	char* t_cs = new char[n];

	while (*cs) *t_cs++ = *cs++;	//use pointer arethmatic to move to next memory block

	*t_cs = 0;		//add terminating c_style string 0
	cs -= n;		//go back to [0]
	t_cs -= n;		//go back to [0]
	return t_cs;
}

int main()
{
	char mystring[] = { "Hello me!" };

	cout << my_strdup(mystring);
}
