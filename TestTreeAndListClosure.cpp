#include <iostream>
#include "TreeClosure.h"

using namespace std;

int main()
{
    auto node = MakeList(6);
    auto l = MakeList(5, MakeList(4, MakeList(3, MakeList(6))));
    cout << ListLen(l) << endl; // prints 4
    print_list(l); // prints 5 4 3 6 
    auto t = MakeTree(8,
             MakeList(Leaf(4), MakeList(Leaf(5), MakeList(MakeTree(3,
                                                          MakeList(Leaf(9), MakeList(Leaf(10))))))));
    print_levels(t);
    /*
    Prints: 
    8
    4 5 3
    9 10
    */
    //deallocate(t);
    return 0;
}

