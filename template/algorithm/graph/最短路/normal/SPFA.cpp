#include<bits/stdc++.h>
using namespace std;
struct edge{int v,w;};
int N,M,S;long long dis[10010];
bool vis[10010];
vector<edge>to[10010];
void SPFA(int S){
	memset(vis,0,sizeof(vis));
	memset(dis,0x7f,sizeof(dis));
	queue<int>Q;
	dis[S] = 0;
	Q.push(S);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		vis[u] = 0;
		for(auto V : to[u]){
			if(dis[V.v] > dis[u]+V.w){
				dis[V.v] = dis[u]+V.w;
				if(!vis[V.v]){
					Q.push(V.v);
					vis[V.v] = 1;
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> S;
	for(int i = 1;i <= M;++i){
		int u,v,w;
		cin >> u >> v >> w;
		to[u].push_back({v,w});
	}
	SPFA(S);
	for(int i = 1;i <= N;++i){cout << min(1ll*0x7fffffff,dis[i]) <<" ";}
	return 0;
}
