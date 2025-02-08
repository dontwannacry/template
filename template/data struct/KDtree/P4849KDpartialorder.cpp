#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
int N,M,cmpid,cnt,tot,root,rub[80010],len;
struct anscase{
    ll res,ti;
    anscase(){res = ti = 0;}
    anscase operator + (const anscase other)const{
        anscase re;
        re.res = max(res,other.res);
        if(re.res == res){re.ti += ti;}
        if(re.res == other.res){re.ti += other.ti;}
        if(re.ti >= MOD){re.ti -= MOD;}
        return re;
    }
}ans,res;
struct point{
	int x[4];anscase val;
	bool operator < (const point other)const{return x[cmpid] < other.x[cmpid];}
}P[80010],in[80010];
struct node{
    int mx[3],mi[3],son[2],si;anscase maxn;point p;
    node(){}
    node(point in){
        p = in;
        son[0] = son[1] = 0;
        si = 1;maxn = in.val;
        for(int i = 0;i < 3;++i){mi[i] = mx[i] = p.x[i];}
    }
}T[80010];
int newnode(){
	if(len){return rub[len--];}
	return ++tot;
}
void pushup(int now){
	int ls = T[now].son[0],rs = T[now].son[1];
	T[now].si = 1;T[now].maxn = T[now].p.val;
	if(ls){
        for(int i = 0;i < 3;++i){
            T[now].mi[i] = min(T[now].mi[i],T[ls].mi[i]);
            T[now].mx[i] = max(T[now].mx[i],T[ls].mx[i]);
        }
		T[now].si += T[ls].si;
		T[now].maxn = T[now].maxn+T[ls].maxn;
	}if(rs){
        for(int i = 0;i < 3;++i){
            T[now].mi[i] = min(T[now].mi[i],T[rs].mi[i]);
            T[now].mx[i] = max(T[now].mx[i],T[rs].mx[i]);
        }
		T[now].si += T[rs].si;
        T[now].maxn = T[now].maxn+T[rs].maxn;
	}
}
void setup(int l,int r,int k,int now){
	cmpid = k;
	int mid = (l+r)>>1;
	nth_element(P+l,P+mid,P+r+1);
	T[now] = node(P[mid]);
	if(l < mid){T[now].son[0] = newnode();setup(l,mid-1,(k+1)%3,T[now].son[0]);}
	if(mid < r){T[now].son[1] = newnode();setup(mid+1,r,(k+1)%3,T[now].son[1]);}
	pushup(now);
}
void remove(int now){
	P[++cnt] = T[now].p;rub[++len] = now;
	if(T[now].son[0]){remove(T[now].son[0]);}
	if(T[now].son[1]){remove(T[now].son[1]);}
}
void check(int k,int now){
	int ls = T[now].son[0],rs = T[now].son[1];
	if((ls&&T[now].si*0.75<T[ls].si)||(rs&&T[now].si*0.75<T[rs].si)){
		cnt = 0;
		P[++cnt] = T[now].p;
		if(ls){remove(ls);}
		if(rs){remove(rs);}
		setup(1,cnt,k,now);
	}
}
void insert(point in,int k,int &now){
	if(!now){
		now = newnode();
		T[now] = node(in);
		return;
	}
	cmpid = k;
	if(in < T[now].p){insert(in,(k+1)%3,T[now].son[0]);}
	else{insert(in,(k+1)%3,T[now].son[1]);}
	pushup(now);
	check(k,now);
}
void query(point check,int now){
    if(!now){return;}
	if(check.x[0] < T[now].mi[0]||check.x[1] < T[now].mi[1]||check.x[2] < T[now].mi[2]){return;}
	if(T[now].mx[0] <= check.x[0]&&T[now].mx[1] <= check.x[1]&&T[now].mx[2] <= check.x[2]){res = res+T[now].maxn;return;}
	if(T[now].p.x[0] <= check.x[0]&&T[now].p.x[1] <= check.x[1]&&T[now].p.x[2] <= check.x[2]){res = res+T[now].p.val;}
    anscase ld = T[T[now].son[0]].maxn,rd = T[T[now].son[1]].maxn;
    if(ld.res > rd.res){
        if(ld.res >= res.res){query(check,T[now].son[0]);}
        if(rd.res >= res.res){query(check,T[now].son[1]);}
    }else{
        if(rd.res >= res.res){query(check,T[now].son[1]);}
        if(ld.res >= res.res){query(check,T[now].son[0]);}
    }
	return;
}
bool cmp(point A,point B){
    if(A.x[3] != B.x[3]){return A.x[3] < B.x[3];}
    if(A.x[2] != B.x[2]){return A.x[2] < B.x[2];}
    if(A.x[1] != B.x[1]){return A.x[1] < B.x[1];}
    return A.x[0] < B.x[0];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
    for(int i = 1;i <= N;++i){
        cin >> in[i].x[0] >> in[i].x[1] >> in[i].x[2] >> in[i].x[3];
        cin >> in[i].val.res;in[i].val.ti = 1;
    }
    sort(in+1,in+1+N,cmp);T[0].maxn.res = -1;
    for(int i = 1;i <= N;++i){
        res = anscase();
        query(in[i],root);
        in[i].val.res += res.res;
        in[i].val.ti = max(in[i].val.ti,res.ti);
        ans = ans+in[i].val;
        insert(in[i],0,root);
    }
    cout << ans.res << "\n" << ans.ti%MOD << "\n";
	return 0;
}