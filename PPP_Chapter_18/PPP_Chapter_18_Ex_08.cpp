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

bool is_palindrome(const string& s)
{    
    int n = s.length();
    string backwards;
    for (int i = n-1; i > -1; --i) {    //backward copy
        backwards.push_back(s[i]);
    }

    for (int i = 0; i < n; ++i) {    // compare
        if (backwards[i] != s[i]) return false;
    }
   
    return true;
}

bool is_palindrome(const char s[], int n)
{
    char* c_copy = new char[n+1];
    c_copy[n] = 0;
    int c_i{ n-1 };
    // copy backwards
    for (int i = 0; i < n; ++i) {
        c_copy[i] = s[c_i];
        --c_i;
    }

    // compare
    for (int i = 0; i < n; ++i) {
        if (c_copy[i] != s[i]) {
            delete[] c_copy;
            return false;
        }
            
    }
    delete[] c_copy;
    return true;
}

bool is_palindrome(const char* first, const char* last)
{
    int c_size = last - first + 1;
    char* c_copy = new char[c_size+1];
    char* c_copy_ptr = c_copy;
    
    while (last>=first) {
        *c_copy_ptr = *last;
        ++c_copy_ptr;
        --last;
    }
    *c_copy_ptr = 0;
    
    for (int i = 0; i < c_size; ++i) {
        if (c_copy[i] != first[i]) {
            delete[] c_copy;
            return false;
        }
    }
    delete[] c_copy;
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
    
    // 18.7.1 Palindromes using string
    /*
    cout << "Enter a string:\n";
    for (string s; cin >> s; ) {
        cout << s << " is";
        if (!is_palindrome(s)) cout << " not";
        cout << " a palindrome\n";
    }
    */
    
    
    // 18.7.2 Palindromes using arrays
    /*
    constexpr int max = 128;
    cout << "Enter a string:\n";
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n";
    }
    */



    // 18.7.3 Palindromes using pointers
    ///*
    const int max = 128;
    cout << "Enter a string:\n";
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(&s[0], &s[strlen(s)-1])) cout << " not";
        cout << " a palindrome\n";
    }
    //*/

}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
}
catch (...) {
    std::cerr << "exception\n";
    return 2;
}
