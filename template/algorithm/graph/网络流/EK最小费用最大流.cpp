#include<bits/stdc++.h>
using namespace std;
struct edge{int ne,v,w,c;}E[100010];
struct back{int from,eid;}pre[5010];
struct answer{int flow,cost;};
int N,M,S,T,head[5010],dis[5010],tot = 1;
bool vis[5010];
void addedge(int u,int v,int w,int c){
	E[++tot].ne = head[u];
	E[head[u] = tot].v = v;
	E[tot].w = w;E[tot].c = c;
}
bool spfa(){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x7f,sizeof(dis));
	vis[S] = 1;dis[S] = 0;
	queue<int>Q;Q.push(S);
	while(!Q.empty()){
		int u = Q.front();Q.pop();
		vis[u] = 0;
		for(int i = head[u];i;i = E[i].ne){
			int v = E[i].v,w = E[i].w,c = E[i].c;
			if(!w)continue;
			if(dis[u]+c < dis[v]){
				dis[v] = dis[u]+c;
				pre[v].eid = i;pre[v].from = u;
				if(!vis[v]){
					vis[v] = 1;
					Q.push(v);
				}
			}
		}
	}
	return dis[T] != 0x7f7f7f7f;
}
answer EK(){
	answer res = {0,0};
	while(spfa()){
		int minn = 0x7fffffff;
		for(int i = T;i != S;i = pre[i].from){minn = min(minn,E[pre[i].eid].w);}
		for(int i = T;i != S;i = pre[i].from){
			E[pre[i].eid].w -= minn;
			E[pre[i].eid^1].w += minn;
		}
		res.flow += minn;
		res.cost += minn*dis[T];
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> S >> T;
	for(int i = 1;i <= M;++i){
		int u,v,w,c;
		cin >> u >> v >> w >> c;
		addedge(u,v,w,c);
		addedge(v,u,0,-c);
	}
	answer ans = EK();
	cout << ans.flow <<" "<<ans.cost<<"\n";
	return 0;
}
