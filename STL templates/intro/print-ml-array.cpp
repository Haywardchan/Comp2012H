/* File: print-ml-array.cpp */
void print_mailing_labels(const Person_Array& pa) 
{
    for (int i = 0; i < pa.size(); ++i)
    {
        const Person& p = pa.get_person(i);
        cout << p.get_name() << endl;
        cout << p.get_address() << endl;
        // ...
    }
}
