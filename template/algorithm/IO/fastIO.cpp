namespace fastIO{
	const int SIZE = 1<<14;
	char getchar(){
		static char buf[SIZE], *begin = buf, *end = buf;
		if(begin == end){
			begin = buf;
			end = buf + fread(buf,1,SIZE,stdin);
		}
		return *begin++;
	}
	int getint(){
		int ret = 0,sgn = 0,ch = getchar();
		while(!isdigit(ch)) sgn |= ch == '-',ch = getchar();
		while(isdigit(ch)) ret = ret * 10 + ch - '0',ch = getchar();
		return sgn ? -ret : ret;
	}
}
