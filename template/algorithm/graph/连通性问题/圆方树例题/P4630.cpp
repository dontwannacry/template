#include<bits/stdc++.h>
using namespace std;
int N,M,stake[100010],len;
int dfn[100010],low[100010],si[200010],cnt,all;
int head[100010],ne[400010],to[400010],tot = 1;
vector<int>E[200010];
long long ans,S[200010],have;
bool vis[200010];
void push_back(int u,int v){
	ne[++tot] = head[u];to[head[u] = tot] = v;
	ne[++tot] = head[v];to[head[v] = tot] = u;
}
void dfs(int now,int fa){
	low[now] = dfn[now] = ++cnt;
	stake[++len] = now;
	int son = 0;
	for(int i = head[now];i;i = ne[i]){
		//if(i == (la^1))continue;
		int v = to[i];
		if(fa == v)continue;
		if(!dfn[v]){
			son++;
			dfs(v,now);
			low[now] = min(low[now],low[v]);
			if(low[v] >= dfn[now]){
				++all;
				while(stake[len] != v) E[all+N].push_back(stake[len--]);
				E[all+N].push_back(v);len--;
				E[all+N].push_back(now);
			}
		}else low[now] = min(low[now],dfn[v]);
	}
	if(fa == -1&&son == 0) E[++all+N].push_back(now);
}
void getsi(int now,int fa){
	vis[now] = 1;
	if(now <= N) S[now] = 1;
	for(int v:E[now]){
		if(v == fa) continue;
		getsi(v,now);
		S[now] += S[v];
	}
}
void dfsdp(int now,int fa){
	S[now] = 0;
	for(int v:E[now]){
		if(v == fa) continue;
		dfsdp(v,now);
		ans += si[now]*S[v]*S[now];
		S[now] += S[v];
	}
	if(now <= N) S[now]++;
	if(now <= N){ans -= (have-S[now])*(S[now]-1)+have-1;}
	else{ans += si[now]*(have-S[now])*(S[now]);}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int u,v;cin >> u >> v;
		push_back(u,v);
	}
	for(int i = 1;i <= N;++i)if(!dfn[i]){len = 0;dfs(i,-1);} 
	for(int i = 1;i <= N;++i) si[i] = -1;
	for(int i = 1;i <= all;++i){
		si[i+N] = E[i+N].size(); 
		for(int u:E[i+N]){E[u].push_back(i+N);}
	}
	for(int i = 1;i <= N+all;++i){
//		cout << i <<" :";
//		for(int u:E[i]){cout << u <<" ";}
//		cout << "\n";
		if(!vis[i]){
			getsi(i,0);have = S[i];
			//cout << i<<"||"<<have<<"\n";
			dfsdp(i,0);
		}
	}
	cout << ans*2;
	return 0;
}
