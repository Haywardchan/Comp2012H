template <typename K, typename V>
Skiplist<K,V>::Node::Node(){
    nexts = new Node*[1];
    nexts[0] = nullptr;
    levels = 1;
}
template <typename K, typename V>
Skiplist<K,V>::Node::Node(K key, V value, int levels){
    nexts = new Node*[levels];
    for(int i=0;i<levels;i++){
        nexts[i]=nullptr;
    }
    this->levels=levels;
    this->key=key;
    this->value=value;
}
template <typename K, typename V>
Skiplist<K,V>::Node::~Node(){
    delete [] this->nexts;
}
template <typename K, typename V>
Skiplist<K, V>::Skiplist(double prob){
    head= new Node();
    this->prob=0.25;//default prob value
    this->prob=prob;
}
template <typename K, typename V>
Skiplist<K, V>::~Skiplist(){
    Node* temp = head;
    while (temp!=NULL)
    {
        temp=*(temp->nexts);
        delete head;
        head=temp;
    }
    return;
}
template <typename K, typename V>
Skiplist<K, V>& Skiplist<K,V>::operator=(const Skiplist<K, V>& other){
// //delete the old skiplist
    if(head->nexts!=nullptr){
        Node* temp = *(head->nexts);
        while (temp!=NULL)
        {
            temp=*(temp->nexts);
            delete head;
            head=temp;
        }
    }
    delete []this->head->nexts;
//deep copy the skiplist
    //copy the sentinel node
    int n_levels=other.head->levels;
    this->head->levels=n_levels;
    this->head->nexts=new Node*[n_levels];

    //copy the prob
    this->prob=other.prob;

    // copy K, V value and level of connected nodes using constructor
    Node** curpos= new Node*[n_levels];//create a variable to track the cur node of each levels
    for(int i=0;i<n_levels;curpos[i]=head, i++);//all current nodes are set to be the head of the skiplist
    for(Node*temp=other.head->nexts[0]; temp!=NULL; temp = temp->nexts[0]){
        //create new node
        Node* New_Node= new Node(temp->key, temp->value, temp->levels);
        for (int i = 0; i < temp->levels; i++){
            //link the list if curpos is not null
            if(curpos[i]){
                curpos[i]->nexts[i]=New_Node;
                curpos[i]=New_Node;
            }
            //assign nullptr to rightmost nodes
            if(temp->nexts[i]==NULL){
                curpos[i]->nexts[i]=nullptr;
            }
        }
    }
    //delete heap memory allocated by the cur Nodes
    delete []curpos;
    return *this;
}
template <typename K, typename V>
Skiplist<K,V>::Skiplist(const Skiplist<K, V>& other){
    //create the head of the skiplist
    head=new Node();
    //assignment
    *this=other;
}
template <typename K, typename V>
bool Skiplist<K,V>::get(const K& get_key, V& rtn_value) const{
    int height=head->levels;
    Node*prev=head;
    Node*curr=head->nexts[height-1];
    for(int current_lv=height-1; current_lv>=0; current_lv--){
        //set back to prev 
        if(current_lv!=height-1)curr=prev->nexts[current_lv];
        if(!curr){
            continue;
        }
        else{
        //traversal
        for(Node*temp=curr;temp!=NULL;temp=temp->nexts[current_lv], prev=prev->nexts[current_lv]){
            if(temp->key==get_key){
                rtn_value = temp->value;
                return true;
            }
        }
        }
    }
    return false;
}
template <typename K, typename V>
void Skiplist<K,V>::update(const K& update_key, const V& update_value){ 
    //found
    Node**curpos=new Node*[head->levels];
    int height=head->levels;
    Node*prev=head;
    Node*curr=head->nexts[height-1];
    for(int current_lv=height-1; current_lv>=0; current_lv--){
        //set back to prev 
        if(current_lv!=height-1){
            curr=prev->nexts[current_lv];
        }
        if(!curr){
            curpos[current_lv]=prev;
            continue;
        }
        else{
        //traversal
        for(Node*temp=curr;temp!=NULL;temp=temp->nexts[current_lv], prev=prev->nexts[current_lv]){
            if(temp->key==update_key){
                temp->value=update_value;
                delete[]curpos;
                return;
            }else if(temp->key>update_key){
                curpos[current_lv]=prev;
                break;
            }
            if(temp->nexts[current_lv]==NULL)curpos[current_lv]=temp;
        }

        }
    }
    //cant find
    Node* NewNode=new Node(update_key,update_value,getRandomLevels());
    int newlevel=NewNode->levels;
    int headlevel=head->levels;
    if(headlevel<newlevel){
        //extend the head height
        Node** new_sentinel=new Node*[newlevel];
        //initializing the sentinel pointer
        for(int i=0;i<newlevel;i++)
            (i<headlevel)?new_sentinel[i]=head->nexts[i]:new_sentinel[i]=nullptr;
        delete[]head->nexts;
        head->nexts=new_sentinel;
        head->levels=newlevel;
    }
    //link the skiplist
    //find the prev node of each levels
    for (int i = 0; i < newlevel; i++){
        //insertion
        if(i<headlevel){
            NewNode->nexts[i]=curpos[i]->nexts[i];
            curpos[i]->nexts[i]=NewNode;
        }else
        //insertion at head
        {
            NewNode->nexts[i]=head->nexts[i];
            head->nexts[i]=NewNode;
        }
    }
    delete[]curpos;
}
template <typename K, typename V>
bool Skiplist<K,V>::remove(const K& remove_key){    
    int height=head->levels;
    bool found=false;
    Node*prev=head;
    Node*curr=head->nexts[height-1];
    Node**prev_nodes=new Node*[height];
    Node*del=curr;
    //find the pointer to del Node
    for(int current_lv=height-1; current_lv>=0; current_lv--){
        
        //set back to prev 
        if(current_lv!=height-1)curr=prev->nexts[current_lv];

        if(!curr){
            prev_nodes[current_lv]=prev;
            continue;
        }
        else{
        //traversal
        for(Node*temp=curr;temp!=NULL;temp=temp->nexts[current_lv], prev=prev->nexts[current_lv]){
            if(temp->key==remove_key){
                del=temp;
                prev_nodes[current_lv]=prev;
                found=true;
                break;
            }
            else if(temp->key>remove_key){
                prev_nodes[current_lv]=prev;
                break;
            }
            if(temp->nexts[current_lv]==NULL)prev_nodes[current_lv]=temp;
        }

        }
    }
    if(found){
        //relink the nodes by layer
        // Node* del = curr;
        int i;
        for(i=0;i<head->levels;i++){
            if(!head->nexts[i])break;
            if(prev_nodes[i]->nexts[i])
                prev_nodes[i]->nexts[i]=del->nexts[i];
        }
        if(i<head->levels){
            //rebuild sentinel if removed stack of pointer is the highest
            Node**new_sentinel=new Node*[i];
            for(int height=0;height<i;i++){
                new_sentinel[height]=head->nexts[i];
            }
            delete []head->nexts;
            head->nexts=new_sentinel;
            i++;
            head->levels=i;
        }
        delete del;
    }
    delete[]prev_nodes;
    return found;
}
template <typename K, typename V>
int Skiplist<K,V>::size() const{
    int count;
    for(Node*temp=head->nexts[0];temp!=NULL;temp=temp->nexts[0])count++;
    return count;
}
template <typename K, typename V>
bool Skiplist<K,V>::empty() const{
    if(head->nexts[0]==nullptr)return true;
    return false;
}
template <typename K, typename V>
void Skiplist<K,V>::print() const{
    if(empty())std::cout<<"{}";
    else{
        std::cout<<"{";
        for(Node*temp=head->nexts[0];temp!=NULL;temp=temp->nexts[0]){
            std::cout<<temp->key<<": "<<temp->value;
            if(temp->nexts[0]!=NULL)std::cout<<", ";
        }
        std::cout<<"}";
    }
}
template <typename K, typename V>
template <typename T>
Skiplist<K, T> Skiplist<K,V>::map(T (*f)(V value)) const{
    Skiplist<K,T>new_skiplist;
    for(Node*temp=head->nexts[0];temp!=NULL;temp=temp->nexts[0]){
        new_skiplist.update(temp->key,f(temp->value));
    }
    return new_skiplist;
}
template <typename K, typename V>
Skiplist<K, V> Skiplist<K,V>::filter(bool (*f)(V value)) const{
    Skiplist<K,V>new_skiplist;
    for(Node*temp=head->nexts[0];temp!=NULL;temp=temp->nexts[0]){
        if(f(temp->value))new_skiplist.update(temp->key,temp->value);
    }
    return new_skiplist;
}
template <typename K, typename V>
Skiplist<K, V> Skiplist<K,V>::operator+(const Skiplist& other) const{
    Skiplist<K,V> updated_skiplist;
    updated_skiplist=*this;
    for(Node*temp=other.head->nexts[0];temp!=NULL;temp=temp->nexts[0])
        updated_skiplist.update(temp->key,temp->value);
    return updated_skiplist;
}