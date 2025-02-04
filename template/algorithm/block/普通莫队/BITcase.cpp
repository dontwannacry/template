#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
struct BIT{
	int num[30010],len;
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
}tree;
struct question{
	int l,r,id;
	bool operator < (const question link)const{
		if(r == link.r)return l < link.l;
		return r < link.r;
	}
}ask[200010];
int N,Q,num[30010],re[1000010],ans[200010],len = 1;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;tree.len = N;
	for(int i = 1;i <= N;++i) cin >> num[i];
	cin >> Q;
	for(int i = 1;i <= Q;++i){
		cin >> ask[i].l >> ask[i].r;
		ask[i].id = i;
	}
	sort(ask+1,ask+1+Q);
	for(int i = 1;i <= N;++i) tree.num[i] = lowbit(i);
	for(int i = 1;i <= N;++i){
		if(re[num[i]]) tree.add(re[num[i]],-1);
        re[num[i]] = i;
		while(ask[len].r == i){
			int sum = tree.getsum(ask[len].r)-tree.getsum(ask[len].l-1);
			ans[ask[len].id] = sum;
			++len;
		}
	}
	for(int i = 1;i <= Q;++i){cout << ans[i] <<"\n";}
	return 0;
}
