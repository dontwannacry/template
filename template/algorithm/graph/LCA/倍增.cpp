#include<bits/stdc++.h>
using namespace std;
int N,M,S,up[500010][20],deep[500010];
bool vis[500010];
vector<int>to[500010];
void dfs(int now){
	vis[now] = 1;
	for(int i = 0;i < to[now].size();++i){
		if(!vis[to[now][i]]){
			deep[to[now][i]] = deep[now]+1;
			up[to[now][i]][0] = now;
			dfs(to[now][i]);
		}
	}
}
void init(){
	for(int t = 1;t <= 18;++t){
		for(int i = 1;i <= N;++i){
			up[i][t] = up[up[i][t-1]][t-1];
		}
	}
}
int LCA(int a,int b){
	if(deep[a] > deep[b])swap(a,b);
	for(int i = 18;i >= 0;--i){
		if(deep[up[b][i]] >= deep[a]){
			b = up[b][i];
		}
	}
	if(a == b)return a;
	for(int i = 18;i >= 0;--i){
		if(up[a][i] != up[b][i]){
	 		a = up[a][i];
			b = up[b][i];
		}
	}
	return up[a][0];
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
	deep[S] = 1;
	dfs(S);
	init();
	while(M--){
		int a,b;
		cin >> a >> b;
		cout << LCA(a,b)<<"\n";
	}
	return 0;
}
