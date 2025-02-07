#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5010;
int N,M,dis[MAXN],tot,ans;
bool vis[MAXN];
struct bian{
	int v,w;
	bool operator < (const bian x)const{return w > x.w;}
}tmp;
priority_queue<bian>q;
vector<bian>to[MAXN+10];
void prim(){
	memset(dis,127,sizeof(dis));
	tmp.v = 1;tmp.w = 0;dis[1] = 0;
	q.push(tmp);
	while(!q.empty()){
		tmp = q.top();q.pop();
		int u = tmp.v,w = tmp.w;
		if(vis[u])continue;
		tot++;vis[u] = 1;ans += dis[u];
		for(int i = 0;i < to[u].size();++i){
			int v = to[u][i].v,w = to[u][i].w;
			if(w < dis[v]){
				tmp.w = dis[v] = w;
				tmp.v = v;
				q.push(tmp);
			}
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
