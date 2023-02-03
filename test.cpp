#include <iostream>
using namespace std;
int main(){
   const int* a=new int;
   *a=100;
   const int &b=*a;
   int*c=a;
   cout<<c; 

}
auto ans = reverseList(head->next);
head->next->next = head;
head->next = NULL;

return ans;