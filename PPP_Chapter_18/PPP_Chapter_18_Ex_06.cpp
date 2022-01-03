//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	6. Modify cat_dot() from the previous exercise to take a string to be used as
//	the separator(rather than dot) as its third argument.


#include "std_lib_facilities.h"

string cat_dot(const string& s1, const string& seperator, const string& s2)
{
	return s1 + seperator + s2;
}

int main()
{
	std::string s1{ "Neil" };
	std::string s2{ "Young" };
	std::cout << cat_dot(s1,".",s2) << '\n';
}
