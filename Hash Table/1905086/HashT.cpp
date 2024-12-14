#include<bits/stdc++.h>
#include "HLL.cpp"
using namespace std;
class Hash{
private:
    int capacity;
    linked_list* table;
public:
    Hash(int size){
        this->capacity = size;
        table = new linked_list[capacity];
    }
    ///separate chaining insert
    void Insert(string key, int value){
        int index = hashCode1(key);
        table[index].append(key,value);
    }
    ///separate chaining delete
    void Delete(string key){
        int index = hashCode1(key);
        table[index].deleteNode(key);
    }
    /// separate chaining search
    bool search(string key){
        int index = hashCode1(key);
        if(table[index].Search(key) != -1) return true;
        else return false;
    }
    /// separate chaining print
    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            linked_list x = table[i];
            x.print();
        }
    }
    int hashCode1(string s)
    {
        unsigned int h = 0;
        for (int i = 0; i < s.size(); i++)
        {
            h = (h << 5) | (h >> 27);
            h += (unsigned int) s.at(i);
        }
        // long long x = 3*h + 7;
        return h%capacity;
    }
    int hashCode2(string s){
    int sum = 0;
        for (int i = 0; i < s.size(); i++)
            sum = sum + int(s[i]);
        return  sum%capacity;
    }
};
