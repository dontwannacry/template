#include<bits/stdc++.h>
using namespace std;
int N,M,can[110][110];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	memset(can,0x3f,sizeof(can));
	for(int i = 1;i <= N;++i) can[i][i] = 0;
	for(int i = 1;i <= M;++i){
		int u,v,w;
		cin >> u >> v >> w;
		can[u][v] = w;
		can[v][u] = w;
	}
	for(int k = 1;k <= N;++k){
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){
				can[i][j] = min(can[i][j],can[i][k]+can[k][j]);
			}
		}	
	}
	for(int i = 1;i <= N;++i){
		for(int j = 1;j <= N;++j){
			cout << (can[i][j] == 0x3f3f3f3f?0:can[i][j]) <<" ";
		}
		cout <<"\n";
	}
	return 0;
}
