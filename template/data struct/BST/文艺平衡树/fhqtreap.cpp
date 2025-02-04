#include<bits/stdc++.h>
using namespace std;
mt19937 randomplay(time(0));
struct node{
	node *son[2];
	int val,pri,siz;
	bool tag;
	node(int v){
		val = v;tag = 0;siz = 1;
		son[0] = son[1] = nullptr;
		pri = randomplay();
	}
	void getsiz(){
		siz = 1;
		if(son[0] != nullptr) siz += son[0]->siz;
		if(son[1] != nullptr) siz += son[1]->siz;
	}
}*root = nullptr;
void pushdown(node *now){
	if(now->son[0] != nullptr) now->son[0]->tag^=1;
	if(now->son[1] != nullptr) now->son[1]->tag^=1;
	now->tag = 0;
	swap(now->son[0],now->son[1]);
}
pair<node*,node*>split(node *now,int k){
	if(now == nullptr) return {nullptr,nullptr};
	if(now->tag){pushdown(now);}
	int L = 0;if(now->son[0] != nullptr) L = now->son[0]->siz;
	if(k <= L){
		auto res = split(now->son[0],k);
		now->son[0] = res.second;
		now->getsiz();
		return {res.first,now};
	}else{
		auto res = split(now->son[1],k-L-1);
		now->son[1] = res.first;
		now->getsiz();
		return {now,res.second};
	}
}
node *mix(node *lnow,node *rnow){
	if(lnow == nullptr&&rnow == nullptr){return nullptr;}
	if(lnow == nullptr){return rnow;}
	if(rnow == nullptr){return lnow;}
	if(lnow->tag){pushdown(lnow);}
	if(rnow->tag){pushdown(rnow);}
	if(lnow->pri < rnow->pri){
		lnow->son[1] = mix(lnow->son[1],rnow);
		lnow->getsiz();
		return lnow;
	}else{
		rnow->son[0] = mix(lnow,rnow->son[0]);
		rnow->getsiz();
		return rnow;
	}
}
void update(int l,int r){
	node *L,*T,*R;
	auto res = split(root,r);
	L = res.first,R = res.second;
	res = split(L,l-1);
	L = res.first,T = res.second;
	T->tag ^= 1;
	root = mix(mix(L,T),R);
}
void out(node *now){
	if(now == nullptr) return;
	if(now->tag){pushdown(now);}
	out(now->son[0]);
	cout << now->val <<" ";
	out(now->son[1]);
}
int N,M;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	root = new node(1);
	for(int i = 2;i <= N;++i){
		node *tmp = new node(i);
		root = mix(root,tmp);
	}
	for(int i = 1;i <= M;++i){
		int l,r;cin >> l >> r;
		update(l,r);
	}
	out(root);
	return 0;
}
