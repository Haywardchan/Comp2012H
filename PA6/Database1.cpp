#include <fstream>
#include <iomanip>
#include <iostream>
#include "Database.h"
#include "String.h"
#include "Table.h"

using namespace std;

void Database::printTable(Table *table) const
{
    if (table == nullptr)
    {
        cout << "No such table exists in the database." << endl;
        return;
    }

    for (Field *cur = table->getFieldHead(); cur != nullptr; cur = cur->next)
    {
        cout << setw(15) << left;
        String curPrintName = (cur == table->getPrimaryKey() ? "*" : "") + cur->name + ' ' + (cur->type == INT ? "0" : "1");
        cout << curPrintName;
    }
    cout << endl;
    for (int i = 0; i < table->getNumRows(); ++i)
    {
        for (int j = 0; j < table->getNumCols(); ++j)
        {
            cout << setw(15) << left;
            cout << (*table)[j][i];
        }
        cout << endl;
    }

    return;
}

/* Create a new Database. In this function you can assume 0 <= numTables && numTables < 100.
Set currentTable to nullptr, this->numTables to be numTables, this->name to be name.
Create numTables tables and name them as Table_i where i ranges from 1 to numTables (inclusive). 
The first table in the linked list (pointed by tableHead) should be Table_1, and so on. */
Database::Database(const String &name, int numTables){
    currentTable=nullptr;
    this->numTables=numTables;
    this->name=name;
    if(numTables<1)return;
    Table* tableHead=new Table("Table_1");
    Table* temp=tableHead;
    for(int i = 2; i < numTables+1; i++){
        String Tname="Table_"+i;
        temp->next=new Table(Tname);
        this->name=name;
        temp->next->next=nullptr;
        temp=temp->next;
    }
}
/* Set currentTable to nullptr.
This function may need to call the overloaded table constructor.
You can assume the file always exists and the format is correct.
You can make use of the >> operator or the getline(istream&, String&, char) function to 
read data into a String object from a file. */
//Note: you will need to make use of String::getStr() to create the filestream object because the 
//constructor for the filestream takes character arrays, and not our custom String class, as a parameter.
//check the std::sprintf function
Database::Database(const String &filename){
    currentTable=nullptr;
    return;
}
//The destructor that deallocates all of the Table objects added to the Database.
Database::~Database(){
    Table* temp = tableHead;
    while (temp!=NULL){
        temp=temp->next;
        delete tableHead;
        tableHead=temp;
    }
    return;
}
/* Push the provided table to the end of the Table linked-list.
If table is a null pointer, print Table is a null pointer.\n and return false.
If a table with the same name as table already exists in the database, print Table with 
given name already exists in the database.\n and return false.
Otherwise push the new table to the end of the linked list, increase numTables and return true.
You may use the == operator to compare two String-type objects. */
bool Database::addTable(Table *table){
    if(table==nullptr){
        cout<<"Table is a null pointer.\n";
        return false;
        }
    if(findTable(table->getName())!=nullptr){
        cout<<"Table with given name already exists in the database.\n";
        return false;
    }
    //push to the end
    // for(Table* p = tableHead; p->next!=nullptr; p=p->next){}
    
    return 0;
}
/* Create a new table with name name.
If a table with the provided name exists in the database, print Table with given name already exists in the database.
\n and return.
Otherwise, allocate a new table object, add it to the end of the linked list, and increase numTables. */
void Database::addTable(const String &name){
    return;
}
/* Return a pointer to the table with the name specified by name. Return nullptr
 if no table with the provided name exists in the database. */
Table *Database::findTable(const String &name)const{
    for(Table* find_table=tableHead; find_table!=nullptr; find_table=find_table->next){ 
        if(find_table->getName()==name){
            return find_table;
        }
    }
    return nullptr;
}
/* Print the tables in the database in this format:
The tables currently existing in the database are:
Table_1_Name
Table_2_Name
...
Table_LastOne_Name\n */
void Database::listTables()const{
    return;  
}
/* Delete the table with the given name from the database.
If no table with the given name exists in the database, print No such table exists in the database.\n
Otherwise, deallocate the table, remove it from the linked-list, and decrease numTables. */
void Database::deleteTable(const String &name){
    return;
}
/* Set currentTable to be the table specified by name.
If no table with the given name exists in the database, set currentTable to be 
nullptr and print No such table exists in the database.\n */
void Database::setCurrentTable(const String &name){
    return;
}
/* Save the database, its tables, and their data to a file named filename, 
using the format in the Storing Data section. You may use the << operator to output String objects 
and int values to the output filestream. Remember to prepend an asterisk to the primary key field. 
Remember to use commas as a separation between fields, and \n as a separation between records. 
Finally, remember that 0 represents a field of type int and 1 represents a field of type String.
Note: you will need to make use of String::getStr() to create the filestream object because the constructor 
for the filestream takes character arrays as a parameter. */
void Database::saveDatabase(const String &filename)const{
    return;
}
//bonus
void Database::innerJoin(Table* table1, Table* table2){
    return;
}