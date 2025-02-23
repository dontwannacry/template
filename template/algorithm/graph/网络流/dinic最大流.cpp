#include<bits/stdc++.h>
using namespace std;
struct edge{int v,ne,w;}E[10010];
int N,M,S,T,head[210],cur[210],deep[210],tot = 1;
void addedge(int u,int v,int w){E[++tot].ne = head[u];E[head[u] = tot].v = v;E[tot].w = w;}
bool bfs(){
	memset(deep,0,sizeof(deep));
	deep[S] = 1;
	queue<int>Q;
	Q.push(S);
	while(!Q.empty()){
		int u = Q.front();Q.pop();
		for(int i = head[u];i;i = E[i].ne){
			int v = E[i].v,w = E[i].w;
			if(deep[v]||!w)continue;
			deep[v] = deep[u]+1;
			if(deep[T]) return 1;
			Q.push(v);
		}
	}
	return 0;
}
long long dfs(int now,int minn){
	int res = 0;
	if(now == T) return minn;
	for(int i = cur[now];i;i = E[i].ne){
        cur[now] = i;
		int v = E[i].v,w = E[i].w,lown = 0;
		if(w&&deep[v]==deep[now]+1){
			lown = dfs(v,min(minn-res,w));
			if(lown){
				E[i].w -= lown;E[i^1].w += lown;res += lown;
				if(res == minn)break;
			}
		}
	}
	return res;
}
long long Dinic(){
	long long ans = 0;
	while(bfs()){
        memcpy(cur,head,sizeof(cur));
		ans += dfs(S,0x7fffffff);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> S >> T;
	for(int i = 1;i <= M;++i){
		int u,v,w;
		cin >> u >> v >> w;
		addedge(u,v,w);
		addedge(v,u,0);
	}
	cout << Dinic();
	return 0;
}
