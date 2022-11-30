#include <iostream>    /* File: fp-min-max-lambda.cpp */
using namespace std;

int main()
{
    int choice;
    cout << "Choice: (1 for my_max; others for my_min): ";
    cin >> choice;
  
    int (*f)(int, int);
  
    if(choice == 1)
       f = [] (int x, int y) { return (x > y) ? x : y; };
    else
       f = [] (int x, int y) { return (x > y) ? y : x; };

    cout << f(3, 5) << endl;
    return 0;
}