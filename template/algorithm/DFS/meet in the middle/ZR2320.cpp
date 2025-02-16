#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&-(x))
typedef long long ll;
ll N,M,A[25],fr[25],tot,sig[(1<<20)+5],sum[(1<<20)+5],dp[11][(1<<20)+5],ans;
vector<ll>C[(1<<10)+5];
void solve(int T,int re,int up,int cas){
	if(T < cas){
		if(!cas){C[re].push_back(up);}
		else{
			for(int i = 0;i < (1<<cas);++i){
				auto it = lower_bound(C[i].begin(),C[i].end(),-up);
				if(it != C[i].end()){dp[1][re+i] = min(dp[1][re+i],abs(*it+up));}
				if(it != C[i].begin()){dp[1][re+i] = min(dp[1][re+i],abs(*(it-1)+up));}
			}
		}
		return;
	}
	solve(T-1,re+(1<<T),up+A[T],cas);
	solve(T-1,re+(1<<T),up-A[T],cas);
	solve(T-1,re,up,cas);
}
void middlesolve(){
	ans = 0;int mid = N/2;
	for(int i = 1;i < (1<<N);++i){dp[1][i] = dp[0][i];}
	solve(mid-1,0,0,0);
	for(int i = 0;i < (1<<mid);++i){sort(C[i].begin(),C[i].end());}
	solve(N-1,0,0,mid);
	for(int i = 1;i < (1<<N);++i){
		dp[1][i] = (sum[i]-dp[1][i])/2;
		dp[1][i] = dp[1][i]*dp[1][i]+(sum[i]-dp[1][i])*(sum[i]-dp[1][i]);
		ans += dp[1][i];
	}
	cout << ans << "\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("C.in","r",stdin);
	cin >> N >> M;
	for(int i = 0;i < N;++i){cin >> A[i];sum[1<<i] = A[i];}
	for(int i = 1;i < (1<<N);++i){
		sum[i] = sum[i-lowbit(i)]+sum[lowbit(i)];
		dp[0][i] = sum[i]*sum[i];
		ans += dp[0][i];
	}
	cout << ans << "\n";
	middlesolve();
	for(int i = 1;i < (1<<N);++i){sum[i] = sum[i]*sum[i];}
	for(int t = 2;t < M;++t){
		ans = 0;
		for(int i = 1;i < (1<<N);++i){dp[t][i] = dp[t-1][i];}
		for(int i = 1;i < (1<<N);++i){
			int i2 = i;
			for(int j = N-1;j >= 0;--j){if(i&(1<<j)){i2 -= (1<<j);break;}}
			for(int j = i2;j > 0;j = (j-1)&i2){
				if(dp[t-1][j]+sum[i-j] < dp[t][i]){dp[t][i] = dp[t-1][j]+sum[i-j];}
			}
			ans += dp[t][i];
		}
		cout << ans << "\n";
	}
	return 0;
}
