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
   QuickPop<int> quickPop;

    quickPop.Push(1);
    quickPop.Push(20);
    quickPop.Push(5);
    quickPop.Push(30);
    quickPop.Push(10);

    std::cout << "Now Poping" << std::endl;

    std::cout << quickPop.Pop() << std::endl;
    std::cout << quickPop.Pop() << std::endl;
    std::cout << quickPop.Pop() << std::endl;
    std::cout << quickPop.Pop() << std::endl;
    std::cout << quickPop.Pop() << std::endl;


   QuickPush<int> quickPush;

    quickPush.Push(1);
    quickPush.Push(20);
    quickPush.Push(5);
    quickPush.Push(10);
    quickPush.Push(30);

    std::cout << "Now Poping" << std::endl;

    std::cout << quickPush.Pop() << std::endl;
    std::cout << quickPush.Pop() << std::endl;
    std::cout << quickPush.Pop() << std::endl;
    std::cout << quickPush.Pop() << std::endl;
    std::cout << quickPush.Pop() << std::endl;

    return 0;
}
