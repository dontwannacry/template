#include<bits/stdc++.h>
using namespace std;
int N,D,T,cnt,prime[80010],phi[1000010];
int li[1000010],len,chk[100],tot;
bool vis[1000010],have[1000010];
void init(){
	phi[1] = vis[1] = 1;
	have[1] = have[2] = have[4] = 1;
    for(int i = 2;i <= 1000000;++i){
        if(!vis[i]){
        	phi[i] = i-1;
            prime[++cnt] = i;
            if(i != 2){
				long long now = i;
				while(now <= 1000000){
					have[now] = 1;
					if(now <= 500000){have[now*2] = 1;}
					now *= i;
				}
			}
        }
        for(int j = 1;j <= cnt&&i*prime[j]<=1000000;j++){
        	vis[i*prime[j]] = 1;
            if(i%prime[j] == 0){phi[i*prime[j]] = phi[i]*prime[j];break;}
            else  phi[i*prime[j]] = phi[i]*(prime[j]-1);
        }
    }
}
int Pow(int A,int B,const int MOD){
	int ans = 1;
	while(B){
		if(B&1){ans = (1ll*A*ans)%MOD;}
		A = (1ll*A*A)%MOD;
		B >>= 1;
	}
	return ans;
}
int gcd(int A,int B){
	if(A%B==0){return B;}
	return gcd(B,A%B);
}
bool check(int a){
	if(Pow(a,phi[N],N)!=1){return 0;}
	for(int i = 1;i <= tot;++i){
		if(Pow(a,phi[N]/chk[i],N)==1){
			return 0;
		}
	}
	return 1;
}
void solve(){
	cin >> N >> D;
	if(!have[N]){
		cout << "0\n";
		cout << "\n";
		return;
	}
	tot = 0;
	int last = phi[N]; 
	for(int i = 1;prime[i]*prime[i] <= N;++i){
		if(last%prime[i] == 0){
			chk[++tot] = prime[i];
			while(last%prime[i] == 0){last/=prime[i];}
		}
	}
	if(last > 1){chk[++tot] = last;}
	len = 0;
	for(int i = 1;i <= N;++i){
		if(check(i)){
			li[++len] = i;
			break;
		}
	}
	for(int i = 2;i <= phi[N];++i){
		if(gcd(i,phi[N]) == 1){
			li[++len] = Pow(li[1],i,N);
		}
	}
	sort(li+1,li+1+len);
	cout << len <<"\n";
	for(int i = D;i <= len;i += D){cout << li[i] <<" ";}
	cout << "\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();
	int T;cin >> T;
	while(T--){solve();}
	return 0;
}
