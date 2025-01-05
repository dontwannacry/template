#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5010;
int N,M,dis[MAXN],tot,ans;
bool vis[MAXN];
struct bian{int v,w;};
vector<bian>to[MAXN];
void prim(){
	memset(dis,127,sizeof(dis));
	dis[1] = 0;
	while(1){
		int u = 0;
		for(int i = 1;i <= N;++i){
			if(!vis[i]&&dis[i] < dis[u]){
				u = i;
			}
		}
		if(!u)break;
		tot++;vis[u] = 1;ans += dis[u];
		for(int i = 0;i < to[u].size();++i){
			int v = to[u][i].v,w = to[u][i].w;
			if(w < dis[v])dis[v] = w;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int x,y,w;
		cin >> x >> y >> w;
		to[x].push_back({y,w});
		to[y].push_back({x,w});
	}
	prim();
	if(tot == N)cout << ans;
	else cout << "orz";
	return 0;
}
