#include <iostream>     /* File: larger-calls.cpp */
using namespace std;
#include "date.h"
#include "student.h"

template <typename T> inline const T&
    larger(const T& a, const T& b) { return (a < b) ? b : a; }

int main()
{
    int x = 4, y = 8;
    cout << larger(x, y) << " is a bigger number." << endl;

    string a("cheetah"), b("gorilla");
    cout << larger(a, b) << " is stronger!" << endl;

    Date date1(120), date2(300); Date r = larger(date1, date2);
    cout << r.month() << "/" << r.day() << " is a later date.\n";

    Student adam("Adam", "CSE", 3.8), joseph("Joseph", "MAE", 3.8);
    cout << larger(joseph, adam) << " has a better GPA!" << endl;
}
