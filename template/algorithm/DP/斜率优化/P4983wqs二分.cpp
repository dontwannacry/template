#include<bits/stdc++.h>
using namespace std;
int N,L,T[100010];
long long dp[100010],Y[100010],S[100010];
struct queue_max{
    int num[100010],st,ed;
    void clear(){st = 1;ed = 0;}
    void push(int now){
        while(ed > st&&((long double)(Y[now]-Y[num[ed]])/(S[now]-S[num[ed]]) <= (long double)(Y[num[ed]]-Y[num[ed-1]])/(S[num[ed]]-S[num[ed-1]]))){--ed;}
        num[++ed] = now;
    }
    int pop(int K){
		while(ed > st&&(long double)(Y[num[st+1]]-Y[num[st]])/(S[num[st+1]]-S[num[st]]) <= 1ll*K){++st;}
		return num[st];
	}
}Q;
int solve(long long AE86){
	//cout << AE86<<":\n";
	Q.clear();
	Q.push(0);
	for(int i = 1;i <= N;++i){
		int P = Q.pop(2*S[i]);
		dp[i] = dp[P]+(S[i]-S[P]+1)*(S[i]-S[P]+1)+AE86;
		T[i] = T[P]+1;
		Y[i] += dp[i];
		//cout << P <<" :"<<dp[i]<<"\n";
		Q.push(i);
	}
	for(int i = 1;i <= N;++i) Y[i] -= dp[i];
	return T[N];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> L;
	for(int i = 1;i <= N;++i){
		cin >> S[i];
		S[i] += S[i-1];
		Y[i] = S[i]*S[i]-2*S[i];
	}
	long long s = 0,e = 1e18,mid;
	while(s <= e){
		mid = (s+e)/2;
		int res = solve(mid);
		if(res < L){e = mid-1;}
		else if(res > L){s = mid+1;}
		else break;
	}
	cout << dp[N]-1ll*L*mid;
	return 0;
}
