class Person {          /* File: person.h */
  public:
    Person() { }
    Person(string n, string a, string e)
        : name(n), address(a), email_address(e) { }
    string get_name() const { return name; }
    string get_address() const { return address; }
    string get_email_address() const { return email_address; }

  private:
    string name; string address; string email_address;
};
