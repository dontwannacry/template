#include<bits/stdc++.h>
using namespace std;
struct relation{long long M,A;}r[50],ANS;
int cnt,P;long long N,M;
long long mul(long long a,long long b,const long long mod){
    long long res=0;
    while(b>0){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}
long long Pow(long long A,long long B,const long long MOD){
	long long sum = A,ans = 1;
	while(B){
		if(B&1){ans = (sum*ans)%MOD;}
		sum = (sum*sum)%MOD;
		B >>= 1;
	}
	return ans;
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
long long fac_in_exlucas(long long N,const long long P,const long long MOD){
	if(!N) return 1;
	long long cycle = 1;
	for(long long i = 1;i <= MOD;++i){if(i%P){cycle=cycle*i%MOD;}}
	cycle = Pow(cycle,N/MOD,MOD);
	for(long long i = 1;i <= N%MOD;++i){if(i%P){cycle=cycle*i%MOD;}}
	return cycle*fac_in_exlucas(N/P,P,MOD)%MOD;
}
long long onecase(long long M,long long N,const long long P,const long long MOD){
	int cnt = 0;
	for(long long i = N;i;i /= P){cnt += i/P;}
	for(long long i = M;i;i /= P){cnt -= i/P;}
	for(long long i = N-M;i;i /= P){cnt -= i/P;}
	return Pow(P,cnt,MOD)*fac_in_exlucas(N,P,MOD)%MOD*Pow(fac_in_exlucas(M,P,MOD),MOD/P*(P-1)-1,MOD)%MOD*Pow(fac_in_exlucas(N-M,P,MOD),MOD/P*(P-1)-1,MOD)%MOD;
}
void exlucas(long long M,long long N,long long MOD){
	for(long long i = 2;i*i<=MOD;++i){
		if(MOD % i == 0){
			r[++cnt].M = 1;
			while(MOD % i == 0){
				MOD /= i;
				r[cnt].M *= i;
			}
			r[cnt].A = onecase(M,N,i,r[cnt].M);
		}
	}
	if(MOD > 1){r[++cnt].M = MOD,r[cnt].A = onecase(M,N,MOD,MOD);}
}
int main(){
	cin >> N >> M >> P;
	exlucas(M,N,P);
	ANS = r[1];
	for(int i = 2;i <= cnt;++i){solve(i);}
	cout << ANS.A;
	return 0;
}
