struct Queue{
	int num[10010],L = 0,R = 0;
	void push(int x){num[++R] = x;}
	bool empty(){return L == R;}
	void pop(){++L;}
	int front(){return num[L+1];}
	int back(){return num[R];}
	int size(){return R-L;}
}Q;
