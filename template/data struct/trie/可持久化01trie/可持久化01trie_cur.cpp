struct point{
	int cnt;
	point *son[2];
	point(){son[0] = son[1] = nullptr;cnt = 0;}
}*root[200010];
void trie_push(point *now,int val){
	now->cnt++;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(now->son[v] == nullptr) now->son[v] = new point();
		now = now->son[v];
		now->cnt++;
	}
}
int find_near(point *now,point *S,int val){
	int res = 0;bool re = 1;
	for(int i = 29;i >= 0;--i){
		int v = (val>>i)&1;
		if(S->son[v] == nullptr){S = S->son[v^1];res+=(1<<i);}
		else if(now->son[v]->cnt == S->son[v]->cnt&&re){
			S = S->son[v^1];
			res+=(1<<i);re = 0;
		}else S = S->son[v];
		now = now->son[v];
	}
	return res;
}
void trie_mix(point *A,point *B){
	A->cnt += B->cnt;
	if(B->son[0]!=nullptr){
		if(A->son[0]==nullptr)A->son[0] = B->son[0];
		else trie_mix(A->son[0],B->son[0]);
	}
	if(B->son[1]!=nullptr){
		if(A->son[1]==nullptr)A->son[1] = B->son[1];
		else trie_mix(A->son[1],B->son[1]);
	}
	delete(B);
	B = nullptr;
}