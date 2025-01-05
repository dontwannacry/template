#include<bits/stdc++.h>
using namespace std;
int N,M,S,dis[100010];
struct edge{int v,w;};
struct point{
	int now,w;
	bool operator < (const point an) const{return w > an.w;}
};
vector<edge>ne[100010];
priority_queue<point>q;
void dji(){
    memset(dis,0x7f,sizeof(dis));
	dis[S] = 0;
	q.push(point{S,0});
	while(!q.empty()){
		point x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[now]){continue;}
		for(int i = 0;i < ne[now].size();++i){
			int v = ne[now][i].v,w = ne[now][i].w;
			if(dis[v] > dis[now]+w){
				dis[v] = dis[now]+w;
				q.push((point){v,dis[v]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> N >> M >> S;
	for(int i = 1;i <= M;++i){
		int f,t,w;
		cin >> f >> t >> w;
		ne[f].push_back((edge){t,w});
	}
	dji();
	for(int i = 1;i <= N;++i){cout << dis[i] <<" ";}
	return 0;
}
