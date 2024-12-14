// #ifndef Arr_H
// #define Arr_H
#include "List.h"
template <typename T>
class Arr : public List<T>
{
private:
    int arraySize;
    int listSize;
    int maxSize;
    int currentPos;
    T *arrayList;

public:
    Arr()
    {
        this->currentPos = 0;
        this->arraySize = 20;
        this->maxSize = 20;
        this->listSize = 0;
        arrayList = new T[maxSize];
    }
    Arr(const T *arr, int listSize = 0, int size = 20)
    {
        arraySize = maxSize = size;
        currentPos = 0;
        arrayList = new T[arraySize];
        this->listSize = listSize;
        for (int i = 0; i < listSize; i++)
        {
            arrayList[i] = arr[i];
        }
    }
    ~Arr()
    {
        delete[] arrayList;
    }
    void clear()
    {
        if (listSize == 0)
            return;
        delete[] arrayList;
        listSize = currentPos = 0;
        arrayList = new T[arraySize];
    }
    void insert(const T &item)
    {
        if (listSize + 1 > maxSize)
        {
            maxSize += arraySize;
            T *temp = new T[maxSize];
            for (int i = 0; i < listSize; i++)
            {
                temp[i] = arrayList[i];
            }
            delete [] arrayList;
            arrayList = temp;
        }
        for (int i = listSize; i > currentPos; i--)
        {
            arrayList[i] = arrayList[i - 1];
        }
        arrayList[currentPos] = item;
        listSize++;
    }
    void append(const T &item)
    {
        if (listSize + 1 > maxSize)
        {
            maxSize += arraySize;
            T *temp = new T[maxSize];
            for (int i = 0; i < listSize; i++)
            {
                temp[i] = arrayList[i];
            }
            delete [] arrayList;
            arrayList = temp;
        }
        arrayList[listSize++] = item;
    }
    T remove()
    {
        if(currentPos<0) return -1;
        T item = arrayList[currentPos];
        for (int i = currentPos; i < listSize - 1; i++)
        {
            arrayList[i] = arrayList[i + 1];
        }
        if (currentPos == listSize - 1)
        {
            currentPos--;
        }
        listSize--;
        return item;
    }
    void moveToStart()
    {
        currentPos = 0;
    }
    void moveToEnd()
    {
        currentPos = listSize - 1;
    }
    void prev()
    {
        if (currentPos != 0)
            currentPos--;
    }
    void next()
    {
        if (currentPos < listSize - 1)
            currentPos++;
    }
    int length()
    {
        return listSize;
    }
    int currPos()
    {
        return currentPos;
    }
    void moveToPos(int pos)
    {
        if (pos >= 0 && pos <= listSize - 1)
            currentPos = pos;
    }
    T getValue()
    {
        if (currentPos < 0 && currentPos >= listSize)
            return -1;
        return arrayList[currentPos];
    }
    int Search(const T &item)
    {
        int found = -1;
        for (int i = 0; i < listSize; i++)
        {
            if (arrayList[i] == item)
            {
                found = i;
                break;
            }
        }

        return found;
    }
};
// #endif