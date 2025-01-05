#include<bits/stdc++.h>
using namespace std;
int N,M;
int dfn[500010],low[500010],si[500010],cnt,ans,all;
int stake[500010],len;
//vector<int>to[10010],G[10010];
int head[500010],ne[4000010],to[4000010],tot = 1;
vector<int>ANS[500010];
void push_back(int u,int v){
	ne[++tot] = head[u];to[head[u] = tot] = v;
	ne[++tot] = head[v];to[head[v] = tot] = u;
}
void dfs(int now,int fa){
	low[now] = dfn[now] = ++cnt;
	stake[++len] = now;
	int son = 0;
	for(int i = head[now];i;i = ne[i]){
		//if(i == (la^1))continue;
		int v = to[i];
		if(fa == v)continue;
		if(!dfn[v]){
			son++;
			dfs(v,now);
			low[now] = min(low[now],low[v]);
			if(low[v] >= dfn[now]){
				++all;
				while(stake[len] != v) ANS[all].push_back(stake[len--]);
				ANS[all].push_back(v);len--;
				ANS[all].push_back(now);
			}
		}else low[now] = min(low[now],low[v]);
	}
	if(fa == -1&&son == 0)ANS[++all].push_back(now);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int u,v;
		cin >> u >> v;
		push_back(u,v);
	}
	for(int i = 1;i <= N;++i)if(!dfn[i]){len = 0;dfs(i,-1);} 
	cout << all <<"\n";
	for(int i = 1;i <= all;++i){
		cout << ANS[i].size()<<" ";
		for(auto u:ANS[i])cout << u <<" ";
		cout << "\n";
	}
	return 0;
}
