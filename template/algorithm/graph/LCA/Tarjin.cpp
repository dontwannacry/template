#include<bits/stdc++.h>
using namespace std;
int N,M,S,fa[500010],ans[500010];
bool vis[500010];
vector<int>to[500010];
struct que{
	int v,id;
};
vector<que>Q[500010];
int find(int x){
	if(x == fa[x])return x;
	return fa[x] = find(fa[x]);
}
void dfs(int now){
	fa[now] = now;
	vis[now] = 1;
	for(int i = 0;i < to[now].size();++i){
		if(!vis[to[now][i]]){
			dfs(to[now][i]);
			fa[to[now][i]] = now;
		}
	}
	for(int i = 0;i < Q[now].size();++i){
		if(vis[Q[now][i].v]){
			ans[Q[now][i].id] = find(Q[now][i].v);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> N >> M >> S;
	for(int i = 1;i < N;++i){
		int u,v;
		cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for(int i = 1;i <= M;++i){
		int a,b;
		cin >> a >> b;
		Q[a].push_back({b,i});
		Q[b].push_back({a,i});
	}
	dfs(S);
	for(int i = 1;i <= M;++i){
		cout << ans[i]<<"\n";
	}
	return 0;
}
