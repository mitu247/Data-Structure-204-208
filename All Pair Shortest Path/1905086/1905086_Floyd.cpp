#include<bits/stdc++.h>
#define N 101
#define INF INT_MAX
using namespace std;
vector<vector<int>>dist(N,vector<int>(N,INF));
vector<vector<int>>graph(N,vector<int>(N,INF));
void floydWarshall(int n){
    for(int k = 1; k<=n; k++){
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                if(dist[i][k]==INF || dist[k][j]==INF)continue;
                if(dist[i][j]>dist[i][k]+dist[k][j]) dist[i][j] = dist[i][k]+dist[k][j];
            }
        }
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
    floydWarshall(n);
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
}
