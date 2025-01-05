#include<bits/stdc++.h>
using namespace std;
int N,M,S,son[500010],top[500010],si[500010],fa[500010],deep[500010];
vector<int>to[500010];
void dfs1(int now,int f){
	si[now] = 1,fa[now] = f;
	for(int i = 0;i < to[now].size();++i){
		if(to[now][i] != f){
			deep[to[now][i]] = deep[now]+1;
			dfs1(to[now][i],now);
			si[now] += si[to[now][i]];
			if(si[to[now][i]] > si[son[now]]) son[now] = to[now][i];
		}
	}
}
void dfs2(int now,int tp){
	top[now] = tp;
	if(!son[now]) return;
	dfs2(son[now],tp);
	for(int i = 0;i < to[now].size();++i){
		if(to[now][i] !=fa[now]&&to[now][i] != son[now]){
			dfs2(to[now][i],to[now][i]);
		}
	}
}
int LCA(int a,int b){
	while(top[a] != top[b]){
		if(deep[top[a]] < deep[top[b]])swap(a,b);
		a = fa[top[a]];
	}
	if(deep[a] < deep[b])return a;
	return b;
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
	dfs1(S,S);
	dfs2(S,S);
	while(M--){
		int a,b;
		cin >> a >> b;
		cout << LCA(a,b)<<"\n";
	}
	return 0;
}
