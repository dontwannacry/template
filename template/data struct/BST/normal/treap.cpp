#include<bits/stdc++.h>
using namespace std;
struct node{
	node *son[2];
	int cnt,val,pri,siz;
	node(int v){
		val = v;
		cnt = siz = 1;
		son[0] = son[1] = nullptr;
		pri = rand();
	}
	void getsiz(){
		siz = cnt;
		if(son[0] != nullptr) siz += son[0]->siz;
		if(son[1] != nullptr) siz += son[1]->siz;
	}
}*head = nullptr;
void reroot(node *now,bool re){
	node *tmp = now->son[re];
	now->son[re] = tmp->son[re];
	tmp->son[re] = tmp->son[!re];
	tmp->son[!re] = now->son[!re];
	now->son[!re] = tmp;
	swap(now->cnt,tmp->cnt);
	tmp->getsiz();now->getsiz();
	swap(now->val,tmp->val);
	swap(now->pri,tmp->pri);
}
void pushin(node *now,int val){
	++now->siz;
	if(val == now->val){++now->cnt;return;}
	bool re = (now->val < val);
	if(now->son[re] != nullptr) {
		pushin(now->son[re],val);
		if(now->son[re]->pri > now->pri){reroot(now,re);}
	}
	else{now->son[re] = new node(val);}
}
void del(node *&now,int val){
	if(now->val == val){
		if(now->cnt > 1){now->cnt--;now->siz--;}
		else{
			if(now->son[0]==nullptr&&now->son[1]==nullptr){
				delete now;
				now = nullptr;
			}
			else if(now->son[0]==nullptr){
				node *p = now;
				now = p->son[1];
				delete p;
			}else if(now->son[1]==nullptr){
				node *p = now;
				now = p->son[0];
				delete p;
			}else{
				bool re = (now->son[0]->pri < now->son[1]->pri);
				reroot(now,re);del(now->son[!re],val);
				now->getsiz();
			}
		}
	}else{
		bool re = (now->val < val);
		del(now->son[re],val);
		now->getsiz();
	}
}
void getrank(node *now,int num,int &ans,int &cnt){
	if(now == nullptr) return;
	bool re = (now->val < num);
	int si = now->siz;
	if(now->son[1] != nullptr){si-=now->son[1]->siz;}
	ans += re*si;
	getrank(now->son[re],num,ans,cnt);
	if(now->val == num) cnt = now->cnt;
}
void getnum(node *now,int fi,int tar,int &ans){
	if(now == nullptr) return;
	int L = 0;if(now->son[0] != nullptr) L = now->son[0]->siz;
	if(fi+L >= tar) getnum(now->son[0],fi,tar,ans);
	else{
		fi+=L;
		if(fi+now->cnt >= tar) ans = now->val;
		else{getnum(now->son[1],fi+now->cnt,tar,ans);}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	srand(time(0));
	int N;cin >> N;
	while(N--){
		int opt,x;
		cin >> opt >> x;
		if(opt == 1){
			if(head == nullptr){head = new node(x);}
			else{pushin(head,x);}
		}else if(opt == 2){
			del(head,x);
		}else if(opt == 3){
			int ans = 0,cnt = 0;
			getrank(head,x,ans,cnt);
			cout << ans+1<<"\n";
		}else if(opt == 4){
			int ans = 0;
			getnum(head,0,x,ans);
			cout << ans<<"\n";
		}else if(opt == 5){
			int ans = 0,cnt = 0;
			getrank(head,x,ans,cnt);
			getnum(head,0,ans,ans);
			cout << ans<<"\n";
		}else{
			int ans = 0,cnt = 0;
			getrank(head,x,ans,cnt);
			getnum(head,0,ans+cnt+1,ans);
			cout << ans<<"\n";
		}
	}
	return 0;
}
