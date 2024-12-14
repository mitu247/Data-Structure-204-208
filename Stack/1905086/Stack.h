#ifndef STACK_H
#define STACK_H
template<typename T> class Stack{
    private:
     void operator = (const Stack&){}
     Stack(const Stack&){}
     public:
     Stack(){}
     virtual ~Stack(){}
     virtual void clear() = 0;
     virtual void push(T& item) = 0;
     virtual T pop() = 0;
     virtual int length() = 0;
     virtual T topValue() = 0;
};
#endif