#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
namespace C_2D{
	ld eps = 1e-8;
	struct point{
		ld x,y;
		point(){}
		point(ld x,ld y){this->x = x;this->y = y;}
        point(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		bool operator == (const point other)const{return abs(other.x-x)<eps&&abs(other.y-y)<eps;}
        friend ld operator * (const point A,const point B){return A.x*B.x+A.y*B.y;}
        friend point operator * (const ld A,const point B){return point(A*B.x,A*B.y);}
        friend point operator * (const point A,const ld B){return point(A.x*B,A.y*B);}
		ld operator ^ (const point other)const{return x*other.y-y*other.x;}
		point operator + (const point other)const{return {x+other.x,y+other.y};}
		point operator - (const point other)const{return {x-other.x,y-other.y};}
	};
	ld farway(point A,point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
	struct line{
		point O,D;
		line(){}
		line(point A,point B){O = A;D = point(A,B);}
        const friend bool operator < (const line A,const line B){
            ld tk1 = atan2(A.D.y,A.D.x),tk2 = atan2(B.D.y,B.D.x);
            if(abs(tk1-tk2) > eps){return tk1 < tk2;}
            return (A.D^(B.O-A.O)) < -eps;
        }
	};
    point crosspoint(line L1,line L2){
        ld S1 = (L2.O+L2.D-L1.O)^L1.D,S2 = (L2.O-L1.O)^L1.D,base = 1.0/(S1-S2);
        point res = (S1*L2.O-S2*(L2.O+L2.D))*base;
        return res;
    }
	struct polygon{
		vector<point>Plist;
		polygon(){}
		ld S(){
			ld sum = 0;int Pcnt = Plist.size();
			for(int i = 1;i < Pcnt-1;++i){sum += point(Plist[0],Plist[i])^point(Plist[0],Plist[i+1]);}
			sum *= 0.5;
			return sum;
		}
	};
}
using namespace C_2D;
bool check(line l1,line l2,line l3){return (l1.D^(crosspoint(l2,l3)-l1.O)) < eps;}
int N,M,K;
point inp[100010];
line L[100010];
struct queue_max{
    line num[100010];int l,r;
    // void debug(){        
    //     for(int i = l,j;i <= r;++i){
    //         cout << L[num[i]].O.x << " " << L[num[i]].O.y << ";" << L[num[i]].D.x << " " << L[num[i]].D.y << "\n";
    //     }
    //     cout << "\n";
    // }
    void clear(){l = 1,r = 0;}
    void push(line x){num[++r] = x;}
    void checkout(line x){
        while(l < r&&check(x,num[r],num[r-1])){--r;}
        while(l < r&&check(x,num[l],num[l+1])){++l;}
    }
    void selfcheck(){
        while(l < r&&check(num[l],num[r],num[r-1])){--r;}
        while(l < r&&check(num[r],num[l],num[l+1])){++l;}
    }
    polygon getpolygon(){
        polygon res;
        // debug();
        for(int i = l,j;i <= r;++i){
            j = i+1;if(j > r){j = l;}
            res.Plist.push_back(crosspoint(num[i],num[j]));
            // cout << crosspoint(L[num[i]],L[num[j]]).x << " " << crosspoint(L[num[i]],L[num[j]]).y << "\n";
        }
        return res;
    }
}Q;
// ld crossx(line l1,line l2){return (l2.b-l1.b)/(l1.k-l2.k);}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;Q.clear();
    for(int i = 1;i <= N;++i){
        cin >> M;  
        for(int j = 1;j <= M;++j){cin >> inp[j].x >> inp[j].y;}
        for(int j = 1;j <= M;++j){L[++K] = line(inp[j],inp[j%M+1]);}
    }
    sort(L+1,L+1+K);
    for(int i = 2,j = 1;i <= K;++i){
        // cout << L[i].O.x << " " << L[i].O.y << ";" << L[i].D.x << " " << L[i].D.y << "\n";
        if(abs(atan2(L[i].D.y,L[i].D.x)-atan2(L[i-1].D.y,L[i-1].D.x)) > eps){L[++j]  = L[i];}
        if(i == K){K = j;}
    }
    // cout << "\n";
    for(int i = 1;i <= K;++i){
        Q.checkout(L[i]);
        Q.push(L[i]);
        // Q.debug();
    }
    Q.selfcheck();
    printf("%.3Lf\n",Q.getpolygon().S());
    // cout << Q.getpolygon().S() << "\n";
    return 0;
}