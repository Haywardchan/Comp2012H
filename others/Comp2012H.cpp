// #include <iostream>
// using namespace std;
// enum COLOR { BLACK, WHITE, RED, ORANGE, YELLOW };
// enum PRIMARY_COLOR { RED, GREEN, BLUE };
// int main() {
// cout << WHITE << ", " << RED << ", " << BLACK << endl;
// }

// #include <iostream>
// using namespace std;
// int main() {
// int* const* const p = new int* const(new int);
// **p = 10;
// }

int*& func() {
int* p = new int;
return p;
}
int main() {
int*& q = func();
delete q;
}


// #include <iostream>
// using namespace std;
// class A {
// public:
// A() { cout << "A"; }
// A(const A& a) { cout << "copyA"; }
// };
// class B {
// public:
// B() { cout << "B"; }
// B(const B& b) { cout << "copyB"; }
// };
// class C {
// A a;
// B b;
// public:
// C() { cout << "C"; }
// C(const C& c) = default;
// };
// int main() {
// C cObj1;
// C cObj2(cObj1);
// }

// #include <iostream>
// using namespace std;
// class A {
// public:
// A() { cout << "Default ctor"; }
// };
// int main() {
// A obj(A());
// }

// #include <iostream>
// using namespace std;
// template <typename T, int N>
// void func(T(&arr)[N]) {
// cout << "General";
// }
// template <typename T, int N>
// void func(int(&arr)[5]) {
// cout << "Specialized";
// }
// int main() {
// int arr[5];
// func(arr);
// }
