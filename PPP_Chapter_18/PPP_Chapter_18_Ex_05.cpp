//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	5. Write a function, string cat_dot(const string& s1, const string& s2),
//	that concatenates two strings with a dot in between.For example, cat_
//	dot("Niels", "Bohr") will return a string containing Niels.Bohr.


#include "std_lib_facilities.h"

string cat_dot(const string& s1, const string& s2)
{
	return s1 + '.' + s2;
}

int main()
{
	std::string s1{ "Neil" };
	std::string s2{ "Young" };
	std::cout << cat_dot(s1,s2) << '\n';
}
