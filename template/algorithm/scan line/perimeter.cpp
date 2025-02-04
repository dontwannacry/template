#include<bits/stdc++.h>
using namespace std;
struct Line{
	int y,x1,x2,val;
	bool operator < (const Line other)const{
		if(y == other.y){return val > other.val;}
		return y < other.y;
	}
}L[200010];
struct point{int l,r,num,add,tag,lo,ro;}node[1600010];
int N,X[200010],ycnt;long long ANS;
void pushup(int now){
	if(node[now].add){
		node[now].num = node[now].r-node[now].l;
		node[now].ro = node[now].lo = 1;
		node[now].tag = 0;
	}else{
		node[now].lo = node[now*2].lo;
		node[now].ro = node[now*2+1].ro;
		node[now].num = node[now*2].num + node[now*2+1].num;
		node[now].tag = node[now*2].tag + node[now*2+1].tag;
		if(node[now*2].ro != node[now*2+1].lo){node[now].tag++;}
	}
}
bool inset(int L,int R,int l,int r){return(L <= l&&R >= r);}
bool outset(int L,int R,int l,int r){return(L > r||R < l);}
void setup(int l,int r,int now){
	node[now].l = X[l],node[now].r = X[r+1];
	if(l >= r){return;}
	int mid = (l+r)/2;
	setup(l,mid,now*2);
	setup(mid+1,r,now*2+1);
}
void update(int l,int r,int add,int now){
	if(inset(l,r-1,node[now].l,node[now].r-1)){node[now].add += add;}
	else if(!outset(l,r-1,node[now].l,node[now].r-1)){
		update(l,r,add,now*2);
		update(l,r,add,now*2+1);
	}
	pushup(now);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){
		int X1,X2,Y1,Y2;cin >> X1 >> Y1 >> X2 >> Y2;
		L[i*2-1].y = Y1;
		L[i*2].y = Y2;
		X[i*2-1] = L[i*2].x1 = L[i*2-1].x1 = X1;
		X[i*2] = L[i*2].x2 = L[i*2-1].x2 = X2;
		L[i*2].val = -1;L[i*2-1].val = 1;
	}
	ycnt = N*2;
	sort(L+1,L+1+ycnt);
	sort(X+1,X+1+ycnt);
	ycnt = unique(X+1,X+1+ycnt)-X-1;
	X[0] = -1000000000;X[ycnt+1] = 1000000000;
	L[2*N+1].y = L[2*N].y;L[0].y = -1000000000;
	setup(0,ycnt,1);
	int last;
	for(int i = 1;i <= 2*N;++i){
		if(L[i-1].y != L[i].y||L[i-1].val != L[i].val){last = node[1].num;}
		update(L[i].x1,L[i].x2,L[i].val,1);
		if(L[i+1].y != L[i].y||L[i+1].val != L[i].val){ANS += abs(last-node[1].num);}
		ANS += 1ll*node[1].tag*(L[i+1].y-L[i].y);
	}
	cout << ANS;
	return 0;
}
