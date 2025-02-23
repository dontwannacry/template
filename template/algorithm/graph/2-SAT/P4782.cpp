#include<bits/stdc++.h>
using namespace std;
int N,Q;
int dfn[2000010],low[2000010],cnt,ans;
bool instake[2000010];
int stake[2000010],len,belong[2000010];
int in[2000010],tot;
vector<int>to[2000010];
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
			instake[v] = 0;
		}while(v != now);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	for(int i = 1;i <= Q;++i){
		int u,a,v,b;
		cin >> u >> a >> v >> b;
		to[u+(a^1)*N].push_back(v+b*N);
		to[v+(b^1)*N].push_back(u+a*N);
	}
	for(int i = 1;i <= N*2;++i)if(!dfn[i])dfs(i);
	for(int i = 1;i <= N;++i){
		if(belong[i] == belong[i+N]){
			cout << "IMPOSSIBLE";
			return 0;
		}
	}
	cout << "POSSIBLE\n";
	for(int i = 1;i <= N;++i){
		if(belong[i] > belong[i+N])cout << "1 ";
		else cout << "0 ";
	}
	return 0;
}
