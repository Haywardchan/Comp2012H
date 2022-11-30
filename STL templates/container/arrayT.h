template <typename T>   /* File: arrayT.h */
class Array
{
  private:
    T* _value;
    int _size;

  public:
    Array<T>(int n = 10);     // Default and conversion constructor
    Array<T>(const Array& a); // Copy constructor
    ~Array<T>();

    int size() const { return _size; }
    void init(const T& k);

    Array& operator=(const Array<T>& a); // Copy assignment operator
    T& operator[](int i) { return _value[i]; } // lvalue 
    const T& operator[](int i) const { return _value[i]; } // rvalue
};
