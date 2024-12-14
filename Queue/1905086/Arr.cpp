#include "Queue.h"
template <typename T>
class Arr : public Queue<T>
{
private:
    int maxSize;
    int front;
    int rear;
    T *queArray;

public:
    Arr(int size = 10)
    {
        maxSize = size + 1;
        rear = 0;
        front = 1;
        queArray = new T[maxSize];
    }
    Arr(T *arr, int size = 10)
    {
        rear = size-1;
        front = 1;
        queArray = arr;
        this->maxSize = size;
    }
    ~Arr()
    {
        delete[] queArray;
    }
    void clear()
    {
        rear = 0;
        front = 1;
        delete[] queArray;
        queArray = new T[maxSize];
    }
     void enqueue(T& item) {
         if(((rear+2)%maxSize) == front){
             int size = 2*(maxSize-1)+1;
             T* temp = new T[size];
             int pos = front;
             int saveFront =front;
             while(length()!=0){
                 temp[pos++] = dequeue(); 
             }
             delete [] queArray;
             maxSize = size;
             rear = pos-1;
             front = saveFront;
             queArray = temp; 
         }
         rear = (rear+1)%maxSize;
         queArray[rear] = item;
     }
     T dequeue() {
         if(length() != 0){
             T item = queArray[front];
             front = (front+1)%maxSize;
             return item;
         }
     }
     T& frontValue() {
        if(length() != 0){
            return queArray[front];
        } 
     }
     T& rearValue(){
         if(length() != 0){
             return queArray[rear];
         }
     }
     int length(){
         return ((rear+maxSize)-front+1)%maxSize;
     }
     T leaveQueue(){
        if(length() != 0){
         T item = queArray[rear];
         rear = (maxSize+rear-1) % maxSize;
         return item;
        }       
     }
};