#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
struct matrix{
	int m,n;
	long long num[110][110];
	matrix operator * (const matrix x)const{
		matrix re;
		re.m = m;re.n = x.n;
		memset(re.num,0,sizeof(re.num));
		for(int i = 1;i <= m;++i){
			for(int k = 1;k <= n;++k){
				for(int j = 1;j <= x.n;++j){
					re.num[i][j] += num[i][k]*x.num[k][j];
					//
					re.num[i][j] %= MOD;
				}
			}
		}
		return re;
	}
	void start(int N){
		memset(num,0,sizeof(num));
		n = m = N;
		for(int i = 1;i <= N;++i){
			num[i][i] = 1;
		}
	}
	void input(int M,int N){
		m = M;n = N;
		for(int i = 1;i <= m;++i){
			for(int j = 1;j <= n;++j){
				cin >> num[i][j];
			}
		}
	}
	void output(){
		for(int i = 1;i <= m;++i){
			for(int j = 1;j <= n;++j){
				cout << num[i][j] <<" ";
			}
			cout << "\n";
		}
	}
}st;
long long N,K;
matrix jc(matrix A,long long B){
	matrix sum = A,ans;
	ans.start(N);
	while(B){
		if(B&1){
			ans = (sum*ans);
		}
		sum = (sum*sum);
		B >>= 1;
	}
	return ans;
}
int main(){
	cin >> N >> K;
	st.input(N,N);
	st = jc(st,K);
	st.output();
	return 0;
}
