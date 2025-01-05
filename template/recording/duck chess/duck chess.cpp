#include<bits/stdc++.h>
using namespace std;
int MAP[10][9] = {
	{5,4,3,2,1,2,3,4,5},
	{0,0,0,0,0,0,0,0,0},
	{6,0,0,0,0,0,0,0,6},
	{7,0,7,0,7,0,7,0,7},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{17,0,17,0,17,0,17,0,17},
	{16,0,0,0,0,0,0,0,16},
	{0,0,0,0,0,0,0,0,0},
	{15,14,13,12,11,12,13,14,15},
};
string piecename[8] = {
	"",
	"captain",
	"guard",
	"elephant",
	"horse",
	"car",
	"duck",
	"soldier",
};
string sidename[3] = {"red","blue","NA"};
bool gameover = 0;
int nowside,captain_x[2] = {0,9},captain_y[2] = {4,4};
int movement_captain_x[4] = {1,-1,0,0};
int movement_captain_y[4] = {0,0,1,-1};
int movement_guard_x[4] = {1,-1,1,-1};
int movement_guard_y[4] = {1,1,-1,-1};
int movement_elephant_x[4] = {2,-2,2,-2};
int movement_elephant_y[4] = {2,2,-2,-2};
int movement_horse_x[8] = {1,1,2,2,-1,-1,-2,-2};
int movement_horse_y[8] = {2,-2,1,-1,2,-2,1,-1};
int movement_car_x[4] = {1,-1,0,0};
int movement_car_y[4] = {0,0,1,-1};
int movement_duck_x[8] = {2,2,3,3,-2,-2,-3,-3};
int movement_duck_y[8] = {3,-3,2,-2,3,-3,2,-2};
int movement_soldier_x[8] = {1,1,1,0,0,-1,-1,-1};
int movement_soldier_y[8] = {1,0,-1,1,-1,1,0,-1};
int dismovement_elephant_x[4] = {1,-1,1,-1};
int dismovement_elephant_y[4] = {1,1,-1,-1};
int dismovement_horse_x[8] = {0,0,1,1,0,0,-1,-1};
int dismovement_horse_y[8] = {1,-1,0,0,1,-1,0,0};
int dismovement_duck_x[2][8] = {
	{0,0,1,1,0,0,-1,-1},
	{1,1,2,2,-1,-1,-2,-2}
};
int dismovement_duck_y[2][8] = {
	{1,-1,0,0,1,-1,0,0},
	{2,-2,1,-1,2,-2,1,-1}
};
int getside(int in){
	if(in == 0)return 2;
	return in>10?1:0;
}
int gettype(int in){return in>10?in-10:in;}
bool inmap(int x,int y){
	if(x < 0||x > 9)return 0;
	if(y < 0||y > 8)return 0;
	return 1;
}
bool canmove_captain(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 4;++i){
		int x = sx+movement_captain_x[i];
		int y = sy+movement_captain_y[i];
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove_guard(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 4;++i){
		int x = sx+movement_guard_x[i];
		int y = sy+movement_guard_y[i];
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove_elephant(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 4;++i){
		int x = sx+movement_elephant_x[i];
		int y = sy+movement_elephant_y[i];
		int rx = sx+dismovement_elephant_x[i];
		int ry = sy+dismovement_elephant_y[i];
		if(!inmap(rx,ry))continue;
		if(MAP[rx][ry])continue;
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove_horse(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 8;++i){
		int x = sx+movement_horse_x[i];
		int y = sy+movement_horse_y[i];
		int rx = sx+dismovement_horse_x[i];
		int ry = sy+dismovement_horse_y[i];
		if(!inmap(rx,ry))continue;
		if(MAP[rx][ry])continue;
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove_car(int sx,int sy,int ex,int ey){
	for(int t = 0;t < 4;++t){
		for(int i = 1;i <= 9;++i){
			int x = sx+movement_car_x[t]*i;
			int y = sy+movement_car_y[t]*i;
			if(!inmap(x,y))break;
			if(i != 1){
				int rx = sx+movement_car_x[t]*(i-1);
				int ry = sy+movement_car_y[t]*(i-1);
				if(MAP[rx][ry]){break;}
			}
			if(x==ex&&y==ey)return 1;
		}
	}
	return 0;
}
bool canmove_duck(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 8;++i){
		int x = sx+movement_duck_x[i];
		int y = sy+movement_duck_y[i];
		int rx0 = sx+dismovement_duck_x[0][i];
		int ry0 = sy+dismovement_duck_y[0][i];
		int rx1 = sx+dismovement_duck_x[1][i];
		int ry1 = sy+dismovement_duck_y[1][i];
		if(!inmap(rx0,ry0))continue;
		if(!inmap(rx1,ry1))continue;
		if(MAP[rx0][ry0])continue;
		if(MAP[rx1][ry1])continue;
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove_soldier(int sx,int sy,int ex,int ey){
	for(int i = 0;i < 8;++i){
		int x = sx+movement_soldier_x[i];
		int y = sy+movement_soldier_y[i];
		if(x==ex&&y==ey)return 1;
	}
	return 0;
}
bool canmove(int type,int sx,int sy,int ex,int ey){
	if(type == 1)return canmove_captain(sx,sy,ex,ey);
	if(type == 2)return canmove_guard(sx,sy,ex,ey);
	if(type == 3)return canmove_elephant(sx,sy,ex,ey);
	if(type == 4)return canmove_horse(sx,sy,ex,ey);
	if(type == 5)return canmove_car(sx,sy,ex,ey);
	if(type == 6)return canmove_duck(sx,sy,ex,ey);
	if(type == 7)return canmove_soldier(sx,sy,ex,ey);
	return 0;
}
bool if_checkmate(){
	for(int i = 0;i < 10;++i){
		for(int j = 0;j < 9;++j){
			int side = getside(MAP[i][j]);
			int price = gettype(MAP[i][j]);
			if(side == 2)continue;
			if(canmove(price,i,j,captain_x[side^1],captain_y[side^1]))return 1;
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;cin >> T;
	while(T--){
		if(gameover){cout << "Invalid command\n";continue;}
		int sx,sy,ex,ey;cin >> sx >> sy >> ex >> ey;
		int side = getside(MAP[sx][sy]),eside = getside(MAP[ex][ey]);
		if(side != nowside){cout << "Invalid command\n";continue;}
		if(side == eside){cout << "Invalid command\n";continue;}
		int piece = gettype(MAP[sx][sy]),eprice = gettype(MAP[ex][ey]);
		if(!canmove(piece,sx,sy,ex,ey)){cout << "Invalid command\n";continue;}
		cout << sidename[side] <<" "<<piecename[piece]<<";";
		cout<<sidename[eside]<<(eprice?" ":"")<<piecename[eprice]<<";";
		if(piece == 1){captain_x[nowside] = ex;captain_y[nowside] = ey;}
		if(eprice == 1){gameover = 1;}
		if(gameover){cout<<"no;yes\n";continue;}
		MAP[ex][ey] = MAP[sx][sy];MAP[sx][sy] = 0;
		cout<<(if_checkmate()?"yes":"no")<<";no\n";
		nowside^=1;
	}
	return 0;
}
