#include "Zombie.h"

Zombie::Zombie(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 20;
    atk = 9, def = 3;
}

//write your code here
Zombie::~Zombie(){

}
string Zombie::get_monster_str() const{
    char hp_string[10];
    (cur_hp<10)?sprintf(hp_string,"Z0%d",cur_hp):sprintf(hp_string,"Z%d",cur_hp);
    return hp_string;
}
void Zombie::action(Player &p, MapUnit *map[][MAP_SIZE]){
    int x,y;
    p.get_position(x,y);
    int mx=this->get_x();
    int my=this->get_y();
    int d_x=x-mx;
    int d_y=y-my;
    d_x=(d_x<0)?-d_x:d_x;
    d_y=(d_y<0)?-d_y:d_y;
    int distance=d_x+d_y;
    if(distance<=1)p.attacked_by(this->atk);
    return;
}