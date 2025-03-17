namespace Calculate_geometry_2D{
	typedef long double ld;
	ld esp = 1e-6;
	bool inset(ld x,ld l,ld r){return (x >= min(l,r))&&(x <= max(l,r));}
	struct point{
		ld x,y;
		point(){}
		point(ld x,ld y){this->x = x;this->y = y;}
        point(point A,point B){x = B.x-A.x;y = B.y-A.y;}
		bool operator == (const point other)const{return abs(other.x-x)<esp&&abs(other.y-y)<esp;}
		ld operator * (const point other)const{return x*other.x+y*other.y;}
		ld operator ^ (const point other)const{return x*other.y-y*other.x;}
		point operator + (const point other)const{return {x+other.x,y+other.y};}
		point operator - (const point other)const{return {x-other.x,y-other.y};}
	};
	ld farway(point A,point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
	struct circle{
		point O;ld r;
		circle(){}
		circle(point O,ld r){this->O = O;this->r = r;}
	};
	struct segment{
		point A,B;
		segment(){}
		segment(point A,point B){this->A = A;this->B = B;}
		ld length(){return farway(A,B);}
		point direct(){return B-A;}
	};
	struct line_vector{
		point O,D;
		line_vector(){}
		line_vector(point A,point B){O = A;D = point(A,B);}
		line_vector(segment AB){O = AB.A;D = point(AB.A,AB.B);}
	};
	struct triangle{
		point A,B,C;
		triangle(){}
		triangle(point A,point B,point C){this->A = A;this->B = B;this->C = C;}
		ld Clength(){return farway(A,B)+farway(A,C)+farway(C,B);}
	};
	struct polygon{
		vector<point>Plist;int Pcnt;
		polygon(){}
		polygon(int N,point *li){
			Pcnt = N;
			for(int i = 1;i <= N;++i) Plist.push_back(*(li+i));
		}
		ld C(){
			ld sum = 0;
			for(int i = 0;i < Pcnt;++i){sum += farway(Plist[i],Plist[(i+1)%Pcnt]);}
			return sum;
		}
		ld S(){
			ld sum = 0;
			for(int i = 1;i < Pcnt-1;++i){sum += point(Plist[0],Plist[i])^point(Plist[0],Plist[i+1]);}
			sum *= 0.5;
			return sum;
		}
	};
	bool point_in_circle(point A,circle O){return farway(A,O.O) < O.r-esp;}
	bool point_on_circle(point A,circle O){return abs(farway(A,O.O)-O.r) < esp;}
	bool vector_Parallel(point A,point B){return abs(A.x*B.y-A.y*B.x) < esp;}
	bool vector_Vertical(point A,point B){return abs(A.x*B.y+A.y*B.x) < esp;}
	bool line_vector_Parallel(line_vector A,line_vector B){return vector_Parallel(A.D,B.D);}
	bool line_vector_Vertical(line_vector A,line_vector B){return vector_Vertical(A.D,B.D);}
	bool point_on_line_vector(point P,line_vector L){return vector_Parallel(point(P,L.O),L.D);}
	bool point_on_segment(point P,segment AB){return point_on_line_vector(P,line_vector(AB))&&inset(P.x,AB.A.x,AB.B.x)&&inset(P.y,AB.A.y,AB.B.y);}
	bool point_on_triangle(point P,triangle ABC){return point_on_segment(P,segment(ABC.A,ABC.B))||point_on_segment(P,segment(ABC.A,ABC.C))||point_on_segment(P,segment(ABC.C,ABC.B));}
	bool segment_intersect_line(segment AB,line_vector L){return (point(L.O,AB.A)^L.D)*(point(L.O,AB.B)^L.D) < esp;}
    bool segment_intersect_segment(segment AB,segment CD){
        bool res1 = (((AB.A-CD.A)^CD.direct())*((AB.B-CD.A)^CD.direct()) < esp);
        bool res2 = (((CD.A-AB.A)^AB.direct())*((CD.B-AB.A)^AB.direct()) < esp);
        return (res1&res2);
    }
	bool point_in_triangle(point P,triangle ABC){
		ld c1 = point(ABC.A,ABC.B)^point(ABC.A,P),c2 = point(ABC.B,ABC.C)^point(ABC.B,P),c3 = point(ABC.C,ABC.A)^point(ABC.C,P);
		return (c1*c2>esp&&c1*c3>esp);
	}
	bool point_in_polygon(point P,polygon X){
		bool in = 1;
		ld c1 = point(X.Plist[0],X.Plist[1])^point(X.Plist[0],P),cn;
		for(int i = 1;i < X.Pcnt;++i){
			cn = point(X.Plist[i],X.Plist[(i+1)%X.Pcnt])^point(X.Plist[i],P);
			in = in&(cn*c1 > 0);
			if(!in) return 0;
		}
		return 1;
	}
}