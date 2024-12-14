#include "Queue.h"
#include <cstddef>
template <typename E>
class Link
{
public:
    E element;
    Link *next;
    Link(E& element, Link* next = NULL)
    {
        this->element = element;
        this->next = next;
    }
    Link(Link *next = NULL)
    {
        this->next = next;
    }
};
template <typename T>
class LL : public Queue<T>
{
private:
    Link<T>* front;
    Link<T>* rear;
    int size;

public:
    LL(int size=10){
        front = rear = new Link<T>();
        this->size = 0;
    }
    ~LL(){
        while (front->next != NULL)
         {
             rear = front;
             front = front->next;
             delete rear;
         }
         delete front;
    }
     void clear(){
         while (front->next != NULL)
         {
             rear = front;
             front = front->next;
             delete rear;
         }
         rear = front;
         size = 0;
     }
     void enqueue(T& item){ 
         rear->next = new Link<T>(item, NULL);
         rear = rear->next;
         size++;
     }
     T dequeue(){
         if(size){
             T item = front->next->element;
             Link<T>* temp = front->next;
             front->next = temp->next;
             if(rear == temp) rear = front;
             delete temp;
             size--;
             return item;
         }  
     }
     T& frontValue(){
         if(size){
             return front->next->element;
         }
     }
     T& rearValue(){
         if(size){
             return rear->element;
         }
     }
     int length(){
         return size;
     }
     T leaveQueue(){
         if(size){
         T item = rear->element; 
         Link<T>* temp = front;
         while(temp->next != rear){
         temp = temp->next; 
         }
         temp->next = NULL;
         delete rear;
         rear = temp;
         size--;
         return item;
         }
     }
};