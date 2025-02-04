#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,cmpid,cnt,tot,root,lastans,rub[200010],len;
struct point{
	int x[2],val;
	bool operator < (const point other)const{
		return x[cmpid] < other.x[cmpid];
	}
}P[200010];
struct node{point p;int mx[2],mi[2],son[2],sum,si;}tree[200010];
int newnode(){
	if(len){return rub[len--];}
	return ++tot;
}
bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2){return (x1 >= X1&&y1 >= Y1&&x2 <= X2&&y2 <= Y2);}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2){return (x2 < X1||y2 < Y1||x1 > X2||y1 > Y2);}
void pushup(int now){
	int ls = tree[now].son[0],rs = tree[now].son[1];
	tree[now].si = 1;tree[now].sum = tree[now].p.val;
	if(ls){
		tree[now].mi[0] = min(tree[now].mi[0],tree[ls].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[ls].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[ls].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[ls].mx[1]);
		tree[now].si += tree[ls].si;
		tree[now].sum += tree[ls].sum;
	}if(rs){
		tree[now].mi[0] = min(tree[now].mi[0],tree[rs].mi[0]);
		tree[now].mi[1] = min(tree[now].mi[1],tree[rs].mi[1]);
		tree[now].mx[0] = max(tree[now].mx[0],tree[rs].mx[0]);
		tree[now].mx[1] = max(tree[now].mx[1],tree[rs].mx[1]);
		tree[now].si += tree[rs].si;
		tree[now].sum += tree[rs].sum;
	}
}
void setup(int l,int r,int k,int now){
	cmpid = k;
	int mid = (l+r)>>1;
	nth_element(P+l,P+mid,P+r+1);
	tree[now].p = P[mid];
	tree[now].son[0] = tree[now].son[1] = 0;
	tree[now].si = 1;tree[now].sum = P[mid].val;
	tree[now].mi[0] = tree[now].mx[0] = P[mid].x[0];
	tree[now].mi[1] = tree[now].mx[1] = P[mid].x[1];
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
		tree[now].son[0] = tree[now].son[1] = 0;
		tree[now].p = in;tree[now].si = 1;tree[now].sum = in.val;
		tree[now].mx[0] = tree[now].mi[0] = in.x[0];
		tree[now].mx[1] = tree[now].mi[1] = in.x[1];
		return;
	}
	cmpid = k;
	if(in < tree[now].p){insert(in,k^1,tree[now].son[0]);}
	else{insert(in,k^1,tree[now].son[1]);}
	pushup(now);
	check(k,now);
}
int query(int x1,int y1,int x2,int y2,int now){
//	cout << now << ":" <<tree[now].p.x[0]<<" "<<tree[now].p.x[1] << "\n";
//	cout << tree[now].mi[0] << " "<< tree[now].mi[1] << " "<< tree[now].mx[0] << " "<< tree[now].mx[1] << "!!\n";
	if(out(tree[now].mi[0],tree[now].mi[1],tree[now].mx[0],tree[now].mx[1],x1,y1,x2,y2)){return 0;}
	if(in(tree[now].mi[0],tree[now].mi[1],tree[now].mx[0],tree[now].mx[1],x1,y1,x2,y2)){return tree[now].sum;}
	int res = 0;
	if(in(tree[now].p.x[0],tree[now].p.x[1],tree[now].p.x[0],tree[now].p.x[1],x1,y1,x2,y2)){res += tree[now].p.val;}
	if(tree[now].son[0]){res += query(x1,y1,x2,y2,tree[now].son[0]);}
	if(tree[now].son[1]){res += query(x1,y1,x2,y2,tree[now].son[1]);}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	while(1){
		int op;cin >> op;
		if(op == 3){break;}
		else if(op == 1){
			int x,y,del;cin >> x >> y >> del;
			x ^= lastans;y ^= lastans;del ^= lastans;
			insert({x,y,del},0,root);
		}else{
			int x1,x2,y1,y2;cin >> x1 >> y1 >> x2 >> y2;
			x1 ^= lastans;y1 ^= lastans;x2 ^= lastans;y2 ^= lastans;
//			cout << x1 << " "<<y1 << " "<<x2 << " "<<y2 << ":\n";
			if(!root){lastans = 0;}
			else{lastans = query(x1,y1,x2,y2,root);}
			cout << lastans << "\n";
		}
	}
	return 0;
}
