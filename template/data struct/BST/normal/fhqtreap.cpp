#include<bits/stdc++.h>
using namespace std;
mt19937 randomplay(time(0));
struct node{
	node *son[2];
	int cnt,val,pri,siz;
	node(int v){
		val = v;
		cnt = siz = 1;
		son[0] = son[1] = nullptr;
		pri = randomplay();
	}
	void getsiz(){
		siz = cnt;
		if(son[0] != nullptr) siz += son[0]->siz;
		if(son[1] != nullptr) siz += son[1]->siz;
	}
}*root = nullptr;
pair<node*,node*>split(node *now,int k){
	if(now == nullptr) return {nullptr,nullptr};
	if(now->val <= k){
		auto res = split(now->son[1],k);
		now->son[1] = res.first;
		now->getsiz();
		return {now,res.second};
	}else{
		auto res = split(now->son[0],k);
		now->son[0] = res.second;
		now->getsiz();
		return {res.first,now};
	}
}
tuple<node*,node*,node*>split_rank(node *now,int k){
	if(now == nullptr) return {nullptr,nullptr,nullptr};
	int L = 0;if(now->son[0] != nullptr) L = now->son[0]->siz;
	if(k <= L){
		node *l,*mid,*r;
		tie(l,mid,r) = split_rank(now->son[0],k);
		now->son[0] = r;
		now->getsiz();
		return {l,mid,now};
	}else if(k <= L+now->cnt){
		node *l,*r;
		l = now->son[0];r = now->son[1];
		now->son[0] = now->son[1] = nullptr;
		return {l,now,r};
	}else{
		node *l,*mid,*r;
		tie(l,mid,r) = split_rank(now->son[1],k-(L+now->cnt));
		now->son[1] = l;
		now->getsiz();
		return {now,mid,r};
	}
}
node *mix(node *lnow,node *rnow){
	if(lnow == nullptr&&rnow == nullptr){return nullptr;}
	if(lnow == nullptr){return rnow;}
	if(rnow == nullptr){return lnow;}
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
void pushin(int val){
	auto res = split(root,val);
	node *rootl = res.first,*rootr = res.second,*newnode;
	res = split(rootl,val-1);
	rootl = res.first,newnode = res.second;
	if(newnode == nullptr){newnode = new node(val);}
	else{newnode->cnt++;newnode->siz++;}
	rootl = mix(rootl,newnode);
	root = mix(rootl,rootr);
}
void del(int val){
	auto res = split(root,val);
	node *rootl = res.first,*rootr = res.second,*delnode;
	res = split(rootl,val-1);
	rootl = res.first,delnode = res.second;
	if(delnode->cnt==1){delete(delnode);delnode = nullptr;}
	else{delnode->cnt--;delnode->siz--;}
	rootl = mix(rootl,delnode);
	root = mix(rootl,rootr);
}
int getrank(int val){
	auto res = split(root,val-1);
	int result = (res.first == nullptr?0:res.first->siz)+1;
	root = mix(res.first,res.second);
	return result;
}
int getkth(int k){
	node *l,*ans,*r;
	tie(l,ans,r) = split_rank(root,k);
	int res = ans->val;
	l = mix(l,ans);
	root = mix(l,r);
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N;cin >> N;
	for(int i = 1;i <= N;++i){
		int op,x;cin >> op >> x;
		if(op == 1){pushin(x);}
		else if(op == 2){del(x);}
		else if(op == 3){cout << getrank(x) <<"\n";}
		else if(op == 4){cout << getkth(x) <<"\n";}
		else if(op == 5){cout << getkth(getrank(x)-1) <<"\n";}
		else{cout << getkth(getrank(x+1)) <<"\n";}
	}
	return 0;
}
