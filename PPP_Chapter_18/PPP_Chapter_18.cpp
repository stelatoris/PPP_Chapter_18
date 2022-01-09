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

    Skip_list* search(const string& v);
    Skip_list* search_lvl(Skip_list* p, const string& v);
    Skip_list* insert(Skip_list* n);
    //double size() const { return *sz; }

    // add new entry n after p, above q
    Skip_list* insert_Above(Skip_list* p, Skip_list* q, Skip_list* n);
    //Skip_list* insert_Above(Skip_list* s, Skip_list* p, Skip_list* q, Skip_list* n);

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
    , height{ nullptr }//, sz{ nullptr }
{
    succ = max;
    succ->prev = this;
    succ->min = this;
    start = this;
    //sz = new double{ 0 };
    height = new int{ 0 };
    max->height = height;
    //max->sz = sz; //list size
    t_height = new int{ 0 };
    *t_height = *height;
}

Skip_list* Skip_list::search(const string& v)   
{
    Skip_list* p = start;

    while (p->below) {  //go to lowest level
        p = search_lvl(p, v);   // traverse forward till v is less or equal than value
        p = p->below;  
        
    }
    
    return p;
}

Skip_list* Skip_list::search_lvl(Skip_list* p, const string& v)
{

    if (!p->succ) return p;
    while (p->succ->value <= v) p = p->succ;    // traverse forward till v is less or equal than value
    return p;
}

Skip_list* Skip_list::insert(Skip_list* n)
{
    if (!n) return nullptr;

    Skip_list* s = max->min; //s is start node of list on each level
    Skip_list* p = search(n->value);
    //insert on lowest level
    n->prev = p;
    n->succ = p->succ;    
    n->max = p->max;
    n->min = max->min;  // change to p->min when stable    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    p->succ->prev = n;
    p->succ = n;
    n->start = p->start;

    n->height = p->height;
    //n->sz = p->sz;

    //*n->sz += 1;
    
    Skip_list* q = n;
    int i = -1;
   
    while (coin_flip()) {         // even or odd?
        ++i;
       
        //Skip_list* new_s{ nullptr };
        if (i >= *height) {       // add a new level with -inf(min) and +inf(max)
            *height += 1;            
            Skip_list* new_min = new Skip_list{ n->min->value };
            Skip_list* new_max = new Skip_list{ n->max->value };

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
            
            s = new_min;            
        }
        q = n;
        n = insert_Above(p, q, n);
        p = n->prev;
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

Skip_list* Skip_list::insert_Above(Skip_list* p, Skip_list* q, Skip_list* n)
{
    while (p->prev) p = p->prev;
    p = p->above;  // move back to next level above starting at min(-inf)
    p = search_lvl(p, n->value);

    //get min and max of same level as p
    Skip_list* temp_min = p->max->min;
    Skip_list* temp_max = p->max;

    Skip_list* temp = new Skip_list{ n->value };    //temp is added above n
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



int main()
try
{
    srand(time(NULL));
    Skip_list* list1 = new Skip_list;
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
    while (list1->below) list1 = list1->below;
    while (list1) {
        cout << "Value: "<<list1->value << '\n';
        cout << "height: " << *list1->height << " ,size: " << list1->height << '\n';
        list1 = list1->succ;
    }


    

}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
