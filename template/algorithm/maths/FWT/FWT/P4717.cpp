#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353,NY2 = 499122177;
int N,BN,A[1<<17],B[1<<17],fwta[1<<17],fwtb[1<<17],fwtc[1<<17];
void in(){
	for(int i = 0;i < N;++i){fwta[i] = A[i];}
	for(int i = 0;i < N;++i){fwtb[i] = B[i];}
}
void out(){
	for(int i = 0;i < N;++i) cout << fwtc[i] <<" ";
	cout << "\n";
}
void sub_or(){
	in();
	for(int re = 1;re <= BN;++re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				fwta[j+block] += fwta[j];
				if(fwta[j+block]>=MOD) fwta[j+block]-=MOD;
			}
			for(int j = i;j < i+block;++j){
				fwtb[j+block] += fwtb[j];
				if(fwtb[j+block]>=MOD) fwtb[j+block]-=MOD;
			}
		}
	}
	for(int i = 0;i < N;++i){fwtc[i] = 1ll*fwta[i]*fwtb[i]%MOD;}
	for(int re = BN;re >= 1;--re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				fwtc[j+block] -= fwtc[j];
				if(fwtc[j+block]<0) fwtc[j+block]+=MOD;
			}
		}
	}
	out();
}
void sub_and(){
	in();
	for(int re = 1;re <= BN;++re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				fwta[j] += fwta[j+block];
				if(fwta[j]>=MOD) fwta[j]-=MOD;
			}
			for(int j = i;j < i+block;++j){
				fwtb[j] += fwtb[j+block];
				if(fwtb[j]>=MOD) fwtb[j]-=MOD;
			}
		}
	}
	for(int i = 0;i < N;++i){fwtc[i] = 1ll*fwta[i]*fwtb[i]%MOD;}
	for(int re = BN;re >= 1;--re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				fwtc[j] -= fwtc[j+block];
				if(fwtc[j]<0) fwtc[j]+=MOD;
			}
		}
	}
	out();
}
void sub_xor(){
	in();
	for(int re = 1;re <= BN;++re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				int a = fwta[j],b = fwta[j+block];
				fwta[j] = (a+b)%MOD;fwta[j+block] = (a-b+MOD)%MOD;
			}
			for(int j = i;j < i+block;++j){
				int a = fwtb[j],b = fwtb[j+block];
				fwtb[j] = (a+b)%MOD;fwtb[j+block] = (a-b+MOD)%MOD;
			}
		}
	}
	for(int i = 0;i < N;++i){fwtc[i] = 1ll*fwta[i]*fwtb[i]%MOD;}
	for(int re = BN;re >= 1;--re){
		int nowre = (1<<re);
		for(int i = 0;i < N;i+=nowre){
			int block = nowre>>1;
			for(int j = i;j < i+block;++j){
				int a = fwtc[j],b = fwtc[j+block];
				fwtc[j] = (1ll*a+b)*NY2%MOD,fwtc[j+block] = (1ll*a-b+MOD)*NY2%MOD;
			}
		}
	}
	out();
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> BN;N = (1<<BN);
	for(int i = 0;i < N;++i){cin >> A[i];}
	for(int i = 0;i < N;++i){cin >> B[i];}
	sub_or();
	sub_and();
	sub_xor();
	return 0;
}
