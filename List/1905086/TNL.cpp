#include <iostream>
#include <string>
#include <cstdlib>
#include "Arr.cpp"
#include "LL.cpp"
using namespace std;

template <template <typename> class M, typename T>
void printTNL(M<T> &rStops, M<T> &list, int max)
{
    int i, n;
    list.moveToStart(); 
    for (i = 0; i < max - 1; i++){
        n = rStops.Search(list.getValue());
        if (i == n){
            cout << list.getValue() << ",";
            list.next();
        }
        else{
            cout << ",";
        }
    }
    n = rStops.Search(list.getValue());
    if (i == n){
        cout << list.getValue() << endl;
    }
    else{
        cout << "," << endl;
    }
}
int main()
{
    int K, L, M, T = -1;
    cin >> K >> L;
    int* rStop = new int[K];
    for(int i=0;i<K;i++) rStop[i]=i;
    Arr<int>rList(rStop,K);
    int* bStop = new int[L];
    for(int i=0;i<L;i++){
        cin>>bStop[i];
    }
    Arr<int>bList(bStop,L);
    cin>>M;
    int *tStop = new int[M];
    for(int i=0;i<M;i++){
        cin>>tStop[i];
    }
    Arr<int>tList(tStop,M);
     tList.moveToPos(2);
     tList.insert(9);

    cin >> T;
    if (T == 1)
    {
        printTNL(rList, rList, K);
        printTNL(rList, bList, K);
        printTNL(rList, tList, K);
    }

    return 0;
}