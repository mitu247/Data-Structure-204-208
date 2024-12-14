#include<bits/stdc++.h>
#define N 101
#define INF INT_MAX
using namespace std;
vector<vector<int>>dist(N,vector<int>(N,INF));
vector<vector<int>>graph(N,vector<int>(N,INF));
vector<vector<int>> matrix_muls(vector<vector<int>>&temp,int n){
    for(int i = 1;  i<=n; i++){
        for(int j = 1; j<=n; j++){
            int sum = dist[i][j];
            for(int k = 1; k<=n; k++){
                if(temp[i][k]!=INF && temp[k][j]!=INF){
                    sum = min(sum,temp[i][k]+temp[k][j]);
                }
            }
            dist[i][j] = sum;
        }
    }
    return dist;
}
void APSP(int n){
   vector<vector<int>> temp(N);
   temp = graph;
   for(int i = 2; i<=n-1; i++){
    temp = matrix_muls(temp,n);
   }
}
int main(){
    int n,m,u,v,w;
    //fstream cin("mat.txt");
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        cin>>u>>v>>w;
        graph[u][v] = w;
        dist[u][v] = w;
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(i==j) {
                dist[i][j] = 0;
                graph[i][j] = 0;
            }
        }
    }
    APSP(n);
    cout<<"Shortest distance matrix :"<<endl;
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(dist[i][j]==INF)
                cout<<"INF"<<" ";
            else
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
