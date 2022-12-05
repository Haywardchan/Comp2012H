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
1. traversal
```C++
template <class T>
void btree_preorder(BTnode<T>* root,
     void (*action)(BTnode<T>* r)) // Expect a function on r->data
{
    if (root)
    {
        action(root);              // e.g. print out root->data
        btree_preorder(root->get_left(), action); //inorder here
        btree_preorder(root->get_right(), action);//postorder here
    }
}
```
2. 