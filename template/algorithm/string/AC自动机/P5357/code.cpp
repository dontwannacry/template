#include<bits/stdc++.h>
using namespace std;
int trans[200010][26],fail[200010],trielen,N;
char S[200010],T[2000010];
int geted[200010],getin[200010],endonit[200010];
void pushin(int T,char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		if(trans[now][tmp] == 0){trans[now][tmp] = ++trielen;}
		now = trans[now][tmp];
	}
	endonit[T] = now;
}
void findfail(){	
	queue<int>Q;
	for(int i = 0;i < 26;++i){if(trans[0][i]){Q.push(trans[0][i]);}}
	while(!Q.empty()){
		int now = Q.front();Q.pop();
		int u = fail[now];
		for(int i = 0;i < 26;++i){
			if(trans[now][i]){
				fail[trans[now][i]] = trans[u][i];
				getin[trans[u][i]]++;
				Q.push(trans[now][i]);
			}else{trans[now][i] = trans[u][i];}
		}
	}
}
void findS(char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		now = trans[now][tmp];
		geted[now]++;
	}
	queue<int>Q;
	for(int i = 1;i <= trielen;++i){if(!getin[i]) Q.push(i);}
	while(!Q.empty()){
		int now = Q.front();Q.pop();
		int v = fail[now];
		geted[v] += geted[now];
		--getin[v];
		if(!getin[v]) Q.push(v);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		cin >> S;
		pushin(i,S);
	}
	findfail();
	cin >> T;
	findS(T);
	for(int i = 1;i <= N;++i){cout << geted[endonit[i]] <<"\n";}
	return 0;
}
