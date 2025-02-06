#include<bits/stdc++.h>
using namespace std;
int N,M,start[200010],order[200010],root[200010],tot,len;
struct point{
	int l,r,num,son[2];
}tree[200010*18];
void pushup(int now){
	tree[now].num = tree[tree[now].son[0]].num+tree[tree[now].son[1]].num;
}
bool inset(int n,int now){return(n >= tree[now].l&&n <= tree[now].r);}
void setup(int now,int L,int R){
	tree[now].l = L,tree[now].r = R;
	if(L == R){return;}
	int mid = (L+R)/2;
	tree[now].son[0] = ++len;setup(tree[now].son[0],L,mid);
	tree[now].son[1] = ++len;setup(tree[now].son[1],mid+1,R);
}
void update(int addr,int now,int from){
	int L = tree[from].l,R = tree[from].r;
	tree[now].l = L;
	tree[now].r = R;
	if(L == R&&R == addr){tree[now].num = tree[from].num+1;return;}
	if(inset(addr,tree[from].son[0])){
		tree[now].son[1] = tree[from].son[1];
		tree[now].son[0] = ++len;
		update(addr,tree[now].son[0],tree[from].son[0]);
	}else{
		tree[now].son[0] = tree[from].son[0];
		tree[now].son[1] = ++len;
		update(addr,tree[now].son[1],tree[from].son[1]);
	}
	pushup(now);
}
int findk(int k,int L,int R){
	if(tree[L].l == tree[L].r)return tree[L].l;
	int tmp = tree[tree[R].son[0]].num - tree[tree[L].son[0]].num;
	if(k <= tmp)return findk(k,tree[L].son[0],tree[R].son[0]);
	else return findk(k-tmp,tree[L].son[1],tree[R].son[1]);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> start[i];order[i] = start[i];}
	sort(order+1,order+1+N);
	tot = unique(order+1,order+1+N)-order-1;
	root[0] = ++len;
	setup(root[0],1,tot);
	for(int i = 1;i <= N;++i){
		root[i] = ++len;
		int on = lower_bound(order+1,order+1+tot,start[i])-order;
		update(on,root[i],root[i-1]);
	}
	while(M--){
		int L,R,k;
		cin >> L >> R >> k;
		int ans = findk(k,root[L-1],root[R]);
		cout << order[ans]<<"\n";
	}
	return 0;
}
