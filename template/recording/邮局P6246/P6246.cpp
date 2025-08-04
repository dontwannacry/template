#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,T[500010],res;
ll A[500010],S[500010],dp[500010];
struct node{int l,r,from;};
ll w(int l,int r){
	int mid = (l+r)>>1;
	return S[l-1]+S[r]-S[mid]-S[mid-1]+A[mid]*((mid<<1)-l-r);
}
bool check(int i,int j,int k){return dp[i]+w(i+1,k) <= dp[j]+w(j+1,k);}
struct queue_max{
    node num[500010];int l,r;
    void clear(){l = 1;r = 0;}
    void push(int now){
        while(l <= r&&check(now,num[r].from,num[r].l)){--r;}
        if(r < l){num[++r] = {now+1,N,now};return;}
        int nl = num[r].l,nr = num[r].r;
        while(nl <= nr){
			int mid = (nl+nr)>>1;
			if(check(now,num[r].from,mid)){nr = mid-1;}
			else{nl = mid+1;}
		}
		if(nl != N+1){num[r].r = nl-1;num[++r] = {nl,N,now};}
    }
    node pop(int i){
		while(l < r&&num[l].r < i){++l;}
		return num[l];
	}
}Q;
int solve(ll tag){
	Q.clear();Q.push(0);dp[0] = T[0] = 0;
	for(int i = 1;i <= N;++i){
		node P = Q.pop(i);
		dp[i] = dp[P.from]+w(P.from+1,i)+tag;
		T[i] = T[P.from]+1;
		Q.push(i);
	}
	return T[N];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> A[i];}
	sort(A+1,A+1+N);for(int i = 1;i <= N;++i){S[i] = S[i-1]+A[i];}
	ll l = 0,r = 1e12,mid;
	while(l <= r){
		mid = (l+r)/2;
		res = solve(mid);
		if(res < M){r = mid-1;}
		else{l = mid+1;}
	}
	solve(r);
	cout << dp[N]-1ll*M*r << "\n";
	return 0;
}
