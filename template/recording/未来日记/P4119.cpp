#include<bits/stdc++.h>
using namespace std;
const int numblock = 340,block = 600;
struct Unionfind{
	int fa[100010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return fa[now] = ancestor(fa[now]);
	}
	void clear(int len){for(int i = 1;i <= len;++i){fa[i] = i;}}
}U;
int N,M,A[100010],E[100010],sumb[180][310],sum[180][100010],rt[180][100010];
int newli[block*2+10],cntb[310],cnt[100010];
inline void init(){
	U.clear(N);
	for(int i = 1,j = block;;++i,j += block){
		for(int j = 1;j <= 100000;++j){sum[i][j] = sum[i-1][j];}
		for(int j = 0;j <= 300;++j){sumb[i][j] = sumb[i-1][j];}
		E[i] = j<N?j:N;
		for(int j = E[i-1]+1;j <= E[i];++j){
			if(!rt[i][A[j]]){rt[i][A[j]] = j;}
			else{U.fa[j] = rt[i][A[j]];}
			sum[i][A[j]]++;
			sumb[i][A[j]/numblock]++;
		}
		if(j >= N){break;}
	}
}
inline int tinyblock(int l,int r,int bid,int x,int y){
	int cnt = 0,len = 0;
	rt[bid][x] = 0;
	for(int i = E[bid-1]+1;i <= E[bid];++i){
		A[i] = A[U.ancestor(i)];
		if(A[i] == x){
			newli[++len] = i;

		}
	}
	for(int i = 1;i <= len;++i){
		U.fa[newli[i]] = newli[i];
		if(l <= newli[i]&&newli[i] <= r){A[newli[i]] = y;++cnt;}
		if(!rt[bid][A[newli[i]]]){rt[bid][A[newli[i]]] = newli[i];}
		else{U.fa[newli[i]] = rt[bid][A[newli[i]]];}
	}
	return cnt;
}
inline void update(int l,int r,int x,int y){
	if(x == y){return;}
	int lo = (l-1)/block+1,ro = (r-1)/block+1;
	if(lo == ro){
		int cnt = tinyblock(l,r,lo,x,y);
		for(int id = lo;E[id];++id){
			sumb[id][x/numblock]-=cnt;sumb[id][y/numblock]+=cnt;
			sum[id][x]-=cnt;sum[id][y]+=cnt;
		}
		return;
	}
	int cnt = tinyblock(l,E[lo],lo,x,y);
	sumb[lo][x/numblock]-=cnt;sumb[lo][y/numblock]+=cnt;
	sum[lo][x]-=cnt;sum[lo][y]+=cnt;
	for(int i = lo+1;i < ro;++i){
		if(rt[i][x]){
			cnt = sum[i][x]-sum[lo][x];
			if(rt[i][y]){U.fa[rt[i][x]] = rt[i][y];}
			else{rt[i][y] = rt[i][x];A[rt[i][y]] = y;}
			rt[i][x] = 0;
		}
		sumb[i][x/numblock]-=cnt;sumb[i][y/numblock]+=cnt;
		sum[i][x]-=cnt;sum[i][y]+=cnt;
	}
	cnt += tinyblock(E[ro-1]+1,r,ro,x,y);
	for(int i = ro;E[i];++i){
		sumb[i][x/numblock]-=cnt;sumb[i][y/numblock]+=cnt;
		sum[i][x]-=cnt;sum[i][y]+=cnt;	
	}
}
int kth(int l,int r,int k){
	int lo = (l-1)/block+1,ro = (r-1)/block+1;
	if(lo == ro){
		int len = 1,it = l;
		for(;;++len){
			newli[len] = A[U.ancestor(it)];
			if(it == r){break;}
			++it;
		}
		sort(newli+1,newli+1+len);
		return newli[k];
	}
	for(int i = 0;i <= 300;++i){cntb[i] = sumb[ro-1][i]-sumb[lo][i];}
	for(int i = l;i <= E[lo];++i){cntb[A[U.ancestor(i)]/numblock]++;}
	for(int i = E[ro-1]+1;i <= r;++i){cntb[A[U.ancestor(i)]/numblock]++;}
	int in = 0;
	while(k > cntb[in]){k -= cntb[in++];}
	in *= numblock;
	for(int i = 0;i < numblock;++i){cnt[i+in] = sum[ro-1][i+in]-sum[lo][i+in];}
	for(int i = l;i <= E[lo];++i){cnt[A[U.ancestor(i)]]++;}
	for(int i = E[ro-1]+1;i <= r;++i){cnt[A[U.ancestor(i)]]++;}
	while(k > cnt[in]){k -= cnt[in++];}
	return in;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> A[i];}
	init();
	for(int i = 1;i <= M;++i){
		int opt,l,r;cin >> opt >> l >> r;
		if(opt == 1){
			int x,y;cin >> x >> y;
			update(l,r,x,y);
		}else{
			int k;cin >> k;
			cout << kth(l,r,k) <<"\n";
		}
	}
	return 0;
}
