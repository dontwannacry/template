#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct point{
	int son[2],num;
	point(){son[0] = son[1] = num = 0;}
};
struct SGT{
	int root[100010],len;
	point node[100010*50];
	void getroot(int now){root[now] = ++len;}
	void update(int nl,int nr,int at,int delta,int now){
		node[now].num += delta;
		if(nl == nr&&nr == at){return;}
		int mid = (nl+nr)>>1;
		if(nl <= at&&at <= mid){
			if(!node[now].son[0]){node[now].son[0] = ++len;}
			update(nl,mid,at,delta,node[now].son[0]);
		}else{
			if(!node[now].son[1]){node[now].son[1] = ++len;}
			update(mid+1,nr,at,delta,node[now].son[1]);
		}
	}
	int getans(int nl,int nr,int l,int r,int now){
		if(l <= nl&&nr <= r){return node[now].num;}
		if(r < nl||nr < l||nr < nl){return 0;}
		int mid = (nl+nr)>>1;
		return getans(nl,mid,l,r,node[now].son[0])+getans(mid+1,nr,l,r,node[now].son[1]);
	}
}T1,T2;
int N,M,A[100010],lastans;
int si[100010],fa[100010],maxn[100010],dis[100010][20],tot,root;
int up[17][100010],dep[100010];
bool vis[100010];
vector<int>ne[100010];
void firstdfs(int now,int fa){
	up[0][now] = fa;dep[now] = dep[fa]+1;
	for(int v:ne[now]){
		if(fa == v){continue;}
		firstdfs(v,now);
	}
}
void getroot(int now,int fa){
	si[now] = 1;maxn[now] = 0;
	for(int v:ne[now]){
		if(vis[v]||fa == v){continue;}
		getroot(v,now);
		si[now] += si[v];
		maxn[now] = max(si[v],maxn[now]);
	}
	maxn[now] = max(maxn[now],tot-maxn[now]);
	if(maxn[now] < maxn[root]){root = now;}
}
void initdfs(int now){
//	cout << now << " " << fa[now] << "\n";
	vis[now] = 1;
	T1.getroot(now);T2.getroot(now);
	for(int v:ne[now]){
		if(vis[v]){continue;}
		tot = si[v];maxn[root = 0]=N;
		getroot(v,0);
		fa[root] = now;
		initdfs(root);
	}
}
int getdis(int x,int y){
	int dis = 0;
	if(dep[y] < dep[x]){swap(x,y);}
	for(int i = 16;i >= 0;--i){
		if(dep[up[i][y]] >= dep[x]){
			y = up[i][y];
			dis += (1<<i);
		}
	}
	if(x == y){return dis;}
	for(int i = 16;i >= 0;--i){
		if(up[i][x] != up[i][y]){
			x = up[i][x];y = up[i][y];
			dis += (2<<i);
		}
	}
	return dis+2;
}
void init(){
	firstdfs(1,0);
	for(int i = 1;i <= 16;++i){
		for(int j = 1;j <= N;++j){
			up[i][j] = up[i-1][up[i-1][j]];
		}
	}
	maxn[root = 0] = tot = N;
	getroot(1,0);
	initdfs(root);
	for(int i = 1;i <= N;++i){
		for(int j = 0,now = i;now;++j,now = fa[now]){dis[i][j] = getdis(i,now);}
		for(int j = 0,now = i,u = fa[i];now;++j,now = u,u = fa[u]){
			T1.update(0,N,dis[i][j],A[i],T1.root[now]);
			if(u){T2.update(0,N,dis[i][j+1],A[i],T2.root[now]);}
		}
	}
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M;
    for(int i = 1;i <= N;++i){cin >> A[i];}
    for(int i = 1;i < N;++i){
		int u,v;cin >> u >> v;
		ne[u].push_back(v);
		ne[v].push_back(u);
	}
	init();
	for(int i = 1;i <= M;++i){
		int op,x,y;cin >> op >> x >> y;
		x ^= lastans;y ^= lastans;
		if(op == 0){
			int ans = 0;
			ans += T1.getans(0,N,0,y-dis[x][0],T1.root[x]);
			for(int j = 0,d = x,u = fa[x];u;++j,d = u,u = fa[u]){
				ans += T1.getans(0,N,0,y-dis[x][j+1],T1.root[u]);
				ans -= T2.getans(0,N,0,y-dis[x][j+1],T2.root[d]);
//				cout << d << " " << downlim+1 << " " << y-dis[x][j] << " " << T.getans(0,N,downlim+1,y-dis[x][j],T.root[d]) << "\n";
			}
			lastans = ans;
			cout << ans << "\n";
		}else{
			int delta = y-A[x];A[x] = y;
			for(int j = 0,now = x,u = fa[x];now;++j,now = u,u = fa[u]){
				T1.update(0,N,dis[x][j],delta,T1.root[now]);
				if(u){T2.update(0,N,dis[x][j+1],delta,T2.root[now]);}
			}
		}
	}
    return 0;
}
