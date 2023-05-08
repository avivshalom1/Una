/**************************************************
* Developer:      Aviv Shalom              	      *
* Version:        1.0                             *   
* Date:           08.03.23                        *   
* Description:    Testing Zemingo Home Assignment *
***************************************************/

#include "pop_and_push.hpp"

bool CompareInts(int lhs, int rhs)
{
    return lhs < rhs;
}


using namespace ilrd;

int main()
{
    QuickPopDS<int> quickPop;

    quickPop.QuickPopDSPush(1);
    quickPop.QuickPopDSPush(20);
    quickPop.QuickPopDSPush(5);
    quickPop.QuickPopDSPush(30);
    quickPop.QuickPopDSPush(10);

    std::cout << "Now Poping" << std::endl;

   std::cout << quickPop.QuickPopDSPop() << std::endl;
    std::cout << quickPop.QuickPopDSPop() << std::endl;
    std::cout << quickPop.QuickPopDSPop() << std::endl;
    std::cout << quickPop.QuickPopDSPop() << std::endl;
    std::cout << quickPop.QuickPopDSPop() << std::endl;


    return 0;
}
