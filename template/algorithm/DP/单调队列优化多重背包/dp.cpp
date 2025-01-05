#include<bits/stdc++.h>
using namespace std;
struct queue_max{
    int num[40010],t[40010],st,ed;
    void clear(){st = 0;ed = -1;}
    void push(int w,int now,int val){
        while(num[ed]+(now-t[ed])*val < w&&ed >= st){--ed;}
        num[++ed] = w;
        t[ed] = now;
    }
    int topval(int now,int val){return num[st]+(now-t[st])*val;}
    void pop(){st++;}
}A;
int W,N;
int v[110],m[110],w[110],dp[40010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> W;
	for(int i = 1;i <= N;i++){cin >> v[i] >> w[i] >> m[i];}
	for(int i = 1;i <= N;i++){
		for(int mod = 0;mod < w[i];mod++){
			A.clear();
			for(int j = 0;mod+j*w[i] <= W;++j){
				A.push(dp[mod+j*w[i]],j,v[i]);
				dp[mod+j*w[i]] = A.topval(j,v[i]);
				if(j-A.t[A.st] >= m[i]) A.pop();
			}
		}
	}
	cout << dp[W];
	return 0;
}
