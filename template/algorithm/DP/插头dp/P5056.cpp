#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[2][70010],ans;
int N,M,cas[70010],tranid[70010][13],caslen;
unordered_map<int,int>id;
char mp[16][16];
void init(){
	int len = 0,nowre = 0,maxre = 1<<((M+1)<<1);
	memset(tranid,-1,sizeof(tranid));
	while(nowre < maxre){
		len = 0;
		for(int j = 0;j <= M;++j){
			int p = (nowre>>(j<<1))&3;
			if(p == 1){++len;}
			if(p == 2){--len;}
			if(len < 0){break;}
		}
		if(len == 0){
			cas[caslen] = nowre;
			id[nowre] = caslen++;
		}
		nowre += 1;int addti = 0;
		while(((nowre>>addti)&3) == 3){nowre = nowre+(1<<addti);addti += 2;}
	}
	for(int i = 0;i < caslen;++i){
		for(int j = 0;j < M;++j){
			int p = (cas[i]>>(j<<1))&3,q = (cas[i]>>((j+1)<<1))&3;
			int blank = cas[i]-((p+(q<<2))<<(j<<1));
			if(!p&&!q){tranid[i][j] = id[blank+(9<<(j<<1))];}
			else if(p&&q){
				len = 0;
				if(p == 2&&q == 1){tranid[i][j] = id[blank];}
				else if(p == 1&&q == 1){
					for(int k = j+2;k <= M;++k){
						if(((blank>>(k<<1))&3) == 1){++len;}
						if(((blank>>(k<<1))&3) == 2){
							if(len){--len;}
							else{							
								tranid[i][j] = id[blank-(1<<(k<<1))];
								break;
							}
						}
					}
				}else if(p == 2&&q == 2){
					for(int k = j-1;k >= 0;--k){
						if(((blank>>(k<<1))&3) == 2){++len;}
						if(((blank>>(k<<1))&3) == 1){
							if(len){--len;}
							else{
								tranid[i][j] = id[blank+(1<<(k<<1))];
								break;
							}
						}
					}
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 0;i < N;++i){for(int j = 0;j < M;++j){cin >> mp[i][j];}}
	init();
	int tmp = 0;dp[tmp][0] = 1;
	for(int i = 0;i < N;++i){
		for(int j = 0;j < M;++j){
			if(mp[i][j] == '.'){ans = 0;}
			tmp ^= 1;
			memset(dp[tmp],0,sizeof(dp[tmp]));
			int maxre = 1<<((M+1)<<1);
			if(j == 0){maxre >>= 2;}
			for(int t = 0;t < caslen;++t){
				int nowre = cas[t],truere = nowre,trueid;
				if(nowre >= maxre){break;}
				if(j == 0){truere = nowre<<2;}
				trueid = id[truere];
				int p = (truere>>(j<<1))&3,q = (truere>>((j+1)<<1))&3;
				if(mp[i][j] == '*'){
					if(p||q){continue;}
					dp[tmp][trueid] += dp[tmp^1][t];
					continue;
				}
				int blank = truere-((p+(q<<2))<<(j<<1));
				if(p == 1&&q == 2){if(!blank){ans += dp[tmp^1][t];}}
				else if((!p||!q)&&(p|q)){
					q = p|q;
					int tmpid = id[blank+(q<<(j<<1))];
					dp[tmp][tmpid] += dp[tmp^1][t];
					tmpid = id[blank+(q<<((j+1)<<1))];
					dp[tmp][tmpid] += dp[tmp^1][t];
				}
				else{dp[tmp][tranid[trueid][j]] += dp[tmp^1][t];}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}