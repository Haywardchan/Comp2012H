template <typename T>   /* File: larger-template.cpp */
inline const T& larger(const T& a, const T& b)
{
    return (a > b) ? a : b;
}
