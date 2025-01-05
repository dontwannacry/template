#include<bits/stdc++.h>
using namespace std;
int N,M,start,cnt_Antithief;char in,gameresult;
struct Queue{
	char num[2010];int L = 0,R = 0;
	bool empty(){return L == R;}
	int size(){return R-L;}
	void push(int x){num[++R] = x;}
	void pop(){if(size() > 1)++L;}
	int front(){return num[L+1];}
	int back(){return num[R];}
}Q;
struct cardnode{
	cardnode *left = nullptr,*right = nullptr;
	char type;
	cardnode(char x){type = x;}
	void del(){
		if(left != nullptr)left->right = right;
		if(right != nullptr)right->left = left;
		delete this;
	}
	void push_right(cardnode *x){
		x->right = right;
		x->left = this;
		if(right != nullptr)right->left = x;
		right = x;
	}
};
struct member{
	member *ne = nullptr,*la = nullptr;
	cardnode *card = nullptr;
	int identity,looklike,blood;//0未亮1主猪2忠猪3反猪4类反
	bool crossbow,canusekill,alive;
	member(){
		alive = 1;
		blood = 4;
		card = new cardnode(0);
	}
	void clear(){
		crossbow = 0;
		while(card->right != nullptr){card->right->del();}
	}
	void die(){
		clear();
		alive = 0;
		ne->la = la;
		la->ne = ne;
	}
};
member *pigs[15] = {nullptr};
void pushcard(cardnode *now,char type){
	if(now->right == nullptr)now->push_right(new cardnode(type));
	else pushcard(now->right,type);
}
bool ask_card(cardnode *now,char type){
	if(now->type == type){now->del();return 1;}
	if(now->right == nullptr)return 0;
	return ask_card(now->right,type);
}
bool isenemy(member *x,member *y){
	if(x == nullptr||y == nullptr)return 0;
	int idx = x->identity,idy = y->looklike;
	if(idx == 1){return idy == 3||idy == 4;}
	if(idx == 2){return idy == 3;}
	if(idx == 3){return idy == 1||idy == 2;}
	return 0;
}
bool isfriend(member *x,member *y){
	if(x == nullptr||y == nullptr)return 0;
	int idx = x->identity,idy = y->looklike;
	if(idx == 1||idx == 2){return idy == 1||idy == 2;}
	if(idx == 3){return idy == 3;}
	return 0;
}
void getcard(member *now,int times){for(int i = 1;i <= times;++i){char card = Q.front();Q.pop();pushcard(now->card,card);}}
void ending(){
	cout << gameresult<<"P\n";
	for(int i = 1;i <= N;++i){
		if(!pigs[i]->alive)cout << "DEAD\n";
		else{
			cardnode *now = pigs[i]->card;
			while(now->right != nullptr){
				now = now->right;
				cout << now->type<<" ";
			}
			cout << "\n";
		}
	}
	exit(0);
}
void willdie(member *now,member *from){
	while(now->blood<=0){
		if(ask_card(now->card,'P'))now->blood++;
		else break;
	}
	if(now->blood <= 0){
		int idn = now->identity,idf = from->identity;
		now->die();
		if(idn == 1){gameresult = 'F';ending();}
		if(idn == 3){
			--cnt_Antithief;
			if(cnt_Antithief==0){gameresult = 'M';ending();}
			getcard(from,3);
		}
		if(idn == 2&&idf == 1){from->clear();}
	}
}
bool wuxie(member *outer,member *needer){
	if(needer == nullptr)outer->looklike = outer->identity;
	member *now = outer;int cnt = 0;
	while(cnt < 2){
		if(now == outer)++cnt;
		if(cnt >= 2)break;
		if((isenemy(now,outer)&&needer == nullptr)||isfriend(now,needer)){
			if(ask_card(now->card,'J')){
				if(!wuxie(now,nullptr))return 1;
				//return 0;
			}
		}
		now = now->ne;
	}
	return 0;
}
void bekilled(member *now,member *from){
	from->looklike = from->identity;
	if(!ask_card(now->card,'D')){
		now->blood--;
		willdie(now,from);
	}
}
void bedueled(member *now,member *from){
	from->looklike = from->identity;
	if(wuxie(from,now))return;
	member *ask = now,*wait = from;
	while(isenemy(ask,wait)){
		if(ask_card(ask->card,'K'))swap(ask,wait);
		else break;
	}
	ask->blood--;
	willdie(ask,wait);
}
member *try_duel(member *outer){
	if(outer->identity == 3){return pigs[start];}
	member *be = outer->ne;
	while(be != outer){
		if(isenemy(outer,be)){return be;}
		be = be->ne;
	}
	return nullptr;
}
void nanman(member *outer){
	member *be = outer->ne;
	while(be != outer){
		if(wuxie(outer,be)){be = be->ne;continue;}
		if(ask_card(be->card,'K')){be = be->ne;continue;}
		be->blood--;
		willdie(be,outer);
		if(be->identity == 1&&outer->looklike == 0)outer->looklike = 4;
		be = be->ne;
	}
}
void wanjian(member *outer){
	member *be = outer->ne;
	while(be != outer){
		if(wuxie(outer,be)){be = be->ne;continue;}
		if(ask_card(be->card,'D')){be = be->ne;continue;}
		be->blood--;
		willdie(be,outer);
		if(be->identity == 1&&outer->looklike == 0)outer->looklike = 4;
		be = be->ne;
	}
}
bool ask_canuse(member *nowmember,cardnode *now){
	bool res = 0;
	if(now->type == 'Z'){
		now->del();
		nowmember->crossbow = 1;
		res = 1;
	}else if(now->type == 'P'&&nowmember->blood < 4){
		now->del();
		nowmember->blood++;
		res = 1;
	}else if(now->type == 'K'&&isenemy(nowmember,nowmember->ne)&&(nowmember->crossbow||nowmember->canusekill)){
		nowmember->canusekill = 0;
		now->del();
		bekilled(nowmember->ne,nowmember);
		res = 1;
	}else if(now->type == 'F'){
		member *to = try_duel(nowmember);
		if(to != nullptr){
			now->del();
			bedueled(to,nowmember);
			res = 1;
		}
	}else if(now->type == 'N'){
		now->del();
		nanman(nowmember);
		res = 1;
	}else if(now->type == 'W'){
		now->del();
		wanjian(nowmember);
		res = 1;
	}
	if(res)return 1;
	if(now->right == nullptr)return 0;
	return ask_canuse(nowmember,now->right);
}
void gameacting(){
	member *active = pigs[start];
	while(1){
		member *ne = active->ne;
		if(!active->alive){active = ne;continue;}
		getcard(active,2);
		active->canusekill = 1;
		while(ask_canuse(active,active->card))if(!active->alive)break;
		active = ne;
	}
}
void starting(){
	cin >> N >> M;
	for(int i = 1;i <= N;++i) pigs[i] = new member();
	for(int i = 1;i <= N;++i){
		pigs[i]->ne = pigs[i%N+1];
		pigs[i]->la = pigs[(i+N-2)%N+1];
		cin >> in;
		if(in == 'M'){pigs[i]->identity = pigs[i]->looklike = 1;start = i;}
		if(in == 'Z'){pigs[i]->identity = 2;pigs[i]->looklike = 0;}
		if(in == 'F'){pigs[i]->identity = 3;pigs[i]->looklike = 0;++cnt_Antithief;}
		cin >> in;
		for(int t = 1;t <= 4;++t){
			cin >> in;
			pushcard(pigs[i]->card,in);
		}
	}
	for(int i = 1;i <= M;++i){
		cin >> in;
		Q.push(in);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	starting();
	gameacting();
	return 0;
}
