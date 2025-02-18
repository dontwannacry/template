#include<bits/stdc++.h>
using namespace std;
struct line{
	int u,v,w;
	bool operator < (const line other)const{return w < other.w;}
}L[200010];
struct LCT{
	struct node{
		int son[2],fa,val,minn,tag;
		node(){son[0] = son[1] = fa = tag;val = minn = 0x7f7f7f7f;}
	}P[250010];
	void pushup(int now){P[now].minn = min(P[now].val,min(P[P[now].son[0]].minn,P[P[now].son[1]].minn));}
	bool getfrom(int now){return now == P[P[now].fa].son[1];}
	bool isroot(int now){return (P[P[now].fa].son[0] != now&&P[P[now].fa].son[1] != now);}
	void maketag(int now){swap(P[now].son[0],P[now].son[1]);P[now].tag ^= 1;}
	void pushdown(int now){
		if(P[now].tag){
			if(P[now].son[0]){maketag(P[now].son[0]);}
			if(P[now].son[1]){maketag(P[now].son[1]);}
			P[now].tag = 0;
		}
	}
	void update(int now){
		if(!isroot(now)){update(P[now].fa);}
		pushdown(now);
	}
	void reroot(int now){
		int tmp = P[now].fa,grf = P[tmp].fa,chk = getfrom(now);
		if(!isroot(tmp)){P[grf].son[getfrom(tmp)] = now;}
		P[tmp].son[chk] = P[now].son[chk^1];
		if(P[now].son[chk^1]){P[P[now].son[chk^1]].fa = tmp;}
		P[now].son[chk^1] = tmp;
		P[tmp].fa = now;P[now].fa = grf;
		pushup(tmp);pushup(now);
	}
	void splay(int now){
		update(now);
		for(int fa = P[now].fa;!isroot(now);reroot(now)){
			fa = P[now].fa;
			if(!isroot(fa)){
				if(getfrom(fa) == getfrom(now)){reroot(fa);}
				else{reroot(now);}
			}
		}
	}
	int access(int now){
		int down;
		for(down = 0;now;down = now,now = P[now].fa){
			splay(now);
			P[now].son[1] = down;
			pushup(now);
		}
		return down;
	}
	void makeroot(int now){
		access(now);
		splay(now);
		maketag(now);
	}
	int findroot(int now){
		access(now);
		splay(now);
		while(P[now].son[0]){pushdown(now);now = P[now].son[0];}
		splay(now);
		return now;
	}
	void link(int x,int y){
		makeroot(x);
		if(findroot(y) != x){P[x].fa = y;}
	}
	void split(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
	}
	void cut(int x,int y){
		makeroot(x);
		if(findroot(y) == x&&P[y].fa == x&&!P[y].son[0]){
			P[y].fa = P[x].son[1] = 0;
			pushup(x);
		}
	}
	void fix(int x,int val){
		splay(x);
		P[x].val = val;
		pushup(x);
	}
}T;
int N,M,cur,tot,ans = 0x7f7f7f7f;
bool vis[200010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		cin >> L[i].u >> L[i].v >> L[i].w;
		if(L[i].u == L[i].v){--i;--M;}
	}
	sort(L+1,L+1+M);
	for(int i = 1;i <= M;++i){T.P[N+i].val = T.P[N+i].minn = i;}
	cur = 1;
	for(int i = 1;i <= M;++i){
		if(T.findroot(L[i].v) == T.findroot(L[i].u)){
			T.split(L[i].u,L[i].v);
			vis[T.P[L[i].v].minn] = 1;--tot;
			int del = T.P[L[i].v].minn+N;
			T.splay(del);
			T.P[T.P[del].son[0]].fa = T.P[T.P[del].son[1]].fa = 0;
		}
		T.link(L[i].u,N+i);T.link(L[i].v,N+i);++tot;
		while(vis[cur]){++cur;}
		if(tot == N-1){ans = min(ans,L[i].w-L[cur].w);}
	}
	cout << ans << "\n";
	return 0;
}
