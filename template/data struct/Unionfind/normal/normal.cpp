struct Unionfind{
	int fa[100010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		return fa[now] = ancestor(fa[now]);
	}
	bool equalancestor(int a,int b){
		a = ancestor(a);b = ancestor(b);
		return a == b;
	}
	void mix(int a,int b){
		a = ancestor(a);b = ancestor(b);
		fa[a] = b;
	}
	void start(int len){for(int i = 1;i <= len;++i){fa[i] = i;}}
};
