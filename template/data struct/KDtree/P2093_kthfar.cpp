#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,cmpid,tot,root,px,py,K;
struct anscase{
	ll val,id;
	bool operator < (const anscase other)const{
		if(val == other.val){return id < other.id;}
		return val > other.val;
	}
};
struct point{
	int x[2],id;
	bool operator < (const point other)const{
		return x[cmpid] < other.x[cmpid];
	}
}P[100010];
struct node{point p;int mx[2],mi[2],son[2];}tree[100010];
priority_queue<anscase>Q;
ll dis(point p){return 1ll*(p.x[0]-px)*(p.x[0]-px)+1ll*(p.x[1]-py)*(p.x[1]-py);}
ll maxdis(node now){
	ll delx = max(abs(now.mx[0]-px),abs(now.mi[0]-px)),dely = max(abs(now.mx[1]-py),abs(now.mi[1]-py));
	return delx*delx+dely*dely;
}
void pushup(int now){
	int ls = tree[now].son[0],rs = tree[now].son[1];
	if(ls){
		tree[now].mi[0] = min(tree[now].mi[0],tree[ls].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[ls].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[ls].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[ls].mx[1]);
	}if(rs){
		tree[now].mi[0] = min(tree[now].mi[0],tree[rs].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[rs].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[rs].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[rs].mx[1]);
	}
}
void setup(int l,int r,int k,int now){
	cmpid = k;
	int mid = (l+r)>>1;
	nth_element(P+l,P+mid,P+r+1);
	tree[now].p = P[mid];
	tree[now].mi[0] = tree[now].mx[0] = P[mid].x[0];
	tree[now].mi[1] = tree[now].mx[1] = P[mid].x[1];
	if(l < mid){tree[now].son[0] = ++tot;setup(l,mid-1,k^1,tot);}
	if(mid < r){tree[now].son[1] = ++tot;setup(mid+1,r,k^1,tot);}
	pushup(now);
}
void query(int now){
	ll res = dis(tree[now].p);
	Q.push({res,tree[now].p.id});Q.pop();
	int ls = tree[now].son[0],rs = tree[now].son[1];
	ll ld = -2,rd = -2;
	if(ls){ld = maxdis(tree[ls]);}
	if(rs){rd = maxdis(tree[rs]);}
	if(ld > rd){
		if(ld >= Q.top().val){query(ls);}
		if(rd >= Q.top().val){query(rs);}
	}else{
		if(rd >= Q.top().val){query(rs);}
		if(ld >= Q.top().val){query(ls);}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){cin >> P[i].x[0] >> P[i].x[1];P[i].id = i;}
	root = ++tot;
	setup(1,N,0,root);
	cin >> M;
	for(int i = 1;i <= M;++i){
		while(!Q.empty()){Q.pop();}
		cin >> px >> py >> K;
		for(int i = 1;i <= K;++i){Q.push({-1,0});}
		query(root);
		cout << Q.top().id << "\n";
	}
	return 0;
}
