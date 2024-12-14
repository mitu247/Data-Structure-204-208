#include<bits/stdc++.h>
using namespace std;
struct h2_node{
    string key;
    int value;
};
class HashDH{
private:
    int capacity;
    h2_node* table;
    int cnt;
    int PRIME;
    h2_node dummy;
    bitset<100000> isPrime;
public:
    HashDH(int n){
       this->capacity = n;
       cnt = 0;
       table = new h2_node[capacity];
       for(int i = 0; i<capacity; i++){
        table[i].key = "";
        table[i].value = -1;
       }
       dummy.key = "";
       dummy.value = -2;
       setSieve(n);
       PRIME = n-1;
       while(isPrime[PRIME] == 1)
       PRIME--;
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
    void setSieve(int sz){
            isPrime[0] = isPrime[1] = 1;
            for(long long i = 2; i*i <= sz; i++)
                if(isPrime[i] == 0) {
                    for(long long j = i*i; j <= sz; j += i)
                        isPrime[j] = 1;
                }
        }
    int hashCode2(string s){
        unsigned int h = 0;
        for (int i = 0; i < s.size(); i++)
        {
            h = (h << 5) | (h >> 27);
            h += (unsigned int) s.at(i);
        }
        return  PRIME-(h%PRIME);
    }
    void insertDH(string item, int n){
        h2_node temp;
        temp.key = item;
        temp.value = n;
        int index,idx,idx1;
        index = idx = hashCode1(item);
        idx1 = hashCode2(item);
        int i = 0;
        while(table[index].value != -1 && table[index].value != -2){
           i++;
           index = (idx+i*idx1)%capacity;
        }
        if(table[index].value == -1 || table[index].value == -2 ||table[index].key == "")
           cnt++;
            table[index] = temp;

    }
    void delete_node(string item){
        int index,idx,idx1;
        index = idx = hashCode1(item);
        idx1 = hashCode2(item);
        int i = 0;
        while(table[index].key != ""&& table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                table[index] = dummy;
                cnt--;
                break;
            }
            i++;
            index = (idx+i*idx1)%capacity;
        }
        ///cout<<i<<endl; count probing
    }
    int get(string item){
        int index,idx,idx1;
        index = idx = hashCode1(item);
        idx1 = hashCode2(item);
        int i = 0;
        while(table[index].key != "" && table[index].value!=-1 && i<=capacity){
            if(table[index].key == item){
                return i;
            }
            i++;
            index = (idx+i*idx1)%capacity;
        }
       return i;
    }
};
