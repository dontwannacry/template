struct Bright{
	bool re;
	int num[20100],len;
	Bright(){re = 0;len = 1;memset(num,0,sizeof(num));}
	Bright(long long in){
		re = 0;if(in < 0){re = 1;in = -in;}
		memset(num,0,sizeof(num));len = 1;
		while(in){
			num[len] = in%10;
			if(in/=10){++len;}
		}
	}
	bool operator < (const Bright an) const{
		if(len == an.len){
			for(int i = len;i >= 2;--i){
				if(num[i] == an.num[i]) continue;
				return num[i] < an.num[i];
			}
			return num[1] < an.num[1];
		}
		return len < an.len;
	}
	Bright operator - (const Bright an) const{
		Bright a,b,turn;
		if(*this < an){a = an,b = *this,turn.re = 1;}
		else{a = *this,b = an,turn.re = 0;}
		turn.len = max(a.len,b.len);
		for(int i = 1;i <= turn.len;++i){
			turn.num[i] += a.num[i]-b.num[i];
			turn.num[i+1] -= turn.num[i]<0?1:0;
			turn.num[i] = (turn.num[i]+10)%10;
			if(turn.num[i+1]>0&&i == len){++turn.len;}
		}
		while(turn.num[turn.len] == 0&&turn.len>1){turn.len--;}
		return turn;
	}
	Bright operator + (const Bright an) const{
		Bright turn;turn.re = 0;
		turn.len = max(len,an.len);
		for(int i = 1;i <= turn.len;++i){
			turn.num[i] += an.num[i]+num[i];
			turn.num[i+1] += turn.num[i]/10;
			turn.num[i] = turn.num[i]%10;
			if(turn.num[i+1]>0&&i == len){++turn.len;}
		}
		while(turn.num[turn.len] == 0&&turn.len>1){turn.len--;}
		return turn;
	}
	Bright operator * (const Bright an) const{
		Bright turn;turn.re = 0;
		turn.len = len+an.len-1;
		for(int i = 1;i <= len;++i){
            for(int j = 1;j <= an.len;++j){
                turn.num[i+j-1] += num[i]*an.num[j];
            }
		}
		for(int i = 1;i <= turn.len;++i){
			turn.num[i+1]+=turn.num[i] / 10;
			turn.num[i] %= 10;
			if(i == turn.len&&turn.num[i+1] != 0){
				++turn.len;
			}
		}
		while(turn.num[turn.len] == 0&&turn.len>1){turn.len--;}
		return turn;
	}
	Bright operator / (const long long an) const{
		Bright turn;turn.re = 0;
		long long a = 0;
		turn.len = len;
		for(int i = len;i >= 1;--i){
            a *= 10;
            a += num[i];
            turn.num[i] = a / an;
            a = a%an;
		}
		while(turn.len > 1&&turn.num[turn.len] == 0){--turn.len;}
		return turn;
	}
	Bright operator / (Bright an) const{
		Bright turn;turn.re = 0;
		Bright a;
		turn.len = len;
		for(int i = len;i >= 1;--i){
			for(int j = a.len;j >= 1;--j) a.num[j+1] = a.num[j];
			a.num[1] = num[i];a.len++;
			while(a.len > 1&&a.num[a.len] == 0){--a.len;}
			while(!(a < an)){++turn.num[i];a = a-an;}
		}
		while(turn.len > 1&&turn.num[turn.len] == 0){--turn.len;}
		return turn;
	}
	Bright operator % (Bright an) const{
		Bright a;
		for(int i = len;i >= 1;--i){
			for(int j = a.len;j >= 1;--j) a.num[j+1] = a.num[j];
			a.num[1] = num[i];a.len++;
			while(a.len > 1&&a.num[a.len] == 0){--a.len;}
			while(!(a < an)){a = a-an;}
		}
		while(a.len > 1&&a.num[a.len] == 0){--a.len;}
		return a;
	}
	void out(){
		if(re){cout << '-';}
		for(int i = len;i >= 1;--i){cout << char(num[i]+'0');}
	}
	void in(){
		re = 0;
		string A;cin >> A;
		len = A.size();
		for(int i = 1;i <= len;++i){num[i] = A[len-i] - '0';}
	}
};
