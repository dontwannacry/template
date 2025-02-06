struct point{
	int l,r,son[2],num,on;
	point(){}
	point(int l,int r){
		this->l = l;this->r = r;
		on = son[0] = son[1] = num = 0;
		if(l == r) on = l;
	}
};
struct addabletree{
	int root[100010],len;point node[100010*24];
	void getroot(int now){
		root[now] = ++len;
		node[len] = point(1,100000);
	}
	void pushup(int now){
		int ls = node[now].son[0],rs = node[now].son[1];
		if(node[ls].num >= node[rs].num){node[now].num = node[ls].num,node[now].on = node[ls].on;}
		else{node[now].num = node[rs].num,node[now].on = node[rs].on;}
		if(node[now].num == 0)node[now].on = 0;
	}
	bool inset(int n,int l,int r){return(n >= l&&n <= r);}
	void update(int addr,int delta,int now){
		int l = node[now].l,r = node[now].r,mid;
		mid = (l+r)/2;
		if(l == r&&r == addr){node[now].num += delta;return;}
		if(inset(addr,l,mid)){
			if(!node[now].son[0]){node[now].son[0] = ++len;node[len] = point(l,mid);}
			update(addr,delta,node[now].son[0]);
		}else{
			if(!node[now].son[1]){node[now].son[1] = ++len;node[len] = point(mid+1,r);}
			update(addr,delta,node[now].son[1]);
		}
		pushup(now);
	}
	void treeadd(int now,int from){
		int l = node[now].l,r = node[now].r;
		if(l == r){node[now].num += node[from].num;return;}
		if(node[from].son[0]){
			if(!node[now].son[0]){node[now].son[0] = node[from].son[0];}
			else{treeadd(node[now].son[0],node[from].son[0]);}
		}
		if(node[from].son[1]){
			if(!node[now].son[1]){node[now].son[1] = node[from].son[1];}
			else{treeadd(node[now].son[1],node[from].son[1]);}
		}
		pushup(now);
	}
}tree;
