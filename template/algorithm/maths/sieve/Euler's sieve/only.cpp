int N,len,prime[10000100];
bool vis[100000010];
void init(){
    vis[1] = 1;
    for(int i = 2;i <= N;++i){
        if(!vis[i]){prime[++len] = i;}
        for(int j = 1;j <= len&&i*prime[j]<=N;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j] == 0)break;
        }
    }
}
