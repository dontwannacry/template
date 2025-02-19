#include<bits/stdc++.h>
using namespace std;
const int blocklen = 2000;
struct node{
	node *ne,*ba;
	vector<char>li;
	node(){ne = ba = nullptr;};
	void split(){
		node *tmp = new node();
		if(ne != nullptr){ne->ba = tmp;}tmp->ne = ne;
		tmp->ba = this;this->ne = tmp;
		int out = li.size()>>1;
		for(int i = out;i < li.size();++i){tmp->li.push_back(li[i]);}
		for(;li.size() > out;){li.pop_back();}
	}
	void del(){
		if(ne != nullptr){ne->ba = ba;}
		if(ba != nullptr){ba->ne = ne;}
		delete this;
	}
}*head;
struct cursor{
	node *now;int it;
	void Prev(){--it;if(it == -1){now = now->ba;it = now->li.size()-1;}}
	void Next(){++it;if(it == now->li.size()+1){now = now->ne;it = 1;}}
	void Move(int k){
		now = head;it = 0;
		while(now->li.size() < k){
			k -= now->li.size();
			now = now->ne;
		}
		it = k;
	}
	void Delete(){
		if(it == now->li.size()){now = now->ne;it = 0;}
		now->li.erase(now->li.begin()+it);
		if(now->li.size() == 0){
			if(now->ba != nullptr){
				now = now->ba;it = now->li.size();
				now->ne->del();
			}else if(now->ne != nullptr){
				if(head == now){head = head->ne;}
				now = now->ne;it = 0;
				now->ba->del();
			}
		}
	}
	void Insert(char ch){
		now->li.insert(now->li.begin()+it,ch);
		if(now->li.size() > blocklen){
			now->split();
			if(it > now->li.size()){
				it -= now->li.size();
				now = now->ne;
			}
		}
	}
	void out(int N){
		cursor item = *this;
		for(int i = 1;i <= N;++i){
			if(item.it == item.now->li.size()){
				item.it = 0;
				item.now = item.now->ne;
			}
			putchar(item.now->li[item.it]);
			item.Next();
		}
		putchar('\n');
	}
}cur;
int N;char in,li[3000010];
int getint(){
	int res = 0;
	while(!isdigit(in)){in = getchar();}
	while(isdigit(in)){res *= 10;res += in-'0';in = getchar();}
	return res;
}
void getorder(char *on){
	while(in == ' '||in == '\n'||in == '\r'){in = getchar();}
	while(in != ' '&&in != '\n'&&in != '\r'){
		*on = in;++on;
		in = getchar();
	}
	*on = 0;
}
void gettext(char *on,int N){
	while(N){
		if(in != '\n'&&in != '\r'){*on = in;++on;--N;}
		in = getchar();
	}
	*on = 0;
}
int main(){
	N = getint();head = new node();
	cur.now = head;cur.it = 0;
	for(int i = 1;i <= N;++i){
		getorder(li);
		if(li[0] == 'M'){
			int k = getint();
			cur.Move(k);
		}else if(li[0] == 'I'){
			int k = getint();
			gettext(li+1,k);
			for(int i = k;i >= 1;--i){cur.Insert(li[i]);}
		}else if(li[0] == 'D'){
			int k = getint();
			for(int i = 1;i <= k;++i){cur.Delete();}
		}else if(li[0] == 'G'){
			int k = getint();
			cur.out(k);
		}
		else if(li[0] == 'P'){cur.Prev();}
		else{cur.Next();}
	}
	return 0;
}
