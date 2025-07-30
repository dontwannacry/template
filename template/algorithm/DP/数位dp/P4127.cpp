#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[20][200][200];
int spl[20],len;
ll dfs(int pos,int sum,int num,const int mod,bool limit){
	if(pos > len){
		if(sum == mod&&num == 0){return 1;}
		else{return 0;}
	}
	if(!limit&&dp[pos][sum][num] != -1){return dp[pos][sum][num];}
	int lim = limit?spl[len-pos+1]:9;
	ll res = 0;
	for(int i = 0;i <= lim;++i){
		res += dfs(pos+1,sum+i,(num*10+i)%mod,mod,limit&&i == lim);
	}
	if(!limit){dp[pos][sum][num] = res;}
	return res;
}
ll solve(ll x){
	len = 0;while(x){spl[++len] = x%10;x /= 10;}
	ll res = 0;
	for(int i = 1;i <= 9*len;++i){
		memset(dp,-1,sizeof(dp));
		res += dfs(1,0,0,i,1);
	}
	return res;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll l,r;cin >> l >> r;
	cout << solve(r)-solve(l-1) << "\n";
    return 0;
}
