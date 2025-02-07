#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int cmp(ll x,ll y){
    if(x < y){return 1;}
    if(y < x){return -1;}
    return 0;
}
ll dp[1000010],S[1000010],val[1000010],ans;
int N,X[1000010],P[1000010],C[1000010];
struct line{
    ll k,b;
    line(){k = b = 0;}
    ll gety(ll x){return k*x+b;}
}L[1000010];
struct LCSGT{
    int node[4000010];
	bool inset(int L,int R,int l,int r){return(L <= l&&r <= R);}
	bool outset(int L,int R,int l,int r){return(r < L||R < l);}
    void insert(int nl,int nr,int in,int now){
        int mid = (nl+nr)>>1;
        int chk = cmp(L[in].gety(X[mid]),L[node[now]].gety(X[mid]));
        if(chk == 1||(chk == 0&&in < node[now])){swap(in,node[now]);}
        if(nl == nr){return;}
        int chl = cmp(L[in].gety(X[nl]),L[node[now]].gety(X[nl])),chr = cmp(L[in].gety(X[nr]),L[node[now]].gety(X[nr]));
        if(chl != -1){insert(nl,mid,in,now*2);}
        if(chr != -1){insert(mid+1,nr,in,now*2+1);}
    }
	int findans(int nl,int nr,int at,int now){
        int res = node[now];
        if(nl == nr){return res;}
        int mid = (nl+nr)>>1,sp;
        if(at <= mid){sp = findans(nl,mid,at,now*2);}
        else{sp = findans(mid+1,nr,at,now*2+1);}
        int chk = cmp(L[res].gety(X[at]),L[sp].gety(X[at]));
        if(chk == 1){return res;}
        else if(chk == -1){return sp;}
        else{return min(sp,res);}
	}
}T;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 1;i <= N;++i){
        cin >> X[i] >> P[i] >> C[i];
        S[i] = S[i-1]+P[i];
        val[i] = val[i-1]+S[i-1]*(X[i]-X[i-1]);
    }
    for(int i = 1;i <= N;++i){
        int j = T.findans(1,N,i,1);
        dp[i] = C[i]+val[i]-val[j]-(X[i]-X[j])*S[j]+dp[j];
        L[i].b = dp[i]-val[i]+X[i]*S[i];L[i].k = -S[i];
        T.insert(1,N,i,1);
    }
    ans = dp[N];
    while(N&&P[N] == 0){--N;ans = min(ans,dp[N]);}
    cout << ans << "\n";
	return 0;
}
