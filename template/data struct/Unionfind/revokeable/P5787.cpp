#include<bits/stdc++.h>
using namespace std;
struct event{int point,fa,add;};
struct Unionfind{
	int fa[200010],si[200010];stack<event>history;
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return ancestor(fa[now]);
	}
	bool equalancestor(int a,int b){
		a = ancestor(a);b = ancestor(b);
		return a == b;
	}
	void mix(int a,int b){
		int x1 = ancestor(a),x2 = ancestor(b+100005);
		if(si[x1] > si[x2]) swap(x1,x2);
		fa[x1] = x2;
		si[x2] = max(si[x1]+1,si[x2]);
		history.push({x1,x2,max(si[x1]+1-si[x2],0)});
		int y1 = ancestor(a+100005),y2 = ancestor(b);
		if(si[y1] > si[y2]) swap(y1,y2);
		fa[y1] = y2;
		si[y2] = max(si[y1]+1,si[y2]);
		history.push({y1,y2,max(si[y1]+1-si[y2],0)});
	}
	void start(int len){
		for(int i = 1;i <= len;++i){
			fa[i] = i;fa[i+100005] = i+100005;
			si[i] = 1;si[i+100005] = 1;
		}
	}
	void back(int backto){
		while(history.size() > backto){
			event E = history.top();history.pop();
			si[E.fa] -= E.add;
			fa[E.point] = E.point;
		}
	}
}U;
struct edge{int u,v;};
struct Segment_Tree{
	vector<edge>node[400010];
	bool inset(int L,int R,int l,int r){return(L <= l&&R >= r);}
	bool outset(int L,int R,int l,int r){return(L > r||R < l);}
	void update(int l,int r,edge E,int nl,int nr,int now){
		if(inset(l,r,nl,nr)){node[now].push_back(E);}
		else if(!outset(l,r,nl,nr)){
			int mid = (nl+nr)>>1;
			update(l,r,E,nl,mid,now*2);
			update(l,r,E,mid+1,nr,now*2+1);
		}
	}
	void findans(int nl,int nr,int now){
		int nows = U.history.size();
		for(edge e:node[now]){
			if(U.equalancestor(e.u,e.v)){
				for(int i = nl;i <= nr;++i)cout << "No\n";
				U.back(nows);
				return;
			}
			U.mix(e.u,e.v);
		}
		if(nl != nr){
			int mid = (nl+nr)>>1;
			findans(nl,mid,now*2);
			findans(mid+1,nr,now*2+1);
		}else{cout << "Yes\n";}
		U.back(nows);
		return;
	}
}tree;
int N,M,K;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> K;
	for(int i = 1;i <= M;++i){
		int u,v,l,r;
		cin >> u >> v >> l >> r;++l;
		tree.update(l,r,{u,v},1,K,1);
	}
	U.start(N);
	tree.findans(1,K,1);
	return 0;
}
