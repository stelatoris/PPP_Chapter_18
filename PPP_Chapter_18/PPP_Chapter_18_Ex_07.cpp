//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	7. Write versions of the cat_dot()s from the previous exercises to take
//	C - style strings as arguments and return a free - store - allocated C - style string
//	as the result.Do not use standard library functions or types in the implementation.
//	Test these functions with several strings.Be sure to free
//	(using delete) all the memory you allocated from free store(using new).
//	Compare the effort involved in this exercise with the effort involved for
//	exercises 5 and 6.


#include "std_lib_facilities.h"

char* cat_dot(const char* s1, const char* seperator, const char* s2)
{
	if (!s1 || !s2) return nullptr;

	int s1_size{};
	int s2_size{};
	int seperator_size{};

	while (s1[s1_size]) ++s1_size;
	while (s2[s2_size]) ++s2_size;
	while (seperator[seperator_size]) ++seperator_size;

	char* s = new char[s1_size + seperator_size + s2_size];
	int s_count{};

	// add 1st string
	for (int i = 0; i < s1_size;++i) {
		s[i] = s1[i];
		++s_count;
	}
	
	// add seperator string
	for (int ii = 0; ii < seperator_size; ++ii) {
		s[s_count] = seperator[ii];
		s_count++;
	}
	
	// add 2nd string
	for (int j = 0; j < s2_size; ++j) {		
		s[s_count] = s2[j];	
		++s_count;
	}

	s[s_count] = 0;
	return s;
}  

int main()
{
	char my_string1[] = { "Pink" };
	char my_string2[] = { "Floyd" };
	char seperator[] = { " " };

	cout<<cat_dot(my_string1, seperator, my_string2) << '\n';
}
