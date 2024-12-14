#include<bits/stdc++.h>
#define N 10000
using namespace std;
int n;
vector<int> graph[N];
vector<int> win(N);
vector<int> loss(N);
vector<int> r(N);
int g[N][N];
int r_cap[N][N];
vector<string> teams(N);

int bfs(int s,int t,vector<int>&parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>>q;
    q.push({s,INT_MAX});
    while(!q.empty())
    {
        int u = q.front().first;
        int score = q.front().second;
        q.pop();
        for(int v: graph[u])
        {
            if(parent[v]== -1 && r_cap[u][v])
            {
                parent[v] = u;
                int new_score = min(r_cap[u][v],score);
                if(v == t)
                    return new_score;
                q.push({v,new_score});
            }
        }
    }
    return 0;
}
int max_score(int s,int t)
{
    int mscore = 0;
    int value = n*n;
    int score;
    vector<int> parent(value);
    while(true)
    {
        score = bfs(s,t,parent);
        if(!score)
            break;
        mscore+= score;
        int curr = t;
        while(curr!=s)
        {
            int prev = parent[curr];
            r_cap[prev][curr] -= score;
            r_cap[curr][prev] += score;
            curr = prev;
        }
    }
    return mscore;
}
void dfs(int s,int t,vector<int>& reachable,bool visited[])
{
    visited[s] = true;
    if(s<=n && s)
        reachable.push_back(s);
    for (int i = 0; i < t; i++)
        if (r_cap[s][i] && !visited[i])
            dfs(i,t,reachable,visited);
}
void baseball()
{
    for(int i=1; i<=n; i++)
    {
        int point = win[i]+r[i];
        int sum = 0;
        int w = n+1;
        int s = 0,t;
        for(int j = 1; j<=n; j++)
        {
            for(int k = j+1; k<=n; k++)
            {
                if(j == i || k == i ||g[j][k]==0)
                    continue;

                sum+= g[j][k];

                graph[w].push_back(0);
                graph[0].push_back(w);

                graph[w].push_back(j);
                graph[j].push_back(w);

                graph[w].push_back(k);
                graph[k].push_back(w);

                r_cap[0][w] = r_cap[w][k] = r_cap[w][j] = g[j][k];
                w++;
            }
        }
        t = w;
        bool eliminate = false;
        for(int j = 1; j<=n; j++)
        {
            if(j==i)
                continue;
            graph[t].push_back(j);
            graph[j].push_back(t);
            r_cap[j][t] = point - win[j];
            if(point-win[j]<0)
            {
                eliminate = true;
                cout<<teams[i]<<" is eliminated"<<endl;
                cout<<"They can win at most "<< win[i] <<"+"<< r[i]<<" = "<<point<<" games."<<endl;
                cout<<teams[j]<<" have won a total of "<< win[j]<<" games."<<endl;
                cout<<"They play each other 0 times"<<endl;
                cout<<"So on average, each of the teams in this group wins "<<win[j]<<"/1 = "<<win[j]<<" games"<<endl;
                cout<<endl;
                break;
            }
        }
        int y = max_score(s,t);

        if(sum > y & eliminate==false)
        {
            cout<<teams[i]<<" is eliminated"<<endl;
            cout<<"They can win at most "<< win[i] <<"+"<< r[i]<<" = "<<point<<" games."<<endl;
            bool visited[t+1];
            for(int k = 0; k<=t; k++)
                visited[k] = false;
            vector<int> reachable;
            dfs(s,t,reachable,visited);
            int total = 0,m;
            for(m = 0; m<reachable.size()-1; m++)
            {
                cout<<teams[reachable[m]]<<", ";
                total+=win[reachable[m]];
            }
            total+=win[reachable[m]];
            cout<<teams[reachable[m]]<<" have won a total of "<<total<<" games."<<endl;
            int remain = 0;
            for(m = 0; m<reachable.size(); m++)
            {
                for(int z = m+1; z<reachable.size(); z++)
                    remain+=g[reachable[m]][reachable[z]];
            }
            float average = (float)(remain+total)/reachable.size();
            cout<<"They play each other "<<remain<<" times."<<endl;
            cout<<"So on average, each of the teams wins "<<(remain+total)<<"/"<<reachable.size()<<" = "<<average<<" games."<<endl;
            cout<<endl;
        }
        for(int j = 0; j<=N; j++)
        {
            graph[j].clear();
        }
        memset(r_cap,0,sizeof(r_cap));
    }
}

int main()
{
    fstream cin("team.txt");
    cin>>n;
    for(int i = 1; i<=n; i++)
    {
        cin>>teams[i]>>win[i]>>loss[i]>>r[i];
        for(int j = 1; j<=n; j++)
        {
            cin>>g[i][j];
        }
    }
    baseball();
    return 0;
}
