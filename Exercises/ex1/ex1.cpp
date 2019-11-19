#include <iostream>
#include "ex1.h"
using namespace std;


int main()
{
    Variable x = Variable("X", 6);
    cout << x.calculate() << endl;
    x++;
    return 0;
}