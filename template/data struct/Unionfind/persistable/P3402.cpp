#include<bits/stdc++.h>
using namespace std;
int N,Q;
struct point{int son[2],num;};
struct chairmantree{
	public: int root[200010],vtot,len;point node[200010*20];
	private:
		bool inset(int n,int l,int r){return(n >= l&&n <= r);}
		void setup(int now,int L,int R,bool start){
			if(L == R){
				if(start)node[now].num = L;
				else node[now].num = 1;
				return;
			}
			int mid = (L+R)/2;
			node[now].son[0] = ++len;setup(node[now].son[0],L,mid,start);
			node[now].son[1] = ++len;setup(node[now].son[1],mid+1,R,start);
		}
		void update(int L,int R,int addr,int newval,int now,int from){
			int mid = (L+R)/2;
			if(L == R&&R == addr){node[now].num = newval;return;}
			if(inset(addr,L,mid)){
				node[now].son[1] = node[from].son[1];
				node[now].son[0] = ++len;
				update(L,mid,addr,newval,node[now].son[0],node[from].son[0]);
			}else{
				node[now].son[0] = node[from].son[0];
				node[now].son[1] = ++len;
				update(mid+1,R,addr,newval,node[now].son[1],node[from].son[1]);
			}
		}
		int findnum(int L,int R,int addr,int now){
			if(L == R&&R == addr){return node[now].num;}
			int mid = (L+R)/2;
			if(inset(addr,L,mid)){return findnum(L,mid,addr,node[now].son[0]);}
			else{return findnum(mid+1,R,addr,node[now].son[1]);}
		}
	public:
		void setup(bool start){
			root[0] = ++len;
			setup(root[0],1,N,start);
		}
		void update(int addr,int newval){
			root[++vtot] = ++len;
			update(1,N,addr,newval,root[vtot],root[vtot-1]);
		}
		int findans(int addr){return findnum(1,N,addr,root[vtot]);}
};
struct Unionfind{
	chairmantree fa,si;int nowv;
	void back(int v){
		fa.root[++fa.vtot] = ++fa.len;
		fa.node[fa.len] = fa.node[fa.root[v]];
		si.root[++si.vtot] = ++si.len;
		si.node[si.len] = si.node[si.root[v]];
		nowv++;
	}
	int ancestor(int now){
		int F = fa.findans(now);
		if(F == now)return now;
		else return ancestor(F);
	}
	bool equalancestor(int a,int b){
		a = ancestor(a);b = ancestor(b);
		return a == b;
	}
	void mix(int a,int b){
		a = ancestor(a);b = ancestor(b);
		int SA = si.findans(a),SB = si.findans(b);
		if(SA > SB) swap(a,b);
		fa.update(a,b);
		si.update(b,SB+1);
		++nowv;
	}
	void start(){
		nowv = 0;
		fa.setup(1);
		si.setup(0);
	}
}U;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	U.start();
	for(int i = 1;i <= Q;++i){
		int x,y,op;cin >> op;
		if(op == 1){
			cin >> x >> y;
			U.mix(x,y);
		}
		else if(op == 2){
			cin >> x;
			U.back(x);
		}else{
			cin >> x >> y;
			cout << (U.equalancestor(x,y)?"1\n":"0\n");
			U.back(U.nowv);
		}
	}
	return 0;
}
