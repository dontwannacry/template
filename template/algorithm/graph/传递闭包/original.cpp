#include<bits/stdc++.h>
using namespace std;
int N,can[110][110];
int main(){	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		for(int j = 1;j <= N;++j){
			cin >> can[i][j];
		}
	}
	for(int k = 1;k <= N;++k){
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){
				can[i][j] = can[i][j]|(can[i][k]&can[k][j]);
			}
		}	
	}
	for(int i = 1;i <= N;++i){
		for(int j = 1;j <= N;++j){
			cout << can[i][j] <<" ";
		}
		cout <<"\n";
	}
	return 0;
}
