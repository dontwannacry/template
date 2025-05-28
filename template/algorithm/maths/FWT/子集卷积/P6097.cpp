#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000009,NY2 = 500000005;
int N,BN,A[21][(1<<20)+5],B[21][(1<<20)+5],C[21][(1<<20)+5],cnt[(1<<20)+5];
void FWTor(int *A){
	for(int re = 1;re <= BN;++re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				A[j+block] += A[j];
				if(A[j+block] >= MOD){A[j+block] -= MOD;}
			}
		}
	}
}
void IFWTor(int *A){
	for(int re = BN;re >= 1;--re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				A[j+block] -= A[j];
				if(A[j+block] < 0){A[j+block] += MOD;}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> BN;N = (1<<BN);
	for(int i = 1;i < N;++i){cnt[i] = cnt[i>>1]+(i&1);}
	for(int i = 0;i < N;++i){cin >> A[cnt[i]][i];}
	for(int i = 0;i < N;++i){cin >> B[cnt[i]][i];}
	for(int i = 0;i <= BN;++i){FWTor(A[i]);}
	for(int i = 0;i <= BN;++i){FWTor(B[i]);}
	for(int i = 0;i <= BN;++i){
		for(int j = 0;j <= i;++j){
			for(int k = 0;k < N;++k){
				C[i][k] = (C[i][k]+1ll*A[j][k]*B[i-j][k])%MOD;
			}
		}
	}
	for(int i = 0;i <= BN;++i){IFWTor(C[i]);}
	for(int i = 0;i < N;++i){cout << C[cnt[i]][i] << " ";}cout << "\n";
	return 0;
}
