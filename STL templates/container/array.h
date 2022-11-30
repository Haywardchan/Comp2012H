template <typename T>   /* File: array.h */
class Array
{
  private:
    T* _value;
    int _size;

  public:
    Array(int n = 10);     // Default and conversion constructor
    Array(const Array& a); // Copy constructor
    ~Array();

    int size() const { return _size; }
    void init(const T& k);

    Array& operator=(const Array& a); // Copy assignment operator
    T& operator[](int i) { return _value[i]; } // lvalue 
    const T& operator[](int i) const { return _value[i]; } // rvalue
};
