int T,len,prime[6000010],ans[100000010];
bool vis[100000010];
void init(){
	vis[1] = 1;
    for(int i = 2;i <= 100000000;++i){
        if(!vis[i]){
        	ans[i] = i-1;
            prime[++len] = i;
        }
        for(int j = 1;j <= len&&i*prime[j]<=100000000;j++){
        	vis[i*prime[j]] = 1;
            if(i%prime[j] == 0){ans[i*prime[j]] = ans[i]*prime[j];break;}
            else  ans[i*prime[j]] = ans[i]*(prime[j]-1);
        }
    }
}
