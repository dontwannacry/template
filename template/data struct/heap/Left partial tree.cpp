#include<bits/stdc++.h>
using namespace std;
struct node{
	int son[2],dist,val,id,fa;
	node(){dist = 1;}
	bool operator < (const node other)const{
		if(val == other.val) return id < other.id;
		return val < other.val;
	}
}H[100010];
int N,M;
int find(int now){
	if(H[now].fa == now)return now;
	else return H[now].fa = find(H[now].fa);
}
int mix(int x,int y){
	if(!x||!y) return x|y;
	if(H[y] < H[x]){swap(x,y);}
	H[x].son[1] = mix(H[x].son[1],y);
	if(H[H[x].son[0]].dist < H[H[x].son[1]].dist){swap(H[x].son[0],H[x].son[1]);}
	H[x].dist = H[H[x].son[1]].dist+1;
	H[x].fa = H[H[x].son[0]].fa = H[H[x].son[1]].fa = x;
	return x;
}
void pop(int x){
	H[x].id = -1;
	H[H[x].son[0]].fa = H[x].son[0];
	H[H[x].son[1]].fa = H[x].son[1];
	H[x].fa = mix(H[x].son[0],H[x].son[1]);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	for(int i = 1;i <= N;++i){
		cin >> H[i].val;
		H[i].fa = H[i].id = i;
	}
	for(int i = 1;i <= M;++i){
		int op;cin >> op;
		if(op == 1){
			int x,y;cin >> x >> y;
			if(H[x].id == -1||H[y].id == -1){continue;}
			int hx = find(x),hy = find(y);
			if(hx == hy) continue;
			mix(hx,hy);
		}else{
			int x;cin >> x;
			if(H[x].id == -1){cout << "-1\n";continue;}
			int hx = find(x);
			cout << H[hx].val <<"\n";
			pop(hx);
		}
	}
	return 0;
}
