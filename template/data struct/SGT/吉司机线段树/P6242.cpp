#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x7f7f7f7f;
struct matrix{
	int a,b;
	matrix(){}
	matrix(int A,int B){a = A;b = B;}
	matrix operator + (const matrix other)const{return {max(a,other.a),max(b,other.b)};}
	matrix operator * (const matrix other)const{
		matrix res;
		if(min(a,other.a) == -inf){res.a = -inf;}
		else{res.a = a+other.a;}
		if(min(a,other.b) == -inf){res.b = b;}
		else{res.b = max(a+other.b,b);}
		return res;
	}
}zerotag = {0,-inf};
struct point{
	ll sum;int cnt;
	matrix maxn[2],tag[2];
	point(){}
	point(int val){
		sum = val;cnt = 1;
		maxn[0] = {val,val};
		maxn[1] = {-inf,-inf};
		tag[0] = tag[1] = zerotag;
	}
	point operator + (const point other)const{
		point res;
		res.maxn[1] = maxn[1]+other.maxn[1];
		res.tag[0] = res.tag[1] = zerotag;
		res.sum = sum+other.sum;
		if(maxn[0].a < other.maxn[0].a){
			res.maxn[0] = other.maxn[0];
			res.maxn[1] = res.maxn[1]+maxn[0];
			res.cnt = other.cnt;
		}else if(maxn[0].a > other.maxn[0].a){
			res.maxn[0] = maxn[0];
			res.maxn[1] = res.maxn[1]+other.maxn[0];
			res.cnt = cnt;
		}else{
			res.maxn[0] = maxn[0]+other.maxn[0];
			res.cnt = cnt+other.cnt;
		}
		return res;
	}
};
struct SGT{
	point T[2000010];
	void setup(int nl,int nr,int now,int *A){
		if(nl == nr){
			T[now] = point(A[nl]);
			return;
		}
		int mid = (nl+nr)>>1;
		setup(nl,mid,now*2,A);
		setup(mid+1,nr,now*2+1,A);
		T[now] = T[now*2]+T[now*2+1];
	}
	void maketag(int nl,int nr,int now,matrix M1,matrix M2){
		T[now].maxn[0] = T[now].maxn[0]*M1;
		T[now].maxn[1] = T[now].maxn[1]*M2;
		T[now].tag[0] = T[now].tag[0]*M1;
		T[now].tag[1] = T[now].tag[1]*M2;
		T[now].sum += 1ll*T[now].cnt*M1.a;
		T[now].sum += 1ll*(nr-nl+1-T[now].cnt)*M2.a;
	}
	void pushdown(int nl,int nr,int now){
		int mid = (nl+nr)>>1;
		if(T[now*2].maxn[0].a == T[now].maxn[0].a-T[now].tag[0].a)
		{maketag(nl,mid,now*2,T[now].tag[0],T[now].tag[1]);}
		else{maketag(nl,mid,now*2,T[now].tag[1],T[now].tag[1]);}
		if(T[now*2+1].maxn[0].a == T[now].maxn[0].a-T[now].tag[0].a)
		{maketag(mid+1,nr,now*2+1,T[now].tag[0],T[now].tag[1]);}
		else{maketag(mid+1,nr,now*2+1,T[now].tag[1],T[now].tag[1]);}
		T[now].tag[0] = T[now].tag[1] = zerotag;
	}
	void update(int nl,int nr,int l,int r,int delta,int now){
		if(r < nl||nr < l){return;}
		if(l <= nl&&nr <= r){
			maketag(nl,nr,now,{delta,delta},{delta,delta});
			return;
		}
		pushdown(nl,nr,now);
		int mid = (nl+nr)>>1;
		update(nl,mid,l,r,delta,now*2);
		update(mid+1,nr,l,r,delta,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
	}
	void makemin(int nl,int nr,int l,int r,int tar,int now){
		if(r < nl||nr < l||T[now].maxn[0].a <= tar){return;}
		if(l <= nl&&nr <= r&&T[now].maxn[1].a <= tar){
			int delta = tar-T[now].maxn[0].a;
			maketag(nl,nr,now,{delta,delta},zerotag);
			return;
		}
		pushdown(nl,nr,now);
		int mid = (nl+nr)>>1;
		makemin(nl,mid,l,r,tar,now*2);
		makemin(mid+1,nr,l,r,tar,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
	}
	point getsum(int nl,int nr,int l,int r,int now){
		if(l <= nl&&nr <= r){return T[now];}
		pushdown(nl,nr,now);
		int mid = (nl+nr)>>1;point res;
		if(mid < l){res = getsum(mid+1,nr,l,r,now*2+1);}
		else if(r <= mid){res = getsum(nl,mid,l,r,now*2);}
		else{res = getsum(nl,mid,l,r,now*2)+getsum(mid+1,nr,l,r,now*2+1);}
		T[now] = T[now*2]+T[now*2+1];
		return res;
	}
}T;
int N,M,A[500010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> A[i];}
	T.setup(1,N,1,A);
	for(int i = 1;i <= M;++i){
		int op;cin >> op;
		if(op == 1){
			int l,r,k;cin >> l >> r >> k;
			T.update(1,N,l,r,k,1);
		}else if(op == 2){
			int l,r,k;cin >> l >> r >> k;
			T.makemin(1,N,l,r,k,1);
		}else{
			int l,r;cin >> l >> r;
			point res = T.getsum(1,N,l,r,1);
			if(op == 3){cout << res.sum << "\n";}
			else if(op == 4){cout << res.maxn[0].a << "\n";}
			else{cout << max(res.maxn[0].b,res.maxn[1].b) << "\n";}
		}
	}
	return 0;
}
