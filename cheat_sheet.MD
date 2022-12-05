##### Comp2012H Cheat sheet
$Assignment\space operator:$
1. Check if the object is same, if same then return
2. delete all current members (linked list need for loop)
3. memberwise copy all members from copy object
4. delete allocated heap spaces
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

BST functions
```C++
template <class T>
void btree_preorder(BTnode<T>* root, void (*action)(BTnode<T>* r)){ // Expect a function on r->data
    if (root){
        action(root);              // e.g. print out root->data
        btree_preorder(root->get_left(), action); //inorder here
        btree_preorder(root->get_right(), action);//postorder here
    }}
template <typename T>           /* File: bst-remove.cpp */
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
    }}
template <typename T>               /* File: bst-print.cpp */
void BST<T>::print(int depth) const{
    if (is_empty())return;          // Base case
    root->right.print(depth+1);     // Recursion: right sub-tree
    for (int j = 0; j < depth; j++) // Print the node value
        cout << '\t';
    cout << root->value << endl;
    root->left.print(depth+1);      // Recursion: left sub-tree
}
template <typename T>          /* File: bst-insert.cpp */
void BST<T>::insert(const T& x){
    if (is_empty())            // Find the spot
        root = new BSTnode(x);
    else if (x < root->value)
        root->left.insert(x);  // Recursion on the left sub-tree
    else if (x > root->value)
        root->right.insert(x); // Recursion on the right sub-tree
}
```