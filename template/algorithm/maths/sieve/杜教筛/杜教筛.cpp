#include<bits/stdc++.h>
using namespace std;
int T,N,phi[3000010],mu[3000010],smu[3000010],prime[220010],primelen;
bool vis[3000010];
long long sphi[3000010];
unordered_map<int,int>smump;
unordered_map<int,long long>sphimp;
void init(){
	vis[1] = sphi[1] = smu[1] = mu[1] = phi[1] = 1;
    for(int i = 2;i <= 3000000;++i){
        if(!vis[i]){
        	phi[i] = i-1;
        	mu[i] = -1;
            prime[++primelen] = i;
        }
        smu[i] = smu[i-1]+mu[i];
        sphi[i] = sphi[i-1]+phi[i];
        for(int j = 1;j <= primelen&&i*prime[j]<=3000000;j++){
        	vis[i*prime[j]] = 1;
            if(i%prime[j] == 0){
				phi[i*prime[j]] = phi[i]*prime[j];
				mu[i*prime[j]] = 0;
				break;
			}
            else{
				phi[i*prime[j]] = phi[i]*(prime[j]-1);
				mu[i*prime[j]] = -mu[i];
			}
        }
    }
}
long long getsphi(long long N){
	if(N <= 3000000) return sphi[N];
	if(sphimp[N]) return sphimp[N];
	long long res = 1ll*N*(N+1)/2;
	for(long long i = 2,maxi;i <= N;i = maxi+1){
    	maxi = N/(N/i);
    	res -= (maxi-i+1)*getsphi(N/i);
	}
	return sphimp[N] = res;
}
int getsmu(long long N){
	if(N <= 3000000) return smu[N];
	if(smump[N]) return smump[N];
	int res = 1;
	for(long long i = 2,maxi;i <= N;i = maxi+1){
    	maxi = N/(N/i);
    	res -= (maxi-i+1)*getsmu(N/i);
	}
	return smump[N] = res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();
	cin >> T;
	while(T--){
		cin >> N;
		cout << getsphi(N) <<" "<<getsmu(N)<<"\n";
	}
	return 0;
}
