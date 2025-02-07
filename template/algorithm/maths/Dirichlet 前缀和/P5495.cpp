#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
uint N,seed,A[20000010];
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
int len,prime[1300100];
bool vis[20000010];
void init(){
    vis[1] = 1;
    for(int i = 2;i <= N;++i){
        if(!vis[i]){prime[++len] = i;}
        for(int j = 1;j <= len&&i*prime[j]<=N;++j){
            vis[i*prime[j]]=1;
            if(i%prime[j] == 0)break;
        }
    }
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> seed;
    for(int i = 1;i <= N;++i){A[i] = getnext();}
    init();
    for(int i = 1;i <= len;++i){
        for(int j = 1;j <= N/prime[i];++j){
            A[j*prime[i]] += A[j];
        }
    }
    for(int i = 1;i <= N;++i){A[i] ^= A[i-1];}
    cout << A[N];
	return 0;
}