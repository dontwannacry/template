#include<bits/stdc++.h>
using namespace std;
char str[1000010];
int border[1000010],len,M;
int up[1000010][20],deep[1000010];
vector<int>ne[1000010];
void dfs(int now){
	for(int i = 0;i < ne[now].size();++i){
		if(ne[now][i] != up[now][0]){
			deep[ne[now][i]] = deep[now]+1;
			up[ne[now][i]][0] = now;
			dfs(ne[now][i]);
		}
	}
}
void init(){
	for(int t = 1;t <= 19;++t){
		for(int i = 0;i <= len;++i){
			up[i][t] = up[up[i][t-1]][t-1];
		}
	}
}
int LCA(int a,int b){
	if(deep[a] > deep[b])swap(a,b);
	for(int i = 19;i >= 0;--i){
		if(deep[up[b][i]] >= deep[a]){
			b = up[b][i];
		}
	}
	if(a == b)return a;
	for(int i = 19;i >= 0;--i){
		if(up[a][i] != up[b][i]){
	 		a = up[a][i];
			b = up[b][i];
		}
	}
	return up[a][0];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> (str+1);
	len = strlen(str+1);
	ne[0].push_back(1);
	for(int i = 2;i <= len;++i){
		int p = border[i-1];
		while(p){
			if(str[p+1] == str[i]) break;
			p = border[p];
		}
		if(str[p+1] == str[i]) border[i] = p+1;
		else border[i] = 0;
		ne[border[i]].push_back(i);
	}
	dfs(0);
	init();
	cin >> M;
	for(int i = 1;i <= M;++i){
		int x,y;cin >> x >> y;
		cout << LCA(border[x],border[y]) <<"\n";
	}
	return 0;
}
