#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll up[40],full;
int N,M,ans = 10086;
map<ll,int>mp;
void solve(int T,int val,ll re,int cas){
	if(T < cas){
		if(cas == 0){
			if(mp.find(re) == mp.end()){mp[re] = val;}
			else{mp[re] = min(mp[re],val);}
		}
		else if(mp.find(full-re) != mp.end()){ans = min(ans,val+mp[full-re]);}
		return;
	}
	solve(T-1,val+1,re^up[T],cas);
	solve(T-1,val,re,cas);
}
void middlesolve(){
	int mid = N/2;
	solve(mid-1,0,0,0);
	solve(N-1,0,0,mid);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;full = (1ll<<N)-1;
	for(int i = 0;i < N;++i){up[i] += (1<<i);}
	for(int i = 1;i <= M;++i){
		int u,v;cin >> u >> v;--u;--v;
		up[u] += (1ll<<v);up[v] += (1ll<<u);
	}
	middlesolve();
	cout << ans << "\n";
	return 0;
}
