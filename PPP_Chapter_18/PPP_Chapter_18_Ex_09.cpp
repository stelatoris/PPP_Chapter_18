//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//  Chapter 18, exercise 09: write program that tells the order in which static
//  storage, the stack and the free store are laid out. Does stack grow upward
//  or downward? In an array on free store, are elements with higher indices
//  allocated at higher or lower addresses?

#include "std_lib_facilities.h"

// static storage
int static_1 = 0;
int static_2 = 0;
int static_3 = 0;

int main()
try {
    // static storage
    int* p_static_1 = &static_1;
    int* p_static_2 = &static_2;
    int* p_static_3 = &static_3;
    cout << "Static storage:\n"
        << "p_static_1: " << p_static_1 << " | " << int(reinterpret_cast<int*>(p_static_1)) << '\n'
        << "p_static_2: " << p_static_2 << " | " << int(reinterpret_cast<int*>(p_static_2)) << '\n'
        << "p_static_3: " << p_static_3 << " | " << int(reinterpret_cast<int*>(p_static_3)) << '\n';
    cout << "\nStatic storage grows ";
    if (p_static_2 > p_static_1) cout << "upwards\n";
    else cout << "downwards\n";
    cout << "-------------------------------------\n";

    // stack
    int stack_1 = 0;
    int stack_2 = 0;
    int stack_3 = 0;

    int* p_stack_1 = &stack_1;
    int* p_stack_2 = &stack_2;
    int* p_stack_3 = &stack_3;

    cout << "Stack:\n"
        << "p_stack_1: " << p_stack_1 << " | " << int(reinterpret_cast<int*>(p_stack_1)) << '\n'
        << "p_stack_2: " << p_stack_2 << " | " << int(reinterpret_cast<int*>(p_stack_2)) << '\n'
        << "p_stack_3: " << p_stack_3 << " | " << int(reinterpret_cast<int*>(p_stack_3)) << '\n';
    cout << "\nStack grows ";
    if (p_stack_2 > p_stack_1) cout << "upwards\n";
    else cout << "downwards\n";
    cout << "-------------------------------------\n";

    // free store
    int* freestore_1 = new int(0);
    int* freestore_2 = new int(0);
    int* freestore_3 = new int(0);
    cout << "Free store:\n"
        << "freestore_1: " << freestore_1 << " | " << int(reinterpret_cast<int*>(freestore_1)) << '\n'
        << "freestore_2: " << freestore_2 << " | " << int(reinterpret_cast<int*>(freestore_2)) << '\n'
        << "freestore_3: " << freestore_3 << " | " << int(reinterpret_cast<int*>(freestore_3)) << '\n';
    cout << "\nFree store grows ";
    if (freestore_2 > freestore_1) cout << "upwards\n";
    else cout << "downwards\n";
    cout << "-------------------------------------\n";

    // array on free store
    int* free_array = new int[] {1, 2, 3, 4, 5};
    cout << "Array on free store:\n"
        << "free_array[0]: " << free_array[0] << " | " << int(reinterpret_cast<int*>(free_array[0])) << '\n'
        << "free_array[1]: " << free_array[1] << " | " << int(reinterpret_cast<int*>(free_array[1])) << '\n'
        << "free_array[2]: " << free_array[2] << " | " << int(reinterpret_cast<int*>(free_array[2])) << '\n';
    cout << "\nFree store grows ";
    if (free_array[1] > free_array[0]) cout << "upwards\n";
    else cout << "downwards\n";
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
