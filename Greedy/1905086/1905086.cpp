#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k;
    int arr[101];
    cin>>n>>k;
    for(int i = 0; i < n; i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    int temp[101],j = 1,p = k;
    for(int i = n-1; i >= 0; i--){
        if(p>0){
            temp[i] = j;
            p--;
        }
        else{
            j++;
            temp[i] = j;
            p=k-1;
        }
    }
    long long sum = 0;
    for(int i = 0;i< n;i++){
         sum += temp[i]*arr[i];
    }
    cout<<sum<<endl;
    return 0;
}
