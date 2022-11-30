template <typename T> /* File: swap.cpp */
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
