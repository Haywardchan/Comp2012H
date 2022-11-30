class Person { /* File: person-and-container.h */
  public:
  Person(string n, string a, string e)
      : name(n), address(a), email_address(e) { }
    string get_email_address( ) const;
    string get_name( ) const;
    string get_address( ) const;
  private:
    string name; string address; string email_address;
};
class Person_Container { /* File: person-cont-array.h */
  public:
    Person_Container(int n) : MAX_SIZE(n), size(0)
        { array = new Person [MAX_SIZE]; }
    int size( ) const { return size; }
    void add_person(const Person& pers);
    const Person& get_person(int i) const;
    void delete_person(int i);
  private:
    const int MAX_SIZE;
    Person* array; // One-time pre-allocated storage
    int size; // Number of Persons actually stored
};
