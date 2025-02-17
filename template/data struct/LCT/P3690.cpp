#include<bits/stdc++.h>
using namespace std;
int N,M;
struct LCT{
	struct node{int son[2],fa,val,sum,tag;}P[100010];
	void pushup(int now){P[now].sum = P[now].val^P[P[now].son[0]].sum^P[P[now].son[1]].sum;}
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
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> T.P[i].val;T.P[i].sum = T.P[i].val;}
	for(int i = 1;i <= M;++i){
		int op,x,y;cin >> op >> x >> y;
		if(op == 0){T.split(x,y);cout << T.P[y].sum << "\n";}
		else if(op == 1){T.link(x,y);}
		else if(op == 2){T.cut(x,y);}
		else{T.fix(x,y);}
	}
	return 0;
}
