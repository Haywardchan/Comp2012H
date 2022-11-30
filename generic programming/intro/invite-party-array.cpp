/* File: invite-party-array.cpp */
void invite_to_party(const Person_Array& pa) 
{
    for (int i = 0; i < pa.size(); ++i)
    {
        const Person& p = pa.get_person(i);
        string command = "cat party.txt | mail -s \"Demo\" ";
        command += p.get_email_address();
        system( command.c_str() ); // "system call" to send emails
    }
}
