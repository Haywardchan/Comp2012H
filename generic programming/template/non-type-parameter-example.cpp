#include <iostream>     /* File: non-type-parameter-example.cpp */
using namespace std;
 
template<typename T, unsigned int SIZE>
inline unsigned int check_array_size(T (&arr)[SIZE])  
{
    return SIZE;
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    const int SIZE = check_array_size(arr);
    cout << "Size of array: " << SIZE << endl;
    return 0;
}
