#include<bits/stdc++.h>
using namespace std;
struct Unionfind{
	int fa[200010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return fa[now] = ancestor(fa[now]);
	}
	void start(int len){for(int i = 1;i <= len;++i){fa[i] = i;}}
}U;
struct line{
	int u,v,w;
	bool operator < (const line other)const{return w < other.w;}
}L[500010];
struct point{
	int l,r,num;
	point *son[2];
	point(int L,int R){
		l = L,r = R;
		num = 0;
		son[0] = son[1] = nullptr;
	}
	void pushup(){
		num = 0;
		if(son[0]!=nullptr)num+=son[0]->num;
		if(son[1]!=nullptr)num+=son[1]->num;
	}
}*root[200010] = {nullptr};
struct node{int l,r;}D[200010];
int N,FN,M,Q,A[100010],val[200010],reval[200010],up[200010][18],order[200010],dfn,tot;
vector<int>ne[200010];
bool inset(int n,point *now){return(n >= now->l&&n <= now->r);}
void setup(point *now){
	int L = now->l,R = now->r;
	if(L == R){
		now->num = 0;
		return;
	}
	int mid = (L+R)/2;
	now->son[0] = new point(L,mid);setup(now->son[0]);
	now->son[1] = new point(mid+1,R);setup(now->son[1]);
	now->pushup();
}
void update(int addr,point *now,point *from){
	if(now->l == now->r&&now->r == addr){now->num = from->num+1;return;}
	if(inset(addr,from->son[0])){
		now->son[1] = from->son[1];
		now->son[0] = new point(from->son[0]->l,from->son[0]->r);
		update(addr,now->son[0],from->son[0]);
	}else{
		now->son[0] = from->son[0];
		now->son[1] = new point(from->son[1]->l,from->son[1]->r);
		update(addr,now->son[1],from->son[1]);
	}
	now->pushup();
}
int findk(int k,point *L,point *R){
	if(L->l == L->r)return L->l;
	int tmp = R->son[0]->num - L->son[0]->num;
	if(k <= tmp)return findk(k,L->son[0],R->son[0]);
	else return findk(k-tmp,L->son[1],R->son[1]);
}
void kruskal(){
	sort(L+1,L+1+M);
	U.start(2*N-1);
	FN = N;
	for(int i = 1;i <= M;++i){
		int fu = U.ancestor(L[i].u),fv = U.ancestor(L[i].v);
		if(fu == fv)continue;
		U.fa[fu] = ++FN;U.fa[fv] = FN;
		val[FN] = L[i].w;
		ne[FN].push_back(fu);ne[FN].push_back(fv);
		if(FN == 2*N-1) break;
	}
	val[0] = 0x7fffffff;
}
void dfs(int now){
	if(now <= N){
		D[now].l = dfn++;
		reval[dfn] = A[now];
	}else{D[now].l = dfn;}
	for(int v:ne[now]){
		up[v][0] = now;
		dfs(v);
	}
	D[now].r = dfn;
}
void init(){
	for(int i = 1;i <= 17;++i){
		for(int j = 1;j <= FN;++j){
			up[j][i] = up[up[j][i-1]][i-1];
		}
	}
	root[0] = new point(1,tot);
	setup(root[0]);
	for(int i = 1;i <= N;++i){
		int on = lower_bound(order+1,order+1+tot,reval[i])-order;
		root[i] = new point(1,tot);
		update(on,root[i],root[i-1]);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> Q;
	for(int i = 1;i <= N;++i){cin >> A[i];order[i] = A[i];}
	sort(order+1,order+1+N);
	tot = unique(order+1,order+1+N)-order-1;
	for(int i = 1;i <= M;++i){cin >> L[i].u >> L[i].v >> L[i].w;}
	kruskal();
	for(int i = 1;i <= FN;++i){if(U.fa[i] == i) dfs(i);}
	init();
	while(Q--){
		int u,x,k;cin >> u >> x >> k;
		for(int i = 17;i >= 0;--i){if(x >= val[up[u][i]]&&up[u][i] != 0) u = up[u][i];}
		if(D[u].r-D[u].l<k){cout << "-1\n";continue;}
		cout << order[findk(D[u].r-D[u].l-k+1,root[D[u].l],root[D[u].r])] <<"\n";
	}
	return 0;
}
