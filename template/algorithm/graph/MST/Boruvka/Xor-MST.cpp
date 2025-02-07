#include<bits/stdc++.h>
using namespace std;
struct Unionfind{
	int fa[200010],si[200010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return fa[now] = ancestor(fa[now]);
	}
	void start(int len){
		for(int i = 1;i <= len;++i){
			fa[i] = i;
			si[i] = 1;
		}
	}
}U;
struct point{
	int cnt,son[2];
	point(){
		son[0] = son[1] = -1;
		cnt = 0;
	}
}trie[9000010];
struct edge{int u,v;};
int A[200010],minn[200010][2],onit[200010][2],change[200010],chval[200010],N,ANS,tot,last,len;
int root[200010];
long long sum;
queue<edge>Q;
void trie_push(int now,int val){
	trie[now].cnt++;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(trie[now].son[v] == -1) trie[now].son[v] = ++len;
		now = trie[now].son[v];
		trie[now].cnt++;
	}
}
int find_near(int now,int S,int val){
	int res = 0;bool re = 1;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(trie[S].son[v] == -1){S = trie[S].son[v^1];res+=(1<<i);}
		else if(trie[trie[now].son[v]].cnt == trie[trie[S].son[v]].cnt&&re){
			S = trie[S].son[v^1];
			res+=(1<<i);re = 0;
		}else S = trie[S].son[v];
		now = trie[now].son[v];
	}
	return res;
}
void trie_mix(int A,int B){
	trie[A].cnt += trie[B].cnt;
	if(trie[B].son[0] != -1){
		if(trie[A].son[0] == -1)trie[A].son[0] = trie[B].son[0];
		else trie_mix(trie[A].son[0],trie[B].son[0]);
	}
	if(trie[B].son[1] != -1){
		if(trie[A].son[1] == -1)trie[A].son[1] = trie[B].son[1];
		else trie_mix(trie[A].son[1],trie[B].son[1]);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;len = 0;
	for(int i = 1;i <= N;++i){cin >> A[i];}
	sort(A+1,A+1+N);
	N = unique(A+1,A+1+N)-A-1;
	for(int i = 1;i <= N;++i){trie_push(0,A[i]);}
	for(int i = 1;i <= N;++i){
		root[i] = ++len;
		trie_push(root[i],A[i]);
	}
	U.start(N);last = N-1;
	while(last){ //Boruvka
		memset(onit,-1,sizeof(onit));
		memset(change,-1,sizeof(change));
		memset(minn,0x7f,sizeof(minn));
		for(int i = 1;i <= N;++i){
			int f = U.ancestor(i);
			if(onit[i][0] == -1){onit[i][0] = f;}
			else{onit[i][1] = f;}
		}
		for(int i = 1;i <= N;++i){
			int f = U.ancestor(i);
			int delta = find_near(root[f],0,A[i]);
			if(delta < minn[f][0]){
				minn[f][0] = delta;
				minn[f][1] = A[i]^delta;
			}
		}
		for(int i = 1;i <= N;++i){
			int f = U.ancestor(i);
			if(f != i) continue;
			int on = lower_bound(A+1,A+1+N,minn[f][1])-A;
			chval[f] = minn[f][0];
			if(onit[on][0] == f){change[f] = onit[on][1];}
			else{change[f] = onit[on][0];}
		}
		for(int i = 1;i <= N;++i){
			if(change[i] == -1) continue;
			int fu = U.ancestor(i),fv = U.ancestor(change[i]);
			if(fu == fv)continue;
			--last;
			sum += chval[i];
			if(U.si[fu] < U.si[fv]) swap(fu,fv);
			trie_mix(root[fu],root[fv]);
			U.fa[fv] = U.fa[fu];
			U.si[fu] += U.si[fv];
		}
	}
	cout << sum;
	return 0;
}
