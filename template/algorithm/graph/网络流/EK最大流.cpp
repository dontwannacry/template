#include<bits/stdc++.h>
using namespace std;
struct edge{int v,ne;long long w;}E[10010];
struct back{int from,eid;}pre[210];
int N,M,S,T,head[210],tot = 1;
bool vis[210];
void addedge(int u,int v,long long w){E[++tot].ne = head[u];E[head[u] = tot].v = v;E[tot].w = w;}
bool bfs(){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	vis[S] = 1;
	queue<int>Q;
	Q.push(S);
	while(!Q.empty()){
		int u = Q.front();Q.pop();
		for(int i = head[u];i;i = E[i].ne){
			int v = E[i].v;long long w = E[i].w;
			if(vis[v]||!w)continue;
			vis[v] = 1;
			pre[v].eid = i;pre[v].from = u;
			if(v == T)return 1;
			Q.push(v);
		}
	}
	return 0;
}
long long EK(){
	long long ans = 0;
	while(bfs()){
		long long minn = 0x3fffffffffffffff;
		for(int i = T;i != S;i = pre[i].from){minn = min(minn,E[pre[i].eid].w);}
		for(int i = T;i != S;i = pre[i].from){
			E[pre[i].eid].w -= minn;
			E[pre[i].eid^1].w += minn;
		}
		ans += minn;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> S >> T;
	for(int i = 1;i <= M;++i){
		int u,v;long long w;
		cin >> u >> v >> w;
		addedge(u,v,w);
		addedge(v,u,0);
	}
	cout << EK();
	return 0;
}
