#include <iostream> /* File: ll_cnode.h */
using namespace std;

struct ll_cnode
{
    char data;          // Contains useful information
    ll_cnode* next;     // The link to the next node
};

const char NULL_CHAR = '\0';
ll_cnode* ll_create(char);
ll_cnode* ll_create(const char []);
int ll_length(const ll_cnode*);
void ll_print(const ll_cnode*);
const ll_cnode* ll_search(const ll_cnode*, char c);
void ll_insert(ll_cnode*&, char, unsigned);
void ll_delete(ll_cnode*&, char);
void ll_delete_all(ll_cnode*&);
