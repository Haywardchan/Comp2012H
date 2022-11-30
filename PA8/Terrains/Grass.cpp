#include "Grass.h"

//write your codes here
/* The constructor of the class Grass. Input argument x and y 
specifies the coordinate where the target Grass unit locates. 
The coordinate should be assigned to the protected member variable x and y defined in the class MapUnit. */
Grass::Grass(int x, int y):Terrain(x,y){

}

Grass::~Grass(){

}
/* Override the pure virtual function virtual bool is_blocked() const = 0 declared in the class MapUnit.
 This function should always return false since the Grass unit is not blocked. */
bool Grass::is_blocked() const {
    return false;
}
/* Override the pure virtual function virtual string get_display_str() const = 0 declared in the class MapUnit.
 This function should always return the constant SYM_GRASS defined in MapUnit.h. */
string Grass::get_display_str() const {
    return SYM_GRASS;
}
