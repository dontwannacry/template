struct Unionfind{
	int fa[10010],si[10010];
	int ancestor(int now){
		if(fa[now] == now)return now;
		return ancestor(fa[now]);
	}
	bool equalancestor(int a,int b){
		a = ancestor(a);b = ancestor(b);
		return a == b;
	}
	void mix(int a,int b){
		a = ancestor(a);b = ancestor(b);
		if(si[a] > si[b]) swap(a,b);
		fa[a] = b;
		si[b] = max(si[a]+1,si[b]);
	}
	void start(int len){
		for(int i = 1;i <= len;++i){
			fa[i] = i;
			si[i] = 1;
		}
	}
}U;
