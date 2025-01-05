#include<bits/stdc++.h>
using namespace std;
long long A,M,O,B,ans;char in;
long long oul(long long N){
	long long res = N;
	for(long long i = 2;i*i <= N;++i){
		if(N%i == 0){
			res = res/i*(i-1);
			while(N%i == 0) N /= i;
		}
	}
	if(N > 1) res = res/N*(N-1);
	return res;
}
long long jc(long long A,long long B,const long long MOD){
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
	cin >> A >> M;
	O = oul(M);
	bool have = 0;
	while(cin >> in){
		B = B*10+in-'0';
		if(B > O){B %= O;have = 1;}
	}
	if(have)B += O;
	ans = jc(A,B,M);
	cout << ans;
	return 0;
}
