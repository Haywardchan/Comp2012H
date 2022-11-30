#include "EmptyLand.h"

//write your codes here
/* The constructor of the class EmptyLand. Input argument x and y 
specifies the coordinate where the target EmptyLand unit locates. 
The coordinate should be assigned to the protected member variable x and y 
defined in the class MapUnit. */
EmptyLand::EmptyLand(int x, int y):Terrain(x,y){

}

EmptyLand::~EmptyLand(){

}
/* Override the pure virtual function virtual bool is_blocked() const = 0 declared in the class MapUnit. 
This function should always return false since the EmptyLand unit is not blocked. */
bool EmptyLand::is_blocked()const {
    return false;
}
/* Override the pure virtual function virtual string get_display_str() const = 0 declared in the class MapUnit. 
This function should always return the constant SYM_EMPTY defined in MapUnit.h. */
string EmptyLand::get_display_str()const {
    return SYM_EMPTY;
}