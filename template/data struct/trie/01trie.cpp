struct trie{
	struct point{int num,son[2];}tree[100010*30];
	int len,root[100010];
	void update(int val,int now,int from){
		now = root[now] = ++len;from = root[from];
		tree[now].num = tree[from].num+1;
		for(int i = 29;i >= 0;--i){
			int re = (val>>i)&1;
			tree[now].son[re^1] = tree[from].son[re^1];
			now = tree[now].son[re] = ++len;
			from = tree[from].son[re];
			tree[now].num = tree[from].num+1;
		}
	}
	int findmax(int lon,int ron,int val){
		int res = 0;lon = root[lon];ron = root[ron];
		for(int i = 29;i >= 0;--i){
			int v = (val>>i)&1;
			if(tree[tree[ron].son[v^1]].num-tree[tree[lon].son[v^1]].num==0){
				lon = tree[lon].son[v];
				ron = tree[ron].son[v];
			}else{
				lon = tree[lon].son[v^1];
				ron = tree[ron].son[v^1];
				res += (1<<i);
			}
		}
		return res;
	}
}T1,T2;