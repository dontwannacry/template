#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace C_2D{
	bool inset(ll x,ll l,ll r){return (x >= min(l,r))&&(x <= max(l,r));}
	struct point{
		ll x,y;
		point(){}
		point(ll x,ll y){this->x = x;this->y = y;}
		bool operator < (const point other)const{
			if(x == other.x) return y < other.y;
			return x < other.x; 
		}
	};
	ll farway(point A,point B){return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);}
	struct vector{
		ll x,y;
		vector(){}
		vector(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		vector(ll x,ll y){this->x = x;this->y = y;}
		ll operator * (const vector other)const{return x*other.x+y*other.y;}
		ll operator ^ (const vector other)const{return x*other.y-y*other.x;}
		vector operator + (const vector other)const{return {x+other.x,y+other.y};}
		vector operator - (const vector other)const{return {x-other.x,y-other.y};}
	};
	bool vector_Parallel(vector A,vector B){return A.x*B.y == A.y*B.x;}
	bool vector_Vertical(vector A,vector B){return A.x*B.y+A.y*B.x == 0;}
	vector operator - (const point A,const point B){return vector(A,B);}
}
using C_2D::point;
using C_2D::farway;
struct stack_max{
    point num[100010];int len;
    void clear(){len = 0;}
    void push(point now){
        while(len > 1&&((num[len-1]-num[len])^(num[len-1]-now)) <= 0){num[len--] = {0,0};}
        num[++len] = now;
    }
}Q;
point P[100010],li[200010];
int N,len;
ll ans = 0;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){cin >> P[i].x >> P[i].y;}
	sort(P+1,P+1+N);
	Q.clear();
	for(int i = 1;i <= N;++i){Q.push(P[i]);}
//	for(int i = 2;i <= Q.len;++i){ans += farway(Q.num[i],Q.num[i-1]);}
	for(int i = 1;i <= Q.len;++i){li[++len] = Q.num[i];}
	Q.clear();
	for(int i = N;i >= 1;--i){Q.push(P[i]);}
	for(int i = 2;i <= Q.len;++i){li[++len] = Q.num[i];}
//	for(int i = 2;i <= Q.len;++i){ans += farway(Q.num[i],Q.num[i-1]);}
	if(len < 4){
		cout << farway(li[1],li[2]) << "\n";
		return 0;
	}
	for(int i = 1,j = 3;i < len;++i){
		while(abs((li[i]-li[i+1])^(li[i]-li[j])) <= abs((li[i]-li[i+1])^(li[i]-li[j%len+1]))){j = j%len+1;}
		ans = max(ans,farway(li[i],li[j]));
		ans = max(ans,farway(li[i+1],li[j]));
//		cout << i << " "<<j <<":"<<farway(li[i],li[j]) <<" "<<farway(li[i+1],li[j])<<"\n";
	}
//	cout << len << "!\n";
//	for(int i = 1;i <= len;++i){cout << li[i].x << " "<<li[i].y << ";\n";}
	cout << ans;
	return 0;
}
