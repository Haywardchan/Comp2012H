##### Comp2012H Cheat sheet
$Assignment\space operator:$
1. Check if the object is same, if same then return
2. delete all current members (linked list need for loop)
3. memberwise copy all members from copy object
4. delete allocated heap spaces (if have)
5. return *this

$[\space]\space operator:$
1. check if index within the range
2. return required index in the list/ array
3. exit(-1)

$Copy\space Constructor:$
1. check if empty do nth
2. assign all members to this
3. use assignment operator

$+= operator:$
1. check if size of the list is full
    1. If full then extend the size to required size
    2. create new heap space 
    3. copy back original list to new heap array
    4. delete the original array
    5. set back the pointer to new heap space
2. assign the adding object to corresponding index and add index size by 1.

$>>operator$
1. consider adding as friend to access private members
2. print the whole stuff using os  
3. return the ouput stream os

{ } narrowed conversions

constexpr: only 1 return statement, non-void, refer only constant variables, constexpr functions, non-virtual

lambdas [capture list **=/&/variables** ] (parameter list) **mutable** {body} _(input variable)_ //mutable to allow changing value for = PBV
[&,a]: all are captured by reference except a is captured by value

explicit can be added to conversion operators to prevent implicit conversion

Unnamed objects: pointer held multidimensional dynamic array: 

int** ptr = new int* [size]; for(int j = 0;j < col; j++) ptr[j] = new int [size];

rvalue reference is alias of temp obj: const ref init, argument passing, function return value, evaluation of expr

must have to be inited, cannot be binded to lvalue
const& cannot be modified and can take almost any arguments, && can be modified but can only hold temp objects

$move\space constructor$ Word(Word&& w) : freq(w.freq), str(w.str){set default}

$move\space assignment$ memberwise copy->assignment using move constructor

explicit generation: =default/ =delete (not)

public: accessible for any functions (only this can cast derived obj to base, is-a relationship)

protected: member functions and friends including derived classes (less data encapsulation) (protected inheritence turns public to protected) 

private: accessible only to member functions and friends (private inheritence keeps all private) (has-a relationship)

DON'T expose data items inclass, difference between stored and derived data, internal class structures, class implementation details

outside class body, inline is mandatory with the scope operator ::

non-const function cannot take literal constant, and const object

MIL remember follow data member sequences parents->data member->itself

assignment from derived class to base class results in slicing

pointer/ reference must be used to take advantages of polymorphism (dynamic_cast() called RTTI, pointer to obj else return nullptr, slower than static_cast())

RTTI: typeid(expr) return an object of the type type_info which is the typename of the expr

virtual double function() const = 0 //ABC derived class must also implement pure virtual functions else become ABC as well

final have no offspring
BST functions
```C++
template <class T>
void btree_preorder(BTnode<T>* root, void (*action)(BTnode<T>* r)){ // Expect a function on r->data
    if (root){
        action(root);              // e.g. print out root->data
        btree_preorder(root->get_left(), action); //inorder here
        btree_preorder(root->get_right(), action);//postorder here
}}template <typename T>           /* File: bst-remove.cpp */
void BST<T>::remove(const T& x){ // leftmost item of its right subtree
    if (is_empty())             // Item is not found; do nothing
        return;
    if (x < root->value)        // Remove from the left subtree
        root->left.remove(x);
    else if (x > root->value)   // Remove from the right subtree
        root->right.remove(x);
    else if (root->left.root && root->right.root){ // Found node has 2 children
        root->value = root->right.find_min(); // operator= defined?
        root->right.remove(root->value); // min is copied; can be deleted now 
    }else{                        // Found node has 0 or 1 child
        BSTnode* deleting_node = root; // Save the root to delete first
        root = (root->left.is_empty()) ? root->right.root : root->left.root;
        // Set subtrees to nullptr before removal due to recursive destructor
        deleting_node->left.root = deleting_node->right.root = nullptr;
        delete deleting_node;
}}template <typename T>               /* File: bst-print.cpp */
void BST<T>::print(int depth) const{
    if (is_empty())return;          // Base case
    root->right.print(depth+1);     // Recursion: right sub-tree
    for (int j = 0; j < depth; j++) // Print the node value
        cout << '\t';
    cout << root->value << endl;
    root->left.print(depth+1);      // Recursion: left sub-tree
}template <typename T>          /* File: bst-insert.cpp */
void BST<T>::insert(const T& x){
    if (is_empty())            // Find the spot
        root = new BSTnode(x);
    else if (x < root->value)
        root->left.insert(x);  // Recursion on the left sub-tree
    else if (x > root->value)
        root->right.insert(x); // Recursion on the right sub-tree
}template <typename T>   /* File: bst-find-min.cpp */
const T& BST<T>::find_min() const{
    const BSTnode* node = root;
    while (!node->left.is_empty()) // Look for the leftmost node
        node = node->left.root;//right.root for find_max
    return node->value;
}template <typename T>         /* File: bst-contains.cpp */
bool BST<T>::contains(const T& x) const{
    if (is_empty())return false;            // Base case #1
    if (root->value == x)return true;       // Base case #2
    else if (x < root->value) return root->left.contains(x);// Recursion on the left sub-tree
    else return root->right.contains(x);// Recursion on the right sub-tree
}AVL://return left_subtree().contains(x);return left_subtree().contains(x);
```
AVL functions
```C++
template <typename T>
void AVL<T>::balance(){
    if (is_empty())return;
    fix_height();
    int balance_factor = bfactor();
    if (balance_factor == 2){       // Right subtree is taller by 2
        if (right_subtree().bfactor() < 0) // Case 4: insertion to the L of RT
            right_subtree().rotate_right();
        return rotate_left();}      // Cases 1 or 4: Insertion to the R/L of RT
    else if (balance_factor == -2){ // Left subtree is    taller by 2
        if (left_subtree().bfactor() > 0) // Case 3: insertion to the R of LT
            left_subtree().rotate_left();
        return rotate_right();}     // Cases 2 or 3: insertion to the L/R of LT
}template <typename T>
int AVL<T>::bfactor() const{
    return is_empty() ? 0 : right_subtree().height() - left_subtree().height();
}template <typename T>
const T& AVL<T>::find_min() const{// It is assumed that the calling tree is not empty
    const AVL& left_avl = left_subtree();
    if (left_avl.is_empty())    // Base case: Found!
        return root->value;
    return left_avl.find_min(); // Recursion on the left subtree
}int AVL<T>::height() const { return is_empty() ? -1 : root->height; }
template <typename T>
void AVL<T>::insert(const T& x){
    if (is_empty())root = new AVLnode(x);//base case
    else if (x < root->value)left_subtree().insert(x);  // Recursion on the left sub-tree
    else if (x > root->value)right_subtree().insert(x); // Recursion on the left sub-tree
    balance(); // Re-balance the tree at every visited node
}template <typename T>
void AVL<T>::remove(const T& x)
{
    if (is_empty()) return;               // Item is not found; do nothing
    if (x < root->value) left_subtree().remove(x);  // Recursion on the left sub-tree
    else if (x > root->value) right_subtree().remove(x); // Recursion on the right sub-tree
    else{
        AVL& left_avl = left_subtree();
        AVL& right_avl = right_subtree();
        // Found node has 2 children 
        if (!left_avl.is_empty() && !right_avl.is_empty()){
            root->value = right_avl.find_min(); // Copy the min value
            right_avl.remove(root->value); // Remove node with min value
        }
        else{  // Found node has 0 or 1 child
            AVLnode* node_to_remove = root; // Save the node first
            *this = left_avl.is_empty() ? right_avl : left_avl;
            // Reset the node to be removed with empty children
            right_avl.root = left_avl.root = nullptr;
            delete node_to_remove;
        }}
    balance(); // Re-balance the tree at every visited node
}template <typename T> (LR/RL: double rotation)
void AVL<T>::rotate_left(){ // The calling AVL node is node a
    AVLnode* b = right_subtree().root; // Points to node b
    right_subtree() = b->left;
    b->left = *this;    // Note: *this is node a
    fix_height();       // Fix the height of node a
    this->root = b;     // Node b becomes the new root
    fix_height();       // Fix the height of node b, now the new root
}//rotate right is replacing right with left.
```
