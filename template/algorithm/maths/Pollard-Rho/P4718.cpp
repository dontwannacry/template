#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
ll N,ans,checkbase[8] = {2,3,5,7,11,13,17,37};
mt19937 randomplay(time(0));
ll Mul(ll A,ll B,const ll P){return ((ull)(A)*(ull)(B)-(ull)((ld)A/P*B)*P+P)%P;}
ll Pow(ll A,ll B,const ll P){
	ll res = 1;
    while(B){
        if(B&1){res = Mul(res,A,P);}
        A = Mul(A,A,P);
        B >>= 1;
    }
    return res;
}
bool Miller_Rabin(const ll x,const ll base){
    ll u = x-1;
    while(!(u&1)){u >>= 1;}
    ll v = Pow(base,u,x);
    if(v == 1){return 1;}
    while(u < x-1){
        if(v == x-1){return 1;}
        v = Mul(v,v,x);
        u <<= 1;
    }
    return 0;
}
bool isprime(ll x){
    if(x <= 1){return 0;}
    for(int i = 0;i < 8;++i){
        if(x == checkbase[i]){return 1;}
        if(x%checkbase[i] == 0){return 0;}
        if(!Miller_Rabin(x,checkbase[i])){return 0;}
    }
	return 1;
}
ll rho(ll N){
	ll x,y,z,c,g = 1;
	while(1){
		int i = 0,j = z = 1;
		x = y = randomplay()%N;
		c = randomplay()%N;
		while(++i){
			x = (Mul(x,x,N)+c)%N;
			z = Mul(z,abs(y-x),N);
			if(x == y||z == 0){break;}
			if(i == j||(i&127) == 0){
				g = __gcd(z,N);
				if(g != 1){return g;}
				if(i == j){y = x;j <<= 1;}
			}
		}		
	}
}
void prho(ll N,ll &ans){
	if(N <= ans){return;}
	if(isprime(N)){ans = N;return;}
	ll tiny = rho(N);
	while(N%tiny == 0){N /= tiny;}
	prho(N,ans);prho(tiny,ans);
}
void solve(){
	cin >> N;ans = 1;
	prho(N,ans);
	if(ans == N){cout << "Prime\n";}
	else{cout << ans << "\n";}
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;cin >> T;
    for(int i = 1;i <= T;++i){solve();}
    return 0;
}
