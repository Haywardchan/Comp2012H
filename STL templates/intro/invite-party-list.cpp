/* File: invite-party-list.cpp */
void invite_to_party(const Person_List& pl)
{
    if (pl.get_first()) // List is not empty
        do {
            const Person& p = pl.get_current();
            string command = "cat party.txt | mail ";
            command += p.get_email_address();
            system( command.c_str() ); // Send invitation email
        } while (pl.get_next()); // While end of list is not reached
}
