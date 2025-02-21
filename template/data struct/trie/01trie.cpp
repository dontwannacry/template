struct trie{
	struct point{int num,son[2];}T[150010*30];
	int tot,root;
	void update(int val){
		int now = root;++T[now].num;
		for(int i = 29;i >= 0;--i){
			int re = (val>>i)&1;
			if(!T[now].son[re]){T[now].son[re] = ++tot;}
			now = T[now].son[re];
			++T[now].num;
		}
	}
	int findmax(int val){
		int res = 0,now = root;
		for(int i = 29;i >= 0;--i){
			int v = (val>>i)&1;
			if(!T[now].son[v^1]){now = T[now].son[v];}
			else{now = T[now].son[v^1];res += (1<<i);}
		}
		return res;
	}
}T;
