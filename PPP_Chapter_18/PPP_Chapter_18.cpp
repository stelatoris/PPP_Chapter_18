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

    Skip_list(const string& v,
        Skip_list* p, Skip_list* s,
        Skip_list* a, Skip_list* b,
        Skip_list* min, Skip_list* max,
        Skip_list* start );

    Skip_list();    // initializes empty list with min and max towers only

    // links
    Skip_list* prev;
    Skip_list* succ;
    Skip_list* above;
    Skip_list* below;
    Skip_list* min;
    Skip_list* max;
    Skip_list* start;

    Skip_list* skip_search(const string& v);    
    Skip_list* skip_insert(const string& v);
    int get_height() const { return *height; }

    ~Skip_list()
    { delete max; delete height; delete t_height; }
    
private:
    int* height;    // tower height
    int* t_height;
    const int low_infty = numeric_limits<int>::min();
    const int high_infty = numeric_limits<int>::max();

    bool coin_flip();   //generate even or odd number to expand tower or not
    Skip_list* insert_after(Skip_list* p, const string& v);
    Skip_list* search_lvl(Skip_list* p, const string& v);
    Skip_list* init_new_lvl(Skip_list* p);  //adds new empty level with min and max

    // add new entry n after p, above q
    Skip_list* insert_Above(Skip_list* p, Skip_list* q, const string& v);
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
    max->start = start;
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

    if(!p->below&&!p->above) p = search_lvl(p, v);
    
    return p;
}

Skip_list* Skip_list::search_lvl(Skip_list* p, const string& v)
{
    if (!p->succ) return p;
    while (p->succ->value <= v) p = p->succ;    // traverse forward till v is less than or equal to value
    return p;
}

Skip_list* Skip_list::init_new_lvl(Skip_list* s)
// creates new empty level with min and max to extend entry tower heights 
{
    Skip_list* new_min = new Skip_list{ "1"};    //min possible number?
    Skip_list* new_max = new Skip_list{ "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" };   //max possible number?

    // set links to new_min
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
    new_min->start = new_min;
    start = new_min;
    new_max->start = start;

    s->above = new_min;
    s->max->above = new_max;
    s->start = new_min;
    s->max->start = new_min;

    return new_min;
}

Skip_list* Skip_list::skip_insert(const string& v)
// We skip search till we find p where p->value<=v
// If p->value==v then we overwrite it, otherwise we move one level down and repeat
// till we reach lowest level, then add new entry after lowest p on that level.
// We flip coin, if tail, we end here. If head, we expand min and max towers to house new tower height.
// Then we add new level on entry.
{
    if (v == "") return this;

    Skip_list* s=this; //s is start node of list: uppermost min(-inf)
    while (s->prev)s =s-> prev;
    while (s->above)s =s-> above;
    start = s;  // to make sure start is indeed top most level of min(-inf) tower

    Skip_list* p = skip_search(v);
    if (p->value == v) return p;    // already exists. Skip for now.

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
        p = p->above;
    }

    return q;
}

Skip_list* Skip_list::insert_after(Skip_list* p, const string& v)
{
    if (p==nullptr) return this;    // nothing to insert
    
    Skip_list* n = new Skip_list{ v };
    n->prev = p;
    n->succ = p->succ;
    n->max = p->max;
    n->min = p->max->min; //min->min is nullptr so we use max->min
    p->succ->prev = n;
    p->succ = n;

    n->height = p->height;
    n->start = p->start->start;

    return n;
}

Skip_list* Skip_list::insert_Above(Skip_list* p, Skip_list* q, const string& v)
{
    if (p==nullptr || q==nullptr) return this;  // nothing to insert

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
    *temp->t_height = *temp->below->t_height + 1;
    temp->start = temp_min;

    return temp;
}

bool Skip_list::coin_flip()
//generate random number: return 1 if odd(tails), and 2 if even(heads)
{
    int coin = (rand() % 100) + 1;    // generate random number
    if (coin % 2 == 1) return 0;    // if odd number (tails)
    else return 1;                  // if even number (heads)
}

void print_skip_list(Skip_list* list)
{
    while (list->prev) list = list->prev;
    while (list->below) list = list->below;

    cout << list->value;
    if (list->above) {
        list = list->above;
        cout << "->" << list->value;
    }
    cout << '\n';
    while (list->below) list = list->below; // go back down to base level

    if (list->succ) {        
        while (list->succ) {
            list = list->succ;
            cout << list->value;
            if (list->above) {
                while (list->above) {
                    list = list->above;
                    cout << "->" << list->value;
                }                
            }
            cout << '\n';
            while (list->below) list = list->below;
        }
    } 
    cout << "-End of Skip List-";
}

void fill_list(ifstream& ist, Skip_list* l)
{
    for (string s; ist >> s;) l = l->skip_insert(s);
    if (ist.eof()) return;
}

int main()
try
{
    srand(time(NULL));
    Skip_list* list1 = new Skip_list;

    //list1 = list1->skip_insert("Beta");
    //list1 = list1->skip_insert("Delta");
    //list1 = list1->skip_insert("Alpha");
    //list1 = list1->skip_insert("Charlie");
    //list1 = list1->skip_insert("Zulu");
    //list1 = list1->skip_insert("Foxtrot");
    //list1 = list1->skip_insert("Sierra");
    //list1 = list1->skip_insert("Echo");
    //list1 = list1->skip_insert("Finden");

    string name{ "data_input.txt" };
    ifstream ist{ name };
    if (!ist)error("can't open input file", name);

    fill_list(ist, list1);

    print_skip_list(list1);
    cout << "\nMaximum tower height: "<<list1->get_height()+1 << " levels.";
}

catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
