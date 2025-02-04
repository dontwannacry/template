#include<bits/stdc++.h>
using namespace std;
int N,Q,num[30010],ans[200010],cnt[1000010],blolen;
struct question{
	int l,r,id,blo;
	bool operator < (const question x)const{
		if(blo == x.blo) return r < x.r;
		return blo < x.blo;
	}
}ask[200010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	blolen = sqrt(N);
	for(int i = 1;i <= N;++i)cin >> num[i];
	cin >> Q;
	for(int i = 1;i <= Q;++i){
		cin >> ask[i].l >> ask[i].r;
		ask[i].id = i;
		ask[i].blo = (ask[i].l-1)/blolen+1;
	}
	sort(ask+1,ask+1+Q);
	int l = 1,r = 1,uninum = 1;
	cnt[num[1]]++;
	for(int i = 1;i <= Q;++i){
		while(r < ask[i].r){
			cnt[num[++r]]++;
			if(cnt[num[r]] == 1)uninum++;
		}
		while(r > ask[i].r){
			cnt[num[r]]--;
			if(cnt[num[r--]] == 0)uninum--;
		}
		while(l < ask[i].l){
			cnt[num[l]]--;
			if(cnt[num[l++]] == 0)uninum--;
		}
		while(l > ask[i].l){
			cnt[num[--l]]++;
			if(cnt[num[l]] == 1)uninum++;
		}
		ans[ask[i].id] = uninum;
	}
	for(int i = 1;i <= Q;++i){cout << ans[i] <<"\n";}
	return 0;
}
