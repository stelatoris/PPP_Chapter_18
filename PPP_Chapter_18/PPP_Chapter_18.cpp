//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	8. Rewrite all the functions in §18.7 to use the approach of making a backward
//	copy of the string and then comparing; for example, take "home",
//	generate "emoh", and compare those two strings to see that they are
//	different, so home isn’t a palindrome.


#include "std_lib_facilities.h"

string is_palindrome(const string& s)
{
    
    int n = s.length();
    string backwards;
    for (int i = n; i > -1; --i) {
        backwards.push_back(s[i]);
    }
   
    return backwards;
}


bool is_palindrome(const char s[], int n)
{
    int first = 0;
    int last = n - 1;
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;
}

bool is_palindrome(const char* first, const char* last)
{
    while (first < last) {
        if (*first != *last) return false;
        ++first;
        --last;
    }
    return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
    is.width(max);
    is >> buffer;

    return is;
}

int main()
try
{
    string s1{ "hasan" };
    cout<<is_palindrome(s1);
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
}
catch (...) {
    std::cerr << "exception\n";
    return 2;
}
