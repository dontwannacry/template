#include<bits/stdc++.h>
using namespace std;
bitset<2010>can[2010];
int N;
int main(){
ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		for(int j = 1;j <= N;++j){
			int a;
			cin >> a;
			can[i][j] = a;
		}
	}
	for(int k = 1;k <= N;++k){
		for(int i = 1;i <= N;++i){
			if(can[i][k]){
				can[i] = can[i]|can[k];
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
