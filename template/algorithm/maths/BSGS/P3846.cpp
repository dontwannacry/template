#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,B,P;
map<ll,ll>f;
ll BSGS(ll r,ll a,ll P){
	ll S = sqrt(P)+0.999,p = 1,pp = 1;
	for(int i = 1;i <= S;++i){f[a*(p = p*r%P)%P] = i;}
	for(int i = 1;i <= S;++i){
		if(f.find(pp = p*pp%P) != f.end()){
			return i*S-f[pp];
		}
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> P >> B >> N;
    ll res = BSGS(B,N,P);
	if(res == -1){cout << "no solution\n";}
	else{cout << res << "\n";}
	return 0;
}