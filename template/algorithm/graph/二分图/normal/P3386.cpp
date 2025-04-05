#include<bits/stdc++.h>
using namespace std;
int N,M,E,ans,with[510];
bool vis[510];
vector<int>to[510];
bool found(int now){
	if(vis[now])return 0;
	vis[now] = 1;
	for(int i = 0;i < to[now].size();++i){
		if(!with[to[now][i]]||found(with[to[now][i]])){
			with[to[now][i]] = now;
			return 1;
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> E;
	for(int i = 1;i <= E;++i){
		int u,v;cin >> u >> v;
		to[u].push_back(v);
	}
	for(int i = 1;i <= N;++i){
		memset(vis,0,sizeof(vis));
		if(found(i))++ans;
	}
	cout << ans;
	return 0;
}
