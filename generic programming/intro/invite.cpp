/* File: invite.cpp */
#include <iostream>
using namespace std;
#include "person.h"
#include "person-array-container.h"
#include "invite-party-array.cpp"

int main()
{
    Person_Array pa(10);
    pa.add_person(Person("Brian", "HKUST", "mak@cse.ust.hk"));
    //pa.add_person(Person("COMP2012L1", "HKUST", "comp2012l1@cse.ust.hk"));
    
    invite_to_party(pa) ;
    return 0;
    
}
