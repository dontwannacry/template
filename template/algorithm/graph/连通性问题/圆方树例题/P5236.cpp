#include<bits/stdc++.h>
using namespace std;
struct edge{int v,w;};
vector<edge>G[200010],ne[100010];
int N,M,Q,ext,up[200010][18],uw[200010][18],deep[200010];
int dfn[100010],low[100010],fa[100010],fw[100010],sum[200010],cnt;
void dfs(int now,int fa){
	deep[now] = deep[fa]+1;
	for(edge E:G[now]){
		if(E.v == fa){continue;}
		up[E.v][0] = now;uw[E.v][0] = E.w;
		dfs(E.v,now);
	}
}
void init(){
	for(int t = 1;t <= 17;++t){
		for(int i = 1;i <= ext;++i){
			up[i][t] = up[up[i][t-1]][t-1];
			uw[i][t] = uw[i][t-1]+uw[up[i][t-1]][t-1];
		}
	}
}
int LCA(int a,int b){
	int res = 0;
	if(deep[a] > deep[b])swap(a,b);
	for(int i = 17;i >= 0;--i){
		if(deep[up[b][i]] >= deep[a]){
//			cout << res <<" "<<uw[b][i]<<" "<<b<<" "<< up[b][i]<<"\n"; 
			res += uw[b][i];
			b = up[b][i];
		}
	}
	if(a == b){return res;}
	for(int i = 17;i >= 0;--i){
		if(up[a][i] != up[b][i]){
			res += uw[a][i];
			res += uw[b][i];
			a = up[a][i];
			b = up[b][i];
		}
	}
	if(up[a][0] > N){res += min(abs(sum[a]-sum[b]),sum[up[a][0]]-abs(sum[a]-sum[b]));}
	else{res += uw[a][0]+uw[b][0];}
	return res;
}
void solve(int u,int v,int w){
	++ext;
	int pre = w,now = v;
	while(now != fa[u]){
		sum[now] = pre;
		pre += fw[now];
		now = fa[now];
//		cout << now <<" "<<pre <<" "<<fw[now]<<"?\n";
	}
	sum[ext] = sum[u];
	now = v;
	while(now != fa[u]){
		int dis = min(sum[now],sum[ext]-sum[now]);
//		cout << now <<" "<<sum[now] <<" "<<sum[ext]<<";\n";
		G[now].push_back({ext,dis});
		G[ext].push_back({now,dis});
		now = fa[now];
	}
}
void tarjan(int now,int f){
	dfn[now] = low[now] = ++cnt;
	for(edge E:ne[now]){
		if(E.v == f){continue;}
		if(!dfn[E.v]){
			fa[E.v] = now;fw[E.v] = E.w;
			tarjan(E.v,now);
//			cout << fw[E.v] <<" "<<E.w<<"!\n";
		}
		low[now] = min(low[now],low[E.v]);
		if(low[E.v] > dfn[now]){
			G[now].push_back({E.v,E.w});
			G[E.v].push_back({now,E.w});
		}
	}
	for(edge E:ne[now]){
		if(fa[E.v] == now||dfn[E.v] <= dfn[now]){continue;}
		solve(now,E.v,E.w);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
	cin >> N >> M >> Q;ext = N;
	for(int i = 1;i <= M;++i){
		int u,v,w;cin >> u >> v >> w;
		ne[u].push_back({v,w});
		ne[v].push_back({u,w});
	}
	tarjan(1,0);
	dfs(1,0);
	init();
//	for(int i = 1;i <= ext;++i){
//		cout << i <<":\n";
//		for(edge E:G[i]){cout <<E.v <<" "<<E.w<<"\n";}
//	}
	for(int i = 1;i <= Q;++i){
		int x,y;cin >> x >> y;
		cout << LCA(x,y) << "\n";
	}
	return 0;
}
