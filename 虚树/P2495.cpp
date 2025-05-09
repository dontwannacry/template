#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge{
    int v,w;
    bool operator < (const edge other)const{return w < other.w;}
}L[250010];
int N,M,K,dfn[250010],dep[250010],up[18][250010],minup[18][250010],tot;
bool vis[250010];
ll ans;
vector<edge>ne[250010],G[250010];
vector<int>ingraph;
stack<int>S;
void initdfs(int now,int fa){
    dfn[now] = ++tot;
    dep[now] = dep[fa]+1;
    for(edge E:ne[now]){
        if(E.v == fa){continue;}
        up[0][E.v] = now;
        minup[0][E.v] = E.w;
        initdfs(E.v,now);
    }
}
void init(){
    initdfs(1,0);
    for(int i = 1;i <= 17;++i){
        for(int j = 1;j <= N;++j){
            up[i][j] = up[i-1][up[i-1][j]];
            minup[i][j] = min(minup[i-1][j],minup[i-1][up[i-1][j]]);
        }
    }
}
int LCA(int u,int v){
    if(dep[v] < dep[u]){swap(u,v);}
    for(int i = 17;i >= 0;--i){
        if(dep[u] <= dep[up[i][v]]){
            v = up[i][v];
        }
    }
    if(u == v){return u;}
    for(int i = 17;i >= 0;--i){
        if(up[i][u] != up[i][v]){
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}
void setedge(int u,int v){
    edge E = {v,0x3f3f3f3f};
    for(int i = 17;i >= 0;--i){
        if(dep[u] <= dep[up[i][v]]){
            E.w = min(E.w,minup[i][v]);
            v = up[i][v];
        }
    }
    G[u].push_back(E);
}
void setup(){
    sort(L+1,L+1+K);int v = ans = 0;
    S.push(1);ingraph.push_back(1);
    for(int i = 1;i <= K;++i){
        int A = LCA(L[i].v,S.top());v = 0;
        while(dep[A] < dep[S.top()]){
            if(v){setedge(S.top(),v);}
            v = S.top();S.pop();
        }
        setedge(A,v);
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
ll getans(int now){
    ll res = 0;
    if(vis[now]){res = 0x3f3f3f3f3f3f3f3f;}
    for(edge E:G[now]){
        ll tmp = min(getans(E.v),1ll*E.w);
        res += tmp;
    }
    return res;
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
        int u,v,w;cin >> u >> v >> w;
        ne[u].push_back({v,w});
        ne[v].push_back({u,w});
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
        ans = getans(1);
        cout << ans << "\n";
        clear();
    }
    return 0;
}