struct queue_max{
    int num[40010],t[40010],st,ed;
    void clear(){st = 0;ed = -1;}
    void push(int w,int now,int val){
        while(num[ed]+(now-t[ed])*val < w&&ed >= st){--ed;}
        num[++ed] = w;
        t[ed] = now;
    }
    int topval(int now,int val){return num[st]+(now-t[st])*val;}
    void pop(){st++;}
}A;
