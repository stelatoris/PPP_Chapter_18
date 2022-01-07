//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//  11. Look up(e.g., on the web) skip list and implement that kind of list.This is
//  not an easy exercise.

#include "std_lib_facilities.h"

class Skip_list {
public:
    string value;

    // with value
    Skip_list(const string& v,
        Skip_list* p, Skip_list* s,
        Skip_list* a, Skip_list* b,
        Skip_list* min, Skip_list* max);

    Skip_list();    // initializes list with min and max

    Skip_list* search(const string& v);

    Skip_list* prev;
    Skip_list* succ;
    Skip_list* above;
    Skip_list* below;
    Skip_list* min;
    Skip_list* max;
};

Skip_list::Skip_list(const string& v,
    Skip_list* p = nullptr, Skip_list* s = nullptr,
    Skip_list* a = nullptr, Skip_list* b = nullptr,
    Skip_list* min = nullptr, Skip_list* max = nullptr)
    : value{ v }, prev{ p }, succ{ s }, above{ a }, below{ b } 
{       
}

Skip_list::Skip_list()
    : value{ 0 }, min{ nullptr },
    max{ new Skip_list{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~"} },
    prev{ nullptr }, succ{ max },
    above{ nullptr }, below{ nullptr }
{
}

Skip_list* Skip_list::search(const string& v)
{
    Skip_list* p = min;
    while (p->below) {
        p = p->below;
        while (v >= succ->value) p =p->succ;                  
    }
    return p;
}

int main()
try
{
    Skip_list* list1 = new Skip_list;

    cout << "min value: " << list1->value << '\n';
    cout << "max value: " << list1->max->value << '\n';

}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
