#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
mt19937 randomplay(time(0));
unordered_map<ull,int>fir;
vector<int>ne[55];
ull val[55],ans[55],Hnum,rndpw;
int N;
inline ull shift(ull num){
	num ^= rndpw;
	num ^= (num<<11);
	num ^= (num>>7);
	num ^= (num<<3);
	num ^= rndpw;
	return num;
}
void dfs(int now,int fa){
	val[now] = 1;
	for(int v:ne[now]){
		if(v == fa){continue;}
		dfs(v,now);
		val[now] += shift(val[v]);
	}
}
void getval(int now,int fa){
	for(int v:ne[now]){
		if(v == fa){continue;}
		ans[v] = val[v]+shift(ans[now]-shift(val[v]));
		getval(v,now);
	}
}
void clear(){
	for(int i = 1;i <= N;++i){ne[i].clear();}
	memset(val,0,sizeof(val));
	memset(ans,0,sizeof(ans));
	Hnum = 0;
}
void solve(int T){
	clear();
	cin >> N;
	for(int i = 1;i <= N;++i){
		int f;cin >> f;
		if(f){
			ne[i].push_back(f);
			ne[f].push_back(i);
		}
	}
	dfs(1,0);
	ans[1] = val[1];
	getval(1,0);
	sort(ans+1,ans+1+N);
	for(int i = 1;i <= N;++i){Hnum = Hnum*29+ans[i];}
	if(fir.find(Hnum) == fir.end()){fir[Hnum] = T;}
	cout << fir[Hnum] <<"\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N;cin >> N;rndpw = randomplay();
	for(int i = 1;i <= N;++i){solve(i);}
	return 0;
}
