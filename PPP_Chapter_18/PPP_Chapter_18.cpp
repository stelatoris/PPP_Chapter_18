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
        Skip_list* min, Skip_list* max,
        Skip_list* start );

    Skip_list();    // initializes list with min and max

    Skip_list* skip_search(const string& v);    
    Skip_list* skip_insert(const string& v);

    // add new entry n after p, above q
    Skip_list* insert_Above(Skip_list* p, Skip_list* q, const string& v);

    Skip_list* prev;
    Skip_list* succ;
    Skip_list* above;
    Skip_list* below;
    Skip_list* min;
    Skip_list* max;
    Skip_list* start;
    int* height;    // tower height
    int* t_height;
    
private:
    //double* sz;     // size of list
    bool coin_flip();   //generate even or odd number to expand tower or not
    Skip_list* insert_after(Skip_list* p, const string& v);
    Skip_list* search_lvl(Skip_list* p, const string& v);
    Skip_list* init_new_lvl(Skip_list* p);  //adds new empty level with min and max
};

Skip_list::Skip_list(const string& v,
    Skip_list* p = nullptr, Skip_list* s = nullptr,
    Skip_list* a = nullptr, Skip_list* b = nullptr,
    Skip_list* min = nullptr, Skip_list* max = nullptr,
    Skip_list* start = nullptr)
    : value{ v }, prev{ p }, succ{ s }, above{ a }, below{ b }, t_height{ new int{0} }
{ 
}

Skip_list::Skip_list()
    : value{ 0 }, min{ nullptr },
    max{ new Skip_list{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~"} },
    start{nullptr},
    prev{ nullptr }, succ{ nullptr },
    above{ nullptr }, below{ nullptr }
    , height{ nullptr }
{
    succ = max;
    succ->prev = this;
    succ->min = this;
    start = this;
    height = new int{ 0 };
    max->height = height;
    t_height = new int{ 0 };
    *t_height = *height;
}

Skip_list* Skip_list::skip_search(const string& v)   
//  go to lower level, search. If match found, overwrite, else go down one level and repeat
//  until most bottom level reached. output p so next function can use p to insert new entry
//  on lowest level
{
    Skip_list* p = start;

    while (p->below) {  
        p = p->below;
        p = search_lvl(p, v);   // traverse forward till v is less or equal than value
    }
    
    return p;
}

Skip_list* Skip_list::search_lvl(Skip_list* p, const string& v)
{

    if (!p->succ) return p;
    while (p->succ->value <= v) p = p->succ;    // traverse forward till v is less or equal than value
    return p;
}

Skip_list* Skip_list::init_new_lvl(Skip_list* s)
// creates new empty level with min and max to extend entry tower heights 
{
    
    Skip_list* new_min = new Skip_list{ "1"};    //min possible number?
    Skip_list* new_max = new Skip_list{ "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" };   //max possible number?

    new_min->max = new_max;
    new_min->below = s;
    new_min->succ = new_max;
    *new_min->t_height += 1;     // for testing
    new_min->height = s->height;

    new_max->min = new_min;
    new_max->prev = new_min;
    new_max->below = s->max;
    *new_max->t_height += 1;     // for testing
    new_max->height = s->height;
    start = new_min;
    new_max->start = start;

    s->above = new_min;
    s->max->above = new_max;

    return start;
}

Skip_list* Skip_list::skip_insert(const string& v)
// We skip search till we find p where p->value<=v
// If p->value==v then we overwrite it, otherwise we move one level down and repeat
// till we reach lowest level, then add new entry after lowest p on that level.
// We flip coin, if tail, we end here. If head, we expand min and max towers to house new tower height.
// Then we add new level on entry.
{
    Skip_list* s=this; //s is start node of list: uppermost min(-inf)
    while (s->prev)s =s-> prev;
    while (s->above)s =s-> above;

    Skip_list* p = skip_search(v);
    //insert on lowest level
    Skip_list* q = nullptr;
    q = insert_after(p, v); // insert new value v after p
    
    int i = -1;
   
    while (coin_flip()) {         // even or odd?
        ++i;
       
        if (i >= *height) {       // add a new level with -inf(min) and +inf(max)
            *height += 1;            
            s = init_new_lvl(s);
        }        
        q = insert_Above(p, q, v);
        while (!p->above) p = p->prev;
    }

    return q;
}

Skip_list* Skip_list::insert_after(Skip_list* p, const string& v)
{
    Skip_list* n = new Skip_list{ v };
    n->prev = p;
    n->succ = p->succ;
    n->max = p->max;
    n->min = max->min; //min->min is nullptr so we use max->min
    p->succ->prev = n;
    p->succ = n;
    n->start = p->start;

    n->height = p->height;

    return n;
}

Skip_list* Skip_list::insert_Above(Skip_list* p, Skip_list* q, const string& v)
{
    while (p->prev) p = p->prev;
    p = p->above;  // move back to next level above starting at min(-inf)
    p = search_lvl(p, v);

    //get min and max of same level as p
    Skip_list* temp_min = p->max->min;
    Skip_list* temp_max = p->max;

    Skip_list* temp = new Skip_list{ v };    //temp is added above n
    temp->below = q;
    q->above = temp;
    temp->prev = p;
    temp->succ = p->succ;
    p->succ->prev = temp;
    p->succ = temp;    
    temp->min = temp_min;
    temp->max = temp_max;
    temp->height = p->height;
    //temp->sz = p->sz;
    *temp->t_height = *temp->below->t_height + 1;
    temp->start = temp_min;

    return temp;
}

bool Skip_list::coin_flip()
//generate random number: return 1 if odd(tails), and 2 if even(heads)
{
    int coin = (rand() % 2) + 1;    // generate random number
    if (coin % 2 == 1) return 0;    // if odd number (tails)
    else return 1;                  // if even number (heads)
}

//Skip_list* Skip_list::insert_Above(Skip_list* s, Skip_list* p, Skip_list* q, Skip_list* n)
//// add new entry n after p, above q
//{
//    //while (q->above) q = q->above;  
//    while (!p->above) {
//        if(p->prev) p = p->prev;
//    }
//
//    //if p is less than S height-1
//    if (!p->prev) {     
//        while (p->above) p = p->above;
//    }
//    else p = p->above;
//    
//
//    Skip_list* temp = new Skip_list{ n->value };
//
//    // extend tower q upwards
//    temp->below = q;
//    q->above = temp;
//    temp->prev = p;
//    temp->succ = p->succ;
//    p->succ->prev = temp;
//    p->succ = temp;
//    temp->min = s;
//    temp->max = s->max; // !!!!!!!  takes lvl 0 max and min. fix it please.
//    
//    
//    temp->height = n->height;
//    temp->t_height = n->t_height;
//    *temp->t_height += 1;
//    temp->sz = n->sz;
//    return temp;
//}

void print_skip_list(Skip_list* list)
{
    while (list->prev) list = list->prev;
    while (list->below) list = list->below;

    while (list->succ) {
        while (list->above) {
            cout << list->value << "->";
            list = list->above;
        }
        cout << '\n';
        while (list->below) list = list->below;
        list = list->succ;
    }
}

int main()
try
{
    srand(time(NULL));
    Skip_list* list1 = new Skip_list;
    list1 = list1->skip_insert("Sierra");
    list1 = list1->skip_insert("Foxtrot");
    list1 = list1->skip_insert("Alpha");
    list1 = list1->skip_insert("Zulu");
    list1 = list1->skip_insert("Delta");
    list1 = list1->skip_insert("Beta");
    list1 = list1->skip_insert("Charlie");
    //list1 = list1->skip_search("Beta");
    //cout << "Search result is " << list1->value << '\n';
    list1 = list1->skip_insert("Echo");


    print_skip_list(list1);
    
    
    
    /*while (list1->prev) list1 = list1->prev;
    while (list1->below) list1 = list1->below;
    while (list1) {
        cout << "Value: "<<list1->value << '\n';
        cout << "height: " << *list1->height << " ,size: " << list1->height << '\n';
        list1 = list1->succ;
    }*/


    

}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
