#include<bits/stdc++.h>
using namespace std;
int N,M,tot,ans;
struct Unionfind{
	int fa[200010],si[200010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return ancestor(fa[now]);
	}
	bool equalancestor(int a,int b){
		a = ancestor(a);b = ancestor(b);
		return a == b;
	}
	void mix(int a,int b){
		a = ancestor(a);b = ancestor(b);
		if(si[a] > si[b]) swap(a,b);
		fa[a] = b;
		si[b] = max(si[a]+1,si[b]);
	}
	void start(int len){
		for(int i = 1;i <= len;++i){
			fa[i] = i;
			si[i] = 1;
		}
	}
}U;
struct bian{
	int u,v,w;
	bool operator < (const bian x)const{return w < x.w;}
}line[200010];
void kruskal(){
	sort(line+1,line+1+M);
	U.start(N);
	for(int i = 1;i <= M;++i){
		if(U.equalancestor(line[i].u,line[i].v))continue;
		U.mix(line[i].u,line[i].v);
		ans += line[i].w;
		tot++;
	
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){cin >> line[i].u >> line[i].v >> line[i].w;}
	kruskal();
	if(tot == N-1)cout << ans;
	else cout << "orz";
	return 0;
}
