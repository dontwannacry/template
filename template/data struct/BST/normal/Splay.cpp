#include<bits/stdc++.h>
using namespace std;
struct node{
	node *son[2],*fa;
	int cnt,val,siz;
	node(int v){
		val = v;
		cnt = siz = 1;
		fa = son[0] = son[1] = nullptr;
	}
	void getsiz(){
		siz = cnt;
		if(son[0] != nullptr){siz += son[0]->siz;}
		if(son[1] != nullptr){siz += son[1]->siz;}
	}
	bool get(){return this == fa->son[1];}
	void clear(){delete this;}
}*root = nullptr;
void reroot(node *now){
	node *tmp = now->fa,*grf = tmp->fa;int chk = now->get(),from = -1;
	if(grf != nullptr){from = tmp->get();}
	tmp->son[chk] = now->son[chk^1];
	if(now->son[chk^1] != nullptr){now->son[chk^1]->fa = tmp;}
	now->son[chk^1] = tmp;
	tmp->fa = now;now->fa = grf;
	if(grf != nullptr){grf->son[from] = now;}
	tmp->getsiz();now->getsiz();
}
void splay(node *now){
	for(node *fa = now->fa;now->fa != nullptr;reroot(now)){
		fa = now->fa;
		if(fa->fa != nullptr){
			if(fa->get() == now->get()){reroot(fa);}
			else{reroot(now);}
		}
		root = now;
	}
}
void insert(int val){
	node *now = root,*fa = nullptr;
	if(root == nullptr){root = new node(val);return;}
	while(1){
		if(val == now->val){
			++now->cnt;
			now->getsiz();
			splay(now);
			return;
		}
		fa = now;
		now = now->son[now->val < val];
		if(now == nullptr){
			now = new node(val);
			now->fa = fa;
			fa->son[fa->val < val] = now;
			splay(now);
			return;
		}
	}
}
int getrank(int val){
	int res = 0;node *now = root;
	if(now == nullptr){return res+1;}
	while(1){
		if(val < now->val){
			if(now->son[0] == nullptr){
				splay(now);
				return res+1;
			}
			now = now->son[0];
		}else{
			if(now->son[0] != nullptr){res += now->son[0]->siz;}
			if(val == now->val){
				splay(now);
				return res+1;
			}
			res += now->cnt;
			if(now->son[1] == nullptr){
				splay(now);
				return res+1;
			}
			now = now->son[1];
		}
	}
}
int getkth(int k){
	node *now = root;
	while(1){
		if(now->son[0] != nullptr&&k <= now->son[0]->siz){now = now->son[0];}
		else{
			if(now->son[0] != nullptr){k -= now->son[0]->siz;}
			k -= now->cnt;
			if(k <= 0){
				splay(now);
				return now->val;
			}
			now = now->son[1];
		}
	}
}
node *pre_nxt(bool re){
	node *now = root->son[re];
	if(now == nullptr){return now;}
	while(now->son[re^1] != nullptr){now = now->son[re^1];}
	splay(now);
	return now;
}
void del(int val){
	getrank(val);
	if(root->cnt > 1){--root->cnt;--root->siz;return;}
	if(root->son[0] == nullptr){
		node *rs = root->son[1];
		if(rs != nullptr){rs->fa = nullptr;}
		root->clear();root = rs;
	}else{
		node *ort = root;
		pre_nxt(0);
		node *rs = ort->son[1];
		if(rs != nullptr){rs->fa = root;}
		root->son[1] = rs;
		ort->clear();
		root->fa = nullptr;
		root->getsiz();
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N;cin >> N;
	for(int i = 1;i <= N;++i){
		int op,x;cin >> op >> x;
		if(op == 1){insert(x);}
		else if(op == 2){del(x);}
		else if(op == 3){cout << getrank(x) <<"\n";}
		else if(op == 4){cout << getkth(x) <<"\n";}
		else if(op == 5){insert(x);cout << pre_nxt(0)->val <<"\n";del(x);}
		else{insert(x);cout << pre_nxt(1)->val <<"\n";del(x);}
	}
	return 0;
}
