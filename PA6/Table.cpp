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

    return;
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
Field *findField_add(const String &name, Field*fieldHead) {
    for(Field*find_field=fieldHead; find_field!=nullptr; find_field=find_field->next){
        if(find_field->name==name)return find_field;
    }
    return nullptr;
}
Table::Table(ifstream &ifs, const String &name){
    ifs>>numCols;
    ifs>>numRows;
    String fieldname;
    String type;
    TYPE etype;
    int temp_col=numCols;
    int temp_row=numRows;
    primaryKey = nullptr; fieldHead = nullptr; next = nullptr;  //later back
    tableSize = 100;    //later back
    this->name=name;
    for(int i = 0; i<temp_col;i++){
        ifs>>fieldname;
        if(i==temp_col-1){getline(ifs, type, '\n');}
        else getline(ifs, type, ',');
        if(fieldname.substr(0,1)=="*"){
            fieldname=fieldname.substr(1,fieldname.length()-1);
            if(!stoi(type)){etype=INT;}else{etype=STRING;};
            //cout<<i<<fieldname<<etype;
            addField(i, fieldname, etype);
            primaryKey=findField_add(fieldname,fieldHead);
        }else{
            if(!stoi(type)){etype=INT;}else{etype=STRING;};
            addField(i, fieldname, etype);
        }
        // cout << "test " << numCols << " ";
        // cout<<fieldname<< " "<<i <<" ";
        // cout<<etype<<endl;
        // addField(i, fieldname, etype);
        //setPrimaryKey(fieldname);
        // primaryKey = fieldHead;
    }
    for(int j=0; j<temp_row; j++){
        for(int i=0; i< temp_col;i++){
            if(i!=temp_col-1)getline(ifs,(*this)[i][j],',');
            else getline(ifs,(*this)[i][j],'\n');
        }
    }
    numCols/=2;
}

/* Deallocate all of the fields in the Table object. Remember to deallocate the dynamic array. */
Table::~Table(){
    Field* temp = fieldHead;
    while (temp!=NULL){
        delete [] temp->column;
        temp->column=nullptr;
        temp=temp->next;
        delete fieldHead;
        fieldHead=temp;
    }
    fieldHead=nullptr;
    return;
}
bool duplicate(const Field* key, const int numRows){
    for(int i=0; i<numRows; i++){
        for(int j=0; j<numRows;j++){
            if(key->column[i]==key->column[j]&&i!=j)return true;
        }
    }
    return false;
}
Field* columnptr(Field*fieldhead, const int Column){
    Field*temp=fieldhead;
    for(int idx=1; idx < Column; idx++){
        temp=temp->next;
    }
    return temp;
}
bool duplicate(const Field* key, const int numRows, const String Val, const int Column, Field* FieldHead){
    for(int i=0; i<numRows; i++){
        if(columnptr(FieldHead, Column)==key && Val==key->column[i])return true;
    }
    return false;
}
bool empty(const Field* key, const int numRows){
    for(int i=0; i<numRows; i++){
        if(key->column[i]=="")return true;
    }
    if(numRows==0)return true;
    return false;
}
bool empty(const Field* key, const int numRows, const String Val, const int Column, Field* FieldHead){
    for(int i=0; i<numRows; i++){
        if(columnptr(FieldHead, Column)==key && Val=="")return true;
    }
    return false;
}
bool type_mismatch(Field* field_head, const String* record, const int numCols){
    Field* temp= field_head;
    for(int i=0; i< numCols; i++){
        if(temp->type==isInteger(record[i]))return true;
        temp=temp->next;
    }
    return false;
}
bool empty_or_duplicate_addRecord(int numRows, String *record, Field* field_head, const Field* key){
    int k=0;
    for(Field*temp=field_head;temp!=nullptr;temp=temp->next){
        if(key==temp)break;
        k++;
    }
    for(int i = 0; i < numRows; i++){
        if(record[k]==key->column[i])return true; //duplicate
    }
    if(record[k]=="")return true;   //empty
    return false;
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
    if(record==nullptr){
        cout<<"Record is empty.\n";
        return;
    }
    if(index>numRows||index<0){
        cout<<"Table row index is out of bounds.\n";
        return;
    }    
    if(empty_or_duplicate_addRecord(numRows, record, fieldHead, primaryKey)){cout<<"Empty or duplicate primary key.\n";return;}
    if(type_mismatch(fieldHead, record, numCols)){cout<<"Cannot insert non-integer in integer field.\n";return;}
    int count=0;
    if(numRows==tableSize){
        /* Allocate a new dynamic array with 100 more positions and update tableSize.
        Copy all the data from the old column to the new column.
        Deallocate the old column and make the current field point to the new column. */
        for(Field*temp=fieldHead;temp!=nullptr;temp=temp->next){
            String* ns= new String[tableSize+100];
            for(int i =0;i<numRows;i++){
                ns[i]=temp->column[i];
            }
            delete [] temp->column;
            temp->column=ns;
        }
        this->tableSize=tableSize+100;
    }
    if(index!=numRows/* not last row */){
        /* moving the record to next record */
        /* insert record and update numRows */
        for(Field*temp=fieldHead; temp!=nullptr; temp=temp->next){
            for(int num=numRows; num>index; num--){
                temp->column[num]=temp->column[num-1];
            }
            (*this)[count][index]=record[count];
            count++;
        }
        numRows++; 
    }else{
        for(Field*temp=fieldHead; temp!=nullptr; temp=temp->next){
            (*this)[count][numRows]=record[count];
            count++;
        }
        numRows++;  
    }
}

/* Allocate a new Field struct and place it at position index of the linked list.
Dimensions mismatch:
If the target index is greater than numCols or smaller than 0, print Table column index is out of bounds.\n and return.         //good
Name error:
If a field with the given name already exists in the table, print Field with given name already exists in table.\n              //good
and return.
Again, do validation according to the order above.                                                                              //good
Procedure
Allocate a new field. 
Additionally, allocate a String array and make Field::column point to it. Increase numCols.
Place the field at the appropriate position in the linked-list. For instance, if the the target index is 1, 
set the new field's index to be the new second (index 1) column.
If the field is of type INT, initialise all cells to "0", otherwise initialize them to "".
Additionally, if this the first field to be added to the table, set it to be the primary key. */

void Table::addField(int index, const String &name, TYPE type){
    if(index>numCols||index<0){cout<<"Table column index is out of bounds.\n";return;}
    if(findField_add(name, fieldHead)!=nullptr){cout<<"Field with given name already exists in table.\n";return;}

    Field* nf = new Field;
    nf->column = new String[tableSize];
    nf->name=name;
    nf->next=nullptr;
    nf->type=type;
    if(index==0){
        nf->next=this->fieldHead;
        this->fieldHead=nf;
    }else{
        //find prev
        Field* prev_Field=columnptr(fieldHead, index);
        nf->next=prev_Field->next;
        prev_Field->next=nf;
    }
    numCols++;
    if(index==0 && fieldHead==nullptr)setPrimaryKey(name);
    Field* temp = fieldHead;

    int count = 0;
    while(count < index)
    {
        temp = temp->next;
        count++;
    }
    if(type==INT){
        for(int i=0; i<numRows; i++){
            temp->column[i]="0";
        }
    }else
    if(type==STRING){
        for(int i=0; i<numCols; i++){
            temp->column[i]="";
        }
    }
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
    int row_idx=row+1;
    if(row>=numRows||row<0){
        cout<<"Table row index is out of bounds.\n";
        return;
        }
    for(Field* ptr=fieldHead; ptr!=nullptr;ptr=ptr->next){  //ptr.next?
        ptr->column[row]="0";
        while(ptr->column[row_idx]!=NULL){
            ptr->column[row_idx-1]=ptr->column[row_idx];
            row_idx++;
        }
        row_idx=row+1;
    }
    numRows--;
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
bool type_mismatch_modify(int row, int column, const String &newVal, Field* fh){
    Field* field_ptr = columnptr(fh, column);
    if(field_ptr->type==isInteger(newVal))return true;
    return false;
}
void Table::modifyRecord(int row, int column, const String &newVal){
    if(row>=numRows||row<0){cout<<"Table row index is out of bounds.\n";return;}
    if(column>=numCols||column<0){cout<<"Table column index is out of bounds.\n";return;}
    if(empty(this->primaryKey, numRows, newVal, column, fieldHead)||duplicate(this->primaryKey, numRows, newVal, column, fieldHead)){cout<<"Empty or duplicate primary key.\n";return;}
    if(type_mismatch_modify(row, column, newVal, fieldHead)){cout<<"Cannot insert non-integer in integer field.\n";return;}
    Field* field_ptr=columnptr(fieldHead, column);
    field_ptr->column[row]=newVal;
    return;
}
/* Set the field specified by name as the new primary key.
Errors:
If there is no field with the name name in the table, print No such field with provided name exists.\n and return.
If there is such a field, check the column.
If the column has any duplicates, print Cannot set field with duplicate elements as primary key.\n and return.
If the column has any empty data (""), print Cannot set field with empty data as primary key.\n and return. */
void Table::setPrimaryKey(const String &name){
    if(findField(name)==nullptr){return;}
    else{
        if(/* duplicates */duplicate(findField(name),numRows)){cout<<"Cannot set field with duplicate elements as primary key.\n";return;}
        if(/* empty */empty(findField(name),numRows)){cout<<"Cannot set field with empty data as primary key.\n";return;}
        this->primaryKey=findField(name);
    }
    return;
}
/* Move the field specified by target so that it is at position index.
If no field with the given name exists in the table, print No such field with provided name exists.\n and return.
If index is greater than or equal to numCols or less than 0, print Table column index is out of bounds.\n and return.
Again, do validation according to the order above. */
void Table::setColumnIndex(int index, const String &target){
    if(findField(target)==nullptr){return;}
    if(index>=numCols||index<0){cout<<"Table column index is out of bounds.\n";return;}
    //find the target field and its prev field
    Field* target_field=findField(target);
    Field* prev_Field=nullptr;
    for(Field*temp=fieldHead; temp!=nullptr; temp=temp->next){
        if(temp->next==target_field){
            prev_Field=temp;
            break;
        }
    }
    prev_Field->next=prev_Field->next->next;
    if(index==0){
        target_field->next=fieldHead;
        fieldHead=target_field;
    }else{
        Field*index_field=fieldHead;
        for(int idx=1; idx < index; idx++){
            index_field=index_field->next;
        }
        target_field->next=index_field->next;
        index_field->next=target_field;
    }
    return;
}
/* Delete the field specified by name.
If no field with the given name exists in the table, print No such field with provided name exists.\n and return.
If the target field to be deleted is the primary key, print Cannot delete primary key field.\n and return.
Otherwise, deallocate the field and the dynamic array, decrease numCols. */
void Table::deleteField(const String &name){
    if(findField(name)==nullptr){return;}
    if(findField(name)==primaryKey){cout<<"Cannot delete primary key field.\n";return;}
    Field* target=findField(name);
    Field* prev_Field=nullptr;
    for(Field*temp=fieldHead; temp!=nullptr; temp=temp->next){
        if(temp->next==target){
            prev_Field=temp;
            break;
        }
    }
    prev_Field->next=prev_Field->next->next;
    delete [] target->column;
    delete target;
    numCols--;
    return;
}
/* Return a pointer to the field specified by name.
If no field with the given name exists in the table, print No such field with provided name exists.\n 
and return nullptr. */
Field *Table::findField(const String &name) const{
    for(Field*find_field=fieldHead; find_field!=nullptr; find_field=find_field->next){
        if(find_field->name==name)return find_field;
    }
    cout<<"No such field with provided name exists.\n";
    return nullptr;
}
/* Sorts the rows by field in an ascending order. If the field has type INT then ascending order should be numeric. 
Otherwise, the ascending order should be alphabetic.
If field is a null pointer, print Invalid field provided.\n and return.
Otherwise you may assume this field exists in the table and you can start sorting.
For String objects you may use the comparison operators >, <, >=, <= to compare two Strings. 
These operators check for alphabetical orders. For integers, comparisons must be done after converting them to integers. 
This can be achieved by using the stoi() function that returns the numeric value of the number held in the String object. 
You may assume that the field to be sorted will not contain duplicate values. */
void swap_record(Field*fh, int num, int num2, int numCols){
    String temp_record[numCols];
    for(Field*temp=fh; temp!=nullptr; temp=temp->next){
        for(int i=0; i< numCols; i++){
            temp_record[i]=temp->column[num];
            temp->column[num]=temp->column[num2];
            temp->column[num2]=temp_record[i];
        }
    }
}
void Table::sortTable(Field *field){
    if(field==nullptr){cout<<"Invalid field provided.\n";return;}
    if(field->type==INT){
        for(int i = 0; i < numRows-1; i++){
            if(stoi(field->column[i])>stoi(field->column[i+1])){
                swap_record(fieldHead, i, i+1, numCols);
            }
        }
    }else 
    if(field->type==STRING){
        for(int i = 0; i < numRows-1; i++){
            if(field->column[i]>field->column[i+1]){
                swap_record(fieldHead, i, i+1, numCols);
            }
        }
    }
    return;
}
// int main(){
//     ifstream ifs;
//     ifs.open("1.txt");
//     Table a(ifs, "hi");

//     Field* temp = a.getFieldHead();
//     while (temp != nullptr)
//     {
//         if(temp == a.getPrimaryKey())
//             cout<<'*';
//         cout.width(10);
//         cout << left << temp->name << "  ";
//         temp = temp->next;
//     }
//     cout << endl;
//     for(int i = 0; i < 5; i++)
//     {   for(int j = 0; j < 5;j++)
//         {
//             cout.width(10);
//             cout << left << a[j][i] << "  ";
//         }
//         cout << endl;
//     }
// }