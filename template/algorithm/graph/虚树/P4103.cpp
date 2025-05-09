#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge{
    int v,w;
    bool operator < (const edge other)const{return w < other.w;}
}L[1000010];
int N,M,K,dfn[1000010],dep[1000010],up[20][1000010],tot;
bool vis[1000010];
int maxn[1000010],minn[1000010],ansmax,ansmin;
ll sum[1000010],ti[1000010],anssum;
vector<edge>G[1000010];
vector<int>ne[1000010],ingraph;
stack<int>S;
void initdfs(int now,int fa){
    dfn[now] = ++tot;
    dep[now] = dep[fa]+1;
    for(int v:ne[now]){
        if(v == fa){continue;}
        up[0][v] = now;
        initdfs(v,now);
    }
}
void init(){
    initdfs(1,0);
    for(int i = 1;i <= 19;++i){
        for(int j = 1;j <= N;++j){
            up[i][j] = up[i-1][up[i-1][j]];
        }
    }
}
int LCA(int u,int v){
    if(dep[v] < dep[u]){swap(u,v);}
    for(int i = 19;i >= 0;--i){
        if(dep[u] <= dep[up[i][v]]){
            v = up[i][v];
        }
    }
    if(u == v){return u;}
    for(int i = 19;i >= 0;--i){
        if(up[i][u] != up[i][v]){
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}
void setedge(int u,int v){
    edge E = {v,0};
    for(int i = 19;i >= 0;--i){
        if(dep[u] <= dep[up[i][v]]){
            E.w += (1<<i);
            v = up[i][v];
        }
    }
    G[u].push_back(E);
}
void setup(){
    sort(L+1,L+1+K);int v = tot = 0;
    ansmax = anssum = 0;ansmin = 0x3f3f3f3f;
    S.push(1);ingraph.push_back(1);
    for(int i = 1;i <= K;++i){
        if(L[i].v == 1){continue;}
        int A = LCA(L[i].v,S.top());v = 0;
        while(dep[A] < dep[S.top()]){
            if(v){setedge(S.top(),v);}
            v = S.top();S.pop();
        }
        if(v){setedge(A,v);}
        if(A != S.top()){
            S.push(A);
            ingraph.push_back(A);
        }
        S.push(L[i].v);
        ingraph.push_back(L[i].v);
    }
    v = 0;
    while(!S.empty()){
        if(v){setedge(S.top(),v);}
        v = S.top();S.pop();
    }
}
void getans(int now){
    ti[now] = sum[now] = 0;minn[now] = 0x3f3f3f3f;maxn[now] = -0x3f3f3f3f;
    if(vis[now]){ti[now] = 1;maxn[now] = minn[now] = 0;}
    for(edge E:G[now]){
        getans(E.v);
        ansmin = min(ansmin,minn[E.v]+E.w+minn[now]);
        ansmax = max(ansmax,maxn[E.v]+E.w+maxn[now]);
        anssum += (sum[E.v]+ti[E.v]*E.w)*ti[now];
        anssum += sum[now]*ti[E.v];
        minn[now] = min(minn[now],minn[E.v]+E.w);
        maxn[now] = max(maxn[now],maxn[E.v]+E.w);
        sum[now] += sum[E.v]+ti[E.v]*E.w;
        ti[now] += ti[E.v];
    }
}
void clear(){
    for(int u:ingraph){
        vis[u] = 0;
        G[u].clear();
    }
    ingraph.clear();
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 1;i < N;++i){
        int u,v;cin >> u >> v;
        ne[u].push_back(v);
        ne[v].push_back(u);
    }
    init();
    cin >> M;
    for(int i = 1;i <= M;++i){
        cin >> K;
        for(int j = 1;j <= K;++j){
            int u;cin >> u;vis[u] = 1;
            L[j] = {u,dfn[u]};
        }
        setup();
        getans(1);
        cout << anssum << " " << ansmin << " " << ansmax << "\n";
        clear();
    }
    return 0;
}