struct binaryheap{
    int num[1000010],len = 0;
    void up_x(int now){
        if(now == 1){return;}
        if(num[now] < num[now/2]){
            swap(num[now],num[now>>1]);
            up_x(now/2);
        }
    }
    void down_x(int now){
        if(now*2 > len){return;}
        if(now*2+1 > len){
            if(num[now] > num[now*2]){swap(num[now],num[now*2]);}
            return;
        }
        if(num[now] > num[now*2]||num[now] > num[now*2+1]){
            if(num[now*2]<num[now*2+1]){
                swap(num[now<<1],num[now]);
                down_x(now*2);
            }else{
                swap(num[(now<<1)+1],num[now]);
                down_x(now*2+1);
            }
        }
    }
    int top(){return num[1];}
    void push(int n){
        num[++len] = n;
        up_x(len);
    }
    void pop(){
        swap(num[1],num[len]);
        len--;
        down_x(1);
    }
};
