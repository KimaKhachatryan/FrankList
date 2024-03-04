#include "FrankList.h"
#include <iostream>

int main()
{
    monster::FrankList<int> l{5, 9, 4, 2, 1};
    monster::FrankList<int> ll (l);
    ll.print();

    ll.sort(1);
    ll.print();
    

    return 0;
}