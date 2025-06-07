#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct SGSGT{
	int R[400010];
	struct node{ll num,tag;int son[2];}T[20000010];
	int tot,N;
	void setup(int l,int r,int now){
		R[now] = ++tot;
		if(l == r){return;}
		int mid = (l+r)>>1;
		setup(l,mid,now*2);
		setup(mid+1,r,now*2+1);
	}
	void maketag(int nl,int nr,ll delta,int now){
		T[now].tag += delta;
		T[now].num += delta*(nr-nl+1);
	}	
	void pushdown(int nl,int nr,int now){
		int mid = (nr+nl)>>1;
		if(!T[now].son[0]){T[now].son[0] = ++tot;}
		if(!T[now].son[1]){T[now].son[1] = ++tot;}
		maketag(nl,mid,T[now].tag,T[now].son[0]);
		maketag(mid+1,nr,T[now].tag,T[now].son[1]);
		T[now].tag = 0;
	}
	void updatesecond(int nl,int nr,int l,int r,int delta,int now){
		if(l <= nl&&nr <= r){maketag(nl,nr,delta,now);return;}
		if(nr < l||r < nl){return;}
		pushdown(nl,nr,now);
		int mid = (nl+nr)>>1;
		updatesecond(nl,mid,l,r,delta,T[now].son[0]);
		updatesecond(mid+1,nr,l,r,delta,T[now].son[1]);
		T[now].num = T[T[now].son[0]].num + T[T[now].son[1]].num;
	}
	void updatefirst(int nl,int nr,int l,int r,int at,int delta,int now){
		updatesecond(1,N,l,r,delta,R[now]);
		if(nl == nr){return;}
		int mid = (nl+nr)>>1;
		if(at <= mid){updatefirst(nl,mid,l,r,at,delta,now*2);}
		else{updatefirst(mid+1,nr,l,r,at,delta,now*2+1);}
	}
	ll getsum(int nl,int nr,int l,int r,int now){
		if(r < nl||nr < l||now == 0){return 0;}
		if(l <= nl&&nr <= r){return T[now].num;}
		int mid = (nl+nr)>>1;
		pushdown(nl,nr,now);
		ll resl = getsum(nl,mid,l,r,T[now].son[0]);
		ll resr = getsum(mid+1,nr,l,r,T[now].son[1]);
		T[now].num = T[T[now].son[0]].num + T[T[now].son[1]].num;
		return resl+resr;
	}
	int getkth(int nl,int nr,int l,int r,ll K,int now){
		if(nl == nr){return nl;}
		ll rres = getsum(1,N,l,r,R[now*2+1]);
		int mid = (nl+nr)>>1;
		if(rres >= K){return getkth(mid+1,nr,l,r,K,now*2+1);}
		else{return getkth(nl,mid,l,r,K-rres,now*2);}
	}
}T;
int N,M;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//    freopen("D.in","r",stdin);
//    freopen("D.out","w",stdout);
    cin >> N >> M;T.N = N;
    T.setup(-N,N,1);
    for(int i = 1;i <= M;++i){
		int op,l,r;ll c;cin >> op >> l >> r >> c;
		if(op == 1){T.updatefirst(-N,N,l,r,c,1,1);}
		else{cout << T.getkth(-N,N,l,r,c,1) << "\n";}
//		if(T.tot > 19000000){cout << i/10000 << "x\n";return 0;}
	}
    return 0;
}
