#include <fstream>
#include "Table.h"
#include "String.h"

using namespace std;

bool isInteger(const String &test)
{
    if (!test.length())
        return false;

    if (test[0] != '-' && !isdigit(test[0]))
        return false;

    for (int i = 1; i < test.length(); ++i)
    {
        if (!isdigit(test[i]))
            return false;
    }
    return true;
}

String *Table::operator[](int index) const
{

    if (index >= numCols || index < 0)
    {
        cout << "Table column index is out of bounds." << endl;
        return nullptr;
    }

    Field *cur = fieldHead;
    for (int count = 0; count < index; cur = cur->next, ++count)
        ;
    return cur->column;
}
/* The constructor. Create a new Table.
Initilaise pointers to nullptr.
Initialise numRows and numCols to 0, and tableSize to 100.
Set table name as provided. */
Table::Table(const String &name){
    this->name=name;
    this->next=nullptr;

    this->fieldHead=nullptr;
    this->primaryKey=nullptr;

    this->numCols=0;
    this->numRows=0;
    this->tableSize=100;
}
/* Overloaded Table constructor that takes in an already initialised input filstream and name. This function is 
related to Database::Database(const String &filename).
Set table name as provided.
Initilaise pointers to nullptr.
Read numCols, numRows, field names, and records, as described in the format specified the in the Storing Data section.
Set tableSize to 100, in this function you can assume that number of rows will be less than 100.
Remember that the primary key field has been prepended with an asterisk and every field name is followed by a space
 and a number indicating its type. The separator between field names and the individual columns is a comma and a space.
  You may find it more useful to use getline(istream&, String&, char) here 
because the third parameter describes a delimiter and second paramter is populated with data until that delimiter. */
Table::Table(ifstream &ifs, const String &name){

}
/* Deallocate all of the fields in the Table object. Remember to deallocate the dynamic array. */
Table::~Table(){

}
/* Adds a record to the provided row index of the table, 
record is an array containing the values of every field (same order as the fields themselves).
Null pointer:
If record is a null pointer, print Record is empty.\n and return.
Dimensions mismatch:
If the target index is greater than the number of rows in the table or smaller than 0, 
print Table row index is out of bounds.\n and return.
Primary key error:
If primary key stored in record is empty ("") or is the same as another record, 
print Empty or duplicate primary key.\n and return.
Type mismatch:
If a field has type INT but the corresponding value in record is not an integer, 
print Cannot insert non-integer in integer field.\n and return.
Do validation according to the order above. For example, if there are both dimension mismatch and primary key error, 
you print the message of dimension mismatch and return.
Procedure:
If the new record will not be the last row, do some moving to make space for the new record. 
The relative order of those original records should remain the same.
Insert the data from the record and increase numRows.
If numRows is equal to tableSize then:
Allocate a new dynamic array with 100 more positions and update tableSize.
Copy all the data from the old column to the new column.
Deallocate the old column and make the current field point to the new column.
You may use the == operator to compare two String-type objects. 
Additionally, you may use the provided isInteger(const String&) 
function to check whether a particular String object is a number or not. */
void Table::addRecord(int index, String *record){
    return;
}
/* Allocate a new Field struct and place it at position index of the linked list.
Dimensions mismatch:
If the target index is greater than numCols or smaller than 0, print Table column index is out of bounds.\n and return.
Name error:
If a field with the given name already exists in the table, print Field with given name already exists in table.\n 
and return.
Again, do validation according to the order above.
Procedure
Allocate a new field. Additionally, allocate a String array and make Field::column point to it. Increase numCols.
Place the field at the appropriate position in the linked-list. For instance, if the the target index is 1, 
set the new field's index to be the new second (index 1) column.
If the field is of type INT, initialise all cells to "0", otherwise initialize them to "".
Additionally, if this the first field to be added to the table, set it to be the primary key. */
void Table::addField(int index, const String &name, TYPE type){
    return;
}
/* Delete a record from the table.
If row is greater than or equal to the number of rows in the table or smaller than 0,
 print Table row index is out of bounds.\n and return.
Otherwise, delete the row indicated by row. This is done by remove the corresponding value in every field. 
If the deleted row is not the last row, do some moving to fill the blank. 
The relative order of the other records should remain the same.
Decrease numRows. */
void Table::deleteRecord(int row){
    return;
}
/* Modify the cell specified by row and row to hold newVal.
Dimensions mismatch:
If row is greater than or equal to numRows or less than 0, print Table row index is out of bounds.\n and return.
If column is greater than or equal to numCols or less than 0, print Table column index is out of bounds.\n and return.
Primary key error:
If this modification is going to trigger a primary key conflict or if the primary key is going to be empty (""),
 print Empty or duplicate primary key.\n and return.
Type mismatch:
If strVal is a string but the column that it corresponds to is of type INT, print Cannot insert non-integer in 
integer field.\n and return.
Again, do validation according to the order above.
Again, you may use the provided isInteger(const String&) function to check whether a particular String object 
is a number or not. */
void Table::modifyRecord(int row, int column, const String &newVal){
    return;
}
/* Set the field specified by name as the new primary key.
Errors:
If there is no field with the name name in the table, print No such field with provided name exists.\n and return.
If there is such a field, check the column.
If the column has any duplicates, print Cannot set field with duplicate elements as primary key.\n and return.
If the column has any empty data (""), print Cannot set field with empty data as primary key.\n and return. */
void Table::setPrimaryKey(const String &name){
    return;
}
/* Move the field specified by target so that it is at position index.
If no field with the given name exists in the table, print No such field with provided name exists.\n and return.
If index is greater than or equal to numCols or less than 0, print Table column index is out of bounds.\n and return.
Again, do validation according to the order above. */
void Table::setColumnIndex(int index, const String &target){
    return;
}
/* Delete the field specified by name.
If no field with the given name exists in the table, print No such field with provided name exists.\n and return.
If the target field to be deleted is the primary key, print Cannot delete primary key field.\n and return.
Otherwise, deallocate the field and the dynamic array, decrease numCols. */
void Table::deleteField(const String &name){
    return;
}
/* Return a pointer to the field specified by name.
If no field with the given name exists in the table, print No such field with provided name exists.\n 
and return nullptr. */
Field *Table::findField(const String &name) const{
    Field* i;
    return i;
}
/* Sorts the rows by field in an ascending order. If the field has type INT then ascending order should be numeric. 
Otherwise, the ascending order should be alphabetic.
If field is a null pointer, print Invalid field provided.\n and return.
Otherwise you may assume this field exists in the table and you can start sorting.
For String objects you may use the comparison operators >, <, >=, <= to compare two Strings. 
These operators check for alphabetical orders. For integers, comparisons must be done after converting them to integers. 
This can be achieved by using the stoi() function that returns the numeric value of the number held in the String object. 
You may assume that the field to be sorted will not contain duplicate values. */
void Table::sortTable(Field *field){
    return;
}