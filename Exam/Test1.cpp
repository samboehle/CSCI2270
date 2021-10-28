#include <iostream>
using namespace std;
int trit(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else
    {
        int x = 0;
        int y = 1;
        int z;

        for(int i = 1; i <= n-1; i++)
        {
            z = x + y;
            x = y;
            y = z;
        }
        return y;
    }
}

int main()
{
    cout << trit(4) << endl;
}