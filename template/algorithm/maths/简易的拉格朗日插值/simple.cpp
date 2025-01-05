#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int N,K,x[2010],y[2010],ANS;
long long Pow(long long A,long long B){
	long long sum = A,ans = 1;
	while(B){
		if(B&1){ans = (sum*ans)%MOD;}
		sum = (sum*sum)%MOD;
		B >>= 1;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> K;
	for(int i = 1;i <= N;++i){cin >> x[i] >> y[i];}
	for(int i = 1;i <= N;++i){
		int m = 1,s = 1;
		for(int j = 1;j <= N;++j){
			if(i == j) continue;
			s = s*1ll*(K-x[j]+MOD)%MOD;
			m = m*1ll*(x[i]-x[j]+MOD)%MOD;
		}
		ANS = (ANS+(1ll*y[i]*s%MOD)*Pow(m,MOD-2))%MOD;
	}
	cout << ANS;
	return 0;
}
