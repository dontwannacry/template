//case1
for(long long i = 1,maxi;i <= N;i = maxi+1){
    maxi = N/(N/i);
    sumN += (maxi-i+1)*(N/i)
}
//case2
for(long long i = 1,maxi;i <= N;i = maxi+1){
    maxi = N/(N/i);
    sumN += (maxi+i)*(maxi-i+1)/2*(N/i);
}
//case3
for(long long i = 1,maxi;i <= N;i = maxi+1){
    maxi = M/(M/i);
    maxi = min(maxi,N);
    sumM2 += (maxi+i)*(maxi-i+1)/2*(M/i);
}
//case4
for(long long i = 1,maxmi,maxni,maxi;i <= N;i = min(maxmi,maxni)+1){
	maxmi = M/(M/i);maxni = N/(N/i);
	maxi = min(maxmi,maxni);
	sumimn += (maxi*(maxi+1)*(2*maxi+1)-(i-1)*i*(2*i-1))/6*(M/i)*(N/i);
}
