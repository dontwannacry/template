#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,Q,pos[200010],id[200010];
ll A[200010];
vector<int>upd[200010];
struct moves{ll op,l,r;}L[200010];
struct line{
	ll k,b;
	line operator + (const line other)const{return {k+other.k,b+other.b};}
	line operator - (const line other)const{return {k-other.k,b-other.b};}
	ll operator * (const line other)const{return k*other.b-other.k*b;}
}P[200010],S[200010];
struct SGTA{
	struct node{
		ll num,add,tag;
		node operator + (const node other)const{
			node res = {0,0,0};
			res.num = num+other.num;
			res.add = add+other.add;
			return res;
		}
	}T[800010];
	void setup(int nl,int nr,int now,ll *A){
		if(nl == nr){
			T[now] = {A[nl],nl,0};
			return;
		}
		int mid = (nl+nr)>>1;
		setup(nl,mid,now*2,A);
		setup(mid+1,nr,now*2+1,A);
		T[now] = T[now*2]+T[now*2+1];
	}
	void maketag(int now,int val){
		T[now].tag += val;
		T[now].num += T[now].add*val;
	}
	void pushdown(int now){
		maketag(now*2,T[now].tag);
		maketag(now*2+1,T[now].tag);
		T[now].tag = 0;
	}
	void kill(int nl,int nr,int at,int now){
		if(nl == nr){T[now] = {0,0,0};return;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		if(at <= mid){kill(nl,mid,at,now*2);}
		else{kill(mid+1,nr,at,now*2+1);}
		T[now] = T[now*2]+T[now*2+1];
	}
	ll getsum(int nl,int nr,int l,int r,int now){
		if(l <= nl&&nr <= r){return T[now].num;}
		if(r < nl||nr < l){return 0;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		ll resl = getsum(nl,mid,l,r,now*2);
		ll resr = getsum(mid+1,nr,l,r,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
		return resl+resr;
	}
}TA;
struct SGTB{
	struct node{
		ll sum,maxn,maxadd,sumadd,addtag,cnt,tag;
		node operator + (const node other)const{
			node res = {0,0,0,0,0,0,-1};
			res.sum = sum+other.sum;
			res.cnt = cnt+other.cnt;
			res.sumadd = sumadd+other.sumadd;
			res.maxn = max(maxn,other.maxn);
			res.maxadd = max(maxadd,other.maxadd);
			return res;
		}
	}T[800010];
	void setup(int nl,int nr,int now){
		if(nl == nr){
			T[now] = {0,0,0,0,0,0,-1};
			return;
		}
		int mid = (nl+nr)>>1;
		setup(nl,mid,now*2);
		setup(mid+1,nr,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
	}
	void maketag(int now,ll val){
		if(T[now].cnt){T[now].maxn = T[now].tag = val;}
		else{T[now].maxn = T[now].tag = 0;}
		T[now].sum = T[now].cnt*val;
		T[now].addtag = 0;
	}
	void addtag(int now,ll val){
		T[now].maxn += T[now].maxadd*val;
		T[now].sum += T[now].sumadd*val;
		T[now].addtag += val;
	}
	void pushdown(int now){
		if(T[now].tag != -1){
			maketag(now*2,T[now].tag);
			maketag(now*2+1,T[now].tag);
			T[now].tag = -1;
		}
		addtag(now*2,T[now].addtag);
		addtag(now*2+1,T[now].addtag);
		T[now].addtag = 0;
	}
	void update(int nl,int nr,int at,ll val,int now){
		if(nl == nr){T[now] = {val,val,nl,nl,0,1,-1};return;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		if(at <= mid){update(nl,mid,at,val,now*2);}
		else{update(mid+1,nr,at,val,now*2+1);}
		T[now] = T[now*2]+T[now*2+1];
	}
	void update(int nl,int nr,int l,int r,ll val,int now){
		if(l <= nl&&nr <= r){maketag(now,val);return;}
		if(r < nl||nr < l){return;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		update(nl,mid,l,r,val,now*2);
		update(mid+1,nr,l,r,val,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
	}
	int upper_bound(int nl,int nr,ll val,int now){
		if(T[now].maxn <= val){return -1;}
		if(nl == nr){return nl;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		if(T[now*2].maxn > val){return upper_bound(nl,mid,val,now*2);}
		else{return upper_bound(mid+1,nr,val,now*2+1);}
	}
	ll getsum(int nl,int nr,int l,int r,int now){
		if(l <= nl&&nr <= r){return T[now].sum;}
		if(r < nl||nr < l){return 0;}
		pushdown(now);
		int mid = (nl+nr)>>1;
		ll resl = getsum(nl,mid,l,r,now*2);
		ll resr = getsum(mid+1,nr,l,r,now*2+1);
		T[now] = T[now*2]+T[now*2+1];
		return resl+resr;
	}
}TB;
void solve(int nl,int nr,vector<int>chk){
	if(chk.empty()){return;}
	if(nl == nr){
		for(int at:chk){
			if(A[at] >= at*P[nl].k+P[nl].b){pos[at] = nl;}
			else{pos[at] = 0;}
		}
		return;
	}
	int mid = (nl+nr)>>1,len = 0;
	for(int i = nl,j = nl;i <= mid;i = ++j){
		ll minb = P[j].b;
		while(j < mid&&P[j+1].k == P[j].k){minb = min(minb,P[++j].b);}
		line tmp = {P[j].k,minb};
		while(len >= 2&&(S[len]-S[len-1])*(tmp-S[len-1]) >= 0){--len;}
		S[++len] = tmp;
	}
	vector<int>L,R;int now = 1;
	for(int p:chk){
		while(now < len&&S[now+1].k*p+S[now+1].b <= S[now].k*p+S[now].b){++now;}
		if(S[now].k*p+S[now].b <= A[p]){L.push_back(p);}
		else{R.push_back(p);}
	}
	solve(nl,mid,L);
	solve(mid+1,nr,R);
};
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> Q;
    for(int i = 1;i <= N;++i){cin >> A[i];}
    int cnt = 0,tot = 0;
    for(int i = 1;i <= Q;++i){
		cin >> L[i].op;
		if(L[i].op == 1){
			cin >> L[i].l;
			id[++tot] = i;
			P[tot] = {-cnt,L[i].l};
		}
		else if(L[i].op == 2){++cnt;}
		else{cin >> L[i].l >> L[i].r;}
	}
	vector<int>check;
	for(int i = 1;i <= N;++i){check.push_back(i);}
	solve(1,tot,check);
	for(int i = 1;i <= N;++i){upd[id[pos[i]]].push_back(i);}
	TA.setup(1,N,1,A);
	TB.setup(1,N,1);
	for(int i = 1;i <= Q;++i){
		if(L[i].op == 1){
			int pos = TB.upper_bound(1,N,L[i].l,1);
			if(pos != -1){TB.update(1,N,pos,N,L[i].l,1);}
			for(int p:upd[i]){
				TA.kill(1,N,p,1);
				TB.update(1,N,p,L[i].l,1);
			}
		}else if(L[i].op == 2){
			TA.maketag(1,1);
			TB.addtag(1,1);
		}else{
			ll sum1 = TA.getsum(1,N,L[i].l,L[i].r,1);
			ll sum2 = TB.getsum(1,N,L[i].l,L[i].r,1);
			cout << sum1+sum2 << "\n";
		}
	}
    return 0;
}
