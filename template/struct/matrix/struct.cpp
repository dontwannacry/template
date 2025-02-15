struct matrix{
	int m,n;
	long long num[110][110];
	matrix operator * (const matrix x)const{
		matrix re;
		re.m = m;re.n = x.n;
		memset(re.num,0,sizeof(re.num));
		for(int i = 1;i <= m;++i){
			for(int k = 1;k <= n;++k){
				for(int j = 1;j <= x.n;++j){
					re.num[i][j] += num[i][k]*x.num[k][j];
					//
					re.num[i][j] %= MOD;
				}
			}
		}
		return re;
	}
	matrix operator + (const matrix x)const{
		matrix re = x;
		re.m = m;re.n = x.n;
		for(int i = 1;i <= m;++i){
			for(int j = 1;j <= n;++j){
					re.num[i][j] += num[i][j];
					//
					re.num[i][j] %= MOD;
			}
		}
		return re;
	}
	void start(int N){
		memset(num,0,sizeof(num));
		n = m = N;
		for(int i = 1;i <= N;++i){
			num[i][i] = 1;
		}
	}
	void input(int M,int N){
		m = M;n = N;
		for(int i = 1;i <= m;++i){
			for(int j = 1;j <= n;++j){
				cin >> num[i][j];
			}
		}
	}
	void output(){
		for(int i = 1;i <= m;++i){
			for(int j = 1;j <= n;++j){
				cout << num[i][j] <<" ";
			}
			cout << "\n";
		}
	}
}st;
