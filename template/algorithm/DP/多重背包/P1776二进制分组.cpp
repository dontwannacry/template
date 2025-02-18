#include<bits/stdc++.h>
using namespace std;
int W,N;
int v[110],m[110],w[110],dp[40010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> W;
	for(int i = 1;i <= N;i++){cin >> v[i] >> w[i] >> m[i];}
	for(int i = 1;i <= N;i++){
		for(int t = 1;t <= 100010;t *= 2){
			if(m[i] >= t){
				m[i] -= t;
				for(int j = W;j >= t*w[i];j--){
					dp[j] = max(dp[j],dp[j-t*w[i]]+t*v[i]);
				}
			}else break;
		}
		for(int j = W;j >= m[i]*w[i];j--){
			dp[j] = max(dp[j],dp[j-m[i]*w[i]]+m[i]*v[i]);
		}
	}
	cout << dp[W];
	return 0;
}
