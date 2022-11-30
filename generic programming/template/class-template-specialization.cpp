#include <iostream>     /* File: class-template-specialization.cpp */
#include <cmath>
#include <limits>
using namespace std;

template <typename T>
class Wrapper {
  private:
     T x;
  public:
     Wrapper(T x) : x(x) { cout << "Wrapper(T x) is called\n"; }
     bool equals(T y);
};

template <typename T>
bool Wrapper<T>::equals(T y) { return x == y; }




template <>
class Wrapper <double> {
  private:
     double x;
  public:
     Wrapper(double x) : x(x) { cout << "Wrapper(double x) is called\n"; }
     bool equals(double y);
};

bool Wrapper<double>::equals(double y) { 
  return fabs(x - y) < numeric_limits<double>::epsilon();
}

int main() {
  Wrapper<int> a(10);
  cout << boolalpha << "Compare a and 10: " << a.equals(10) << "\n";
  Wrapper<double> b(10.2);
  cout << "Compare b and 10.2: " << b.equals(10.2) << "\n";
  return 0;
}
