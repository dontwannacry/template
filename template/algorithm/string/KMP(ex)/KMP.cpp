#include<bits/stdc++.h>
using namespace std;
char S[1000010],T[1000010];
int lens,lent,border[1000010];
void init(int *border,int len,char *str){
	for(int i = 2;i <= len;++i){
		int p = border[i-1];
		while(p){
			if(str[p+1] == str[i]) break;
			p = border[p];
		}
		if(str[p+1] == str[i]) border[i] = p+1;
		else border[i] = 0;
	}
}
int matching(char *str,int len1,char *S,int len2,int *border){
	int res = 0;
	for(int now = 1;now <= len1;++now){
		while(res){
			if(str[now] == S[res+1]){break;}
			res = border[res];
		}
		if(str[now] == S[res+1]){++res;}
		if(res == len2){
			cout << now-len2+1 <<"\n";
			res = border[res];
		}
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> (S+1);lens = strlen(S+1);
	cin >> (T+1);lent = strlen(T+1);
	init(border,lent,T);
	matching(S,lens,T,lent,border);
	for(int i = 1;i <= lent;++i){cout << border[i] <<" ";}
	return 0;
}
