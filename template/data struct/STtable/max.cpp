int start[200010];
struct STtable{//max
	int st[200010][18],lg[200010];
	void setup(int N){
		for(int i = 1;i <= N;++i) st[i][0] = start[i];
		for(int i = 1;i <= 17;++i){
			for(int j = 1;j+(1<<i)-1 <= N;++j){
				st[j][i] = max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
			}
		}
		for(int i = 2;i <= N;++i) lg[i] = lg[i>>1]+1;
	}
	int findmax(int l,int r){
		int g = lg[r-l+1];
		return max(st[l][g],st[r-(1<<g)+1][g]);
	}
}st;
