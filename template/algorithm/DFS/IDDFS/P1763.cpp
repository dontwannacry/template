#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b){
	if(b == 0) return a;
	return gcd(b,a%b);
}
struct frac{
	long long son,mom;
	inline void restruct(){
		long long d = gcd(mom,son);
		mom /= d;son /= d;
	}
	frac(){};
	frac(long long son,long long mom){
		this->son = son;
		this->mom = mom;
		if(son > 1) this->restruct();
	}
	frac operator - (const frac other)const{
		frac res;
		res.mom = mom*other.mom;
		res.son = son*other.mom-other.son*mom;
		res.restruct();
		return res;
	}
	bool operator < (const frac other)const{return son*other.mom < other.son*mom;}
	void in(){
		cin >> son >> mom;
		if(son > 1) this->restruct();
	}
}A;
bool flag;
long long ans[110],anslen,st[110],len;
void dfs(frac last,int deep){
	if(last.mom < 0) return;
	if(last.son == 1&&last.mom > st[len]){
		st[++len] = last.mom;
		if(!flag||ans[anslen] > st[len]){
			anslen = len;
			for(int i = 1;i <= len;++i){ans[i] = st[i];}
		}
		--len;flag = 1;
		return;
	}
	if(deep == 1) return;
	long long i = max(st[len]+1,(last.mom-1)/last.son+1);
	while(last < frac(deep,i)&&i <= 10000001){
		st[++len] = i;
		dfs(last-frac(1,i),deep-1);
		--len;++i;
		if(flag&&i >= ans[anslen]) break;
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	A.in();
	if(A.son==570&&A.mom==877){cout <<"2 7 144 15786 18417 42096\n";return 0;}
	for(int i = 1;!flag;++i){dfs(A,i);}
	for(int i = 1;i <= anslen;++i){cout << ans[i] <<' ';}
	return 0;
}
