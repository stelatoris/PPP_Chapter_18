//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//  10. Look at the “array solution” to the palindrome problem in §18.7.2.Fix it
//  to deal with long strings by(a) reporting if an input string was too long
//  and (b)allowing an arbitrarily long string.Comment on the complexity
//  of the two versions.
//
//  Had a tough time with understanding the idea behind the the buffer overflowing.
//  Checked out others solutions and studied them.

#pragma warning(disable : 4996)
#include "std_lib_facilities.h"

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

istream& read_word(istream& is, char* buffer, int max)
{
    is.width(max);
    is >> buffer;
    if (strlen(buffer) == max - 1) {
        cout << "Input string exeeded " << max << " characters!\n";
        char c;
        while (is.get(c)) {
            if (c == '\n') break;
        }
    }
    return is;
}

istream& read_long_word(istream& is, char*& buffer) {
    int max = 256;
    char* first_batch = new char[max];
    *first_batch = 0;
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') break;
        if (strlen(first_batch) == max - 1) {
            char* second_batch = new char[max];
            strcpy(second_batch, first_batch);
            delete[] first_batch;
            max += max;
            first_batch = new char[max];
            strcpy(first_batch, second_batch);
            delete[] second_batch;            
        }
        first_batch[strlen(first_batch) + 1] = 0;
        first_batch[strlen(first_batch)] = ch;
    }
    buffer = first_batch;
    return is;
}

int main()
try
{
    //constexpr int max = 128;
    //for (char s[max]; read_word(cin, s, max); ) {
    //    cout << s << " is";
    //    if (!is_palindrome(s, strlen(s))) cout << " not";
    //    cout << " a palindrome\n";
    //}

    for (char* s=0; read_long_word(cin, s); ) {
        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n";
    }
}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
