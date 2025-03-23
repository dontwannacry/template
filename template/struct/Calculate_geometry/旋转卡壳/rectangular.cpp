#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
namespace C_2D{
	const ld eps = 1e-8;
	struct point{
		ld x,y;
		point(){}
		point(ld x,ld y){this->x = x;this->y = y;}
        point(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		friend point operator * (const ld num,const point now){return point(num*now.x,num*now.y);}
		friend ld operator * (const point now,const point other){return now.x*other.x+now.y*other.y;}
		ld operator ^ (const point other)const{return x*other.y-y*other.x;}
		point operator + (const point other)const{return {x+other.x,y+other.y};}
		point operator - (const point other)const{return {x-other.x,y-other.y};}
		bool operator < (const point other)const{
			if(x == other.x) return y < other.y;
			return x < other.x;
		}
		ld length(){return sqrt(x*x+y*y);}
	};
	ld farway(point A,point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
}
using namespace C_2D;
struct stack_max{
    point num[100010];int len;
    void clear(){len = 0;}
    void push(point now){
        while(len > 1&&((num[len-1]-num[len])^(num[len-1]-now)) <= 0){num[len--] = {0,0};}
        num[++len] = now;
    }
}Q;
/*
0101
0111
1001
*/
point P[100010],li[200010],ansp[4],tmpp[4];
int N,len;
ld ans = 1e18,tmp;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i){cin >> P[i].x >> P[i].y;}
	sort(P+1,P+1+N);
	Q.clear();
	for(int i = 1;i <= N;++i){Q.push(P[i]);}
	for(int i = 1;i <= Q.len;++i){li[++len] = Q.num[i];}
	Q.clear();
	for(int i = N;i >= 1;--i){Q.push(P[i]);}
	for(int i = 2;i <= Q.len;++i){li[++len] = Q.num[i];}
	// for(int i = 1;i <= len;++i){cout << li[i].x << " " << li[i].y << "\n";}
	int l = 3,r = 2,t = 3;
    for(int i = 1;i < len;++i){
		while(abs((li[i]-li[i+1])^(li[i]-li[t])) < abs((li[i]-li[i+1])^(li[i]-li[t%len+1]))+eps){t = t%len+1;}
		while((li[i]-li[i+1])*(li[i]-li[r]) < (li[i]-li[i+1])*(li[i]-li[r%len+1])+eps){r = r%len+1;}
		if((i <= l&&l <= t)||(l <= t&&t <= i)){l = t;}
		while((li[i]-li[i+1])*(li[i]-li[l]) > (li[i]-li[i+1])*(li[i]-li[l%len+1])-eps){l = l%len+1;}
//		cout << i << ":" << l << " " << r << " " << t << ";" << (li[i]-li[i+1])*(li[i]-li[l]) << " " << (li[i]-li[i+1])*(li[i]-li[l%len+1]) << "\n";
		tmpp[0] = tmpp[1] = tmpp[3] = li[i+1]-li[i];
		swap(tmpp[3].x,tmpp[3].y);tmpp[3].x = -tmpp[3].x;
		tmpp[3] = abs((tmpp[0])^(li[t]-li[i]))/tmpp[0].length()/tmpp[3].length()*tmpp[3];
		// cout << i << " " << abs((tmpp[0])^(li[t]-li[i])) << " " << abs((tmpp[0])^(li[t]-li[i]))/tmpp[0].length()/tmpp[3].length() << ":" << tmpp[3].x << " " << tmpp[3].y << "\n";
		tmpp[0] = ((tmpp[0])*(li[l]-li[i]))/tmpp[0].length()/tmpp[0].length()*tmpp[0];
		tmpp[1] = ((tmpp[1])*(li[r]-li[i]))/tmpp[1].length()/tmpp[1].length()*tmpp[1];
		tmpp[2] = li[i]+tmpp[1]+tmpp[3];tmpp[3] = li[i]+tmpp[0]+tmpp[3];
		tmpp[0] = li[i]+tmpp[0];tmpp[1] = li[i]+tmpp[1];
		tmp = (tmpp[1]-tmpp[0])^(tmpp[3]-tmpp[0]);
        if(tmp+eps < ans){
			// cout << i << ":" << l << " " << r << " " << t << ";\n";
			ans = tmp;
			for(int i = 0;i < 4;++i){ansp[i] = tmpp[i];}
		}
    }
	printf("%.6Lf\n",ans+eps);
	for(int i = 0;i < 4;++i){printf("%.6Lf %.6Lf\n",ansp[i].x+eps,ansp[i].y+eps);}
	return 0;
}
/*
	for(int i = 1,j = 3;i < len;++i){
		while(abs((li[i]-li[i+1])^(li[i]-li[j])) <= abs((li[i]-li[i+1])^(li[i]-li[j%len+1]))){j = j%len+1;}
		ans = max(ans,farway(li[i],li[j]));
		ans = max(ans,farway(li[i+1],li[j]));
//		cout << i << " "<<j <<":"<<farway(li[i],li[j]) <<" "<<farway(li[i+1],li[j])<<"\n";
	}
//	cout << len << "!\n";
//	for(int i = 1;i <= len;++i){cout << li[i].x << " "<<li[i].y << ";\n";}
	cout << ans;
*/