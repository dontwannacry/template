#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,S,dep[500010];
int lu[500010],up[500010];
vector<int>ne[500010];
void dfs(int now,int fa){
	int q = lu[fa],r = lu[q];
	up[now] = fa;dep[now] = dep[fa]+1;
	lu[now] = (dep[fa]-dep[q] != dep[q]-dep[r])?fa:r;
	for(int v:ne[now]){
		if(v == fa){continue;}
		dfs(v,now);
	}
}
int LCA(int u,int v){
	if(dep[u] > dep[v]){swap(u,v);}
	while(dep[u] < dep[v]){
		if(dep[lu[v]] < dep[u]){v = up[v];}
		else{v = lu[v];}
	}
	while(u != v){
		if(lu[u] == lu[v]){u = up[u];v = up[v];}
		else{u = lu[u];v = lu[v];}
	}
	return u;
}
void solve(){
	cin >> N >> M >> S;
	for(int i = 1;i < N;++i){
		int u,v;cin  >> u >> v;
		ne[u].push_back(v);
		ne[v].push_back(u);
	}
	dep[1] = 1;dfs(S,S);
	for(int i = 1;i <= M;++i){
		int u,v;cin >> u >> v;
		int l = LCA(u,v);
		cout << l << "\n";
	}
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//    freopen("wolf.in","r",stdin);
//    freopen("wolf.out","w",stdout);
    int T = 1;
    for(int i = 1;i <= T;++i){solve();}
    return 0;
}
