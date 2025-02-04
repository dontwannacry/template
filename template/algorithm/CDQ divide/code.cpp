#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&-(x))
int cmpid;
struct question{
	int op,x[3];
	bool operator < (const question other){
		if(x[cmpid] == other.x[cmpid]){return op > other.op;}
		return x[cmpid] < other.x[cmpid];
	}
}li[200010];
int N,ans[200010],needout[10010],needlen,len,op;
struct BIT{
	int num[200010];
	void update(int now,int delta){
		while(now <= len){
			num[now] += delta;
			now += lowbit(now);
		}
	}
	int getans(int now){
		int res = 0;
		while(now > 0){
			res += num[now];
			now -= lowbit(now);
		}
		return res;
	}
}T;
void solve(int l,int r){
	if(l == r){return;}
	cmpid = 0;sort(li+l,li+1+r);
	int mid = (l+r)>>1;
	cmpid = 1;sort(li+l,li+1+mid);sort(li+1+mid,li+1+r);
	int lo = l;
	for(int ro = mid+1;ro <= r;++ro){
		while(lo <= mid&&li[lo].x[1] <= li[ro].x[1]){
			if(li[lo].op > 0){T.update(li[lo].x[2],li[lo].op);}
			++lo;
		}
		if(li[ro].op <= 0){
			int w = (li[ro].op == -1?-1:1);
			ans[li[ro].x[2]] += w*T.getans(li[ro].x[2]);
		}
	}
	for(int i = l;i < lo;++i){if(li[i].op > 0){T.update(li[i].x[2],-li[i].op);}}
	solve(l,mid);
	solve(mid+1,r);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> op >> N;
	for(int i = 1;;++i){
		cin >> op;
		if(op == 3){break;}
		if(op == 1){
			int x,y,a;cin >> x >> y >> a;
			li[++len] = {a,x,y,i};
		}else{
			int x1,x2,y1,y2;cin >> x1 >> y1 >> x2 >> y2;
			li[++len] = {0,x2,y2,i};
			if(x1 != 1&&y1 != 1){li[++len] = {0,x1-1,y1-1,i};}
			if(x1 != 1){li[++len] = {-1,x1-1,y2,i};}
			if(y1 != 1){li[++len] = {-1,x2,y1-1,i};}
			needout[++needlen] = i;
		}
	}
	solve(1,len);
	for(int i = 1;i <= needlen;++i){cout << ans[needout[i]] << "\n";}
	return 0;
}
