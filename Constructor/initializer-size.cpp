#include <iostream>  // initializer-size.cpp
using namespace std;

class A{
public: A( int i = 0 ){cout << "A(" << i << ") created\n";}
};

struct B{
  B(){cout << "B created\n";}
};

struct C{
  const int & j = i;  const int i = 7; 
};

class foo{
private:
  A a;  B b;  A a2;
  const int & j;  
  const int i = 7; // this should be put before a2 statement
public:
  foo(): b(), j{i}, a2{i}, a() { cout << "j is " << j << endl;}
};

int main(){
  foo f;  // check the order of data member construction
  // check size of class and struct
  cout << "\nSize of C = " << sizeof(struct C)<< endl;
  cout << "Size of A = " << sizeof(class A) << "; Size of B = " << sizeof( B )
       << "; Size of f = " << sizeof( f ) << endl;
  return 1;   }
