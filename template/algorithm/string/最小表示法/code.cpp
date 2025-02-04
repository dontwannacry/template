#include<bits/stdc++.h>
using namespace std;
int N;
char str[10000010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		cin >> str[i];
		str[i+N] = str[i];
	}
	int i = 1,j = 2;
	while(i <= N&&j <= N){
		int k = 0;
		while(str[i+k] == str[j+k]&&k < N) ++k;
		if(str[i+k] > str[j+k]) i += k+1;
		else j += k+1;
		if(i == j) ++j;
	}
	if(j < i) swap(i,j);
	cout << i-1;
	return 0;
}
