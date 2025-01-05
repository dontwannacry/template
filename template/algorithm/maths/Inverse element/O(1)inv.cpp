#include<bits/stdc++.h>
using namespace std;
long long N,P,inv[3000600];
int read(){
	int x = 0;char g;
	g = getchar();
	while((g < '0'||g > '9')&&g !=EOF)g = getchar();
	while('0' <= g&&g <= '9'&&g !=EOF){
		x *= 10;x += g - '0';
		g = getchar();
	}
	return x;
}
void init(){
	inv[1] = 1;
	for(int i = 2;i <= N;++i){
		inv[i] = (P-inv[P%i]*(P/i)%P);
	}
}
int main(){
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	N = read();P = read();
	init();
	for(int i = 1;i <= N;++i){
		cout << inv[i] <<"\n";
	}
	return 0;
}
