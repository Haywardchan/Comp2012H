#include <iostream>      // lambda-construct.cpp
using namespace std;

struct bar{
  int i = 13;
  bar(){ cout << "bar constructor\n"; }
  bar(const bar& b){ i = b.i; cout << "bar copy constructor\n"; }
};

int main(){
  int a = 1, b = 2;
  bar c;  // bar constructor is called

  //  auto g = [a,c]() mutable {  // bar's copy constructor is called
  //    cout << ++a << " " << ++c.i << endl; }; 
  auto g = [=]() mutable { // bar's copy constructor is called
    cout << "lambda g: " << a << "(a); " << ++b << "(++b); "
    << ++c.i << "(++c.i) \n\n" ;
  }; 

  a = 10; g();
  cout << "c.i after calling g = " << c.i << "\n\n";

  // cout << [a](int x) {return a+= x; }(20) << endl; // no, as a is not mutable
  cout << "b += x in lambda, with x = 20: " <<
    [b](int x) mutable {return b += x; }(20) << endl;
  cout << "a and b in main body: " << a << " " << b << "\n\n";
  return 0; }
