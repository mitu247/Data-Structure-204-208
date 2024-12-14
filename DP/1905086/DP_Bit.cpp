#include<bits/stdc++.h>
using namespace std;
int n;
int arr[10][10];
int dp_array[1<<10][10];

int addCost(int i, int mask)
{
    int sum = 0;
    for (int j=0; j<n; j++) {
        if (mask & (1<<j)) {
            sum += arr[i][j];
        }
    }
    return sum;
}

int optimal_cost(int mask,int position){
    if(mask == (1<<n)-1){
        return 0;
    }

    if(dp_array[mask][position] != -1){
        return dp_array[mask][position];
    }
    int ans = INT_MAX;
    for(int i = 0;i < n;i++){
        if((mask&(1 << i)) == 0){
                int newans = arr[i][i] + addCost(i, mask) + optimal_cost((mask|(1<<i)),i);
                ans = min(ans, newans);
            }
    }
    dp_array[mask][position] = ans;
    return ans;
}

int main(){
    cin>>n;
    for(int i = 0;i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>arr[i][j];
        }
    }
    for(int i = 0;i < (1<<n); i++){
        for(int j = 0;j<n;j++){
           dp_array[i][j] = -1;
        }
    }
    int value1 = optimal_cost(0,0);
    cout<< value1 <<endl;
    return 0;
}
