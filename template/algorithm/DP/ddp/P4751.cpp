#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
struct matrix{
	int num[2][2];
	inline matrix operator * (const matrix x)const{
		matrix res;
		res.num[0][0] = max(num[0][0]+x.num[0][0],num[0][1]+x.num[1][0]);
		res.num[0][1] = max(num[0][0]+x.num[0][1],num[0][1]+x.num[1][1]);
		res.num[1][0] = max(num[1][0]+x.num[0][0],num[1][1]+x.num[1][0]);
		res.num[1][1] = max(num[1][0]+x.num[0][1],num[1][1]+x.num[1][1]);
		return res;
	}
}G[1000010];
int N,M,A[1000010],dp[1000010][2],g[1000010][2],lastans;
vector<int>ne[1000010];
int dfn[1000010],son[1000010],top[1000010],leaf[1000010],si[1000010],fa[1000010],deep[1000010],dfncnt;
struct SGT{
	int root[1000010],len,son[5000010][2];
	matrix T[5000010];
	void setup(int nl,int nr,int now){
		if(nl == nr){
			T[now] = G[nl];
			return;
		}
		int mid = (nl+nr)>>1;
		son[now][0] = ++len;setup(nl,mid,son[now][0]);
		son[now][1] = ++len;setup(mid+1,nr,son[now][1]);
		T[now] = T[son[now][0]]*T[son[now][1]];
	}
	void update(int nl,int nr,int at,int now){
		if(nl == nr){T[now] = G[nl];return;}
		int mid = (nl+nr)>>1;
		if(at <= mid){update(nl,mid,at,son[now][0]);}
		else{update(mid+1,nr,at,son[now][1]);}
		T[now] = T[son[now][0]]*T[son[now][1]];
	}
	matrix getsum(int nl,int nr,int l,int r,int now){
		if(l <= nl&&nr <= r){return T[now];}
		int mid = (nl+nr)>>1;
		if(r <= mid){return getsum(nl,mid,l,r,son[now][0]);}
		else if(mid < l){return getsum(mid+1,nr,l,r,son[now][1]);}
		else{return getsum(nl,mid,l,r,son[now][0])*getsum(mid+1,nr,l,r,son[now][1]);}
	}
}T;
void dfs1(int now,int f){
	si[now] = 1,fa[now] = f;
	dp[now][1] = A[now];
	for(int v:ne[now]){
		if(v == f){continue;}
		deep[v] = deep[now]+1;
		dfs1(v,now);
		dp[now][0] += max(dp[v][0],dp[v][1]);
		dp[now][1] += dp[v][0];
		si[now] += si[v];
		if(si[v] > si[son[now]]){son[now] = v;}
	}
}
void dfs2(int now,int tp){
	dfn[now] = ++dfncnt;top[now] = tp;
	g[now][0] = 0;g[now][1] = A[now];
	if(!son[now]){
		leaf[tp] = dfncnt;
		G[dfn[now]] = {{
			{g[now][0],g[now][0]},
			{g[now][1],-inf}
		}};
		return;
	}
	dfs2(son[now],tp);
	for(int v:ne[now]){
		if(v == fa[now]||v == son[now]){continue;}
		dfs2(v,v);
		g[now][0] += max(dp[v][0],dp[v][1]);
		g[now][1] += dp[v][0];
	}
	G[dfn[now]] = {{
		{g[now][0],g[now][0]},
		{g[now][1],-inf}
	}};
}
inline void update(int now,int val){
	G[dfn[now]].num[1][0] += val-A[now];
	A[now] = val;
	matrix bef,aft;
	while(now){
		bef = T.T[T.root[top[now]]];
		T.update(dfn[top[now]],leaf[top[now]],dfn[now],T.root[top[now]]);
		aft = T.T[T.root[top[now]]];
		now = fa[top[now]];
		G[dfn[now]].num[0][0] += max(aft.num[0][0],aft.num[1][0])-max(bef.num[0][0],bef.num[1][0]);
		G[dfn[now]].num[0][1] = G[dfn[now]].num[0][0];
		G[dfn[now]].num[1][0] += aft.num[0][0]-bef.num[0][0];
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
	deep[1] = 1;
	dfs1(1,0);dfs2(1,1);
	for(int i = 1;i <= N;++i){
		if(i == top[i]){
			T.root[i] = ++T.len;
			T.setup(dfn[i],leaf[i],T.root[i]);
		}
	}
	for(int i = 1;i <= M;++i){
		int x,y;cin >> x >> y;
		x ^= lastans;update(x,y);
		lastans = max(T.T[T.root[1]].num[0][0],T.T[T.root[1]].num[1][0]);
		cout << lastans << "\n";
	}
	return 0;
}