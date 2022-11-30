#include "Monster.h"
#include <cmath>

// write your code here
Monster::Monster(int x, int y):MapUnit(x,y){

}
Monster::~Monster(){

}
bool Monster::is_active() const{
    return active;
}
void Monster::set_active(){
    if(this->is_valid())active=true;
    else return;
}
void Monster::recover_hp(int hp){
    if(this->cur_hp+hp<=this->max_hp)this->cur_hp+=hp;
    else this->cur_hp=this->max_hp;
    return;
}
UnitType Monster::get_unit_type() const{
    return MONSTER;
}
bool Monster::is_blocked() const{
    if(this->is_valid())return true;
    else return false;
}
int Monster::attacked_by(int atk_){
    if(!is_valid())return 0;
    int damage=atk_-def;
    if(damage<0)return 0;
        
    cur_hp-=damage;
    if (cur_hp<=0){
        invalidate();
        active=false;
        return 1;
    } else return 0;
}
string Monster::get_display_str() const{
    if(this->is_valid()==false)return SYM_EMPTY;
    else{
        if(!is_discovered())return SYM_DANGER;
        else{
            return get_monster_str();
        }
    }
}
void Monster::follow(const Player &p, MapUnit *map[][MAP_SIZE]){
    //(x1, y1) and (x2, y2) is |x1-x2|+|y1-y2|
    int px,py;
    p.get_position(px,py);
    int mx=this->get_x();
    int my=this->get_y();
    int d_x=px-mx;
    int d_y=py-my;
    int absd_x=(d_x<0)?-d_x:d_x;
    int absd_y=(d_y<0)?-d_y:d_y;
    int distance=absd_x+absd_y;
    int next_step_x=(d_x>0)?mx+1:mx-1;
    int next_step_y=(d_y>0)?my+1:my-1;
    if(distance==1)return;
    else if(absd_x>0 && !map[next_step_x][my]->is_blocked()){
        map[next_step_x][my]=this;
        this->x=next_step_x;
        this->y=my;
        map[mx][my]=new EmptyLand(mx,my);
    }
    else if (absd_y>0 && !map[mx][next_step_y]->is_blocked())
    {
        map[mx][next_step_y]=this;
        this->x=mx;
        this->y=next_step_y;
        map[mx][my]=new EmptyLand(mx,my);
    }
    else return;
}
