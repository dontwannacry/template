namespace Calculate_geometry_2D{
	long double esp = 1e-6;
	bool inset(long double x,long double l,long double r){return (x >= min(l,r))&&(x <= max(l,r));}
	struct point{
		long double x,y;
		point(){}
		point(long double x,long double y){this->x = x;this->y = y;}
		bool operator == (const point other)const{return abs(other.x-x)<esp&&abs(other.y-y)<esp;}
	};
	long double farway(point A,point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
	struct circle{
		point O;long double r;
		circle(){}
		circle(point O,long double r){this->O = O;this->r = r;}
	};
	struct vector{
		long double x,y;
		vector(){}
		vector(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		vector(long double x,long double y){this->x = x;this->y = y;}
		long double operator * (const vector other)const{return x*other.x+y*other.y;}
		long double operator ^ (const vector other)const{return x*other.y-y*other.x;}
		vector operator + (const vector other)const{return {x+other.x,y+other.y};}
		vector operator - (const vector other)const{return {x-other.x,y-other.y};}
	};
	struct segment{
		point A,B;
		segment(){}
		segment(point A,point B){this->A = A;this->B = B;}
		long double length(){return farway(A,B);}
	};
	struct line_vector{
		point O;vector D;
		line_vector(){}
		line_vector(point A,point B){O = A;D = vector(A,B);}
		line_vector(segment AB){O = AB.A;D = vector(AB.A,AB.B);}
	};
	struct triangle{
		point A,B,C;
		triangle(){}
		triangle(point A,point B,point C){this->A = A;this->B = B;this->C = C;}
		long double Clength(){return farway(A,B)+farway(A,C)+farway(C,B);}
	};
	struct polygon{
		std::vector<point>Plist;int Pcnt;
		polygon(){}
		polygon(int N,point *li){
			Pcnt = N;
			for(int i = 1;i <= N;++i) Plist.push_back(*(li+i));
		}
		long double C(){
			long double sum = 0;
			for(int i = 0;i < Pcnt;++i){sum += farway(Plist[i],Plist[(i+1)%Pcnt]);}
			return sum;
		}
		long double S(){
			long double sum = 0;
			for(int i = 1;i < Pcnt-1;++i){sum += vector(Plist[0],Plist[i])^vector(Plist[0],Plist[i+1]);}
			sum *= 0.5;
			return sum;
		}
	};
	bool point_in_circle(point A,circle O){return farway(A,O.O) < O.r-esp;}
	bool point_on_circle(point A,circle O){return abs(farway(A,O.O)-O.r) < esp;}
	bool vector_Parallel(vector A,vector B){return abs(A.x*B.y-A.y*B.x) < esp;}
	bool vector_Vertical(vector A,vector B){return abs(A.x*B.y+A.y*B.x) < esp;}
	bool line_vector_Parallel(line_vector A,line_vector B){return vector_Parallel(A.D,B.D);}
	bool line_vector_Vertical(line_vector A,line_vector B){return vector_Vertical(A.D,B.D);}
	bool point_on_line_vector(point P,line_vector L){return vector_Parallel(vector(P,L.O),L.D);}
	bool point_on_segment(point P,segment AB){return point_on_line_vector(P,line_vector(AB))&&inset(P.x,AB.A.x,AB.B.x)&&inset(P.y,AB.A.y,AB.B.y);}
	bool point_on_triangle(point P,triangle ABC){return point_on_segment(P,segment(ABC.A,ABC.B))||point_on_segment(P,segment(ABC.A,ABC.C))||point_on_segment(P,segment(ABC.C,ABC.B));}
	bool segment_intersect_line(segment AB,line_vector L){return (vector(L.O,AB.A)^L.D)*(vector(L.O,AB.B)^L.D) < esp;}
	bool point_in_triangle(point P,triangle ABC){
		long double c1 = vector(ABC.A,ABC.B)^vector(ABC.A,P),c2 = vector(ABC.B,ABC.C)^vector(ABC.B,P),c3 = vector(ABC.C,ABC.A)^vector(ABC.C,P);
		return (c1*c2>esp&&c1*c3>esp);
	}
	bool point_in_polygon(point P,polygon X){
		bool in = 1;
		long double c1 = vector(X.Plist[0],X.Plist[1])^vector(X.Plist[0],P),cn;
		for(int i = 1;i < X.Pcnt;++i){
			cn = vector(X.Plist[i],X.Plist[(i+1)%X.Pcnt])^vector(X.Plist[i],P);
			in = in&(cn*c1 > 0);
			if(!in) return 0;
		}
		return 1;
	}
}
