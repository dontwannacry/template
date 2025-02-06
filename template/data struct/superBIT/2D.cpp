#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
int start[100010],N,M;
struct DBIT{
	int num[2050][2050],lenx,leny;
	void add(int x,int y,int delta){
		for(int i = x;i <= lenx;i+=lowbit(i)){
			for(int j = y;j <= leny;j+=lowbit(j)){
				num[i][j] += delta;
			}
		}
	}
	int getsum(int x,int y){
		int sum = 0;
		for(int i = x;i > 0;i-=lowbit(i)){
			for(int j = y;j > 0;j-=lowbit(j)){
				sum += num[i][j];
			}
		}
		return sum;
	}
}tree,treeij,treei,treej;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	char op;int a,b,c,d,delta;
	cin >> op >> N >> M;
	tree.lenx = treei.lenx = treej.lenx = treeij.lenx = N;
	tree.leny = treei.leny = treej.leny = treeij.leny = M;
	while(cin >> op >> a >> b >> c >> d){
		if(op == 'L'){
			cin >> delta;
			tree.add(a,b,delta);
			tree.add(a,d+1,-delta);
			tree.add(c+1,b,-delta);
			tree.add(c+1,d+1,delta);
			treei.add(a,b,delta*a);
			treei.add(a,d+1,-delta*a);
			treei.add(c+1,b,-delta*(c+1));
			treei.add(c+1,d+1,delta*(c+1));
			treej.add(a,b,delta*b);
			treej.add(a,d+1,-delta*(d+1));
			treej.add(c+1,b,-delta*b);
			treej.add(c+1,d+1,delta*(d+1));
			treeij.add(a,b,delta*(a-1)*(b-1));
			treeij.add(a,d+1,-delta*(a-1)*d);
			treeij.add(c+1,b,-delta*c*(b-1));
			treeij.add(c+1,d+1,delta*c*d);
		}else{
			int A = tree.getsum(c,d)*(c*d+c+d)-treei.getsum(c,d)*d-treej.getsum(c,d)*c+treeij.getsum(c,d);
			int B = tree.getsum(a-1,d)*(a*d+a-1)-treei.getsum(a-1,d)*d-treej.getsum(a-1,d)*(a-1)+treeij.getsum(a-1,d);
			int C = tree.getsum(c,b-1)*(c*b+b-1)-treei.getsum(c,b-1)*(b-1)-treej.getsum(c,b-1)*c+treeij.getsum(c,b-1);
			int D = tree.getsum(a-1,b-1)*(a*b-1)-treei.getsum(a-1,b-1)*(b-1)-treej.getsum(a-1,b-1)*(a-1)+treeij.getsum(a-1,b-1);
			cout << A-B-C+D<<"\n";
		}
	}
	return 0;
}
