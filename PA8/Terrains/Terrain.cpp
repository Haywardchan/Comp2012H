#include "Terrain.h"

//write your codes here
/* The constructor of the class Terrain. Input argument x and y 
specifies the coordinate where the target Terrain unit locates. 
The coordinate should be assigned to the protected member variable x and y defined in the class MapUnit. */
Terrain::Terrain(int x, int y):MapUnit(x,y){
}

Terrain::~Terrain(){

}
/* Override the pure virtual function virtual UnitType get_unit_type() const = 0 
declared in the class MapUnit.
 This function should always return the enum value UnitType::TERRAIN defined in MapUnit.h. */
UnitType Terrain::get_unit_type() const {
    return UnitType::TERRAIN;
}