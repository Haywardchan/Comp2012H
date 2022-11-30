#include <iostream>     /* File: function-template-specialization.cpp */
#include <cmath>
#include <limits>
using namespace std;

template <typename T> bool equals(T a, T b) {
  cout << "Generic function template is called\n"; return a == b;
}

// Template specialization: A function specialized for float data type
template <> bool equals<float>(float a, float b) {
  cout << "Specialized function template (float type) is called\n";
  return fabs(a - b) < numeric_limits<float>::epsilon();
}

// Template specialization: A function specialized for double data type
template <> bool equals<double>(double a, double b) {
  cout << "Specialized function template (double type) is called\n";
  return fabs(a - b) < numeric_limits<double>::epsilon();
}

int main() {
  int a = 1, b = 1;
  cout << boolalpha << "Comparing a = 1, b = 1: " << equals(a, b) << "\n";

  float c = 1.2, d = 1.2;
  cout << "Comparing c = 1.2, d = 1.2: " << equals(c, d) << "\n";

  double e = 1.222, f = 1.222;
  cout << "Comparing e = 1.222, f = 1.222: " << equals(e, f) << "\n"; 
  
  return 0;
}