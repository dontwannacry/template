#include<bits/stdc++.h>
using namespace std;
int N,M,S,x[210],y[210],la[210];
double dis[210],ANS = 10000010;const double esp = 1e-6;
struct bian{int ne;double w;};
struct dian{
	int now;double w;
	bool operator < (const dian an) const{
		return w > an.w;
	}
};
vector<bian>to[210];
priority_queue<dian>q;
void dji(){
    for(int i = 1;i <= 200;++i){dis[i] = 1000000;}
	dis[1] = 0;
	q.push(dian{1,0});
	while(!q.empty()){
		dian x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[now]){continue;}
		for(int i = 0;i < to[now].size();++i){
			bian link = to[now][i];
			if(dis[link.ne] > x.w+link.w+esp){
				la[link.ne] = now;
				dis[link.ne] = x.w+link.w;
				q.push((dian){link.ne,dis[link.ne]});
			}
		}
	}
}
void findans(int a,int b){
    for(int i = 1;i <= 200;++i){dis[i] = 1000000;}
	dis[1] = 0;
	q.push(dian{1,0});
	while(!q.empty()){
		dian x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[now]){continue;}
		for(int i = 0;i < to[now].size();++i){
			bian link = to[now][i];
			if(a == now&&b == link.ne)continue;
			if(b == now&&a == link.ne)continue;
			if(dis[link.ne] > x.w+link.w+esp){
				dis[link.ne] = x.w+link.w;
				q.push((dian){link.ne,dis[link.ne]});
			}
		}
	}
	ANS = min(ANS,dis[N]);
}
int main(){
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> x[i] >> y[i];}
	for(int i = 1;i <= M;++i){
		int f,t;
		cin >> f >> t;
		double w = sqrt((x[f]-x[t])*(x[f]-x[t])+(y[f]-y[t])*(y[f]-y[t]));
		to[f].push_back((bian){t,w});
		to[t].push_back((bian){f,w});
	}
	dji();
	for(int a = N;a != 1;a = la[a]){findans(a,la[a]);}
	printf("%.2lf",ANS);
	return 0;
}
