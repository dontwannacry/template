#include<bits/stdc++.h>
using namespace std;
int N,MOD;
struct matrix{
	int num[610][610];
	void input(int N){
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){
				cin >> num[i][j];
			}
		}
	}
}st;
int gauss(matrix A){
    int res = 1,w = 1;
    for(int i = 1;i <= N;++i){
        for(int j = i+1;j <= N;++j){
            while(A.num[i][i]){
                int ti = A.num[j][i]/A.num[i][i];
                for(int k = i;k <= N;++k){
                    A.num[j][k] = (A.num[j][k]-1ll*ti*A.num[i][k]%MOD+MOD)%MOD;
                }
                swap(A.num[i],A.num[j]);w = -w;
            }
            swap(A.num[i],A.num[j]);w = -w;
        }
    }
    for(int i = 1;i <= N;++i){res = 1ll*res*A.num[i][i]%MOD;}
    return (1ll*res*w+MOD)%MOD;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> MOD;
	st.input(N);
	int res = gauss(st);
    cout << res << "\n";
	return 0;
}