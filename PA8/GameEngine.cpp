#include "GameEngine.h"

using namespace std;

// Please do not change the following already implemented code

void GameEngine::print_active_monsters()
{
    int i = 0;
    cout << "Active Monsters:" << endl;
    MonsterNode *cur = head;
    while (cur != nullptr)
    {
        cout << cur->data->get_display_str();
        cout << "@(" << cur->data->get_x();
        cout << "," << cur->data->get_y() << "), ";
        cur = cur->next;
        i++;
        if (i == 4)
        {
            i = 0;
            cout << endl;
        }
    }
}

bool GameEngine::player_win() const
{
    int px, py;
    player->get_position(px, py);
    if (px == MAP_SIZE - 1 && py == MAP_SIZE - 1)
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (map[i][j]->get_unit_type() == UnitType::MONSTER && map[i][j]->is_valid())
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
        return false;
}

GameEngine::GameEngine()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (i > 8 && i < 12 && j > 2 && j < 6)
                map[i][j] = new Wall(i, j);
            else if (i > 14 && i < 18 && j > 2 && j < 6)
                map[i][j] = new Grass(i, j);
            else if (i > 2 && i < 6 && j == 9)
                map[i][j] = new Gem(i, j, GemType::RUBY);
            else if (i > 2 && i < 6 && j == 10)
                map[i][j] = new Gem(i, j, GemType::EMERALD);
            else if (i > 2 && i < 6 && j == 11)
                map[i][j] = new Gem(i, j, GemType::SAPPHIRE);
            else if (i > 8 && i < 12 && j > 8 && j < 12)
                map[i][j] = new Book(i, j);
            else if (i > 14 && i < 18 && j > 8 && j < 12)
                map[i][j] = new Medicine(i, j);
            else if (i > 2 && i < 6 && j > 14 && j < 18)
                map[i][j] = new Zombie(i, j);
            else if (i > 8 && i < 12 && j > 14 && j < 18)
                map[i][j] = new Warlock(i, j);
            else if (i > 14 && i < 18 && j > 14 && j < 18)
                map[i][j] = new ShadowPriest(i, j);
            else
                map[i][j] = new EmptyLand(i, j);
        }
    }
}

char GameEngine::input()
{
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    return c;
}

void GameEngine::run()
{
    string name;
    cout << "Please enter your name:" << endl;
    cin >> name;
    cout << "Please choose your role:" << endl;
    cout << "1 Warrior" << endl;
    cout << "2 Archer" << endl;
    cout << "3 Mage" << endl;

    int x = 0, y = 0;
    char role = input();
    switch (role)
    {
    case '1':
        create_player(x, y, name, Role::WARRIOR);
        break;
    case '2':
        create_player(x, y, name, Role::ARCHER);
        break;
    case '3':
        create_player(x, y, name, Role::MAGE);
        break;
    default:
        exit(0);
        break;
    }
    ui.refresh(this->map, *player);

    while (true)
    {
        switch (input())
        {
        case 'w':
            this->player_move(Direction::UP);
            break;
        case 'a':
            this->player_move(Direction::LEFT);
            break;
        case 's':
            this->player_move(Direction::DOWN);
            break;
        case 'd':
            this->player_move(Direction::RIGHT);
            break;
        case 'h':
            this->player_attack();
            break;
        case 'j':
            this->player_skill();
            break;
        default:
            break;
        }
        if (player_win())
        {
            cout << endl;
            cout << "You win." << endl;
            break;
        }
        player_discover();
        activate_monsters();
        monster_follow();
        monster_act();
        ui.refresh(this->map, *player);
        print_active_monsters();
        if (!player->is_alive())
        {
            cout << endl;
            cout << "You lose." << endl;
            break;
        }
    }
}


// write your code here
GameEngine::~GameEngine(){
    MonsterNode* temp = head;
    while (temp!=NULL)
    {
        temp=temp->next;
        delete head;
        head=temp;
    }
    delete player;
    return;
}
void GameEngine::create_player(int x, int y, const string &name, Role role){
    if(role==ARCHER)player= new Archer(x,y,name);
    if(role==WARRIOR)player = new Warrior(x,y,name);
    if(role==MAGE)player = new Mage(x,y,name);
}
void GameEngine::activate_monster(Monster *monster){
    // cout<<"entered;";
    if(!monster->is_discovered())monster->set_discovered();
    if(monster->is_valid()&&!(monster->is_active())){
        // cout<<"enter if"<<endl;
        monster->set_active();
        MonsterNode* monster1=new MonsterNode;
        monster1->data=monster;
        if(head==nullptr){
            head=monster1;
            monster1->next=nullptr;
        }
        else{
            monster1->next=head;
            head=monster1;
        }
    }
    // cout<<"activated one monster"<<endl;
    return;
}
void GameEngine::activate_monsters(){
    int x, y;
    player->get_position(x,y);
    // cout<<"activating monsters"<<endl;
    for (int dx = x-1; dx < x+2; dx++)
    {
        for (int dy = y-1; dy < y+2; dy++)
        {
            if((dx>=0 && dy>=0 && dx<MAP_SIZE && dy<MAP_SIZE) && map[dx][dy]->get_unit_type()==MONSTER)activate_monster(dynamic_cast<Monster*>(map[dx][dy]));
        }
        
    }
    // cout<<"activation ended"<<endl;
    return;
}
void GameEngine::deactivate_monster(Monster const *const monster){
    int mx=monster->get_x();
    int my=monster->get_y();

    if(head==nullptr)return;
    MonsterNode* temp=head;
    MonsterNode*prev=head;
    if(temp->data==monster){
        head=head->next;
        delete temp;
    }else{
        for(;prev->next->data!=monster && prev!=nullptr;prev=prev->next);
        temp=prev->next;
        prev->next=prev->next->next;
        temp->next=nullptr;
        delete temp;
    }
    map[mx][my]=new EmptyLand(mx,my);
}
void GameEngine::player_move(Direction d){
    int x,y;
    player->get_position(x,y);
    bool outside=false;

    switch (d)
    {
        case UP:
            y++;
            if(y>=MAP_SIZE)outside=true;
            break;
        case DOWN:
            y--;
            if(y<0)outside=true;
            break;
        case LEFT:
            x--;
            if(x<0)outside=true;
            break;
        case RIGHT:
            x++;
            if(x>=MAP_SIZE)outside=true;
            break;
    }

    if(!outside && !(map[x][y]->is_blocked())){
        // cout<<"moving"<<endl;
        player->move(d,1);
        map[x][y]->triggered_by(*player);
    }
    else player->move(d,0);

    return;
}
void GameEngine::player_discover(){
    // cout<<"discovering..."<<endl;
    int px, py;
    player->get_position(px,py);
    for (int x = px-2; x < px+3; x++){
        for (int y = py-2; y < py+3; y++)
            if(x>=0 && y>=0 && x<MAP_SIZE && y<MAP_SIZE)map[x][y]->set_discovered();
    }
    // cout<<"finished discovering"<<endl;
    return;
}
void GameEngine::player_attack(){
    int attack, defense, range, px, py,x,y;
    player->get_position(x, y);
    px=x;
    py=y; 
    player->get_atk_def(attack, defense);
    range=player->get_range();
    Monster*nearest_monster=nullptr;   //default
    for(int i=0; i<range;i++){
        switch (player->get_direction())
        {
            case UP:
                py++;
                if(py>=MAP_SIZE)return;
                break;
            case DOWN:
                py--;
                if(py<0)return;
                break;
            case LEFT:
                px--;
                if(px<0)return;
                break;
            case RIGHT:
                px++;
                if(py>=MAP_SIZE)return;
                break;
        }
        if(map[px][py]->get_unit_type()==MONSTER){
            nearest_monster=dynamic_cast<Monster*>(map[px][py]);

            if(nearest_monster->attacked_by(attack)==1){
                deactivate_monster(nearest_monster);
                player->gain_exp(1);
            }else if(!nearest_monster->is_active()){
                activate_monster(nearest_monster);
            }
        }
    }
    return;
}
void GameEngine::player_skill(){
    int attack, defense, range, px, py, x, y;
    player->get_position(x, y);
    px=x;
    py=y; 
    player->get_atk_def(attack, defense);
    int valid=player->skill(attack,range);
    if(valid==1)return; else{
        Monster*nearest_monster=nullptr;   //default
        for(int i=0; i<range;i++){
            switch (player->get_direction())
            {
                case UP:
                    py++;
                    if(py>=MAP_SIZE)return;
                    break;
                case DOWN:
                    py--;
                    if(py<0)return;
                    break;
                case LEFT:
                    px--;
                    if(px<0)return;
                    break;
                case RIGHT:
                    px++;
                    if(py>=MAP_SIZE)return;
                    break;
            }
            if(map[px][py]->get_unit_type()==MONSTER){
                nearest_monster=dynamic_cast<Monster*>(map[px][py]);

                if(nearest_monster->attacked_by(attack)==1){
                    deactivate_monster(nearest_monster);
                    player->gain_exp(1);
                }else if(!nearest_monster->is_active()){
                    activate_monster(nearest_monster);
                }
            }
        }
    }
    return;
}
void GameEngine::monster_follow(){
    for(MonsterNode*temp=head;temp!=nullptr;temp=temp->next){
        temp->data->follow(*player,map);
    }
    // cout<<"following"<<endl;
}
void GameEngine::monster_act(){
    for(MonsterNode*temp=head;temp!=nullptr;temp=temp->next){
        temp->data->action(*player,map);
    }
    // cout<<"acting"<<endl;
}