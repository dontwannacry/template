#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007,inv6 = 166666668;
typedef long long ll;
ll N,sq,ids[200010],idlen;
ll id1[200010],id2[200010],g1[200010],g2[200010];
ll prime[200010],sum1[200010],sum2[200010],len;
bitset<200010>vis;
void init(){
	vis[1] = 1;
	for(int i = 2;i <= sq;++i){
		if(!vis[i]){
			prime[++len] = i;
			sum1[len] = (sum1[len-1]+i)%MOD;
			sum2[len] = (sum2[len-1]+1ll*i*i)%MOD;
		}
		for(int j = 1;j <= len&&i*prime[j] <= sq;++j){
			vis[i*prime[j]] = 1;
			if(i%prime[j] == 0){break;}
		}
	}
}
ll getid(ll val){
	if(val <= sq){return id1[val];}
	else{return id2[N/val];}
}
void initg(){
	for(ll l = 1,r;l <= N;l = r+1){
		r = (N/(N/l));ids[++idlen] = N/l;
		ll val = ids[idlen]%MOD;
		g1[idlen] = (val*(val+1)/2)%MOD-1;
		g2[idlen] = val*(val+1)%MOD*(val*2+1)%MOD*inv6%MOD-1;
		if(ids[idlen] <= sq){id1[ids[idlen]] = idlen;}
		else{id2[N/ids[idlen]] = idlen;}
	}
	for(int i = 1;i <= len;++i){
		for(int j = 1;j <= idlen&&prime[i]*prime[i] <= ids[j];++j){
			g1[j] = (g1[j]-prime[i]*(g1[getid(ids[j]/prime[i])]-sum1[i-1])%MOD+MOD)%MOD;
			g2[j] = (g2[j]-prime[i]*prime[i]*(g2[getid(ids[j]/prime[i])]-sum2[i-1])%MOD+MOD)%MOD;
		}
	}	
}
ll S(ll x,int j){
	if(prime[j] > x){return 0;}
	ll ANS = ((g2[getid(x)]-g1[getid(x)]+MOD)%MOD-(sum2[j]-sum1[j]+MOD)%MOD+MOD)%MOD;
	for(int i = j+1;i <= len&&1ll*prime[i]*prime[i] <= x;++i){
		for(ll t = 1,val = prime[i];val <= x;++t,val *= prime[i]){
			ANS = (ANS+val%MOD*(val%MOD-1)%MOD*(S(x/val,i)+(t>1)))%MOD;
		}
	}
	return ANS;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;sq = sqrtl(N);
	init();
	initg();
	cout << (S(N,0)+1)%MOD;
	return 0;
}
