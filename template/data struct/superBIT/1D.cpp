#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
int start[100010],N,M;
struct BIT{
	long long num[100010];int len;
	void add(int addr,long long delta){
		while(addr <= len){
			num[addr] += delta;
			addr += lowbit(addr);
		}
	}
	long long getsum(int addr){
		long long sum = 0;
		while(addr > 0){
			sum += num[addr];
			addr -= lowbit(addr);
		}
		return sum;
	}
}tree,tree1;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	tree1.len = tree.len = N;
	for(int i = 1;i <= N;++i){cin >> start[i];}
	for(int i = N;i >= 1;--i){start[i]-=start[i-1];}
	for(int i = 1;i <= N;++i){tree.add(i,start[i]);}
	for(int i = 1;i <= N;++i){tree1.add(i,start[i]*(i-1));}
	while(M--){
		int op,x,y;
		cin >> op >> x >> y;
		if(op == 1){
			int k;cin >> k;
			tree.add(x,k);
			tree.add(y+1,-k);
			tree1.add(x,k*(x-1));
			tree1.add(y+1,-k*y);
		}else{
			long long R = y*tree.getsum(y) - tree1.getsum(y);--x;
			long long L = x*tree.getsum(x) - tree1.getsum(x);
			cout << R-L<<"\n";
		}
	}
	return 0;
}
