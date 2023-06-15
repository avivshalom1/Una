#include <iostream>
#include <string>


int Mult(int p[], int a, int b)
{
    int n, mid;
    n = b - a;

    if(n == 0)
    {
        return a;
    }

    if(n == 1)
    {
        if(p[0] == a)
        {
            return b;
        }

        else
        {
            return a;
        }
    }

    mid = n/2;
    
    if(p[mid] == a+mid)
    {
        return Mult(p+mid+1, a+mid+1, b);
    }
    else
    {
        return Mult(p, a, b-1);
    }
}

int main()
{

    int p[] = {5, 5};

    std::cout << Mult(p, 5, 5);

    return 0;
}
