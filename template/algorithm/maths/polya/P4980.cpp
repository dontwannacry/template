#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int N,ans;
int phi(int x){
    int res = x;
    for(int i = 2;i*i <= x;++i){
        if(x%i == 0){
            res -= res/i;
            while(x%i == 0){x /= i;}
        }
    }
    if(x != 1){res -= res/x;}
    return res;
}
int Pow(int A,int B){
    int res = 1;
    while(B){
        if(B&1){res = 1ll*res*A%MOD;}
        A = 1ll*A*A%MOD;
        B >>= 1;
    }
    return res;
}
void modadd(int &a,int b){a += b;if(a >= MOD){a -= MOD;}}
void solve(){
    cin >> N;ans = 0;
    for(int i = 1;i*i <= N;++i){
        if(N%i){continue;}
        int pi = phi(i),po = Pow(N,N/i-1);
        modadd(ans,1ll*pi*po%MOD);
        if(i*i != N){
            pi = phi(N/i),po = Pow(N,i-1);
            modadd(ans,1ll*pi*po%MOD);
        }
    }
    cout << ans << "\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;cin >> T;
    for(int i = 1;i <= T;++i){solve();}
	return 0;
}