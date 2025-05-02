#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline void modadd(ll &a,ll b,const ll MOD){a += b;if(a >= MOD){a -= MOD;}}
ll qmul(ll A,ll B,const ll MOD){
    ll res = 0;
    while(B){
        if(B&1){modadd(res,A,MOD);}
        modadd(A,A,MOD);
        B >>= 1;
    }
    return res;
}
ll qpow(ll A,ll B,const ll MOD){
    ll res = 1;
    while(B){
        if(B&1){res = qmul(res,A,MOD);}
        A = qmul(A,A,MOD);
        B >>= 1;
    }
    return res;
}
bool Miller_Rabin(const ll x,const ll base){
    ll u = x-1;
    while(!(u&1)){u >>= 1;}
    ll v = qpow(base,u,x);
    if(v == 1){return 1;}
    while(u < x-1){
        if(v == x-1){return 1;}
        v = qmul(v,v,x);
        u <<= 1;
    }
    return 0;
}
bool isprime(ll x){
    if(x <= 1){return 0;}
    ll checkbase[8] = {2,3,5,7,11,13,17,37};
    for(int i = 0;i < 8;++i){
        if(x == checkbase[i]){return 1;}
        if(x%checkbase[i] == 0){return 0;}
        if(!Miller_Rabin(x,checkbase[i])){return 0;}
    }
	return 1;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T = 1;cin >> T;
    for(int i = 1;i <= T;++i){
        ll N;cin >> N;
        if(isprime(N)){cout << "YES\n";}
        else{cout << "NO\n";}
    }
	return 0;
}