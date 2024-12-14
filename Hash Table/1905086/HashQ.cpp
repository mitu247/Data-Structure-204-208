#include<bits/stdc++.h>
using namespace std;
struct h1_node{
    string key;
    int value;
};
class HashQP{
private:
    int capacity;
    h1_node* table;
    int cnt;
    h1_node dummy;
public:
    HashQP(int n){
       this->capacity = n;
       cnt = 0;
       table = new h1_node[capacity];
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
    void insertQP(string item, int n){
        h1_node temp;
        temp.key = item;
        temp.value = n;
        int index,idx;
        index = idx = hashCode1(item);
        int i = 0;
        while(table[index].value != -1 && table[index].value != -2){
            i++;
            int k = 2*i+3*i*i;
            index = (idx+k)%capacity;
        }
        if(table[index].value == -1 || table[index].value == -2 ||table[index].key == "")
           cnt++;
           table[index] = temp;

    }
    void delete_node(string item){
        int index,idx;
        index = idx = hashCode1(item);
        int i = 0;
        while(table[index].key != "" && table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                table[index] = dummy;
                cnt--;
                break;
            }
            i++;
            int k = 2*i+3*i*i;
            index = (idx+k)%capacity;
        }
        ///cout<<i<<endl; count probing
    }
    int get(string item){
        int index,idx;
        index = idx = hashCode1(item);
        int i = 0;
        while(table[index].key != "" && table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                return i;
            }
            i++;
            int k = 2*i+3*i*i;
            index = (idx+k)%capacity;
        }
       return i;
    }
};
