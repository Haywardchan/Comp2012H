#include "Medicine.h"

/* The constructor of the class Medicine. 
Input argument x and y specifies the coordinate where the target Medicine unit locates.
 The coordinate should be assigned to the protected member variable x and y defined in the class MapUnit. */
Medicine::Medicine(int x, int y):Item(x,y){

}
Medicine::~Medicine(){

}
void Medicine::triggered_by(Player &p) {
    if(is_valid()==false)return;
    else {
        p.recover_hp(3);
    }
    this->invalidate();
}
string Medicine::get_item_str() const{
    return SYM_MEDICINE;
}