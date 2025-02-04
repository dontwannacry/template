#include<bits/stdc++.h>
using namespace std;
int N,Q,num[100010],ansc[100010],ansu[100010],blo[100010];
int cnt[100010],vis[100010],blouni[1010],blosum[1010],blolen;
struct question{
	int l,r,a,b,id;
	bool operator < (const question x)const{
		if(blo[l] == blo[x.l]) return r < x.r;
		return blo[l] < blo[x.l];
	}
}ask[100010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	blolen = sqrt(100000);
	for(int i = 1;i <= N;++i)cin >> num[i];
	for(int i = 1;i <= N;++i) blo[i] = (i-1)/blolen+1;
	for(int i = 1;i <= Q;++i){
		cin >> ask[i].l >> ask[i].r >> ask[i].a >> ask[i].b;
		ask[i].id = i;
	}
	sort(ask+1,ask+1+Q);
	int l = 1,r = 0;
	for(int i = 1;i <= Q;++i){
		while(r < ask[i].r){
			++r;
			blosum[blo[num[r]]]++;
			cnt[num[r]]++;
			if(cnt[num[r]] == 1){
				vis[num[r]] = 1;
				blouni[blo[num[r]]]++;
			}	
		}
		while(r > ask[i].r){
			blosum[blo[num[r]]]--;
			cnt[num[r]]--;
			if(cnt[num[r]] == 0){
				vis[num[r]] = 0;
				blouni[blo[num[r]]]--;
			}
			r--;
		}
		while(l < ask[i].l){
			blosum[blo[num[l]]]--;
			cnt[num[l]]--;
			if(cnt[num[l]] == 0){
				vis[num[l]] = 0;
				blouni[blo[num[l]]]--;
			}
			l++;
		}
		while(l > ask[i].l){
			--l;
			blosum[blo[num[l]]]++;
			cnt[num[l]]++;
			if(cnt[num[l]] == 1){
				vis[num[l]] = 1;
				blouni[blo[num[l]]]++;
			}
		}
		int x = blo[ask[i].a],y = blo[ask[i].b],ac = 0,au = 0;
		if(x == y){
			for(int j = ask[i].a;j <= ask[i].b;++j){
				ac += cnt[j];
				au += vis[j];
			}
		}else{
			for(int j = ask[i].a;blo[j] == x&&j <= ask[i].b;++j){
				ac += cnt[j];
				au += vis[j];
			}
			for(int j = x+1;j < y;++j){
				ac += blosum[j];
				au += blouni[j];
			}
			for(int j = ask[i].b;blo[j] == y;--j){
				ac += cnt[j];
				au += vis[j];
			}
		}
		ansc[ask[i].id] = ac;
		ansu[ask[i].id] = au;
	}
	for(int i = 1;i <= Q;++i){cout<<ansc[i]<<" "<<ansu[i]<<"\n";}
	return 0;
}
