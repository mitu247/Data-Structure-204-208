#include<bits/stdc++.h>
using namespace std;
struct h_node{
    string key;
    int value;
};
class HashLP{
private:
    int capacity;
    h_node* table;
    int cnt;
    h_node dummy;
public:
    HashLP(int n){
       this->capacity = n;
       cnt = 0;
       table = new h_node[capacity];
       for(int i = 0; i<capacity; i++){
        table[i].key = "";
        table[i].value = -1;
       }
       dummy.key = "";
       dummy.value = -2;
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
    void insertLP(string item, int n){
        h_node temp;
        temp.key = item;
        temp.value = n;
        int index = hashCode1(item);
        while(table[index].value != -1 && table[index].value != -2){
            index++;
            index %=capacity;
        }
        if(table[index].value == -1 || table[index].value == -2 ||table[index].key == "")
           cnt++;
           table[index] = temp;

    }
    void delete_node(string item){
        int index = hashCode1(item);
        int i = 0;
        while(table[index].key != "" && table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                table[index] = dummy;
                cnt--;
                break;
            }
            index++;
            index %=capacity;
            i++;
        }
        ///cout<<i<<endl; count probing
    }
    int get(string item){
        int index = hashCode1(item);
        int i = 0;
        while(table[index].key != "" && table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                return i;
            }
            i++;
            index++;
            index %=capacity;
        }
       return i;
    }
};
