#ifndef ABSTRACT_LIST
#define ABSTRACT_LIST
template<typename T> class List
{
private:
void operator=(const List&){}
    List(const List&){}
    /* data */
public:
    List(/* args */){};
    ~List(){};
    virtual void clear()=0;
    virtual void insert(const T& item)=0;
    virtual void append(const T& item)=0;
    virtual T remove()=0;
    virtual void moveToStart()=0;
    virtual void moveToEnd()=0;
    virtual void prev()=0;
    virtual void next()=0;
    virtual int length()=0;
    virtual int currPos()=0;
    virtual void moveToPos(int pos)=0;
    virtual T getValue()=0;
    virtual int Search(const T& item)=0;
};
#endif
