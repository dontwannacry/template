#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,cmpid,tot,root,px,py,ans,len,cnt,rub[600010];
struct point{
	int x[2];
	bool operator < (const point other)const{
		return x[cmpid] < other.x[cmpid];
	}
}P[600010];
struct node{
	int mx[2],mi[2],son[2],si;point p;
	node(){}
	node(point in){
		p = in;si = 1;
		mx[0] = mi[0] = p.x[0];
		mx[1] = mi[1] = p.x[1];
		son[0] = son[1] = 0;
	}
}tree[600010];
int newnode(){
	if(len){return rub[len--];}
	return ++tot;
}
int dis(point p){return abs(p.x[0]-px)+abs(p.x[1]-py);}
int mindis(node now){
	int delx = max(0,px-now.mx[0])+max(0,now.mi[0]-px),dely = max(0,py-now.mx[1])+max(0,now.mi[1]-py);
	return delx+dely;
}
void pushup(int now){
	int ls = tree[now].son[0],rs = tree[now].son[1];tree[now].si = 1;
	if(ls){
		tree[now].mi[0] = min(tree[now].mi[0],tree[ls].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[ls].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[ls].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[ls].mx[1]);
        tree[now].si += tree[ls].si;
	}if(rs){
		tree[now].mi[0] = min(tree[now].mi[0],tree[rs].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[rs].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[rs].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[rs].mx[1]);
        tree[now].si += tree[rs].si;
	}
}
void setup(int l,int r,int k,int now){
	cmpid = k;
	int mid = (l+r)>>1;
	nth_element(P+l,P+mid,P+r+1);
	tree[now] = node(P[mid]);
	if(l < mid){tree[now].son[0] = newnode();setup(l,mid-1,k^1,tree[now].son[0]);}
	if(mid < r){tree[now].son[1] = newnode();setup(mid+1,r,k^1,tree[now].son[1]);}
	pushup(now);
}
void remove(int now){
	P[++cnt] = tree[now].p;rub[++len] = now;
	if(tree[now].son[0]){remove(tree[now].son[0]);}
	if(tree[now].son[1]){remove(tree[now].son[1]);}
}
void check(int k,int now){
	int ls = tree[now].son[0],rs = tree[now].son[1];
	if((ls&&tree[now].si*0.75<tree[ls].si)||(rs&&tree[now].si*0.75<tree[rs].si)){
		cnt = 0;
		P[++cnt] = tree[now].p;
		if(ls){remove(ls);}
		if(rs){remove(rs);}
		setup(1,cnt,k,now);
	}
}
void insert(point in,int k,int &now){
	if(!now){
		now = newnode();
		tree[now] = node(in);
		return;
	}
	cmpid = k;
	if(in < tree[now].p){insert(in,k^1,tree[now].son[0]);}
	else{insert(in,k^1,tree[now].son[1]);}
	pushup(now);
	check(k,now);
}
void query(int now){
	ans = min(ans,dis(tree[now].p));
	int ls = tree[now].son[0],rs = tree[now].son[1];
	int ld = 0x7f7f7f7f,rd = 0x7f7f7f7f;
	if(ls){ld = mindis(tree[ls]);}
	if(rs){rd = mindis(tree[rs]);}
	if(ld < rd){
		if(ld < ans){query(ls);}
		if(rd < ans){query(rs);}
	}else{
		if(rd < ans){query(rs);}
		if(ld < ans){query(ls);}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){cin >> P[i].x[0] >> P[i].x[1];}
	root = newnode();
	setup(1,N,0,root);
	for(int i = 1;i <= M;++i){
        int op;cin >> op >> px >> py;
        if(op == 1){
            insert({px,py},0,root);
        }
        else{
            ans = 0x3f3f3f3f;
            query(root);
            cout << ans << "\n";
        }
	}
	return 0;
}