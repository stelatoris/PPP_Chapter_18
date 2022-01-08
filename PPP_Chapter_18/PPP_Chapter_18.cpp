//	PPP_Chapter_18.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//  11. Look up(e.g., on the web) skip list and implement that kind of list.This is
//  not an easy exercise.



#include<time.h>
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
    Skip_list* insert(Skip_list* n);

    // add new entry n after p, above q
    //Skip_list* insert_After_Above(Skip_list* p, Skip_list* q, Skip_list* n);

    Skip_list* prev;
    Skip_list* succ;
    Skip_list* above;
    Skip_list* below;
    Skip_list* min;
    Skip_list* max;
    int h;  // tower height

private:
    bool coin_flip();
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
    prev{ nullptr }, succ{ nullptr },
    above{ nullptr }, below{ nullptr }
{
    succ = max;
    succ->prev = this;
    succ->min = this;
}

Skip_list* Skip_list::search(const string& v)
{
    Skip_list* p;
    if (!prev) p = this;
    else p = min;

    while (p->below) {
        p = p->below;
                          
    }
    while (p->succ->value <= v) p = p->succ;    // traverse forward till v is less or equal than value
    return p;
}

Skip_list* Skip_list::insert(Skip_list* n)
{
    if (!n) return nullptr;

    Skip_list* p = search(n->value);
    //insert on lowest level
    n->prev = p;
    n->succ = p->succ;    
    n->max = p->max;
    n->min = max->min;
    n->h = p->h;
    p->succ->prev = n;
    p->succ = n;

   
    while (coin_flip()) {         // even or odd?
     
    }

    return n;
}

bool Skip_list::coin_flip()
//generate random number: return 1 if odd(tails), and 2 if even(heads)
{    
    int coin = (rand() % 2) + 1;    // generate random number
    if (coin % 2 == 1) return 0;    // if odd number (tails)
    else return 1;                  // if even number (heads)
}


//Skip_list* Skip_list::insert_After_Above(Skip_list* p, Skip_list* q, Skip_list* n)
//// add new entry n after p, above q
//{
//    n->prev = p;
//    p->succ = n;
//
//}



int main()
try
{
    srand(time(NULL));
    /*Skip_list* list1 = new Skip_list;
    list1 = list1->insert(new Skip_list{ "Sierra" });
    list1 = list1->insert(new Skip_list{ "Mike" });
    list1 = list1->insert(new Skip_list{ "Alpha" });
    list1 = list1->insert(new Skip_list{ "Zulu" });
    list1 = list1->insert(new Skip_list{ "Delta" });
    list1 = list1->insert(new Skip_list{ "Beta" });
    list1 = list1->insert(new Skip_list{ "Golf" });
    list1 = list1->insert(new Skip_list{ "Charlie" });
    list1 = list1->search("Beta");
    cout << "Search result is " << list1->value << '\n';
    list1 = list1->insert(new Skip_list{ "Foxtrot" });



    while (list1->prev) list1 = list1->prev;
    while (list1) {
        cout << "Value: "<<list1->value << '\n';
        list1 = list1->succ;
    }*/


    

}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
