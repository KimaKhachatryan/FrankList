#include "/home/user/Lessons/Cpp/OOAD/FrankList/FrankList.h"
#include <iostream>

int main()
{
	monster::FrankList<int> list2{1,5,1,3,2,9,6};
		list2.print();
		list2.print(1);
		list2.print(0,1);
		list2.print(1,1);
		
}