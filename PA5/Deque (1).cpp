#include <iostream>
#include <fstream>
#include "Deque.h"

/*
struct Deque {
    Iterator start;     // the position of first item in deque
    Iterator end;       // the position after last item in deque

    Node* sentinel;     // sentinel of the circular doubly-linked list
    int ll_size;        // size of linked list, notice that this is number of chunks, not items
};

struct Node {
    int arr[CHUNK_SIZE];        // the chunk
    Node* prev;                 // previous Node
    Node* next;                 // next Node
};

struct Iterator {
    int* current;           // current position
    int* first;             // begin of the chunk, i.e., the position of first item
    int* last;              // end of the chunk, i.e., the position after the last item
    const Node* node;       // current Node
};
*/

Deque create_deque(){
    Deque dq;
    dq.sentinel = new Node;
    dq.sentinel->next = new Node;
    dq.sentinel->prev = dq.sentinel->next;

    dq.sentinel->next->next = dq.sentinel;
    dq.sentinel->next->prev = dq.sentinel;

    dq.ll_size = 1;

    set_node(dq.start, dq.sentinel->next);
    dq.start.current = dq.start.first;

    dq.end = dq.start;

    return dq;
}

void destroy_deque(Deque& deque){
    Node* tmp;
    while(deque.sentinel->next != deque.sentinel){
        tmp = deque.sentinel->prev;
        deque.sentinel->prev->prev->next = deque.sentinel->prev->next;
        deque.sentinel->prev = deque.sentinel->prev->prev;
        delete tmp;
    }
    tmp = nullptr;

    delete deque.sentinel->next;
    deque.sentinel->next = nullptr;
    deque.ll_size = 0;

    deque.start.first = nullptr;
    deque.start.last = nullptr;
    deque.start.current = nullptr;
    deque.start.node = nullptr;

    deque.end = deque.start;

    return;
    
}

Iterator begin(const Deque& deque){
    Iterator a;
    a = deque.start;
    return a;
}

Iterator end(const Deque& deque){
    Iterator a;
    a = deque.end;
    return a;
}


int front(const Deque& deque){
    if (empty(deque)){
        cout << "Cannot get front: deque is empty" << endl;
    }else{
        return value(deque.start);
    }
    return -1;
}

int back(const Deque& deque){
    if (empty(deque)){
        cout << "Cannot get end: deque is empty" << endl;
    }else{
        return *(deque.end.current-1);
    }
    return -1;
}

bool empty(const Deque& deque){
    return (deque.start.current==deque.end.current)? true : false;
}
int size(const Deque& deque){
    if (empty(deque))return 0;
    return (deque.ll_size*8 - (deque.start.current - deque.start.first) - (deque.end.last - deque.end.current));
}

void push_back(Deque& deque, int val){
    *(deque.end.current) = val;
    if (next(deque.end).node == deque.sentinel){
        Node* nodeptr = new Node;
        deque.ll_size++;
        deque.sentinel->prev->next = nodeptr;

        nodeptr->prev = deque.sentinel->prev;
        nodeptr->next = deque.sentinel;

        deque.sentinel->prev = nodeptr;
    }
    deque.end = next(deque.end);
    return;
}
void push_front(Deque& deque, int val){
    if (prev(deque.start).node == deque.sentinel){
        Node* nodeptr = new Node;
        deque.ll_size++;
        deque.sentinel->next->prev = nodeptr;

        nodeptr->next = deque.sentinel->next;
        nodeptr->prev = deque.sentinel;

        deque.sentinel->next = nodeptr;
    }

    deque.start = prev(deque.start);
    *(deque.start.current) = val;
    return;
}
void pop_back(Deque& deque){
    if (empty(deque)){cout << "Cannot pop_back: deque is empty" << endl; return;}
    if (prev(deque.end).node != deque.end.node){
        Node* tmp;
        tmp = deque.sentinel->prev;

        deque.sentinel->prev->prev->next = deque.sentinel;
        deque.sentinel->prev = deque.sentinel->prev->prev;

        delete tmp;
        deque.ll_size--;
    }
    deque.end = prev(deque.end);
    return;
}
void pop_front(Deque& deque){
    if (empty(deque)){cout << "Cannot pop_front: deque is empty" << endl; return;}
    if (next(deque.start).node != deque.start.node){
        Node* tmp;
        tmp = deque.sentinel->next;

        deque.sentinel->next->next->prev = deque.sentinel;
        deque.sentinel->next = deque.sentinel->next->next;

        delete tmp;
        deque.ll_size--;
    }
    deque.start = next(deque.start);
    return;
}

void print_deque(const Deque& deque){
    cout << "[";
    if (!(empty(deque))){
        for (Iterator it = deque.start; it.current!=deque.end.current; it=next(it)){
            cout << value(it);
            if (next(it).current != deque.end.current){
                cout << ", ";
            }
        }
    }
    cout << "]" << endl;
    return;
}

void insert(Deque& deque, const Iterator& pos, int val){
    Iterator tmp = deque.end;
    if (pos.current == begin(deque).current){push_front(deque,val);return;}
    for (deque.end; deque.end.current != pos.current; deque.end = prev(deque.end)){
        push_back(deque, value(prev(deque.end)));
        deque.end = prev(deque.end);
    }
    if(next(tmp).node==deque.sentinel){
        Node* nodeptr = new Node;
        deque.ll_size++;
        deque.sentinel->prev->next = nodeptr;

        nodeptr->prev = deque.sentinel->prev;
        nodeptr->next = deque.sentinel;

        deque.sentinel->prev = nodeptr;
    }
    deque.end = next(tmp);
    *(pos.current) = val;
    return;
}
void erase(Deque& deque, const Iterator& pos){
    Iterator tmp = deque.end;
    for (deque.end = pos; deque.end.current != tmp.current;){
        push_back(deque, value(next(deque.end)));
    }
    if (tmp.node != prev(tmp).node){
        Node* a = deque.sentinel->prev;
        a->prev->next = deque.sentinel;
        deque.sentinel->prev = a->prev;
        deque.ll_size--;

        delete a;
    }
    deque.end = prev(tmp);
    return;
}

void store_deque(const Deque& deque, const char* filename){return;}
Deque load_deque(const char* filename){Deque a; return a;}