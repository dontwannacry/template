#include<bits/stdc++.h>
using namespace std;
struct edge{int v,w;};
vector<edge>ne[10010];
int N,Q,request[110];
int si[10010],maxn[10010],root,tot;
int dis[10010],tmp[10010],tmplen,clearli[10010],len;
bool vis[10010],canget[100000010],ans[110];
void getroot(int now,int fa){
	si[now] = 1;
	maxn[now] = 0;
	for(edge E:ne[now]){
		if(vis[E.v]||fa == E.v){continue;}
		getroot(E.v,now);
		si[now] += si[E.v];
		maxn[now] = max(si[E.v],maxn[now]);
	}
	maxn[now] = max(maxn[now],tot-maxn[now]);
	if(maxn[now] < maxn[root]){root = now;}
}
void getdis(int now,int fa){
	tmp[++tmplen] = dis[now];
	for(edge E:ne[now]){
		if(vis[E.v]||fa == E.v){continue;}
		dis[E.v] = dis[now]+E.w;
		getdis(E.v,now);
	}
}
void rootline(int now){
	len = 0;
	for(edge E:ne[now]){
		if(vis[E.v]){continue;}
		tmplen = 0;dis[E.v] = E.w;
		getdis(E.v,now);
		for(int i = 1;i <= tmplen;++i){
			for(int j = 1;j <= Q;++j){
				if(request[j] >= tmp[i]){
					ans[j] |= canget[request[j]-tmp[i]];
				}
			}
		}
		for(int i = 1;i <= tmplen;++i){
			clearli[++len] = tmp[i];
			canget[tmp[i]] = 1;
		}
	}
	for(int i = 1;i <= len;++i){canget[clearli[i]] = 0;}
}
void solve(int now){
	vis[now] = canget[0] = 1;
	rootline(now);
	for(edge E:ne[now]){
		if(vis[E.v]){continue;}
		tot = si[E.v];maxn[root=0]=N;
		getroot(E.v,0);
		solve(root);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	for(int i = 1;i < N;++i){
		int u,v,w;cin >> u >> v >> w;
		ne[u].push_back({v,w});
		ne[v].push_back({u,w});
	}
	for(int i = 1;i <= Q;++i){cin >> request[i];}
	maxn[root] = tot = N;
	getroot(1,0);
	solve(root);
	for(int i = 1;i <= Q;++i){
		if(ans[i]){cout << "AYE\n";}
		else{cout << "NAY\n";}
	}
	return 0;
}
