#include <iostream>      // lambda-access-return.cpp
using namespace std;

double foo(){ return 2.5; }
int d = 1; 

int main(){
  // Global, static and const variables cannot be captured but directly accessed
  [=]() mutable { d = 17; }(); cout << "global d = " << d << endl;
  
  static int m = 1;
  [](){ m = 100; }(); cout << "static m = " << m << endl;
  
  const int l = 200;
  [](){ cout << "const l = " << l << "\n\n"; }();

  auto f = [](int k)-> int { // default return is double. Set to int
    int i = 3; return i*foo()*k;
  }; 
  double range[] = {1.5, 3.5, 5.5};
  for( double v: range ){
    cout << "v = " << v << ": returning double " <<
      [](int k){ int i = 3; return i*foo()*k; }(v);
    cout << "; returning int " << f(v) << endl;
  }
  return 0;  }
