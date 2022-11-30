#include "Warlock.h"

Warlock::Warlock(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 15;
    atk = 5, def = 1;
}

//write your code here

Warlock::~Warlock(){
    
}
string Warlock::get_monster_str() const{
    char hp_string[10];
    (cur_hp<10)?sprintf(hp_string,"W0%d",cur_hp):sprintf(hp_string,"W%d",cur_hp);
    return hp_string;
}
void Warlock::action(Player &p, MapUnit *map[][MAP_SIZE]){
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
    bool can_summon=false;
    for(int i=mx-1;i<mx+2;i++){
        for(int j=my-1;j<my+2;j++){
            if(!map[i][j]->is_blocked()&&!(mx==x&&my==y))can_summon=true;
        }
    }
    if(can_summon){
        for(int i=mx-1;i<mx+2;i++){
            for(int j=my-1;j<my+2;j++){
                if(!(i==mx&&j==my))map[i][j]=new Zombie(i,j);
            }
        }
    }

    return;
}
