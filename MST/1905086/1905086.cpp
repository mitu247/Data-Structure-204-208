#include<bits/stdc++.h>
#define N 100000
using namespace std;
vector<pair<int,float>> adj[N];
vector<float> dist(N,INT_MAX);
vector<pair<float,pair<int,int>>>edgelist;
vector<pair<int,int>> prim_edge;
vector<pair<int,int>> krush_edge;
vector<int> pa(N);
vector<int> sz(N);
void make(int i){
    pa[i] = i;
    sz[i] = 1;
}
int find(int v){
    if(v==pa[v])return v;
    return pa[v] = find(pa[v]);
}
void Union(int u,int v){
   u = find(u);
   v = find(v);
   if(u!=v){
    if(sz[v]>sz[u])swap(u,v);
    pa[v] = u;
    sz[u]+=sz[v];
   }
}
float krush_kal(int src,int n){
    for(int i = 0; i<n; i++){
        make(i);
    }
    sort(edgelist.begin(),edgelist.end());///O(ElogE)
    float total_cost = 0;
    for(auto &edge:edgelist){///O(E)
        float wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if(find(u)==find(v)) continue;
        Union(u,v);///O(logV)
        total_cost+=wt;
        krush_edge.push_back({u,v});
    }
    return total_cost;
}
///O(ElogE)
float prim(int src,int n){
    priority_queue<pair<float,int>,vector<pair<float,int>>,greater<pair<float,int>>>pq;
    vector<bool>inMST(n,false);
    vector<int>parent(n,-1);
    pq.push({0,src});
    dist[src] = 0;
    int u;
    while(!pq.empty()){       ///O(E)
        u = pq.top().second;
        pq.pop();
        if(inMST[u]==false&& u!=src){
           prim_edge.push_back({parent[u],u});
        }
        inMST[u] = true;
        int v;
        float w;
        for(auto x:adj[u]){
            tie(v,w) = x;
            if(inMST[v]==false && dist[v]>w){
                dist[v] = w;
                parent[v]=u;
                pq.push({w,v});///O(logV)
            }
        }
    }
    float cost=0.0;
    for(int i = 0; i<n; i++) cost+=dist[i];
//    for(int i = 1; i<n; i++){
//        if(parent[i]!=-1)prim_edge.push_back({parent[i],i});
//    }
    return cost;
    ///O(ElogV)
}
int main(){
    int n,m,u,v;
    float w;
    fstream cin("mst.in");
    cin>>n>>m;
    for(int i = 0; i<m; i++){
       cin>>u>>v>>w;
       adj[u].push_back({v,w});
       adj[v].push_back({u,w});
       edgelist.push_back({w,{u,v}});
    }
    float p_cost,k_cost;
    p_cost = prim(0,n);
    k_cost = krush_kal(0,n);
    cout<<"Cost of the minimum spanning tree(BY PRIM) : "<<fixed<<setprecision(3)<<p_cost<<endl;
    int i;
    cout<<"{";
    for(i = 0; i < prim_edge.size()-1; i++){
        cout<<"("<<prim_edge[i].first<<","<<prim_edge[i].second<<"), ";
    }
    cout<<"("<<prim_edge[i].first<<","<<prim_edge[i].second<<")}"<<endl;
    cout<<"Cost of the minimum spanning tree(BY KRUSHKAL) : "<<fixed<<setprecision(3)<<k_cost<<endl;

    int j;
    cout<<"{";
    for(j = 0; j < krush_edge.size()-1; j++){
        cout<<"("<<krush_edge[j].first<<","<<krush_edge[j].second<<"), ";
    }
    cout<<"("<<krush_edge[j].first<<","<<krush_edge[j].second<<")}"<<endl;
    return 0;
}

