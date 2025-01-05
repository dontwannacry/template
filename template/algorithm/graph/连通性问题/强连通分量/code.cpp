#include<bits/stdc++.h>
using namespace std;
int N,M;
int w[10010],dfn[10010],low[10010],cnt,ans;
bool instake[10010];
int stake[10010],len,belong[10010],si[10010],dp[10010],in[10010],tot;
vector<int>to[10010],G[10010];
queue<int>q;
void dfs(int now){
	low[now] = dfn[now] = ++cnt;
	stake[++len] = now;
	instake[now] = 1;
	for(int i = 0;i < to[now].size();++i){
		if(!dfn[to[now][i]]){
			dfs(to[now][i]);
			low[now] = min(low[now],low[to[now][i]]);
		}else if(instake[to[now][i]]) low[now] = min(low[now],low[to[now][i]]);
	}
	if(low[now] == dfn[now]){
		++tot;int v;
		do{
			v = stake[len--];
			belong[v] = tot;
			si[tot] += w[v];
			instake[v] = 0;
		}while(v != now);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i)cin >> w[i];
	for(int i = 1;i <= M;++i){
		int u,v;
		cin >> u >> v;
		to[u].push_back(v);
	}
	for(int i = 1;i <= N;++i)if(!dfn[i])dfs(i);
	for(int i = 1;i <= N;++i){
		for(int j = 0;j < to[i].size();++j){
			if(belong[i] != belong[to[i][j]]){
				G[belong[i]].push_back(belong[to[i][j]]);
				in[belong[to[i][j]]]++;
			}	
		}
	}
	for(int i = 1;i <= tot;++i){
		if(!in[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int now = q.front();
		q.pop();
		dp[now] += si[now];
		for(int i = 0;i < G[now].size();++i){
			dp[G[now][i]] = max(dp[G[now][i]],dp[now]);
			--in[G[now][i]];
			if(!in[G[now][i]])q.push(G[now][i]);
		}
	}
	for(int i = 1;i <= tot;++i)ans = max(ans,dp[i]);
	cout << ans ;
	return 0;
}
