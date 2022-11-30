#include <iostream>
#include <fstream>
#include "Deque_Iterator.h"

bool equal(const Iterator& it1, const Iterator& it2){
    return (it1.current==it2.current)?true:false;
}

int value(const Iterator& it){
    return *(it.current);
}

/*
The set_node() function will let the iterator it point at node new_node. Note that you should not update it.current, 
since this pointer is not determined by the node, while other variables in the iterator should be determined by the new node.
*/
void set_node(Iterator& it, Node* new_node){
    it.first = new_node->arr;
    it.last = new_node->arr+CHUNK_SIZE;
    it.node = new_node;
    return;
}

// void set_node(Iterator& it, Node* new_node){
//     it.first = &(new_node->arr[0]);
//     it.last = &(new_node->arr[CHUNK_SIZE]);
// }

/*
The next() function returns an iterator that points to the position next to the given it. 
You should not modify the it passed in, you need to create a new iterator and return it, so we passed it by const to avoid modifying.
*/

Iterator next(const Iterator& it){
    Iterator a;
    a.node = it.node;
    if (it.current+1 < it.last){
        a = it;
        a.current = it.current+1;
    }else{
        set_node(a,a.node->next);
        a.current = a.first;
    }
    return a;
    
}

Iterator prev(const Iterator& it){
    Iterator a;
    a.node = it.node;
    if (it.current-1 >= it.first){
        a = it;
        a.current = it.current-1;
    }else{
        set_node(a,a.node->prev);
        a.current = a.last-1;
    }
    return a;
}

