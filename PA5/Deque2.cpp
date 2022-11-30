#include<iostream>
#include<fstream>
#include "Deque.h"


//task 3
Deque create_deque(){
    //create the new node
    Deque new_deque;
    new_deque.ll_size=1;
    new_deque.sentinel = new Node;
    Node*temp_node = new Node;

    new_deque.sentinel->prev=temp_node;
    new_deque.sentinel->next=temp_node;
    temp_node->prev=new_deque.sentinel;
    temp_node=new_deque.sentinel;

    new_deque.start.current=temp_node->arr;
    new_deque.start.first=temp_node->arr;
    new_deque.start.last=temp_node->arr+CHUNK_SIZE;

    new_deque.end=new_deque.start;
    return new_deque;
}
void destroy_deque(Deque& deque){
    // Node*temp = deque.sentinel->next;
    // while (temp!=deque.sentinel)
    // {
    //     deque.sentinel->next=deque.sentinel->next->next;
    //     delete temp;
    // }
    // deque.sentinel=nullptr;
    // return;

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
//task 6
void push_back(Deque& deque, int val){//last element
    if(deque.end.node->arr+CHUNK_SIZE-1!=deque.end.current){    //case for non last element
        *(deque.end.current)=val;
        deque.end.current++;
    }else{
        if(deque.end.node->next==deque.sentinel){
            //make a new node at the back
        }
            deque.end=next(deque.end);
            *deque.end.current=val;
            deque.end.current++;
    }                 
    return;
}
void push_front(Deque& deque, int val){//first element
    if(deque.start.node->arr!=deque.start.current){    //case for non last element
        *(deque.start.current-1)=val;
        deque.start.current--;
    }else{
        deque.start=prev(deque.start);
        *(deque.start.current)=val;
        deque.start.current--;
    }  
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
// //task 7
void print_deque(const Deque& deque){
    //empty deque
    Iterator run;
    run=deque.start;
    if(empty(deque))cout<<"[]"<<endl;
    //Not empty
    else {
        cout<<"[";
        while(run.current!=deque.end.current){
            (run.current+1==deque.end.current)?cout<<*run.current:cout<<*run.current<<", ";
            run=next(run);
        }
        cout<<"]"<<endl;
    }
    return;
}
//task 8
void insert(Deque& deque, const Iterator& pos, int val){
    int temp;
    Iterator run;
    run=deque.end;
    bool not_inserted=true;
    cout<<*(pos.current);
    temp=*(pos.current);
    *pos.current=val;

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
    return;
}
Deque load_deque(const char* filename){
    Deque new_deque;
    return new_deque;
}
// int main(){
//     cout<<"hello";
// }