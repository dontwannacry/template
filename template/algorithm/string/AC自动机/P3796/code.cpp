#include<bits/stdc++.h>
using namespace std;
int trans[11010][26],fail[11010],trielen,N,cnt[11010],maxcnt;
char S[155][75],T[1000010];
vector<int>endonit[11010],ANS;
void pushin(int T,char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		if(trans[now][tmp] == 0){trans[now][tmp] = ++trielen;}
		now = trans[now][tmp];
	}
	endonit[now].push_back(T);
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
				Q.push(trans[now][i]);
			}else{trans[now][i] = trans[u][i];}
		}
	}
}
void clear(){
	memset(trans,0,sizeof(trans));
	memset(fail,0,sizeof(fail));
	memset(cnt,0,sizeof(cnt));
	trielen = maxcnt = 0;
	for(int i = 1;i <= 10500;++i) endonit[i].clear();
	ANS.clear();
}
int findS(char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		now = trans[now][tmp];
		int p = now;
		while(p){
			for(auto now:endonit[p]){cnt[now]++;}
			p = fail[p];
		}
	}
	return now;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> N){
		if(N == 0) break;
		clear();
		for(int i = 1;i <= N;++i){
			cin >> S[i];
			pushin(i,S[i]);
		}
		findfail();
		cin >> T;
		findS(T);
		for(int i = 1;i <= N;++i){
			if(maxcnt < cnt[i]){
				maxcnt = cnt[i];
				ANS.clear();
			}
			if(maxcnt == cnt[i]) ANS.push_back(i);
		}
		cout << maxcnt <<"\n";
		for(auto i:ANS){cout << S[i] <<"\n";}
	}
	return 0;
}
