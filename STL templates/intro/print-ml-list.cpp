/* File: print-ml-list.cpp */
void print_mailing_labels(const Person_List& pl)
{
    if (pl.get_first()) // List is not empty
        do {
            const Person& p = pl.get_current();
            cout << p.get_name() << endl;
            cout << p.get_address() << endl;
        } while (pl.get_next()); // While end of list is not reached
}
