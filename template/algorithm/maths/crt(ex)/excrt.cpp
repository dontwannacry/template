#include<bits/stdc++.h>
using namespace std;
struct relation{
	long long M,A;
}r[100010],ANS;
long long mul(long long a,long long b,long long mod){
    long long res=0;
    while(b>0){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1,y = 0;
        return a;
    }
    long long gcd = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return gcd;
}
void solve(int T){
	long long A1,A2;
	long long D = exgcd(ANS.M,r[T].M,A1,A2);
	//if((ANS.A-r[T].A)%D != 0)return 0;
	long long K = (r[T].A-ANS.A%r[T].M+r[T].M)%r[T].M/D;
	long long MOD = r[T].M/D;
	A1 = mul(A1,K,MOD);
	ANS.A += ANS.M*A1;
	ANS.M *= MOD;
	ANS.A = (ANS.A%ANS.M+ANS.M)%ANS.M;
}
int main(){
	int N;cin >> N;
	for(int i = 1;i <= N;++i){cin >> r[i].M >> r[i].A;}
	ANS = r[1];
	for(int i = 2;i <= N;++i){solve(i);}
	cout << ANS.A;
	return 0;
}
