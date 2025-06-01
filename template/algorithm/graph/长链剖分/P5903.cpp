#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
int N,Q,root,lastans,dep[500010],lg[500010];
int si[500010],son[500010],up[500010][19];
int top[500010],idx[500010],L[2000010],cnt;
ui s;ll ans;
vector<int>ne[500010];
inline ui get(ui x){
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}
void getli(int x,int T){
	int now = x,i;
	for(;T != now;now = up[now][0]){L[idx[now]=++cnt] = now;}
	L[idx[now]=++cnt] = x = now;
	for(i = 1,now = up[now][0];i <= si[x]&&now;++i){
		L[++cnt] = now;
		now = up[now][0];
	}
}
void secdfs(int now,int fa,int T){
	top[now] = T;
	if(son[now]){secdfs(son[now],now,T);}
	else{getli(now,T);}
	for(int v:ne[now]){
		if(v == fa||v == son[now]){continue;}
		secdfs(v,now,v);
	}
}
void initdfs(int now,int fa){
	dep[now] = dep[fa]+1;
	up[now][0] = fa;
	for(int v:ne[now]){
		if(v == fa){continue;}
		initdfs(v,now);
		if(si[v] > si[son[now]]){son[now] = v;}
	}
	si[now] = si[son[now]]+1;
}
void init(){
	for(int i = 2;i <= N;++i){lg[i] = lg[i>>1]+1;}
	initdfs(root,0);
	secdfs(root,0,root);
	for(int i = 1;i <= 18;++i){
		for(int j = 1;j <= N;++j){
			up[j][i] = up[up[j][i-1]][i-1];
		}
	}
}
int getans(int now,int k){
	if(k == 0){return now;}
	int G = lg[k];
	now = up[now][G];k -= (1<<G);
	return L[idx[now]+k];
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> Q >> s;
    for(int i = 1;i <= N;++i){
		int u;cin >> u;
		if(!u){root = i;}
		else{
			ne[u].push_back(i);
			ne[i].push_back(u);
		}
	}
	init();
	for(int i = 1;i <= Q;++i){
		int x = ((get(s)^lastans)%N)+1;
		int k = (get(s)^lastans)%dep[x];
		lastans = getans(x,k);
		ans ^= 1ll*i*lastans;
	}
	cout << ans << "\n";
    return 0;
}
