#include<bits/stdc++.h>
using namespace std;
char str[1000020],T[100020];
int K,N,M,ans,rk[2000020],tmp[2000020],sa[1000020],cnt[1000020],height[1000020],from[1000020];
bool vis[2010];
stack<int>S;
void suffix_array(){
	M = max(N,300);
	for(int i = 1;i <= N;++i){cnt[rk[i]=str[i]]++;}
	for(int i = 1;i <= M;++i){cnt[i]+=cnt[i-1];}
	for(int i = N;i >= 1;--i){sa[cnt[rk[i]]--] = i;}
	for(int re = 1;re < N;re <<= 1){
	    int cur = 0;
	    for (int i = N-re+1;i <= N;++i){tmp[++cur] = i;}
	    for (int i = 1;i <= N;i++){if(sa[i] > re){tmp[++cur]=sa[i]-re;}}
		for(int i = 0;i <= M;++i){cnt[i] = 0;}
		for(int i = 1;i <= N;++i){cnt[rk[i]]++;}
		for(int i = 1;i <= M;++i){cnt[i]+=cnt[i-1];}
		for(int i = N;i >= 1;--i){sa[cnt[rk[tmp[i]]]--] = tmp[i];}
		for(int i = 1;i <= N;++i){tmp[i] = rk[i];}
		int tot = 0;
		for(int i = 1;i <= N;++i){
			if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+re]==tmp[sa[i-1]+re]){rk[sa[i]] = tot;}
			else{rk[sa[i]] = ++tot;}
		}
	}
}
bool check(int x){
	while(!S.empty()){vis[S.top()] = 0;S.pop();}
	for(int i = 1;i <= N;++i){
		if(height[i] < x){while(!S.empty()){vis[S.top()] = 0;S.pop();}}
		if(!vis[from[sa[i]]]){
			vis[from[sa[i]]] = 1;
			S.push(from[sa[i]]);
			if(S.size() == K){return 1;}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> T){
		++K;str[++N] = K+'A';
		for(int i = 0;T[i];++i){str[++N] = T[i];from[N] = K;}
		str[++N] = K+'A';
	}
	suffix_array();
	for(int i = 1,k = 0;i <= N;++i){
		if(k){--k;}
		while(str[i+k] == str[sa[rk[i]-1]+k]){++k;}
		height[rk[i]] = k;
	}
	int l = 0,r = 100000,mid;
	while(l <= r){
		mid = (l+r)>>1;
		if(check(mid)){l = mid+1;}
		else{r = mid-1;}
	}
	cout << r;
	return 0;
}
