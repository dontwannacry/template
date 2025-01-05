struct Hamel{
	long long P[55];bool zeroed;
	Hamel(){memset(P,0,sizeof(P));zeroed = 0;}
	void tidy(){
		for(int i = 1;i <= 50;++i){
			for(int j = 0;j < i;++j){
				if((P[i]>>j)&1) P[i]^=P[j];
			}
		}
	}
	void push(long long val){
		for(int i = 50;i >= 0;--i){
			if((val>>i)&1){
				if(!P[i]){P[i] = val;break;}
				val^=P[i];
			}
		}
		if(!val) zeroed = 1;
		return;
	}
	long long getmax(long long start){
		long long res = start;
		for(int i = 50;i >= 0;--i){
			if((res^P[i]) > res){
				res ^= P[i];
			}
		}
		return res;
	}
	long long getkth_min(long long k){
		long long res = 0;
		if(zeroed) --k;
		tidy();
		for(int i = 0;i <= 50;++i){
			if(P[i]){
				if(k&1){res ^= P[i];}
				k >>= 1;
			}
		}
		if(k) return -1;
		return res;
	}
	void clear(){memset(P,0,sizeof(P));zeroed = 0;}
	Hamel operator + (const Hamel other)const{
		Hamel res = other;
		res.zeroed |= zeroed;
		for(int i = 1;i <= 50;++i){if(P[i]){res.push(P[i]);}}
		return res;
	}
};
