#include<bits/stdc++.h>
using namespace std;
int len,r[22000010],ANS;
char in[11000010],str[22000010];
void manacher(){
	int maxnow = 0,midnow = 0;
	for(int i = 2;i < len;++i){
		if(i <= maxnow){r[i] = min(r[midnow*2-i],maxnow-i);}
		while(str[i-r[i]-1] == str[i+r[i]+1]) ++r[i];
		if(i+r[i] > maxnow){
			maxnow = i+r[i];
			midnow = i;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> (in+1);
	len = strlen(in+1);
	str[0] = '@';
	for(int i = 1;i <= len;++i){
		str[i*2] = in[i];
		str[i*2-1] = '#';
	}
	len *= 2;
    str[++len] = '#';
	str[++len] = '!';
	manacher();
	for(int i = 1;i < len;++i){ANS = max(r[i],ANS);}
	cout << ANS;
	return 0;
}
