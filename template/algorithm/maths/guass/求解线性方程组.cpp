#include<bits/stdc++.h>
using namespace std;
const long double eps = 1e-6;
struct matrix{
	int m,n;
	long double num[110][110];
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
int N,ret[110];bool re1 = 0,re2 = 1;
bool equal(long double A,long double B){
	long double re = A-B;
	return re < eps && re > -eps;
}
matrix gauss(matrix A){
	int line = 1;
	for(int t = 1;t <= A.m;++t){
		if(equal(A.num[line][t],0)){
			for(int f = line+1;f <= A.m;++f){
				if(!equal(A.num[f][t],0)){
					swap(A.num[f],A.num[line]);
					break;
				}
			}
			if(equal(A.num[line][t],0)){re1 = 1;continue;}
		}
		long double x = A.num[line][t];
		for(int i = 1;i <= A.n;++i){
			A.num[line][i] /= x;
		}
		for(int i = 1;i <= A.m;++i){
			if(i != line){
				x = A.num[i][t];
				for(int j = 1;j <= A.n;++j){
					A.num[i][j] -= x*A.num[line][j];
				}
			}	
		}
		ret[line++] = t;
	}
	return A;
}
int main(){
	cin >> N;
	st.input(N,N+1);
	st = gauss(st);
	//st.output();
	for(int i = 1;i <= N;++i){
		if(equal(st.num[i][ret[i]],0)&&!equal(st.num[i][N+1],0)){
			re2 = 0;break;
		}
	}
	if(re1){
		if(re2) cout << 0;
		else cout << -1;
		return 0;
	}
	for(int i = 1;i <= N;++i){
		printf("x%d=%.2Lf\n",i,st.num[i][N+1]);
	}
	return 0;
}
