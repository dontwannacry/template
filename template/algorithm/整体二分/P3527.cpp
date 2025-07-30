#include<bits/stdc++.h>
using namespace std;
struct rainstone{int id,l,r,a;}li[600010];
vector<int>sta[300010];
int N,M,K,cnt,need[300010],newid[300010],id[300010],res[300010],ans[300010];
long long tmp[300010];
void solve(int ql,int qr,int l,int r,int len){
	if(l > r){return;}
	if(ql > qr){
		for(int i = l;i <= r;++i){ans[id[i]] = ql;}
		return;
	}
	for(int i = 1;i <= len;++i){tmp[i] = 0;}
	for(int i = l;i <= r;++i){for(int now:sta[id[i]]){tmp[now] = 1;}}
	for(int i = 2;i <= len;++i){tmp[i] += tmp[i-1];}
	for(int i = l;i <= r;++i){for(int &now:sta[id[i]]){now = tmp[now];}}
	for(int i = ql;i <= qr;++i){li[i].l = tmp[li[i].l-1]+1;li[i].r = tmp[li[i].r];}
	len = tmp[len];
	int qmid = (ql+qr)>>1,mid = l-1,rmid;
	for(int i = 1;i <= len;++i){tmp[i] = 0;}
	for(int i = ql;i <= qmid;++i){tmp[li[i].l] += li[i].a;tmp[li[i].r+1] -= li[i].a;}
	for(int i = 2;i <= len;++i){tmp[i] += tmp[i-1];}
	for(int i = l;i <= r;++i){
		res[i] = 0;
		for(int now:sta[id[i]]){res[i] = min(tmp[now]+res[i],0x3f3f3f3fll);}
		if(res[i] >= need[id[i]]){newid[++mid] = id[i];}
	}
	rmid = mid;
	for(int i = l;i <= r;++i){
		if(res[i] < need[id[i]]){
			newid[++mid] = id[i];
			need[id[i]] -= res[i];
		}
	}
	for(int i = l;i <= r;++i){id[i] = newid[i];}
	solve(ql,qmid-1,l,rmid,len);
	solve(qmid+1,qr,rmid+1,r,len);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= M;++i){
		int belong;cin >> belong;
		sta[belong].push_back(i);
	}
	for(int i = 1;i <= N;++i){cin >> need[i];}
	cin >> K;
	for(int i = 1;i <= K;++i){
		int l,r,a;cin >> l >> r >> a;
		if(l <= r){li[++cnt] = {i,l,r,a};}
		else{
			li[++cnt] = {i,l,M,a};
			li[++cnt] = {i,1,r,a};
		}
	}
	for(int i = 1;i <= N;++i){id[i] = i;}
	solve(1,cnt,1,N,M);
	for(int i = 1;i <= N;++i){
		if(ans[i] > cnt){cout << "NIE\n";}
		else{cout << li[ans[i]].id <<"\n";}
	}
	return 0;
}
