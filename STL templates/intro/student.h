class Student           /* File: student.h */
{
    friend ostream& operator<<(ostream& os, const Student& s)
    {
        os << "(" << s.name << " , "
           << s.dept << " , " << s.GPA << ")";
        return os;
    }

  private:
    string name;
    string dept; 
    float GPA;

  public:
    Student(string n, string d, float x)
        : name(n), dept(d), GPA(x) { }

    bool operator>(const Student& s) const { return GPA > s.GPA; }
};
