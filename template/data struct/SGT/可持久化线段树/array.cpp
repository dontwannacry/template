int N,M,start[1000010];
struct point{
	int l,r,son[2];
	long long num;
};
struct chairmantree{
	public: int root[1000010],vtot,len;point node[1000010*24];
	private:
		void pushup(int now){node[now].num = node[node[now].son[0]].num+node[node[now].son[1]].num;}
		bool inset(int n,int now){return(n >= node[now].l&&n <= node[now].r);}
		void setup(int now,int L,int R){
			node[now].l = L,node[now].r = R;
			if(L == R){node[now].num = start[L];return;}
			int mid = (L+R)/2;
			node[now].son[0] = ++len;setup(node[now].son[0],L,mid);
			node[now].son[1] = ++len;setup(node[now].son[1],mid+1,R);
			pushup(now);
		}
		void update(int addr,int newval,int now,int from){
			int L = node[from].l,R = node[from].r;
			node[now].l = L;
			node[now].r = R;
			if(L == R&&R == addr){node[now].num = newval;return;}
			if(inset(addr,node[from].son[0])){
				node[now].son[1] = node[from].son[1];
				node[now].son[0] = ++len;
				update(addr,newval,node[now].son[0],node[from].son[0]);
			}else{
				node[now].son[0] = node[from].son[0];
				node[now].son[1] = ++len;
				update(addr,newval,node[now].son[1],node[from].son[1]);
			}
			pushup(now);
		}
		long long findnum(int addr,int now){
			if(node[now].l == node[now].r&&node[now].r == addr){return node[now].num;}
			if(inset(addr,node[now].son[0])){return findnum(addr,node[now].son[0]);}
			else{return findnum(addr,node[now].son[1]);}
		}
	public:
		void setup(int N){
			root[0] = ++len;
			setup(root[0],1,N);
		}
		void update(int addr,int newval,int from){
			root[++vtot] = ++len;
			update(addr,newval,root[vtot],root[from]);
		}
		long long findans(int addr,int v){
			root[++vtot] = ++len;
			node[len] = node[root[v]];
			return findnum(addr,root[v]);
		}
}tree;
