#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>MP,PM;
int N,Q,num[110010],blo[110010],cnt[110010],blolen,numcnt;
long long ans[110010];
struct question{
	int l,r,id;
	bool operator < (const question x)const{
		if(blo[l] == blo[x.l]) return r < x.r;
		return blo[l] < blo[x.l];
	}
}ask[100010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	blolen = sqrt(N);
	for(int i = 1;i <= N;++i){blo[i] = (i-1)/blolen+1;}
	for(int i = 1;i <= N;++i){
		cin >> num[i];
		if(MP[num[i]] == 0){MP[num[i]] = ++numcnt;}
	}
	for(int i = 1;i <= Q;++i){
		cin >> ask[i].l >> ask[i].r;
		ask[i].id = i;
	}
	sort(ask+1,ask+1+Q);
	int blonow = 0,l = 0,r = 0,mid = 0;long long A = 0,A0 = 0;
	for(int i = 1;i <= Q;++i){
		int B = blo[ask[i].l];
		if(B != blonow){
			memset(cnt,0,sizeof(cnt));
		    A = A0 = 0;
			blonow = B;
			mid = min(blolen*B,N);
			l = mid+1;r = mid;
		}
		if(blo[ask[i].r] == B){
			l = ask[i].l;r = ask[i].l-1;
			while(r < ask[i].r){
				cnt[MP[num[++r]]]++;
				A = max(A,1ll*cnt[MP[num[r]]]*num[r]);
			}
			ans[ask[i].id] = A;A = 0;
			while(r >= ask[i].l){cnt[MP[num[r--]]]--;}
			l = mid+1;r = mid;
			continue;
		}
		while(r < ask[i].r){
			cnt[MP[num[++r]]]++;
			A0 = max(A0,1ll*cnt[MP[num[r]]]*num[r]);
		}
		A = A0;
		while(l > ask[i].l){
			cnt[MP[num[--l]]]++;
			A = max(A,1ll*cnt[MP[num[l]]]*num[l]);
		}
		ans[ask[i].id] = A;
		while(l <= mid){cnt[MP[num[l++]]]--;}
	}
	for(int i = 1;i <= Q;++i){cout << ans[i] <<"\n";}
	return 0;
}
