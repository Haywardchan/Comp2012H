#include <vector>
#include <iostream>
#include "dictionary.h"

using namespace std;

// this function will not be used in any way. For C++, templates are usually defined in header files. 
// However, for ZINC grading, we separate it into different files. So we need to use this 'trick' to
// instantiate the temnplate.
void compiler_trick_useless_function(){
    Dictionary d{""};
    lambda_for_main_cpp ct;
    d.foreach(ct);
}

int Dictionary::character_to_index(const char& ch){
    return ch - 97;
}

char Dictionary::index_to_character(const int& idx){
    return (char) (idx + 97);
}

const string& Dictionary::get_name() const{
    return name;
}

void Dictionary::set_name(const string& name){
    this->name = name;
}

Dictionary::Dictionary(const string& name)
    : name(name) 
{
    root = new Node;
}

Dictionary::~Dictionary(){
    delete root;
}

Dictionary::Dictionary(Dictionary&& d){
    root = d.root;
    d.root = nullptr;
}

Dictionary& Dictionary::operator=(Dictionary&& d){
    delete root;
    root = d.root;
    d.root = nullptr;

    return *this;
}

ostream& operator<<(ostream& o, Node* n){
    o << (*n);
    return o;
}

ostream& operator<<(ostream& o, const Node& n){
    o << " (" << n.meaning.type << ") " << n.meaning.meaning << " ";
    return o;
}

/**
 * TODO - Constructor for deep copy of dictionary.
*/
void copymeaning2(Node*node,Node*nnode){
    nnode->meaning.meaning=node->meaning.meaning;
    nnode->meaning.type=node->meaning.type;
}
void link(Node*node,Node*nnode,int idx){
    node->set_child(idx,nnode);
    nnode->get_parent()=node;
    nnode->set_child(idx,nullptr);
}
void relink(Node*node,Node*dnode){
    node->meaning.type=dnode->meaning.type;
    node->meaning.meaning=dnode->meaning.meaning;
    for(int i=0;i<26;i++){
        if((*dnode)[i]){
            Node* nnode=new Node;
            link(node,nnode,i);
            relink(nnode,(*dnode)[i]);
        }
    }
}
Dictionary::Dictionary(const Dictionary& d){
    //delete current dictionary//no need becuase this is not assignment
    //build a new heap space
    this->root=new Node;
    //assign memory to new dict using recursion since we dk the depth
    relink(root, d.root);//alternate method could use foreach
}

/**
 * TODO - Assignment operator for deep copy of dictionary.
*/
Dictionary& Dictionary::operator=(const Dictionary& d){
    //delete the current dict using given node destructor
    delete this->root;
    //build new heap
    this->root=new Node;
    //copy everything to new heap
    relink(root,d.root);
    //return the *this
    return *this;
}

/**
 * TODO - Adds a node with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::add_node(const char* key){
    // if key is empty string return root node
    if(*key=='\0')return this->root;
    //if key is existing return existing node
    if(find_node(key))return find_node(key);

    //create new node using given key
    Node* curr=root;
    Node* nnode;
    const char* search=key;
    for(;*search!='\0';search++){
        int ptridx=character_to_index(*search);
        if((*curr)[ptridx])curr=(*curr)[ptridx];
        else{
            nnode=new Node;
            curr->set_child(ptridx,nnode);
            nnode->get_parent()=curr;
            curr=nnode;
        }
    }
    // curr->get_parent()->set_child(*(search-1)-97,nullptr);//no need default is nullptr
    //return created node
    return curr;
}

/**
 * TODO - Shorthand for add_node.
*/
Node* Dictionary::operator+=(const char* key){
    return add_node(key);
}

/**
 * TODO - Removes all nodes starting with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer const char* key (of course you should clean up the nodes that are removed).
*/
void Dictionary::remove_node(const char* key){
    if(*key=='\0')return;
    if(find_node(key)==nullptr)return;
    const char* search=key;
    Node* curr=root;
    int ptridx;
    for(;*search!='\0';search++){
        ptridx=character_to_index(*search);
        if(!(*curr)[ptridx])return;//no result found
        else{//move till all letters
            curr=(*curr)[ptridx];
        }
    }
    if(curr){
        curr->get_parent()->set_child(ptridx,nullptr);//set the words after to be null
        delete curr;//delete the nodes by default destructor
    }
}

/**
 * TODO - Shorthand for remove_node.
*/
void Dictionary::operator-=(const char* key){
    remove_node(key);
}

/**
 * TODO - Finds a node with the given key string, which is terminated with '\0'.
 * Returns nullptr if no such node is found.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::find_node(const char* key) const{
    if(*key=='\0')return root;
    Node* notetf=root;
    const char*search=key;
    for(;*search!='\0';search++){
        int ptridx=character_to_index(*search);
        if((*notetf)[ptridx])notetf=(*notetf)[ptridx];
        else{
            notetf=nullptr;
            break;
        }
    }
    return notetf;
}

/**
 * TODO - A function to do pre-order traversal on the tree. The function accepts a lambda function as argument,
 * and then the lambda function would be called for every node in the tree (except the root node). 
 * The lambda function accepts two arguments, (Node* current_node, vector<int>& current_key).
 * For each node accessed via pre-order traversal (except root node), call the lambda function.
 * 
 * Of course current_node should be the pointer to the node accessed. current_key should contain
 * a list of integers which corresponds to the indices required to travel to current_node from
 * the root node. For more explanation see the webpage.
 * 
 * The lambda is not supposed to change the dictionary.
*/
template<typename T> void recursive_traversal(Node*temproot,Node* root, vector<int>container, T&& f){
    if(temproot!=root)f(temproot, container);
    for(int i=0;i<26;i++){
        if((*temproot)[i]){
            vector<int>temp=container;
            temp.push_back(i);
            // for(auto i:temp)cout<<i<<" ";
            recursive_traversal((*temproot)[i],root,temp,f);
        }
    }
}
template<typename T> void Dictionary::foreach(T&& lambda) const{
    vector<int>temp;
    recursive_traversal(root, root, temp, lambda);
}
/**
 * TODO - Prints all the nodes in the dictionary, in depth first alphabetical order.
 * See the webpage description for more details.
*/
void Dictionary::print_all_elements(ostream& o) const{
    // cout << key_string_without_spaces << current_node << "[" << count << "]\n";
    int num=0;
    auto print_all=[&](Node* temproot, vector<int> container){
            string str;
            vector<int>::iterator it=container.begin();
            while(it!=container.end()){
                str+=index_to_character(*it);
                it++;
            }
            num++;
            // cout<<"meaning:"<<temproot->meaning.meaning;
            o<<str<<temproot<<"["<<num<<"]"<<endl;
        };
    foreach(print_all);
}


/**
 * TODO - Calls print_all_elements
*/
std::ostream& operator<<(std::ostream& o, const Dictionary& dict){
    dict.print_all_elements(o);
    return o;
}

/**
 * TODO - Prints all the words in the dictionary, such that the word type is equal to the given type,
 * in depth first alphabetical order. See the webpage description for more details.
*/
void Dictionary::print_elements_given_type(const char* type) const{
    int num=0;
    auto print_type=[&](Node* temproot, vector<int> container){
            string str;
            vector<int>::iterator it=container.begin();
            while(it!=container.end()){
                str+=(char)(*it+97);
                it++;
            }
            if(temproot->meaning.meaning[0]!='\0'){
                if(type==nullptr||temproot->meaning.type==type){
                num++;
                cout<<str<<temproot<<"["<<num<<"]"<<endl;
                }
            }
        };
    foreach(print_type);
}

/**
 * TODO - Merges with another dictionary. Creates a new dictionary,
 * and does not modify the contents of the original dictionaries.
 * For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
Dictionary Dictionary::merge(const Dictionary& d2) const{
    Dictionary d3= *this;//copy constructor
    auto merge=[&](Node* temproot, vector<int> container){
        string str;
        vector<int>::iterator it=container.begin();
        while(it!=container.end()){
            str+=(char)(*it+97);
            it++;
        }
        if(find_node(str.c_str())==nullptr){
            Node* nnode=d3+=str.c_str();
            copymeaning2(temproot,nnode);
        }
    };
    d2.foreach(merge);
    d3.set_name("");
    return d3;
}

/**
 * TODO - Merges with another dictionary. Moves the contents of d2
 * into a new dictionary. For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
Dictionary Dictionary::merge(Dictionary&& d2) const{
    //move d2 to d3
    Dictionary&&d3=move(d2);
    //deep copy *this to d3
    auto move=[&](Node* temproot, vector<int> container){
        string str;
        vector<int>::iterator it=container.begin()+1;
        while(it!=container.end()){
            str+=index_to_character(*it);
            it++;
        }
        if(find_node(str.c_str())==nullptr){
            Node* nnode=d3+=str.c_str();
            copymeaning2(temproot,nnode);
        }
    };
    d3.foreach(move);
    d3.set_name("");
    return d3;
}

/**
 * TODO - Creates a new dictionary, consisting only of the words
 * starting with the given key.
*/
Dictionary Dictionary::filter_starting_word(const char* key) const{
    Dictionary d3("");
    if(key==nullptr)return *this;
    if(this->find_node(key)){
        Node* d3rt=d3+=key;
        relink(d3rt,find_node(key));
    }
    return d3;
}

Dictionary Dictionary::operator+(const Dictionary& d2) const{
    return merge(d2);
}

Dictionary Dictionary::operator+(Dictionary&& d2) const{
    return merge(move(d2));
}