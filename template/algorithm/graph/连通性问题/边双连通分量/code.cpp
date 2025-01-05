#include<bits/stdc++.h>
using namespace std;
struct link{
	int n,w;
	bool operator < (const link x) const{
		return w < x.w;
	}
}belong[500010];
int N,M;
int dfn[500010],low[500010],si[500010],cnt,ans,all;
bool instake[500010];
int stake[500010],len;
//vector<int>to[10010],G[10010];
int head[500010],ne[4000010],to[4000010],tot = 1;
void push_back(int u,int v){
	ne[++tot] = head[u];to[head[u] = tot] = v;
	ne[++tot] = head[v];to[head[v] = tot] = u;
}
void dfs(int now,int la){
	low[now] = dfn[now] = ++cnt;
	stake[++len] = now;
	instake[now] = 1;
	for(int i = head[now];i;i = ne[i]){
		if(i == (la^1))continue;
		int v = to[i];
		if(!dfn[v]){
			dfs(v,i);
			low[now] = min(low[now],low[v]);
		}else low[now] = min(low[now],low[v]);
	}
	if(low[now] == dfn[now]){
		++all;int v;
		do{
			v = stake[len--];
			belong[v].w = all;
			si[all]++;
			instake[v] = 0;
		}while(v != now);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int u,v;
		cin >> u >> v;
		push_back(u,v);
	}
	for(int i = 1;i <= N;++i) belong[i].n = i;
	for(int i = 1;i <= N;++i)if(!dfn[i])dfs(i,-1);
	sort(belong+1,belong+1+N);
	cout << all <<"\n";
	int now = 1,la = belong[1].w;
	for(int i = 1;i <= all;++i){
		cout << si[i]<<" ";
		while(belong[now].w == la){
			cout << belong[now++].n <<" ";
		}
		cout << "\n";
		la = belong[now].w;
	}
	return 0;
}
