#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int N,M,with[510],pre[510];
ll tagl[510],tagr[510],dis[510],mp[510][510],sum;
bool vis[510];
void bfs(int S){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	with[0] = S;int now = 0,nr = 0,nv = 0;
	while(1){
		now = with[nr];vis[nr] = 1;ll minn = inf;
		for(int i = 1;i <= N;++i){
			if(vis[i]){continue;}
			ll del = tagl[now]+tagr[i]-mp[now][i];
			if(del < dis[i]){dis[i] = del;pre[i] = nr;}
			if(dis[i] < minn){minn = dis[i];nv = i;}
		}
		tagl[with[0]] -= minn;
		for(int i = 1;i <= N;++i){
			if(vis[i]){tagl[with[i]] -= minn;tagr[i] += minn;}
			else{dis[i] -= minn;}
		}
		nr = nv;if(!with[nr]){break;}
	}
	while(nr){
		with[nr] = with[pre[nr]];
		nr = pre[nr];
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	memset(tagl,0x1f,sizeof(tagl));
	memset(tagr,0x1f,sizeof(tagr));
	memset(mp,-0x3f,sizeof(mp));
    cin >> N >> M;
    for(int i = 1;i <= M;++i){
		int u,v,w;cin >> u >> v >> w;
		mp[u][v] = w;
    }
	for(int i = 1;i <= N;++i){bfs(i);}
	for(int i = 1;i <= N;++i){sum += mp[with[i]][i];}
	cout << sum << "\n";
	for(int i = 1;i <= N;++i){cout << with[i] << " ";}cout << "\n";
	return 0;
}