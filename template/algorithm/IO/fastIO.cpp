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
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
