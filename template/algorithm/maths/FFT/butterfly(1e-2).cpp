#include<bits/stdc++.h>
using namespace std;
const double PI = acosl(-1.0),eps=1e-2;
complex<double>F[1<<21],G[1<<21],tmp[1<<21];
int N,M,sum,LN,FN;
void FFT(complex<double> *f,int LN,int con){
	int FN = (1<<LN),FN2 = FN>>1;
	for(int re = LN;re >= 1;--re){
		for(int i = 0;i < FN;++i) tmp[i] = f[i];
		int nowre = (1<<re),block = nowre>>1,TN = FN>>re;
		complex<double>wn(cos(PI/TN),sin(con*PI/TN)),w0(1,0);
		for(int i = 0;i < TN;++i){
			for(int j = 0;j < block;++j){
				f[i*block+j] = tmp[i*block*2+j]+w0*tmp[block*(i*2+1)+j];
				f[i*block+j+FN2] = tmp[i*block*2+j]-w0*tmp[block*(i*2+1)+j];
			}
			w0 *= wn;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;sum = M+N;
	while(sum){++LN;sum>>=1;}
	sum = M+N;FN = 1<<LN;
	for(int i = 0;i <= N;++i){cin >> F[i];}
	for(int i = 0;i <= M;++i){cin >> G[i];}
	FFT(F,LN,1);
	FFT(G,LN,1);
	for(int i = 0;i < FN;++i) F[i] = F[i]*G[i];
	FFT(F,LN,-1);
	for(int i = 0;i <= sum;++i){cout << int((F[i].real()/FN)+eps) <<" ";}
	return 0;
}
