class Person_Array {     /* File: person-array-container.h */
  public:
    Person_Array(int n) : MAX_SIZE(n), _size(0)
        { array = new Person [MAX_SIZE]; }
    int size() const { return _size; }
    const Person& get_person(int i) const { return array[i]; }
    void add_person(const Person& p) { array[_size++] = p; }

  private:
    const int MAX_SIZE; int _size; // Number of Persons actually stored
    Person* array; // One-time storage pre-allocated by the constructor
};
