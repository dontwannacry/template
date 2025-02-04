#include<bits/stdc++.h>
using namespace std;
char T[20000010],S[20000010];
int Z[20000010],P[20000010];
void getZ(char *S,int *Z){
	int l = 1,r = 1,i;
	for(i = 2;*(S+i);++i){
		if(i > r){
			l = i;
			int j = 0;
			while(*(S+j+1) == *(S+i+j)) ++j;
			r = l+j-1;
			*(Z+i) = j;
		}else{
			if(*(Z+i-l+1) < r-i+1) *(Z+i) = *(Z+i-l+1);
			else{
				int j = r-i+1;
				while(*(S+j+1) == *(S+i+j)) ++j;
				*(Z+i) = j;
				if(i+*(Z+i)-1 > r) l = i,r = i+*(Z+i)-1;
			}
		}
	}
	*(Z+1) = i-1;
}
void exkmp(char *S,int *Z,char *T,int *P){
	int l = 0,r = 0,i;
	for(i = 1;*(T+i);++i){
		if(i > r){
			l = i;
			int j = 0;
			while(*(S+j+1) == *(T+i+j)&&*(S+j+1)&&*(T+i+j)) ++j;
			r = l+j-1;
			*(P+i) = j;
		}else{
			if(*(Z+i-l+1) < r-i+1) *(P+i) = *(Z+i-l+1);
			else{
				int j = r-i+1;
				while(*(S+j+1) == *(T+i+j)&&*(S+j+1)&&*(T+i+j)) ++j;
				*(P+i) = j;
				if(i+*(P+i)-1 > r) l = i,r = i+*(P+i)-1;
			}
		}
	}
}
