struct point{
	int num = 0,cnt = 0;
	point(){num = cnt = 0;}
	point operator + (const point other)const{
		point res;
		if(other.cnt) res = other;
		else if(cnt) res = *this;
		return res;
	}
};
struct Segment_Tree{
	point node[2000010];
	void pushup(int now){node[now] = node[now*2]+node[now*2+1];}
	bool inset(int L,int R,int to){return(L <= to&&R >= to);}
	bool outset(int L,int R,int to){return(L > to||R < to);}
	void setup(int l,int r,int now){
		if(l == r){
			node[now].num = l;
			return;
		}
		int mid = (l+r)/2;
		setup(l,mid,now*2);
		setup(mid+1,r,now*2+1);
		pushup(now);
	}
	void update(int nl,int nr,int to,int add,int now){
		int mid = (nl+nr)/2;
		if(nl == nr){node[now].cnt+=add;return;}
		if(inset(nl,mid,to)){update(nl,mid,to,add,now*2);}
		else{update(mid+1,nr,to,add,now*2+1);}
		pushup(now);
	}
}tree;
