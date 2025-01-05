#include<bits/stdc++.h>
using namespace std;
namespace C_2D{
	long double esp = 1e-6;
	bool inset(long double x,long double l,long double r){return (x >= min(l,r))&&(x <= max(l,r));}
	struct point{
		long double x,y;
		point(){}
		point(long double x,long double y){this->x = x;this->y = y;}
		bool operator == (const point other)const{return abs(other.x-x)<esp&&abs(other.y-y)<esp;}
		bool operator < (const point other)const{
			if(x == other.x) return y < other.y;
			return x < other.x; 
		}
	};
	long double farway(point A,point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
	struct vector{
		long double x,y;
		vector(){}
		vector(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		vector(long double x,long double y){this->x = x;this->y = y;}
		long double operator * (const vector other)const{return x*other.x+y*other.y;}
		long double operator ^ (const vector other)const{return x*other.y-y*other.x;}
		vector operator + (const vector other)const{return {x+other.x,y+other.y};}
		vector operator - (const vector other)const{return {x-other.x,y-other.y};}
	};
	bool vector_Parallel(vector A,vector B){return abs(A.x*B.y-A.y*B.x) < esp;}
	bool vector_Vertical(vector A,vector B){return abs(A.x*B.y+A.y*B.x) < esp;}
}
using C_2D::point;
using C_2D::farway;
using C_2D::esp;
struct stack_max{
    point num[100010];int len;
    void clear(){len = 0;}
    void push(point now){
        while(len > 1&&(C_2D::vector(num[len-1],num[len])^C_2D::vector(num[len-1],now)) < esp){--len;}
        num[++len] = now;
    }
}Q;
point li[100010];
int N;
long double ans = 0;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){cin >> li[i].x >> li[i].y;}
	sort(li+1,li+1+N);
	Q.clear();
	Q.push(li[1]);Q.push(li[2]);
	for(int i = 3;i <= N;++i){Q.push(li[i]);}
	for(int i = 2;i <= Q.len;++i){ans += farway(Q.num[i],Q.num[i-1]);}
	Q.clear();
	Q.push(li[N]);Q.push(li[N-1]);
	for(int i = N-2;i >= 1;--i){Q.push(li[i]);}
	for(int i = 2;i <= Q.len;++i){ans += farway(Q.num[i],Q.num[i-1]);}
	printf("%.2Lf",ans);
	return 0;
}
