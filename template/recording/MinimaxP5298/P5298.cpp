#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353,NY10 = 796898467;
struct point{int son[2],sum,mul;};
struct SGT{
	int root[300010],len;point T[300010*24];
	void setnum(int nl,int nr,int at,int delta,int now){
		T[now].sum = delta,T[now].mul = 1;
		if(nl == nr){return;}
		int mid = (nl+nr)>>1;
		if(at <= mid){
			if(!T[now].son[0]){T[now].son[0] = ++len;}
			setnum(nl,mid,at,delta,T[now].son[0]);
		}else{
			if(!T[now].son[1]){T[now].son[1] = ++len;}
			setnum(mid+1,nr,at,delta,T[now].son[1]);
		}
	}
	void maketag(int now,int num){
		T[now].mul = 1ll*T[now].mul*num%MOD;
		T[now].sum = 1ll*T[now].sum*num%MOD;
	}
	void pushdown(int now){
		if(T[now].son[0]){maketag(T[now].son[0],T[now].mul);}
		if(T[now].son[1]){maketag(T[now].son[1],T[now].mul);}
		T[now].mul = 1;
	}
	int treeadd(int nl,int nr,int lnum,int rnum,int p,int lnow,int rnow){
		if(!lnow&&!rnow){return 0;}
		if(!lnow){maketag(rnow,lnum);return rnow;}
		if(!rnow){maketag(lnow,rnum);return lnow;}
		pushdown(lnow);pushdown(rnow);
		int mid = (nl+nr)>>1;
		int lsl = T[T[lnow].son[0]].sum,lsr = T[T[lnow].son[1]].sum,rsl = T[T[rnow].son[0]].sum,rsr = T[T[rnow].son[1]].sum;
		T[lnow].son[0] = treeadd(nl,mid,(lnum+1ll*lsr*(1+MOD-p))%MOD,(rnum+1ll*rsr*(1+MOD-p))%MOD,p,T[lnow].son[0],T[rnow].son[0]);
		T[lnow].son[1] = treeadd(mid+1,nr,(lnum+1ll*lsl*p)%MOD,(rnum+1ll*rsl*p)%MOD,p,T[lnow].son[1],T[rnow].son[1]);
		T[lnow].sum = (T[T[lnow].son[0]].sum+T[T[lnow].son[1]].sum)%MOD;
		return lnow;
	}
	int getsum(int nl,int nr,int &ans,int down,int now){
		if(!now){return 0;}
		if(nl == nr){
			ans = (ans+1ll*nl*T[now].sum%MOD*T[now].sum%MOD*down)%MOD;
			return 1;
		}
		pushdown(now);
		int mid = (nl+nr)>>1,cnt = 0;
		cnt += getsum(nl,mid,ans,down,T[now].son[0]);
		cnt += getsum(mid+1,nr,ans,down+cnt,T[now].son[1]);
		return cnt;
	}
}T;
int N,A[300010],ans;
vector<int>ne[300010];
int Pow(int A,int B){
	int res = 1;
	while(B){
		if(B&1){res = 1ll*res*A%MOD;}
		A = 1ll*A*A%MOD;
		B >>= 1;
	}
	return res;
}
void dfs(int now,int fa){
	int flag = 0,son[2] = {0,0};
	for(int v:ne[now]){
		if(v == fa){continue;}
		dfs(v,now);
		son[flag++] = v;
	}
	if(!flag){T.setnum(1,1000000000,A[now],1,T.root[now] = ++T.len);}
	else if(flag == 1){T.root[now] = T.root[son[0]];}
	else{T.root[now] = T.treeadd(1,1000000000,0,0,1ll*A[now]*NY10%MOD,T.root[son[0]],T.root[son[1]]);}
}
void solve(){
	cin >> N;
	for(int i = 1;i <= N;++i){
		int f;cin >> f;
		if(f){
			ne[f].push_back(i);
			ne[i].push_back(f);
		}
	}
	for(int i = 1;i <= N;++i){cin >> A[i];}
	dfs(1,1);
	T.getsum(1,1000000000,ans,1,T.root[1]);
	cout << ans << "\n";
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T = 1;
    for(int i = 1;i <= T;++i){solve();}
    return 0;
}
