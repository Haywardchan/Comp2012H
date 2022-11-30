#include "Wall.h"


//write your codes here
/* The constructor of the class Wall. Input argument x and y 
specifies the coordinate where the target Wall unit locates. 
The coordinate should be assigned to the protected member variable x and y defined in the class MapUnit. */
Wall::Wall(int x, int y):Terrain(x,y){
}
Wall::~Wall(){

}
/* Override the pure virtual function virtual bool is_blocked() const = 0 declared in the class MapUnit.
 This function should always return true since the Wall unit is always blocked. */
bool Wall::is_blocked() const {
    return true;
}
/* Override the pure virtual function virtual string get_display_str() const = 0 
declared in the class MapUnit. This function should always return the constant SYM_WALL defined in MapUnit.h.
 */
string Wall::get_display_str() const {
    return SYM_WALL;
}