#include "Gem.h"


//write your codes here
/* The constructor of the class Gem. Input argument x and y specifies the coordinate where the target Gem unit locates. 
The coordinate should be assigned to the protected member variable x and y defined in the class MapUnit. 
gem_type is a enum variable of GemType that specifies the type of that Gem unit.
 It should be assigned to the member variable gtype. */
Gem::Gem(int x, int y, GemType gem_type):Item(x,y){
    gtype=gem_type;
}
Gem::~Gem(){

}
/* If the Gem unit is invalid (call is_valid() defined in class MapUnit to check), do nothing.
If the Gem unit is valid:
Ruby Gem unit charge MP for player of Role::WARRIOR, and do nothing otherwise.
Emerald Gem unit charge MP for player of Role::ARCHER, and do nothing otherwise.
Sapphire Gem unit charge MP for player of Role::MAGE, and do nothing otherwise.
Then mark the Gem unit as invalid. You can call Player::get_role() to get the role of the player, 
and call Player::charge_mp() to charge MP for the player. */
void Gem::triggered_by(Player &p){
    if(is_valid()==false)return;
    switch (gtype)
    {
        case RUBY:
            if(p.get_role()==Role::WARRIOR){p.charge_mp();}
            break;
        case EMERALD:
            if(p.get_role()==Role::ARCHER){p.charge_mp();}
            break;
        case SAPPHIRE:
            if(p.get_role()==Role::MAGE){p.charge_mp();}
            break;
    }
    this->invalidate();
    
}
/* Ruby Gem unit: return SYM_RUBY.
Emerald Gem unit: return SYM_EMERALD.
Sapphire Gem unit: return SYM_SAPPHIRE. */
string Gem::get_item_str() const {
    switch (gtype)
    {
    case RUBY:
        return SYM_RUBY;
        break;
    case EMERALD:
        return SYM_EMERALD;
        break;
    case SAPPHIRE:
        return SYM_SAPPHIRE;
        break;
    }
    return SYM_EMPTY;
}