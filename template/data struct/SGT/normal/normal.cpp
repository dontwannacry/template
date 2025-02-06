long long start[100010];
struct point{
	int l,r;
	long long num = 0,add = 0;
};
struct Segment_Tree{
	point node[400010];
	void pushup(int now){node[now].num = node[now*2].num + node[now*2+1].num;}
	bool inset(int L,int R,int l,int r){return(L <= l&&R >= r);}
	bool outset(int L,int R,int l,int r){return(L > r||R < l);}
	void setup(int l,int r,int now){
		node[now].l = l,node[now].r = r;
		if(l == r){
			node[now].num = start[l];
			return;
		}
		int mid = (l+r)/2;
		setup(l,mid,now*2);
		setup(mid+1,r,now*2+1);
		pushup(now);
	}
	void maketag(int now,long long add){
		node[now].add += add;
		node[now].num += (node[now].r-node[now].l+1)*add;
	}
	void pushdown(int now){
		maketag(now*2,node[now].add);
		maketag(now*2+1,node[now].add);
		node[now].add = 0;
	}
	void update(int l,int r,long long add,int now){
		if(inset(l,r,node[now].l,node[now].r)){
			maketag(now,add);
		}else if(!outset(l,r,node[now].l,node[now].r)){
			pushdown(now);
			update(l,r,add,now*2);
			update(l,r,add,now*2+1);
			pushup(now);
		}
	}
	long long findans(int l,int r,int now){
		if(inset(l,r,node[now].l,node[now].r)){
			return node[now].num;
		}else if(!outset(l,r,node[now].l,node[now].r)){
			pushdown(now);
			return findans(l,r,now*2)+findans(l,r,now*2+1);
		}else{
			return 0;
		}
	}
}tree;
