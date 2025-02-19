struct event{int point,fa,add;};
struct Unionfind{
	int fa[500010],si[500010];stack<event>history;
	int ancestor(int now){
		if(fa[now] == now)return now;
		else return ancestor(fa[now]);
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
		history.push({a,b,max(si[a]+1-si[b],0)});
	}
	void start(int len){
		for(int i = 1;i <= len;++i){
			fa[i] = i;
			si[i] = 1;
		}
	}
	void back(int backto){
		while(history.size() > backto){
			event E = history.top();history.pop();
			si[E.fa] -= E.add;
			fa[E.point] = E.point;
		}
	}
}U;
