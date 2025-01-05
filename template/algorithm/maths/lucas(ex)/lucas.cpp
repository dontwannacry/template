#include<bits/stdc++.h>
using namespace std;
long long T,N,M,P;
long long pow(long long A,long long B,const long long MOD){
	long long sum = A,ans = 1;
	while(B){
		if(B&1){ans = (sum*ans)%MOD;}
		sum = (sum*sum)%MOD;
		B >>= 1;
	}
	return ans;
}
long long factorial(long long N,const long long MOD){
	long long res = 1;
	for(long long i = 2;i <= N;++i) res = res*i%MOD;
	return res;
}
long long C(long long M,long long N,const long long MOD){
	if(N < M) return 0;
	long long son = factorial(N,MOD);
	long long mom = (pow(factorial(M,MOD),MOD-2,MOD)*pow(factorial(N-M,MOD),MOD-2,MOD))%MOD;
	return (son*mom)%MOD;
}
long long Lucas(long long M,long long N,const long long MOD){
	if(N < M)return 0;if(M == 0||M == N) return 1;
	return (C(M%MOD,N%MOD,MOD)*Lucas(M/MOD,N/MOD,MOD))%MOD;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> T;
	while(T--){
		cin >> N >> M >> P;
		M += N;
		cout << Lucas(N,M,P) <<"\n";
	}
	return 0;
}
