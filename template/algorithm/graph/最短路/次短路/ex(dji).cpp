#include<bits/stdc++.h>
using namespace std;
int N,M,S,dis[2][100010];
struct bian{int ne,w;};
struct dian{
	int now,w;
	bool operator < (const dian an) const{
		return w > an.w;
	}
};
vector<bian>to[100010];
priority_queue<dian>q;
void dji(){
    memset(dis,0x7f,sizeof(dis));
	dis[0][1] = 0;
	q.push(dian{1,0});
	while(!q.empty()){
		dian x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[1][now]){continue;}
		for(int i = 0;i < to[now].size();++i){
			bian link = to[now][i];
			if(dis[0][link.ne] > x.w+link.w){
				dis[1][link.ne] = dis[0][link.ne];
				dis[0][link.ne] = x.w+link.w;
				q.push((dian){link.ne,dis[0][link.ne]});
			}else if(dis[1][link.ne] > x.w+link.w&&dis[0][link.ne] != x.w+link.w){
				dis[1][link.ne] = x.w+link.w;
				q.push((dian){link.ne,dis[1][link.ne]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int f,t,w;
		cin >> f >> t >> w;
		to[f].push_back((bian){t,w});
		to[t].push_back((bian){f,w});
	}
	dji();
	cout << dis[1][N];
	return 0;
}
