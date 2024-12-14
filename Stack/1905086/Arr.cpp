#include "Stack.h"

template <typename T>
class Arr : public Stack<T>
{
    int maxSize;
    int top; // The index of the top element
    T *stackArray;
    int dir;

public:
    Arr(int initSize=10)
    {
        dir = 1;
        this->maxSize = initSize;
        stackArray = new T[maxSize];
        top = 0;
    }
    Arr(T *arr, int size = 10, int dir=1)
    {
        if(dir == 1){
            top = 0;
        }
        else if(dir == -1){
            top = size-1;
        }
        stackArray = arr;
        this->maxSize = size;
        this->dir = dir;
    }
    ~Arr() { 
        delete [] stackArray; 
    } // Destructor
    void clear()
    {
        delete[] stackArray;
        if (dir == 1) top = 0;
        else if (dir == -1) {
            top = maxSize - 1;
        }
        stackArray = new T[maxSize];
    }
    void push(T &item)
    {
        if (dir == 1)
        {
            if (top == maxSize)
            {
                maxSize = maxSize*2;
                T *temp = new T[maxSize];
                for (int i = 0; i < top; i++)
                {
                    temp[i] = stackArray[i];
                }
                delete [] stackArray;
                stackArray = temp;
            }
            stackArray[top++] = item; // top moves forward to one slot
        }
        else if (dir == -1) {
            if (top == -1) {
                top = maxSize-1;
                // doubling the size of the stackArray
                maxSize *= 2;
                T *temp = new T[maxSize];
                int cnt = 0; // counter for the new array
                for (int i=top+1; i<maxSize; i++) {
                    temp[i] = stackArray[cnt++];
                }
                delete [] stackArray;
                stackArray = temp;
            }
            stackArray[top--] = item;
        }
    }
    T pop()
    {
        if (dir == 1) {
            if (top > 0) return stackArray[--top];
        }
        else if (dir == -1) {
            if (top < maxSize) return stackArray[++top];
        }
        return stackArray[-1];
    }

    int length()
    {
        if (dir == 1) return top;
        else if (dir == -1) {
            return (maxSize-top-1);
        }
    }

    T topValue()
    {
        if (dir == 1) {
            if (top > 0) return stackArray[top-1];
        }
        else if (dir == -1) {
            if (top < maxSize) return stackArray[top+1];
        }
        return stackArray[-1];
    }
    void setDirection(int dir) {
        this->dir = dir;
        if (dir == -1) {
            top = maxSize-1;
        }
    }
};