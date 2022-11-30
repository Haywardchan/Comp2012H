typedef int* Int_Iterator; /* File: find-int-iterator.cpp */

Int_Iterator find(Int_Iterator begin, Int_Iterator end, const int& value)
{
    while (begin != end && *begin != value)
        ++begin;

    return begin;
} /* This find function is actually already defined in the STL */
