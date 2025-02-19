#include<bits/stdc++.h>
using namespace std;
const int blocklen = 300,splitlim = 1500;
struct node{
	node *ne,*ba;
	vector<int>li;
	int sumb[240],sum[70010];
	node(){
		ne = ba = nullptr;li.clear();
		memset(sumb,0,sizeof(sumb));
		memset(sum,0,sizeof(sum));
	};
	node(node *from){
		ne = ba = nullptr;li.clear();
		memcpy(sumb,from->sumb,sizeof(sumb));
		memcpy(sum,from->sum,sizeof(sum));
	}
	inline void update(int val,int delta){
		sum[val] += delta;
		sumb[val/blocklen] += delta;
	}
	void split(){
		node *tmp = new node(this);
		if(ne != nullptr){ne->ba = tmp;}tmp->ne = ne;
		tmp->ba = this;this->ne = tmp;
		int out = li.size()>>1;
		for(int i = out;i < li.size();++i){
			tmp->li.push_back(li[i]);
			update(li[i],-1);
		}
		for(;li.size() > out;){li.pop_back();}
	}
}*head = new node();
struct cursor{
	node *now;int it;
	inline void Move(int k){
		now = head;it = 0;
		while(now->li.size() < k){
			k -= now->li.size();
			now = now->ne;
		}
		it = k;
	}
	void Insert(int ch){
		now->li.insert(now->li.begin()+it,ch);
		node *item = now;
		while(item != nullptr){
			item->update(ch,1);
			item = item->ne;
		}
		if(now->li.size() > splitlim){
			now->split();
			if(it >= now->li.size()){
				it -= now->li.size();
				now = now->ne;
			}
		}
	}
	void Update(int val){
		if(it == now->li.size()){it = 0;now = now->ne;}
		int ch = now->li[it];
		now->li[it] = val;
		node *item = now;
		while(item != nullptr){
			item->update(ch,-1);
			item->update(val,1);
			item = item->ne;
		}
	}
}cur = {head,0},tmp;
int N,Q,A[35010],cnt[70010],cntb[240],li[70010],lastans;
int kth(int l,int r,int k){
	cur.Move(l-1);tmp.Move(r-1);
	if(cur.it == cur.now->li.size()){cur.it = 0;cur.now = cur.now->ne;}
	if(tmp.it == tmp.now->li.size()){tmp.it = 0;tmp.now = tmp.now->ne;}
	if(cur.now == tmp.now){
		int len = 1,it = cur.it;
		for(;;++len){
			li[len] = cur.now->li[it];
			if(it == tmp.it){break;}
			++it;
		}
		sort(li+1,li+1+len);
		return li[k];
	}
	for(int i = 0;i <= 235;++i){cntb[i] = tmp.now->ba->sumb[i]-cur.now->sumb[i];}
	for(int i = cur.it;i < cur.now->li.size();++i){cntb[cur.now->li[i]/blocklen]++;}
	for(int i = tmp.it;i >= 0;--i){cntb[tmp.now->li[i]/blocklen]++;}
	int in = 0;
	while(k > cntb[in]){k -= cntb[in++];}
	for(int i = 0;i < blocklen;++i){cnt[i+in*blocklen] = tmp.now->ba->sum[i+in*blocklen]-cur.now->sum[i+in*blocklen];}
	for(int i = cur.it;i < cur.now->li.size();++i){cnt[cur.now->li[i]]++;}
	for(int i = tmp.it;i >= 0;--i){cnt[tmp.now->li[i]]++;}
	in *= blocklen;
	while(k > cnt[in]){k -= cnt[in++];}
	return in;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){cin >> A[i];}
	for(int i = N;i >= 1;--i){cur.Insert(A[i]);}
	cin >> Q;
	for(int i = 1;i <= Q;++i){
		char op;cin >> op;
		if(op == 'M'){
			int x,val;cin >> x >> val;
			x ^= lastans;val ^= lastans;
			cur.Move(x-1);
			cur.Update(val);
		}else if(op == 'I'){
			int x,val;cin >> x >> val;
			x ^= lastans;val ^= lastans;
			cur.Move(x-1);
			cur.Insert(val);
		}else{
			int x,y,k;cin >> x >> y >> k;
			x ^= lastans;y ^= lastans;k ^= lastans;
			cout << (lastans = kth(x,y,k)) <<"\n";
		}
	}
	return 0;
}
