#include<bits/stdc++.h>
using namespace std;
int N,M,start[200010],order[200010],tot;
unordered_map<int,int>mp;
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
		now->son[0] = new point(*from->son[0]);
		update(addr,now->son[0],from->son[0]);
	}else{
		now->son[0] = from->son[0];
		now->son[1] = new point(*from->son[1]);
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
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> start[i];order[i] = start[i];}
	sort(order+1,order+1+N);
	tot = unique(order+1,order+1+N)-order-1;
	for(int i = 1;i <= tot;++i){mp[order[i]] = i;}
	root[0] = new point(1,tot);
	setup(root[0]);
	for(int i = 1;i <= N;++i){
		root[i] = new point(1,tot);
		update(mp[start[i]],root[i],root[i-1]);
	}
	while(M--){
		int L,R,k;
		cin >> L >> R >> k;
		int ans = findk(k,root[L-1],root[R]);
		cout << order[ans]<<"\n";
	}
	return 0;
}
