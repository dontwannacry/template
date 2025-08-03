#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct point{
	ll x,y;
	point(){}
	point(ll x,ll y){this->x = x;this->y = y;}
	point(point A,point B){x = B.x-A.x;y = B.y-A.y;}
	ll operator ^ (const point other)const{return x*other.y-y*other.x;}
	point operator + (const point other)const{return {x+other.x,y+other.y};}
	point operator - (const point other)const{return {x-other.x,y-other.y};}
	ll len(){return x*x+y*y;}
};
bool cmp1(point A,point B){
	if(A.y != B.y){return A.y < B.y;}
	return A.x < B.x;
}
bool cmp2(point A,point B){
	if((A^B) != 0){return (A^B) > 0;}
	return A.len() < B.len();
}
struct stack_max{
    point num[200010];int len;
    void clear(){len = 0;}
    void push(point now){
        while(len > 1&&(point(num[len-1],num[len])^point(num[len-1],now)) <= 0){--len;}
        num[++len] = now;
    }
}S;
point P1[100010],P2[100010],P[200010],S1[100010],S2[100010],P0;
int N,M,Q,tot;
void Convex(point *A,int &N){
	sort(A+1,A+1+N,cmp1);
	P0 = A[1];for(int i = 1;i <= N;++i){A[i] = A[i]-P0;}
	sort(A+2,A+1+N,cmp2);
	S.clear();for(int i = 1;i <= N;++i){S.push(A[i]);}
	for(int i = 1;i <= S.len;++i){A[i] = S.num[i]+P0;}
	N = S.len;A[N+1] = A[1];
}
void minkowski(){
	for(int i = 1;i <= N;++i){S1[i] = P1[i+1]-P1[i];}
	for(int i = 1;i <= M;++i){S2[i] = P2[i+1]-P2[i];}
	int l = 1,r = 1;
	P[tot = 1] = P1[l]+P2[r];
	while(l <= N&&r <= M){
		if((S1[l]^S2[r]) >= 0){P[tot+1] = P[tot]+S1[l++];}
		else{P[tot+1] = P[tot]+S2[r++];}
		++tot;
	}
	while(l <= N){P[tot+1] = P[tot]+S1[l++];++tot;}
	while(r <= M){P[tot+1] = P[tot]+S2[r++];++tot;}
}
int check(point A){
	if((A^P[2]) > 0||(P[tot]^A) > 0){return 0;}
	if((A^P[2]) == 0&&A.len() > P[2].len()){return 0;}
	if((P[tot]^A) == 0&&A.len() > P[tot].len()){return 0;}
	int pos = lower_bound(P+1,P+1+tot,A,cmp2)-P-1;
	return ((A-P[pos])^(P[pos%tot+1]-P[pos])) <= 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> Q;
	for(int i = 1;i <= N;++i){cin >> P1[i].x >> P1[i].y;}
	Convex(P1,N);
	for(int i = 1;i <= M;++i){
		cin >> P2[i].x >> P2[i].y;
		P2[i].x = -P2[i].x;
		P2[i].y = -P2[i].y;
	}
	Convex(P2,M);
	minkowski();
	Convex(P,tot);
	P0 = P[1];
//	cout << P0.x << " " << P0.y << "!\n";
	for(int i = 1;i <= tot;++i){
//		cout << P[i].x << " " << P[i].y << "?\n";
		P[i] = P[i]-P0;
	}
	for(int i = 1;i <= Q;++i){
		cin >> P[0].x >> P[0].y;
		cout << check(P[0]-P0) << "\n";
	}
	return 0;
}
