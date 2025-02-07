#include<bits/stdc++.h>
using namespace std;
int N;
long long dp[50010],Y[50010],X[50010],L,S[50010];
struct queue_max{
    int num[1000010],st,ed;
    void clear(){st = 1;ed = 0;}
    void push(int now){
        while(ed > st&&(1ll*(Y[now]-Y[num[ed]])*(X[num[ed]]-X[num[ed-1]]) <= 1ll*(Y[num[ed]]-Y[num[ed-1]])*(X[now]-X[num[ed]]))){--ed;}
        num[++ed] = now;
    }
    int pop(int K){
		while(ed > st&&Y[num[st+1]]-Y[num[st]] <= 1ll*K*(X[num[st+1]]-X[num[st]])){++st;}
		return num[st];
	}
}Q;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	memset(dp,0x80,sizeof(dp));
	cin >> N >> L;
	for(int i = 1;i <= N;++i){
		cin >> S[i];
		S[i] += S[i-1];
		X[i] = S[i]+i;
		Y[i] = X[i]*X[i]+((L+1)<<1)*X[i];
	}
	dp[0] = 0;
	Q.clear();
	Q.push(0);
	for(int i = 1;i <= N;++i){
		int P = Q.pop(2*X[i]);
		dp[i] = dp[P]+(L-X[i]+X[P]+1)*(L-X[i]+X[P]+1);
		Y[i] += dp[i];
		Q.push(i);
//		cout <<Q.st <<" "<<Q.ed<<" "<<P <<" "<< dp[i]<<"\n";
//		cout << X[i] <<" "<< Y[i]<<"\n";
	}
	cout << dp[N];
	return 0;
}
