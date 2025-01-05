#include<bits/stdc++.h>
using namespace std;
long long N,MM = 1,a[11],m[11],M[11],t[11],ans,y;
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1,y = 0;
        return a;
    }
    long long gcd = exgcd(b,a%b,y,x);
    y -= a / b * x;
    return gcd;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		cin >> m[i] >> a[i];
		MM *= m[i];
	}
	//cout << MM <<"\n";
	for(int i = 1;i <= N;++i){
		M[i] = MM/m[i];
		exgcd(M[i],m[i],t[i],y);
		t[i] = (m[i]+t[i]%m[i])%m[i];
		for(int j = 1;j <= a[i];++j){
			ans = (ans + M[i]*t[i])%MM;
		}
		//cout << M[i]<<" "<<t[i]<<" "<<ans<<"\n";
	}
	cout << ans;
	return 0;
}
