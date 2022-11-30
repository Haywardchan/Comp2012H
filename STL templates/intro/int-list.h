class Int_Node /* File: int-list.h */
{
  public:
    Int_Node* get_prev();
    Int_Node* get_next();
  private:
    int data;
    Int_Node* prev;
    Int_Node* next;
};
    
class Int_List
{
  public:
    int size() const;
    int get_current() const { return current->data; }
    int set_first() { current = head; ... }
    int set_next() { current = current->next(); ... }
    int set_prev() { current = current->prev(); ... }
  private:
    int size;
    Int_Node* head;
    Int_Node* current;
};

    
    
