// #ifndef LL_H
// #define LL_H
#include "List.h"
template< typename E> 
class ListNode{
    public:
     E value;
     ListNode* next;
     ListNode(const E& value,ListNode* next = NULL){
         this->value = value;
         this->next = next;
     }
    ListNode(ListNode* next= NULL){
        this->next = next;
    }
};
template <typename T>
class LL: public List<T>{
    private:
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* current;
    int list_size;
    public:
    LL(){
        current = tail = head = new ListNode<T>;
    }
    LL(const T* arr,int list_size=0){
        current = tail = head = new ListNode<T>;
        this->list_size = list_size;
        ListNode<T>* temp = head;
        for(int i=0;i<list_size;i++){
           temp->next = new ListNode<T>(arr[i],NULL);
           temp=temp->next;
        }
        tail = temp;
        tail->next=NULL;
    }
    ~LL(){
        while(head!=NULL){
            current = head;
            head= head->next;
            delete current;
        }
    }
    void clear(){
        while(head!=NULL){
            current = head;
            head= head->next;
            delete current;
        }
        current = tail = head = new ListNode<T>;
        list_size = 0;
    }
    void insert(const T& item){
     current->next = new ListNode<T>(item,current->next);
     if(tail==current) tail = current->next;
     list_size++; 
    }
    void append(const T& item){
        tail=tail->next = new ListNode<T>(item,NULL);
        list_size++;
    }
    T remove(){
        //if(current->next==NULL)return;
        T item = current->next->value;
        ListNode<T>* temp = current->next;
        if(tail==current->next) tail=current;
        current->next= temp->next;
        list_size--;
        delete temp;
        
        return item;
    }
    void moveToStart(){
        current = head;
    }
    void moveToEnd(){
        ListNode<T> *temp = head;
        while (temp->next != tail)
        {
            temp = temp->next;
        }
       current = temp;      
    }
    void prev(){
        if(current==head)return;
        ListNode<T>* temp =head;
        while (temp->next!=current)
        {
            temp=temp->next;
        }
        current = temp;   
    }
    void next(){
       if(current->next!=tail)current = current->next; 
    }
    int length(){
        return list_size;
    }
    int currPos(){
        ListNode<T>* temp = head;
        int i=0;
        for( ;current!=temp;i++)temp=temp->next;
        
        return i;
    }
    void moveToPos(int pos){
        if(pos<0 && pos>= list_size)return;
        current=head;
        for (int i = 0; i < pos; i++)
        {
            current = current->next;
        }
    }
    T getValue(){
        if(current->next==NULL) return -1;
        return current->next->value;   
    }
    int Search(const T& item){
        int found =-1;
       ListNode<T>* temp = head;

       for(int i=0;temp!=tail;i++){
           temp = temp->next;
           if(temp->value==item){
               found=i;
               break;
           }
       }
       
       return found;   
    }

};
// #endif