#include "Item.h"


//write your codes here
Item::Item(int x, int y):MapUnit(x,y){
}
Item::~Item(){

}
/* Override the pure virtual function virtual UnitType get_unit_type() const = 0 
declared in the class MapUnit. 
This function should always return the enum value UnitType::ITEM defined in MapUnit.h. */
UnitType Item::get_unit_type() const {
    return UnitType::ITEM;
}
bool Item::is_blocked() const {
    return false;
}
/* An Item unit will become invalid when attacked by the player.
 You should call the function void invalidate() defined in the class MapUnit to 
 mark the item as invalid, and return 0. */
 int Item::attacked_by(int atk){
    invalidate();
    return 0;
}
/* Called by the game UI to get the display string of the unit on the game map.
If the Item unit is invalid, it should return SYM_EMPTY defined in MapUnit.h.
If the item unit is valid, then:
If it is not discovered, it should return SYM_ITEM defined in MapUnit.h
If it is already discovered, it should return by calling the virtual function 
virtual string get_item_str() const = 0 to get the special display string from its derived classes. */
string Item::get_display_str() const {
    if(is_valid()==false){
        return SYM_EMPTY;
    }else{
        if(!this->is_discovered()){
            return SYM_ITEM;
        }else{
             return this->get_item_str();
        }
    }
}