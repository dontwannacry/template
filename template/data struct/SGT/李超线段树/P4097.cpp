#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld eps = 1e-8;
int cmp(ld x,ld y){
    if(x-y > eps){return 1;}
    if(y-x > eps){return -1;}
    return 0;
}
struct line{
    ld k,b;
    line(){k = b = 0;}
    ld gety(ld x){return k*x+b;}
}L[100010];
struct LCSGT{
    int node[200010];
	bool inset(int L,int R,int l,int r){return(L <= l&&r <= R);}
	bool outset(int L,int R,int l,int r){return(r < L||R < l);}
    void insert(int nl,int nr,int in,int now){
        int mid = (nl+nr)>>1;
        int chk = cmp(L[in].gety(mid),L[node[now]].gety(mid));
        if(chk == 1||(chk == 0&&in < node[now])){swap(in,node[now]);}
        int chl = cmp(L[in].gety(nl),L[node[now]].gety(nl)),chr = cmp(L[in].gety(nr),L[node[now]].gety(nr));
        if(chl != -1){insert(nl,mid,in,now*2);}
        if(chr != -1){insert(mid+1,nr,in,now*2+1);}
    }
	void update(int nl,int nr,int l,int r,int in,int now){
		if(inset(l,r,nl,nr)){insert(nl,nr,in,now);}
        else if(!outset(l,r,nl,nr)){
            int mid = (nl+nr)>>1;
			update(nl,mid,l,r,in,now*2);
			update(mid+1,nr,l,r,in,now*2+1);
		}
	}
	int findans(int nl,int nr,int at,int now){
        int res = node[now];
        if(nl == nr){return res;}
        int mid = (nl+nr)>>1,sp;
        if(at <= mid){sp = findans(nl,mid,at,now*2);}
        else{sp = findans(mid+1,nr,at,now*2+1);}
        int chk = cmp(L[res].gety(at),L[sp].gety(at));
        if(chk == 1){return res;}
        else if(chk == -1){return sp;}
        else{return min(sp,res);}
	}
}T;
int N,lastans;
inline void shift1(int &num){num = (num+lastans-1)%39989+1;}
inline void shift2(int &num){num = (num+lastans-1)%1000000000+1;}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 1,cnt = 0;i <= N;++i){
        int op;cin >> op;
        if(op == 0){
            int k;cin >> k;shift1(k);
            lastans = T.findans(1,40000,k,1);
            cout << lastans << "\n";
        }else{
            int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
            shift1(x1);shift1(x2);shift2(y1);shift2(y2);
            if(x1 > x2){swap(x1,x2);swap(y1,y2);}++cnt;
            if(x1 == x2){L[cnt].k = 0;L[cnt].b = max(y1,y2);}
            else{L[cnt].k = 1.0*(y2-y1)/(x2-x1),L[cnt].b = y1-1.0*x1*(y2-y1)/(x2-x1);}
            T.update(1,40000,x1,x2,cnt,1);
        }
    }
	return 0;
}