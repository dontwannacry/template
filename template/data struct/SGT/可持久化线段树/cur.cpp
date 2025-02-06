#include<bits/stdc++.h>
using namespace std;
int N,M,start[1000010],vtot;
struct point{
	int l,r;
	long long num;
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
}*root[1000010] = {nullptr};
bool inset(int n,point *now){return(n >= now->l&&n <= now->r);}
void setup(point *now){
	int L = now->l,R = now->r;
	if(L == R){
		now->num = start[L];
		return;
	}
	int mid = (L+R)/2;
	now->son[0] = new point(L,mid);setup(now->son[0]);
	now->son[1] = new point(mid+1,R);setup(now->son[1]);
	now->pushup();
}
void update(int addr,int newval,point *now,point *from){
	if(now->l == now->r&&now->r == addr){now->num = newval;return;}
	if(inset(addr,from->son[0])){
		now->son[1] = from->son[1];
		now->son[0] = new point(from->son[0]->l,from->son[0]->r);
		update(addr,newval,now->son[0],from->son[0]);
	}else{
		now->son[0] = from->son[0];
		now->son[1] = new point(from->son[1]->l,from->son[1]->r);
		update(addr,newval,now->son[1],from->son[1]);
	}
	now->pushup();
}
long long findnum(int addr,point *now){
	if(now->l == now->r&&now->r == addr){return now->num;}
	if(inset(addr,now->son[0])){return findnum(addr,now->son[0]);}
	else{return findnum(addr,now->son[1]);}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> start[i];}
	root[0] = new point(1,N);
	setup(root[0]);
	while(M--){
		int v,op,addr;cin >> v >> op >> addr;
		if(op == 1){
			int val;cin >> val;
			root[++vtot] = new point(1,N);
			update(addr,val,root[vtot],root[v]);
		}else{
			cout << findnum(addr,root[v]) <<"\n";
			root[++vtot] = new point(*root[v]);
		}
	}
	return 0;
}
