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
bool __copyNode(Node* me, Node* tar) { // uses 26 * (root + no. of children) accesses
    bool haveWord = false;
    for (int i = 0; i < 26; i++) {
        Node* copyNode = (*tar)[i]; 
        if (copyNode) { // if it is not a nullptr, then copy it
            Node* child = new Node;
            me->set_child(i, child);
            child->get_parent() = me;
            bool res = __copyNode(child, copyNode);
            haveWord = haveWord || res;
        } // else, it is a nullptr (default value)
    }    
    me->meaning = tar->meaning;
    if (me->meaning.meaning[0] != '\0') haveWord = true;
    return haveWord;
}

Dictionary::Dictionary(const Dictionary& d){

    root = new Node;

    __copyNode(root, d.root);

}

/**
 * TODO - Assignment operator for deep copy of dictionary.
*/
void __deleteNode(Node* me) { // action must be done post-order
    // if (me) {
    //     for (int i = 0; i < 26; i++) {
    //         cout << Dictionary::index_to_character(i) << endl;
    //         Node* delNode = (*me)[i];
    //         __deleteNode(delNode);
    //     }
    //     cout << "finished" << endl;
    //     cout << me << endl;
    //     delete me;
    // }
    delete me; // Node's destructor already does it for you
}

Dictionary& Dictionary::operator=(const Dictionary& d){
    __deleteNode(root);
    // cout << "Hey f inished" << endl;
    root = new Node;
    // cout << "Hey not f inished" << endl;
    __copyNode(root, d.root);
    // cout << "Hey finished this la" << endl;
    return *this;
}

/**
 * TODO - Adds a node with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::add_node(const char* key){
    if (key[0] == '\0') return root;

    const char* ptr = key;
    Node* curNode = root;
    bool nodesExist = true;
    Node* nextNode;
    while (*ptr != '\0') {
        int index = character_to_index(*ptr);
        // cout << *ptr;
        if (index < 0 || index >= 26) // just my own testing stuff
            throw runtime_error("error in add_node: key is not lowercase letter");
        nextNode = (*curNode)[index];
        // if (nextNode == nullptr) cout << "nullptr\n";
        // else cout << nextNode << endl;
        if (nodesExist) {
            if (nextNode != nullptr) {
                curNode = nextNode; // node exists
            } else {
                nodesExist = false;
            }
        }
        if (!nodesExist) { // create the nodes
            nextNode = new Node;
            curNode->set_child(index, nextNode);
            nextNode->get_parent() = curNode;
            curNode = nextNode;
        }
        ptr++;
    }
    return curNode;
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
    if (key[0] == '\0') return;

    const char* ptr = key;
    Node* curNode = root;
    Node* nextNode;
    int index;
    while (*ptr != '\0') {
        index = character_to_index(*ptr);
        // cout << *ptr;
        nextNode = (*curNode)[index];
        if (nextNode) {
            curNode = nextNode;
        } else {
            return;
        }
        // if (nextNode == nullptr) cout << "nullptr\n";
        // else cout << nextNode << endl;
        // cout << (curNode == nextNode) << endl;
        ptr++;
    }

    if (curNode) {
        curNode->get_parent()->set_child(index, nullptr);
        __deleteNode(curNode);
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
    if (key[0] == '\0') return root;

    const char* search = key;
    Node* curr = root;
    Node* next;
    while (*search != '\0') {
        int index = character_to_index(*search);
        next = (*curr)[index];
        if (next) {
            curr = next;
        } else {
            return nullptr;
        }
        search++;
    }

    return curr;
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
template<typename T> void __preorderTraversal(vector<int> key, Node* node, T&& lambda) {
    if (key.size() > 1) {
        lambda(node, key);
    }
    for (int i = 0; i < 26; i++) {
        Node* child = (*node)[i];
        if (child) {
            vector<int> newKey = key;
            newKey.push_back(i);
            __preorderTraversal(newKey, child, lambda);
        }
    }
}

template<typename T> void Dictionary::foreach(T&& lambda) const{
    
    vector<int> temp;
    temp.push_back(0);
    __preorderTraversal(temp, root, lambda);
}

/**
 * TODO - Prints all the nodes in the dictionary, in depth first alphabetical order.
 * See the webpage description for more details.
*/
void Dictionary::print_all_elements(ostream& o) const{
    int count = 0;
    foreach([&count, &o](Node* node, vector<int> key){
        string word;
        for (vector<int>::const_iterator it = key.cbegin() + 1; it != key.cend(); it++) {
            word += Dictionary::index_to_character(*it);
        }
        o << word << node << "[" << ++count << "]\n";
    });
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
    int count = 0;
    foreach([&count, type](Node* node, vector<int> key){
        if (type) {
            if (node->meaning.type != type) return;
        }
        if (node->meaning.meaning[0] == '\0') return;
        string word;
        for (vector<int>::const_iterator it = key.cbegin() + 1; it != key.cend(); it++) {
            word += Dictionary::index_to_character(*it);
        }
        cout << word << node << "[" << ++count << "]\n";
    });
}

/**
 * TODO - Merges with another dictionary. Creates a new dictionary,
 * and does not modify the contents of the original dictionaries.
 * For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
Dictionary Dictionary::merge(const Dictionary& d2) const{
    /**
     * Algorithm:
     * 
     * first, copy d1 into the newDict
     * second, for each node in d2,
     * we add it to d1
     * if the meanings conflict
     * then we do not edit the new node
     * else, we will add the meaning in d2 to newDict
     * 
     * problem: add_node is expensive
     * solution: two pointers
     * 
     */
    Dictionary newDict = *this;
    d2.foreach([&](Node* node, vector<int> key) {
        // if (node->meaning.meaning[0] == '\0') return;
        string word;
        for (vector<int>::const_iterator it = key.cbegin() + 1; it != key.cend(); it++) {
            word += Dictionary::index_to_character(*it);
        }
        Node* newNode = newDict.add_node(word.c_str());
        if (newNode == d2.root) return;
        if (newNode->meaning.meaning[0] != '\0') return;
        newNode->meaning = node->meaning;
    });
    newDict.set_name("");
    return newDict;
}

/**
 * TODO - Merges with another dictionary. Moves the contents of d2
 * into a new dictionary. For words that exists in both dictionary,
 * use the word definition in the dictionary this.
*/
void __comparisonTraversal(Node* me, Node* tar) {
    
    if (tar->meaning.meaning[0] != '\0') {
        me->meaning = tar->meaning;
    }

    for (int i = 0; i < 26; i++) {
        Node* tarChild = (*tar)[i];
        if (tarChild) {
            Node* meChild = (*me)[i];
            if (meChild == nullptr) {
                meChild = new Node;
                meChild->get_parent() = me;
                me->set_child(i, meChild);
            }
            __comparisonTraversal(meChild, tarChild);
        }
    }
}

Dictionary Dictionary::merge(Dictionary&& d2) const{
    // cout << "i am moving" << endl;
    // int accessed = NodeStats::get_pointers_accessed();
    Dictionary&& newDict = move(d2);
    // cout << NodeStats::get_pointers_accessed() - accessed << endl;
    __comparisonTraversal(newDict.root, this->root);
    // cout << NodeStats::get_pointers_accessed() - accessed << endl;
    newDict.set_name("");
    return move(newDict); // returns by rvalue reference, good

}

/**
 * TODO - Creates a new dictionary, consisting only of the words
 * starting with the given key.
*/

Dictionary Dictionary::filter_starting_word(const char* key) const{
    Dictionary newDict("");
    if (key == nullptr || key[0] == '\0') {
        newDict = *this;
        return newDict;
    }

    Node* node = find_node(key);
    if (node) {
        Node* roots = newDict.add_node(key);
        if (__copyNode(roots, node)) {
            return newDict;
        }
    }
    return Dictionary("");

}

Dictionary Dictionary::operator+(const Dictionary& d2) const{
    return merge(d2);
}

Dictionary Dictionary::operator+(Dictionary&& d2) const{
    return merge(move(d2));
}