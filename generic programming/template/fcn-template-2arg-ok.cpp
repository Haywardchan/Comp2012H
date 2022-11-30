#include <iostream>     /* File: fcn-template-2arg-ok.cpp */
using namespace std;
    
template <typename T1, typename T2>
void print_max(const T1& a, const T2& b)
{
    if (a > b)
        cout << a << endl;
    else
        cout << b << endl;
}

int main() { print_max(4, 5.5); print_max(5.5, 4); }
