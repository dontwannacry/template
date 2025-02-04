#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>MP;
int N,Q,num[210010],ans[210010],blo[210010],ladd[210010],radd[210010],blolen,numcnt;
struct question{
	int l,r,id;
	bool operator < (const question x)const{
		if(blo[l] == blo[x.l]) return r < x.r;
		return blo[l] < blo[x.l];
	}
}ask[200010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	blolen = sqrt(N);
	for(int i = 1;i <= N;++i){blo[i] = (i-1)/blolen+1;}
	for(int i = 1;i <= N;++i){
		cin >> num[i];
		if(MP[num[i]] == 0){MP[num[i]] = ++numcnt;}
		num[i] = MP[num[i]];
	}
	cin >> Q;
	for(int i = 1;i <= Q;++i){
		cin >> ask[i].l >> ask[i].r;
		ask[i].id = i;
	}
	sort(ask+1,ask+1+Q);
	int blonow = 0,l = 0,r = 0,mid = 0,A = 0,A0 = 0;
	for(int i = 1;i <= Q;++i){
		int B = blo[ask[i].l];
		if(B != blonow){
		    A = A0 = 0;
			memset(radd,0,sizeof(radd));
			memset(ladd,0,sizeof(ladd));
			blonow = B;
			r = blolen*(B-1)+1;mid = min(blolen*B,N);
		}
		while(r < ask[i].r){
			++r;
			radd[num[r]] = r;
			if(ladd[num[r]] == 0&&r > mid) ladd[num[r]] = r;
			if(r > mid)A0 = max(A0,r-ladd[num[r]]);
		}
		A = A0;
		l = mid+1;
		while(l > ask[i].l){
			--l;if(l > ask[i].r)continue;
			A = max(A,radd[num[l]]-l);
		}
		ans[ask[i].id] = A;
	}
	for(int i = 1;i <= Q;++i){cout << ans[i] <<"\n";}
	return 0;
}
