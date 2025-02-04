#include<bits/stdc++.h>
using namespace std;
struct Line{
	int y,x1,x2,val;
	bool operator < (const Line other)const{return y < other.y;}
}L[200010];
struct point{int l,r,num,add;}node[3200010];
int N,X[200010],ycnt;long long ANS;
void pushup(int now){
	if(node[now].add) node[now].num = node[now].r-node[now].l;
	else node[now].num = node[now*2].num + node[now*2+1].num;
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
	if(inset(l,r,node[now].l,node[now].r)){node[now].add += add;}
	else if(!outset(l,r,node[now].l,node[now].r)){
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
	ycnt = unique(X+1,X+1+ycnt)-X-2;
	setup(1,ycnt,1);
	for(int i = 1;i < 2*N;++i){
		update(L[i].x1,L[i].x2,L[i].val,1);
		ANS += 1ll*node[1].num*(L[i+1].y-L[i].y);
	}
	cout << ANS;
	return 0;
}
