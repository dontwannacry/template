int trieS[1000010][26],trielen;
char S[1000010];
vector<int>endonit[1000010];
void pushin(int T,char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		if(trieS[now][tmp] == 0){trieS[now][tmp] = ++trielen;}
		now = trieS[now][tmp];
	}
	endonit[now].push_back(T);
}
int findS(char *str){
	int now = 0;
	for(int i = 0;*(str+i);++i){
		int tmp = *(str+i)-'a';
		if(trieS[now][tmp] == 0){return -1;}
		now = trieS[now][tmp];
	}
	return now;
}
