#include<iostream>
#include<fstream>
#include "Deque_Iterator.h"


// bool equal(const Iterator& it1, const Iterator& it2);
// int value(const Iterator& it);
// void set_node(Iterator& it, Node* new_node);
// Iterator next(const Iterator& it);
// Iterator prev(const Iterator& it);

//task 1 
bool equal(const Iterator& it1, const Iterator& it2){
    if(it1.current==it2.current)return true;
    else return false;
}
int value(const Iterator& it){
    return *(it.current);
}

//task 2 
void set_node(Iterator& it, Node* new_node){
    it.node=new_node;
    it.first=new_node->arr;
    it.last=new_node->arr+CHUNK_SIZE;
}
Iterator next(const Iterator& it){      //kinda wrong
    Iterator temp_it;
    temp_it.node=it.node;
    if(it.current+1<it.last){    
        temp_it=it;
        temp_it.current=it.current+1;
    }else{
        set_node(temp_it,temp_it.node->next);
        temp_it.current=temp_it.first;
    }
    return temp_it;
}
Iterator prev(const Iterator& it){      //kinda wrong
    Iterator temp_it;
    temp_it.node=it.node;
    if(it.current==it.first){    
        set_node(temp_it,temp_it.node->prev);
        temp_it.current=temp_it.last-1;
    }else{
        temp_it=it;
        temp_it.current=it.current-1;
    }
    return temp_it;
}

// int main(){
//     cout<<"hello";
//     Node a;
//     Node b;
//     Iterator test;
//     a.next=&b;
//     test.node=&a;
// }