#include<bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;
struct matrix{
	int m,n;
	long long num[410][810];
	void input(int N){
		m = N;n = N*2;
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){cin >> num[i][j];}
			for(int j = N+1;j <= n;++j){
				if(j-N==i) num[i][j] = 1;
				else num[i][j] = 0;
			}
		}
	}
	void output(){
		for(int i = 1;i <= m;++i){
			for(int j = 1+m;j <= n;++j){
				cout << num[i][j] <<" ";
			}
			cout << "\n";
		}
	}
}st;
int N;
long long pow(long long A,long long B,const long long MOD){
	long long sum = A,ans = 1;
	while(B){
		if(B&1){
			ans = (sum*ans)%MOD;
		}
		sum = (sum*sum)%MOD;
		B >>= 1;
	}
	return ans;
}
void gauss(){
	for(int t = 1;t <= st.m;++t){
		if(st.num[t][t] == 0){
			for(int f = t+1;f <= st.m;++f){
				if(st.num[f][t] != 0){
					swap(st.num[f],st.num[t]);
					break;
				}
			}
			if(st.num[t][t] == 0){cout << "No Solution";return;}
		}
		long long x = st.num[t][t],npy = pow(x,MOD-2,MOD);
		for(int i = 1;i <= st.n;++i){st.num[t][i] = (st.num[t][i]*npy)%MOD;}
		for(int i = 1;i <= st.m;++i){
			if(i != t){
				x = st.num[i][t];
				for(int j = 1;j <= st.n;++j){
					st.num[i][j] -= x*st.num[t][j];
					st.num[i][j] = (st.num[i][j]+MOD*MOD)%MOD;
				}
			}	
		}
	}
	st.output();
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	st.input(N);
	gauss();
	return 0;
}
