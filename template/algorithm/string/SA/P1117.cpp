#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char str[2][100010];
int M,rk[2][200020],tmp[200020],sa[2][100020],cnt[100020],height[2][100020];
int lg[100010],st[2][17][100010];
int N,A[100010],B[100010];
long long ans;
void suffix_array(int T){
	memset(cnt,0,sizeof(cnt));
	memset(tmp,0,sizeof(tmp));
	M = max(N,300);
	for(int i = 1;i <= N;++i){cnt[rk[T][i]=str[T][i]]++;}
	for(int i = 1;i <= M;++i){cnt[i]+=cnt[i-1];}
	for(int i = N;i >= 1;--i){sa[T][cnt[rk[T][i]]--] = i;}
	for(int re = 1;re < N;re <<= 1){
	    int cur = 0;
	    for (int i = N-re+1;i <= N;++i){tmp[++cur] = i;}
	    for (int i = 1;i <= N;i++){if(sa[T][i] > re){tmp[++cur]=sa[T][i]-re;}}
	    memset(cnt,0,sizeof(int)*(M+1));
//		for(int i = 0;i <= M;++i){cnt[i] = 0;}
		for(int i = 1;i <= N;++i){cnt[rk[T][i]]++;}
		for(int i = 1;i <= M;++i){cnt[i]+=cnt[i-1];}
		for(int i = N;i >= 1;--i){sa[T][cnt[rk[T][tmp[i]]]--] = tmp[i];}
		memcpy(tmp,rk[T],sizeof(int)*(N+1));
//		for(int i = 1;i <= N;++i){tmp[i] = rk[T][i];}
		int tot = 0;
		for(int i = 1;i <= N;++i){
			if(tmp[sa[T][i]]==tmp[sa[T][i-1]]&&tmp[sa[T][i]+re]==tmp[sa[T][i-1]+re]){rk[T][sa[T][i]] = tot;}
			else{rk[T][sa[T][i]] = ++tot;}
		}
	}
}
void getheight(int T){
	for(int i = 1,k = 0;i <= N;++i){
		if(k){--k;}
		while(str[T][i+k] == str[T][sa[T][rk[T][i]-1]+k]){++k;}
		height[T][rk[T][i]] = k;
	}
}
void stinit(int T){
	for(int i = 1;i <= N;++i){st[T][0][i] = height[T][i];}
	for(int i = 1;i <= 16;++i){
		for(int j = 1;j <= N-(1<<i)+1;++j){
			st[T][i][j] = min(st[T][i-1][j],st[T][i-1][j+(1<<(i-1))]);
		}
	}
}
int LCP(int l,int r,int T){
	l = rk[T][l],r = rk[T][r];
	if(l > r){swap(l,r);}++l;
	int lv = lg[r-l+1];
	return min(st[T][lv][l],st[T][lv][r-(1<<lv)+1]);
}
void clean(){
	ans = 0;
//	memset(cnt,0,sizeof(int)*(M+1));
//	memset(A,0,sizeof(int)*(N+1));
//	memset(B,0,sizeof(int)*(N+1));
//	memset(rk[0],0,sizeof(int)*(N+1));
//	memset(rk[1],0,sizeof(int)*(N+1));
//	memset(sa[0],0,sizeof(int)*(N+1));
//	memset(sa[1],0,sizeof(int)*(N+1));
//	memset(str[0],0,sizeof(char)*(N+1));
//	memset(str[1],0,sizeof(char)*(N+1));
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
	memset(rk,0,sizeof(rk));
	memset(sa,0,sizeof(sa));
	memset(height,0,sizeof(height));
	memset(st,0,sizeof(st));
	memset(str,0,sizeof(str));
}
void solve(){
	clean();
	cin >> (str[0]+1);
	N = strlen(str[0]+1);
	for(int i = 1;i <= N;++i){str[1][i] = str[0][N-i+1];}
	suffix_array(0);getheight(0);stinit(0);
	suffix_array(1);getheight(1);stinit(1);
//	for(int i = 1;i <= N;++i){cout << sa[0][i] << " ";}cout << "\n";
//	for(int i = 1;i <= N;++i){cout << height[0][i] << " ";}cout << "\n";
//	for(int i = 1;i <= N;++i){cout << str[1][i];}cout << "\n";
//	for(int i = 1;i <= N;++i){cout << sa[1][i] << " ";}cout << "\n";
//	for(int i = 1;i <= N;++i){cout << height[1][i] << " ";}cout << "\n";
	for(int len = 1;len <= N/2;++len){
//		cout << len << ":\n";
		for(int l = len,r = len*2;r <= N;r += len,l += len){
			int L = N-r+2,R = N-l+2;
			int lcp = min(LCP(l,r,0),len);
			int lcs = min(LCP(L,R,1),len-1);
			if(lcp+lcs >= len){
//				cout << l <<" "<<L<<" " <<R<<":"<<lcp<<" "<<LCP(l,r,0) <<" "<<lcs<<" "<<LCP(L,R,1)<<"\n";
				B[l-lcs]++;B[l+lcp-len+1]--;
				A[r+lcp]--;A[r-lcs+len-1]++;
			}
		}
	}
	for(int i = 1;i <= N;++i){A[i] += A[i-1];}
	for(int i = 1;i <= N;++i){B[i] += B[i-1];}
	for(int i = 1;i <= N;++i){
//		cout << A[i] << " "<<B[i] << "\n";
		ans += 1ll*A[i]*B[i+1];
	}
	cout << ans << "\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(int i = 2;i <= 100000;++i){lg[i] = lg[i>>1]+1;}
	int T;cin >> T;
	for(int i = 1;i <= T;++i){solve();}
	return 0;
}
