#include<bits/stdc++.h>
using namespace std;
struct Bright{
	bool re = 0;
	int num[10010] = {0},len = 1;
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
	void out(){
		if(re) cout << '-';
		for(int i = len;i >= 1;--i){cout << char(num[i]+'0');}
	}
	void in(){
		re = 0;
		string A;
		cin >> A;
		len = A.size();
		for(int i = 1;i <= len;++i){num[i] = A[len-i] - '0';}
	}
}A,B,ANS,two;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	A.in();B.in();
	two.num[1] = 2;ANS.num[1] = 1;
	while(1){
		bool re = 0;
		if((A.num[1]&1)&&(B.num[1]&1)){
			if(A < B) swap(A,B);
			A = A-B;
			if(A.len == 1&&A.num[1] == 0)break;
		}
		if(!(A.num[1]&1)){A = A/2;re = 1;}
		if(!(B.num[1]&1)){
			B = B/2;
			if(re) ANS = ANS*two;
		}
	}
	ANS = ANS*B;
	ANS.out();
	return 0;
}
