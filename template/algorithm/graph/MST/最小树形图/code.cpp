#include<bits/stdc++.h>
using namespace std;
struct edge{int u,v,w;}L[20010];
int N,M,R;long long ans;
int vis[210],id[210],nxt[210],val[210];
bool zhuliu(int root){
	while(1){
		memset(nxt,-1,sizeof(nxt));
		memset(vis,-1,sizeof(vis));
		memset(id,-1,sizeof(id));
		memset(val,0x3f,sizeof(val));
		for(int i = 1;i <= M;++i){
			if(L[i].u == L[i].v) continue;
			if(val[L[i].u] > L[i].w){
				nxt[L[i].u] = L[i].v;
				val[L[i].u] = L[i].w;
			}
		}
		val[root] = 0;
		for(int i = 1;i <= N;++i) if(i != root&&nxt[i] == -1) return 0;
		int circle = 0;
		for(int i = 1;i <= N;++i){
			ans += val[i];
			int now = i;
			while(vis[now] != i&&id[now] == -1&&now != root){
				vis[now] = i;
				now = nxt[now];
			}
			if(now != root&&id[now] == -1){
				id[now] = ++circle;
				for(int v = nxt[now];v != now;v = nxt[v]) id[v] = circle;
			}
		}
		if(!circle) break;
		for(int i = 1;i <= N;++i){if(id[i] == -1) id[i] = ++circle;}
		for(int i = 1;i <= M;++i){
			L[i].w -= val[L[i].u];
			L[i].u = id[L[i].u];
			L[i].v = id[L[i].v];
		}
		root = id[root];
		N = circle;
	}
	return 1;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M >> R;
    for(int i = 1;i <= M;++i){
		int u,v,w;cin >> u >> v >> w;
		L[i] = {v,u,w};//·´±ß
	}
	if(!zhuliu(R)){ans = -1;}
	cout << ans <<"\n";
    return 0;
}
