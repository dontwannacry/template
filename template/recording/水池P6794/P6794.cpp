#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,Q,A[200010];
struct SGTB{
    int root[200010],len;
    struct node{int num,son[2];}T[200010*22];
    void setup(int nl,int nr,int now,int *H){
        if(nl == nr){T[now].num = H[nl];return;}
        int mid = (nl+nr)>>1;
        T[now].son[0] = ++len;setup(nl,mid,T[now].son[0],H);
        T[now].son[1] = ++len;setup(mid+1,nr,T[now].son[1],H);
        T[now].num = max(T[T[now].son[0]].num,T[T[now].son[1]].num);
    }
    void update(int nl,int nr,int at,int val,int from,int now){
        T[now].num = max(val,T[now].num);
        if(nl == nr){return;}
        int mid = (nl+nr)>>1;
        if(at <= mid){
            T[now].son[1] = T[from].son[1];
            T[now].son[0] = ++len;T[len] = T[T[from].son[0]];
            update(nl,mid,at,val,T[from].son[0],T[now].son[0]);
        }else{
            T[now].son[0] = T[from].son[0];
            T[now].son[1] = ++len;T[len] = T[T[from].son[1]];
            update(mid+1,nr,at,val,T[from].son[1],T[now].son[1]);
        }
    }
    int searchl(int nl,int nr,int x,int h,int now){
        if(nl == nr){
            if(T[now].num < h){return -1;}
            return nl;
        }
        int mid = (nl+nr)>>1;
        if(nr < x){
            if(T[T[now].son[1]].num >= h){return searchl(mid+1,nr,x,h,T[now].son[1]);}
            else{return searchl(nl,mid,x,h,T[now].son[0]);}
        }else{
            int res = -1;
            if(mid < x-1){res = searchl(mid+1,nr,x,h,T[now].son[1]);}
            if(res == -1&&T[T[now].son[0]].num >= h){res = searchl(nl,mid,x,h,T[now].son[0]);}
            return res;
        }
    }
    int searchr(int nl,int nr,int x,int h,int now){
        if(nl == nr){
            if(T[now].num < h){return -1;}
            return nl;
        }
        int mid = (nl+nr)>>1;
        if(x <= nl){
            if(T[T[now].son[0]].num >= h){return searchr(nl,mid,x,h,T[now].son[0]);}
            else{return searchr(mid+1,nr,x,h,T[now].son[1]);}
        }else{
            int res = -1;
            if(x <= mid){res = searchr(nl,mid,x,h,T[now].son[0]);}
            if(res == -1&&T[T[now].son[1]].num >= h){res = searchr(mid+1,nr,x,h,T[now].son[1]);}
            return res;
        }
    }
    int getmaxn(int nl,int nr,int l,int r,int now){
        if(l <= nl&&nr <= r){return T[now].num;}
        if(r < nl||nr < l){return 0;}
        int mid = (nl+nr)>>1;
        int resl = getmaxn(nl,mid,l,r,T[now].son[0]);
        int resr = getmaxn(mid+1,nr,l,r,T[now].son[1]);
        return max(resl,resr);
    }
}BT;
struct SGTW{
    int root[200010],len;
    struct node{
        int htag,dtag,son[2];
        node(){son[0] = son[1] = 0;htag = dtag = -1;}
    }T[200010*80];
    void setup(int nl,int nr,int now){
        if(nl == nr){T[now].htag = 0;return;}
        int mid = (nl+nr)>>1;
        T[now].son[0] = ++len;setup(nl,mid,T[now].son[0]);
        T[now].son[1] = ++len;setup(mid+1,nr,T[now].son[1]);
    }
    void maketagheight(int now,int val){T[now].htag = val;T[now].dtag = -1;}
    void maketagdelta(int now,int val,int v){T[now].htag = v;T[now].dtag = val;}
    void pushdown(int now){
        T[++len] = T[T[now].son[0]];T[now].son[0] = len;
        T[++len] = T[T[now].son[1]];T[now].son[1] = len;
        if(T[now].dtag != -1){
            maketagdelta(T[now].son[0],T[now].dtag,T[now].htag);
            maketagdelta(T[now].son[1],T[now].dtag,T[now].htag);
            T[now].htag = T[now].dtag = -1;
        }if(T[now].htag != -1){
            maketagheight(T[now].son[0],T[now].htag);
            maketagheight(T[now].son[1],T[now].htag);
            T[now].htag = -1;
        }
    }
    void setheight(int nl,int nr,int l,int r,int h,int from,int now){
        if(l <= nl&&nr <= r){maketagheight(now,h);return;}
        pushdown(from);
        int mid = (nl+nr)>>1;
        if(r < nl||mid < l){T[now].son[0] = T[from].son[0];}
        else{
            T[now].son[0] = ++len;
            setheight(nl,mid,l,r,h,T[from].son[0],T[now].son[0]);
        }
        if(r < mid+1||nr < l){T[now].son[1] = T[from].son[1];}
        else{
            T[now].son[1] = ++len;
            setheight(mid+1,nr,l,r,h,T[from].son[1],T[now].son[1]);
        }
    }
    void setdelta(int nl,int nr,int l,int r,int x,int v,int from,int now){
        if(l <= nl&&nr <= r){maketagdelta(now,x,v);return;}
        pushdown(from);
        int mid = (nl+nr)>>1;
        if(r < nl||mid < l){T[now].son[0] = T[from].son[0];}
        else{
            T[now].son[0] = ++len;
            setdelta(nl,mid,l,r,x,v,T[from].son[0],T[now].son[0]);
        }
        if(r < mid+1||nr < l){T[now].son[1] = T[from].son[1];}
        else{
            T[now].son[1] = ++len;
            setdelta(mid+1,nr,l,r,x,v,T[from].son[1],T[now].son[1]);
        }
    }
    int getheight(int nl,int nr,int at,int now){
        if(nl == nr){
            if(T[now].dtag != -1){
                if(T[now].dtag == nl){T[now].htag = 0;}
                else{
                    if(T[now].dtag < nl){T[now].htag = BT.getmaxn(0,N,T[now].dtag,nl-1,BT.root[T[now].htag]);}
                    else{T[now].htag = BT.getmaxn(0,N,nl,T[now].dtag-1,BT.root[T[now].htag]);}
                }
                T[now].dtag = -1;
            }
            return T[now].htag;
        }
        int mid = (nl+nr)>>1;
        pushdown(now);
        if(at <= mid){return getheight(nl,mid,at,T[now].son[0]);}
        else{return getheight(mid+1,nr,at,T[now].son[1]);}
    }
}WT;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> Q;A[0] = A[N] = 0x3f3f3f3f;
    for(int i = 1;i < N;++i){cin >> A[i];}
    BT.root[0] = ++BT.len;BT.setup(0,N,BT.root[0],A);
    WT.root[0] = ++WT.len;WT.setup(1,N,WT.root[0]);
    for(int i = 1;i <= Q;++i){
        int op;cin >> op;
        if(op == 0){
            int t,x,h;cin >> t >> x >> h;
            int ans = WT.getheight(1,N,x,WT.root[t]);
            BT.root[i] = BT.root[t];
            if(ans >= h){WT.root[i] = WT.root[t];}
            else{
                int nl = BT.searchl(0,N,x,h,BT.root[i]),nr = BT.searchr(0,N,x,h,BT.root[i]);
                WT.root[i] = ++WT.len;
                WT.setheight(1,N,nl+1,nr,h,WT.root[t],WT.root[i]);
            }
        }else if(op == 1){
            int t,x;cin >> t >> x;
            int h = WT.getheight(1,N,x,WT.root[t]);BT.root[i] = BT.root[t];
            int nl = BT.searchl(0,N,x,h,BT.root[i]),nr = BT.searchr(0,N,x,h,BT.root[i]);
            WT.root[i] = ++WT.len;WT.setdelta(1,N,nl+1,nr,x,i,WT.root[t],WT.root[i]);
        }else if(op == 2){
            int t,x,h;cin >> t >> x >> h;
            WT.root[i] = WT.root[t];
            BT.root[i] = ++BT.len;BT.T[BT.len] = BT.T[BT.root[t]];
            BT.update(0,N,x,h,BT.root[t],BT.root[i]);
        }else{
            int t,x;cin >> t >> x;
            int ans = WT.getheight(1,N,x,WT.root[t]);
            cout << ans << "\n";
            WT.root[i] = WT.root[t];
            BT.root[i] = BT.root[t];
        }
    }
	return 0;
}