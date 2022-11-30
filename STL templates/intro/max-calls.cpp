#include <iostream>     /* File: max-calls.cpp */
using namespace std;
#include "date.h"
#include "student.h"

template <typename T>
T my_max(const T& a, const T& b) { return (a > b) ? a : b; }

int main()
{
    int x = 4, y = 8;
    cout << my_max(x, y) << " is a bigger number." << endl;

    string a("cheetah"), b("gorilla");
    cout << my_max(a, b) << " is stronger!" << endl;

    Date date1(120), date2(300); Date r = my_max(date1, date2);
    cout << r.month() << "/" << r.day() << " is a later date.\n";

    Student adam("Adam", "CSE", 3.8), joseph("Joseph", "MAE", 3.8);
    cout << my_max(joseph, adam) << " has a better GPA!" << endl;
}
