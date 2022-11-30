#include<iostream>
#include<fstream>
#include "Deque.h"


//task 3
//task 3
Deque create_deque(){
    //create the new node
    Deque new_deque;
    new_deque.ll_size=1;
    new_deque.sentinel = new Node;
    new_deque.sentinel->next = new Node;

    new_deque.sentinel->prev=new_deque.sentinel->next;
    new_deque.sentinel->next->prev=new_deque.sentinel;
    new_deque.sentinel->next->next=new_deque.sentinel;

    new_deque.start.current=new_deque.sentinel->next->arr;
    new_deque.start.first=new_deque.sentinel->next->arr;
    new_deque.start.last=new_deque.sentinel->next->arr+CHUNK_SIZE;
    new_deque.start.node=new_deque.sentinel->next;
    
    new_deque.end=new_deque.start;
    return new_deque;
}
void destroy_deque(Deque& deque){
    Node* delete_node=deque.sentinel;
    Node* temp=deque.sentinel->next;
    for(int i = 0; i < deque.ll_size+1; i++){
        delete delete_node;
        delete_node=temp;
        temp=temp->next;
    }
    deque.sentinel=nullptr;
    deque.end.current=nullptr;
    deque.end.first=nullptr;
    deque.end.last=nullptr;
    deque.end.node=nullptr;
    deque.start.current=nullptr;
    deque.start.first=nullptr;
    deque.start.last=nullptr;
    deque.start.node=nullptr;
    return;
}
// //task 4
Iterator begin(const Deque& deque){
    return deque.start;
}
Iterator end(const Deque& deque){
    return deque.end;
}
int front(const Deque& deque){
    if(deque.start.current==deque.end.current){
        cout << "Cannot get front: deque is empty" << endl;
        return -1;
        }
    else{
        return value(deque.start);
    }
}
int back(const Deque& deque){
    if(deque.start.current==deque.end.current){
        cout << "Cannot get back: deque is empty" << endl;
        return -1;
        }
        else{
            return value(prev(deque.end));   
        }
}
// //task 5
bool empty(const Deque& deque){
    if(deque.start.current==deque.end.current)return true;
    else return false;
}
int size(const Deque& deque){
    return (deque.ll_size)*8 -(deque.start.current-deque.start.first) - (deque.end.last-deque.end.current);
}
void create_new_node_at_back(Deque& deque){
    Node* new_node= new Node;
    /* deque.end.node->next=new_node;   //does not work as a const node
    new_node->prev=deque.end.node;
    new_node->next=deque.sentinel;
    deque.sentinel->prev=new_node; */
    deque.sentinel->prev->next=new_node;
    new_node->next=deque.sentinel;
    new_node->prev=deque.sentinel->prev;
    deque.sentinel->prev=new_node;
     ++deque.ll_size;
}
void create_new_node_in_front(Deque& deque){
    Node* new_node= new Node;
    deque.sentinel->next->prev=new_node;
    new_node->prev=deque.sentinel;
    new_node->next=deque.sentinel->next;
    deque.sentinel->next=new_node;
    ++deque.ll_size;
}
//task 6
void push_back(Deque& deque, int val){//last element
    *deque.end.current=val;
    if(next(deque.end).node==deque.sentinel){
        //create new node if the next space is sentinel
        create_new_node_at_back(deque);
    }
        deque.end=next(deque.end);       
    return;
}
void push_front(Deque& deque, int val){//first element
    if(prev(deque.start).node==deque.sentinel){    
        //create a new node in front
        create_new_node_in_front(deque);
    }  
        deque.start=prev(deque.start);
        *deque.start.current=val;
    return;
}
void pop_back(Deque& deque){
    if(empty(deque))cout << "Cannot pop_back: deque is empty" << endl;
    else{
        *(deque.end.current-1)=0;
        deque.end=prev(deque.end);
    }
    return;
}
void pop_front(Deque& deque){
    if(empty(deque))cout << "Cannot pop_front: deque is empty" << endl;
    else{
        *(deque.start.current)=0;
        deque.start=next(deque.start);
    }
    return;
}
//task 7
void print_deque(const Deque& deque){
    //empty deque
    Iterator run=deque.start;
    if(empty(deque))cout<<"[]"<<endl;
    //Not empty
    else {
        cout<<"[";
        while(run.current!=deque.end.current){
            (next(run).current==deque.end.current)?cout<<*run.current:cout<<*run.current<<", ";
            run=next(run);
        }
        cout<<"]"<<endl;
    }
    return;
}
//task 8
void insert(Deque& deque, const Iterator& pos, int val){
    //replace value by val and get the temp out
    int temp;       
    Iterator run=deque.end;
    //handle special cases:
    if(pos.current==run.current){push_back(deque,val);return;}
    temp=*(pos.current);
    *pos.current=val;

    if(next(deque.end).node==deque.sentinel){
        //create new node
        create_new_node_at_back(deque);
    }
    while(pos.current!=prev(run).current){
        *run.current=*(prev(run).current);
        run=prev(run);
    }
    *(run.current)=temp;
    deque.end=next(deque.end);
    return;
}
void erase(Deque& deque, const Iterator& pos){
    Iterator run=pos;
    while(run.current!=deque.end.current-1){
        *(run.current)=*(next(run).current);
        run=next(run);
    }
    *(run.current)=0;
    deque.end.current--;
    return;
}
//task 9
void store_deque(const Deque& deque, const char* filename){
    Iterator run=deque.start;
    ofstream ofs;
    ofs.open("deque.txt");
    while(run.current!=deque.end.current){
        ofs<<*run.current<<" ";
        run=next(run);
    }
    ofs<<"\n";
    ofs.close();
    return;
}
Deque load_deque(const char* filename){
    Deque new_deque = create_deque();
    int data_ifs;
    ifstream ifs;
    ifs.open("deque.txt");
    while(ifs>>data_ifs){
        push_back(new_deque,data_ifs);
    }
    ifs.close();
    return new_deque;
}