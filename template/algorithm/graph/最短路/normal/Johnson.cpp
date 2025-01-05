#include<bits/stdc++.h>
using namespace std;
struct edge{int v,w;};
struct point{
	int now,w;
	bool operator < (const point an) const{return w > an.w;}
};
int N,M,cnt[3010],H[3010],dis[3010][3010];
bool vis[3010];
vector<edge>to[3010];
void dji(int S){
	priority_queue<point>q;
	for(int i = 1;i <= N;++i) dis[S][i] = 1000000000;
	dis[S][S] = 0;
	q.push(point{S,0});
	while(!q.empty()){
		point x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[S][now]){continue;}
		for(int i = 0;i < to[now].size();++i){
			edge link = to[now][i];
			if(dis[S][link.v] > dis[S][now]+link.w){
				dis[S][link.v] = dis[S][now]+link.w;
				q.push((point){link.v,dis[S][link.v]});
			}
		}
	}
}
int SPFA(int S){
	memset(vis,0,sizeof(vis));
	memset(H,0x7f,sizeof(H));
	queue<int>Q;
	H[S] = 0;
	Q.push(S);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		vis[u] = 0;
		for(auto V : to[u]){
			if(H[V.v] > H[u]+V.w){
				H[V.v] = H[u]+V.w;
				if(!vis[V.v]){
					Q.push(V.v);
					vis[V.v] = 1;
					cnt[V.v]++;
					if(cnt[V.v] > N) return -1;
				}
			}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){to[0].push_back({i,0});}
	for(int i = 1;i <= M;++i){
		int u,v,w;cin >> u >> v >> w;
		to[u].push_back({v,w});
	}
	if(SPFA(0)==-1){cout << "-1";return 0;}
	for(int i = 1;i <= N;++i){
		for(int j = 0;j < to[i].size();++j){
			to[i][j].w += H[i]-H[to[i][j].v];
		}
	}
	for(int i = 1;i <= N;++i){
		long long ANS = 0;
		dji(i);
		for(int j = 1;j <= N;++j){
			if(dis[i][j] != 1000000000) dis[i][j] += H[j]-H[i];
			ANS += 1ll*j*dis[i][j];
		}
		cout << ANS <<"\n";
	}
	return 0;
}
