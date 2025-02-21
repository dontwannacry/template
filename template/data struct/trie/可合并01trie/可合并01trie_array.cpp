struct point{
	int cnt,son[2];
	point(){
		son[0] = son[1] = -1;
		cnt = 0;
	}
}trie[9000010];
int len;
void trie_push(int now,int val){
	trie[now].cnt++;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(trie[now].son[v] == -1) trie[now].son[v] = ++len;
		now = trie[now].son[v];
		trie[now].cnt++;
	}
}
int find_near(int now,int S,int val){
	int res = 0;bool re = 1;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(trie[S].son[v] == -1){S = trie[S].son[v^1];res+=(1<<i);}
		else if(trie[trie[now].son[v]].cnt == trie[trie[S].son[v]].cnt&&re){
			S = trie[S].son[v^1];
			res+=(1<<i);re = 0;
		}else S = trie[S].son[v];
		now = trie[now].son[v];
	}
	return res;
}
void trie_mix(int A,int B){
	trie[A].cnt += trie[B].cnt;
	if(trie[B].son[0] != -1){
		if(trie[A].son[0] == -1)trie[A].son[0] = trie[B].son[0];
		else trie_mix(trie[A].son[0],trie[B].son[0]);
	}
	if(trie[B].son[1] != -1){
		if(trie[A].son[1] == -1)trie[A].son[1] = trie[B].son[1];
		else trie_mix(trie[A].son[1],trie[B].son[1]);
	}
}