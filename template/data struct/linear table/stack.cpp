struct STACK{
    int num[80010],len = 0;
    bool empty(){return len == 0;}
    int size(){return len;}
    void pop(){len--;}
    void push(int a){num[++len] = a;}
    int top(){return num[len];}
};
