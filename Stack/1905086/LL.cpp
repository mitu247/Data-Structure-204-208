#include "Stack.h"
template<typename E> class Link{
    public:
    E element;
    Link *next;
    Link(E& element, Link* next = NULL){
        this->element = element;
        this->next = next;
    }
    Link(Link* next = NULL){
        this->next = next;
    }
};
template<typename T>
class LL: public Stack<T>{
    private:
    Link<T> *top;
    int size;
    public:
    LL(){
        top = NULL;
        size = 0;
    }
    ~LL(){
          while(top!=NULL){
              Link<T>* temp = top;
              top = top->next;
              delete temp;
          }
    }
      void clear() {
          while(top!=NULL){
              Link<T>* temp = top;
              top = top->next;
              delete temp;
          }
          size = 0;
      }
      void push(T& item) {  
          top = new Link<T>(item, top);
          size++;
      }
      T pop() {
          if(top != NULL && size>0){
          T item = top->element;
          Link<T>* temp = top->next;
          delete top;
          top = temp;
          size--;
          return item;
          }
      }
      int length() {
          return size;
      }
      T topValue() {
          if(top!=NULL){
              return top->element;
          }
      }
};