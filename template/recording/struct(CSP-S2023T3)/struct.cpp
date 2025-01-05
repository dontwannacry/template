#include<bits/stdc++.h>
using namespace std;
struct str{
	long long si,follow,mov;
	string type,name;
	vector<str *>member;
	str(){
		si = follow = mov = 0;
		type = name = "";
	}
	str(long long len,string ty){
		si = follow = len;
		type = ty;
	}
}world;
map<string,str>mp;
long long duiqi(long long N,long long F){return N + (F - N%F)%F;}
void setup_str(string ty,int k){
	str tmp;
	long long o = 0;
	tmp.type = ty;
	for(int i = 1;i <= k;++i){
		string ty,na;
		cin >> ty >> na;
		str *S = new str(mp[ty]);
		S->name = na;
		tmp.follow = max(tmp.follow,S->follow);
		S->mov = o = duiqi(o,S->follow);
		o += S->si;
		tmp.member.push_back(S);
	}
	tmp.si = duiqi(o,tmp.follow);
	mp[ty] = tmp;
	cout << tmp.si <<" "<<tmp.follow<<"\n";
}
void setup_val(string ty,string na){
	str *tmp = new str(mp[ty]);
	tmp->name = na;
	tmp->mov = world.si = duiqi(world.si,tmp->follow);
	world.si += tmp->si;
	world.member.push_back(tmp);
	cout << tmp->mov <<"\n";
}
long long find_add(string na){
	na += ".";
	str *now = &world;long long add = 0;
	string N = "";
	for(int i = 0;i < na.size();++i){
		if(na[i] == '.'){
			for(int i = 0;i < now->member.size();++i){
				if(N == now->member[i]->name){
					now = now->member[i];
					add += now->mov;
					N = "";
				}
			}
		}else N += na[i];
	}
	return add;
}
string find_val(long long addr){
	string ret = "";long long A = 0;
	str *now = &world;
	bool re = 1; 
	while(now -> member.size() > 0){
		re = 1; 
		for(int i = 0;i < now->member.size();++i){
			if(A+now->member[i]->mov <= addr && A+now->member[i]->mov+now->member[i]->si > addr){
				re = 0;
				now = now->member[i];
				A += now->mov;
				if(ret != "") ret+=".";
				ret += now->name;
			}
		}
		if(re){break;}
	}
	if(re) ret = "ERR";
	return ret;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	mp["byte"] = str(1,"byte");
	mp["short"] = str(2,"short");
	mp["int"] = str(4,"int");
	mp["long"] = str(8,"long");
	int T;
	cin >> T;
	while(T--){
		int op;
		cin >> op;
		if(op == 1){
			string ty;int k;
			cin >> ty >> k;
			setup_str(ty,k);
		}else if(op == 2){
			string ty,na;
			cin >> ty >> na;
			setup_val(ty,na);
		}else if(op == 3){
			string na;
			cin >> na;
			cout << find_add(na) <<"\n";
		}else{
			long long addr;
			cin >> addr;
			cout << find_val(addr) <<"\n";
		}
	}
	return 0;
}
