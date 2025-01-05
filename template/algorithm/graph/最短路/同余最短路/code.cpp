#include<bits/stdc++.h>
using namespace std;
int N,A[20];
long long L,R,dis[500010],ans;
struct edge{int v,w;}ne[20];
struct point{
	int now;long long w;
	bool operator < (const point an) const{return w > an.w;}
};
priority_queue<point>q;
void dji(){
    memset(dis,0x3f,sizeof(dis));
	dis[0] = 0;
	q.push(point{0,0});
	while(!q.empty()){
		point x = q.top(); 
		q.pop();
		int now = x.now;
		if(x.w > dis[now]){continue;}
		for(int i = 1;i < N;++i){
			int v = (ne[i].v+now)%A[0],w = ne[i].w;
			if(dis[v] > dis[now]+w){
				dis[v] = dis[now]+w;
				q.push((point){v,dis[v]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> L >> R;
	for(int i = 0;i < N;++i){
		cin >> A[i];
		if(A[i] == 0){--i;--N;}
	}
	sort(A,A+N);
	for(int i = 1;i < N;++i){
		ne[i].v = A[i]%A[0];
		ne[i].w = A[i];
	}
	dji();
	for(int i = 0;i < A[0];++i){
		if(dis[i] > R) continue;
		ans += ((R-i)/A[0])-(max({L-1-i,dis[i]-1-i,0ll})/A[0]);
	}
	cout << ans;
	return 0;
}
