#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
namespace C_2D{
	const ld eps = 1e-16L,inf = 1e12L;
	struct point{
		ld x,y;
		inline point(){}
		inline point(ld x,ld y){this->x = x;this->y = y;}
        inline point(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		inline bool operator == (const point other)const{return abs(other.x-x)<eps&&abs(other.y-y)<eps;}
        inline friend ld operator * (const point A,const point B){return A.x*B.x+A.y*B.y;}
        inline friend point operator * (const ld A,const point B){return point(A*B.x,A*B.y);}
        inline friend point operator * (const point A,const ld B){return point(A.x*B,A.y*B);}
		inline ld operator ^ (const point other)const{return x*other.y-y*other.x;}
		inline point operator + (const point other)const{return {x+other.x,y+other.y};}
		inline point operator - (const point other)const{return {x-other.x,y-other.y};}
	};
	struct line{
		point O,D;ld angle;int id;
		inline line(){}
		inline line(point A,point B,int id){O = A;D = point(A,B);this->id = id;angle = atan2(D.y,D.x);}
        inline friend bool operator < (const line A,const line B){
            if(abs(A.angle-B.angle) > eps){return A.angle < B.angle;}
            return (A.D^(B.O-A.O)) < -eps;
        }
	};
    inline point crosspoint(line L1,line L2){
        ld S1 = (L2.O+L2.D-L1.O)^L1.D,S2 = (L2.O-L1.O)^L1.D,base = 1.0/(S1-S2);
        point res = (S1*L2.O-S2*(L2.O+L2.D))*base;
        return res;
    }
}
using namespace C_2D;
inline bool check(line l1,line l2,line l3){return (l1.D^(crosspoint(l2,l3)-l1.O)) < -eps;}
int N,M,K;
line L[300010],tmp[300010];
struct queue_max{
    line num[300010];int l,r;
    inline void clear(){l = 1,r = 0;}
    inline void push(line x){num[++r] = x;}
    inline void checkout(line x){
        while(l < r&&check(x,num[r],num[r-1])){--r;}
        while(l < r&&check(x,num[l],num[l+1])){++l;}
    }
    inline void selfcheck(){
        while(l < r&&check(num[l],num[r],num[r-1])){--r;}
        while(l < r&&check(num[r],num[l],num[l+1])){++l;}
    }
}Q;
bool check(int AE86){
    Q.clear();int now = 0;
    for(int i = 1;i <= K;++i){
        if(L[i].id > AE86){continue;}
        if(!now||abs(L[i].angle-tmp[now].angle) > eps){tmp[++now]  = L[i];}
    }
    for(int i = 1;i <= now;++i){
        Q.checkout(tmp[i]);
        Q.push(tmp[i]);
    }
    Q.selfcheck();
    return (Q.r-Q.l >= 2);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    L[++K] = line(point(-eps,inf),point(-inf,inf),-1);
    L[++K] = line(point(-inf,inf),point(-inf,eps),-1);
    L[++K] = line(point(-inf,eps),point(-eps,eps),-1);
    L[++K] = line(point(-eps,eps),point(-eps,inf),-1);
    for(int i = 1;i <= N;++i){
        ld x,y1,y2;cin >> x >> y1 >> y2;
        L[++K] = line(point(0,y1/x),point(1,y1/x-x),i);
        L[++K] = line(point(1,y2/x-x),point(0,y2/x),i);
    }
    sort(L+1,L+1+K);
    int l = 1,r = N;
    while(l <= r){
        int mid = (l+r)>>1;
        if(check(mid)){l = mid+1;}
        else{r = mid-1;}
    }
    cout << r << "\n";
    return 0;
}