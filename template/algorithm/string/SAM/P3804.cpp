#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct SAM{
	int siz,lst;
	struct node{
		int len,link,ne[26];
		node(){}
		node(int l){
			len = l;link = -1;
			memset(ne,0,sizeof(ne));
		}
	}state[2000010];
	vector<int>son[2000010];
	int cnt[2000010];
	void clear(){
		for(int i = 0;i < siz;++i){son[i].clear();}
		siz = 1;lst = 0;
		state[0] = node(0);
	}
	void insert(char c){
		int cur = siz++;++cnt[cur];
		state[cur] = node(state[lst].len+1);
		int p = lst;
		while(p != -1&&!state[p].ne[c-'a']){
			state[p].ne[c-'a'] = cur;
			p = state[p].link;
		}
		if(p == -1){state[cur].link = 0;}
		else{
			int q = state[p].ne[c-'a'];
			if(state[q].len == state[p].len+1){state[cur].link = q;}
			else{
				int clone = siz++;
				state[clone] = state[q];
				state[clone].len = state[p].len+1;
				while(p != -1&&state[p].ne[c-'a'] == q){
					state[p].ne[c-'a'] = clone;
					p = state[p].link;
				}
				state[q].link = state[cur].link = clone;
			}
		}
		lst = cur;
	}
	void setson(){for(int i = 1;i < siz;++i){son[state[i].link].push_back(i);}}
	ll dfs(int now){
		ll res = 0;
		for(int v:son[now]){
			res = max(dfs(v),res);
			cnt[now] += cnt[v];
		}
		if(cnt[now] != 1){res = max(res,1ll*cnt[now]*state[now].len);}
		return res;
	}
}M;
char S[1000010];
int N;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> (S+1);N = strlen(S+1);M.clear();
	for(int i = 1;i <= N;++i){M.insert(S[i]);}
	M.setson();
	cout << M.dfs(0) << "\n";
	return 0;
}
