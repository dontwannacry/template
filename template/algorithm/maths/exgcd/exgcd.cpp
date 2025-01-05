#include<bits/stdc++.h>
using namespace std;
long long a,b,c,x,y,g,kx,ky,X1,X2,Y1,Y2;
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1,y = 0;
        return a;
    }
    long long gcd = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return gcd;
}//ax+by=gcd(a,b);
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;cin >> T;
	while(T--){
		cin >> a >> b >> c;
		g = exgcd(a,b,x,y);
		if(c % g){cout << "-1\n";continue;}
		x *= c/g;y *= c/g;
		X1 = (x%(b/g)+(b/g)-1)%(b/g)+1;kx = (X1-x)/(b/g);Y2 = y-(a/g)*kx;
		Y1 = (y%(a/g)+(a/g)-1)%(a/g)+1;ky = (Y1-y)/(a/g);X2 = x-(b/g)*ky;
		if(X2 > 0&&Y2 > 0){cout << (X2-X1)/(b/g)+1 <<" "<<X1<<" "<<Y1<<" "<<X2<<" "<<Y2<<"\n";}
		else{cout << X1<<" "<<Y1<<"\n";}
	}
    return 0;
}
