#ifndef VEC3_HPP
#define VEC3_HPP
struct Vec3{
	Vec3(double a,double b,double c){
		first=a;
		second=b;
		third=c;
	}
	Vec3(){
		first=0;
		second=0;
		third=0;
	}
	Vec3 operator+(Vec3 v){
		return Vec3(first+v.first,second+v.second,third+v.third);
	}
	Vec3 operator+=(Vec3 v){
		return *this=*this+v;
	}
	Vec3 operator-(Vec3 v){
		return Vec3(first-v.first,second-v.second,third-v.third);
	}
	Vec3 operator-=(Vec3 v){
		return *this=*this-v;
	}
	Vec3 operator-(){
		return Vec3(-first,-second,-third);	
	}
	bool operator==(Vec3 v){
		return first==v.first&&second==v.second&&third==v.third;
	}
	bool operator!=(Vec3 v){
		return !(*this==v);	
	}
	bool operator<(const Vec3& v)const{
		if(first>v.first)return 0;
		if(first<v.first)return 1;
		if(second>v.second)return 0;
		if(second<v.second)return 1;
		if(third>v.third)return 0;
		if(third<v.third)return 1;
		return 0;
	}
	bool operator>(const Vec3& v)const{
		return v<(*this);
	}
	double first,second,third;
};
struct Vec4{
	Vec4(double a,double b,double c,double d){
		first=a;
		second=b;
		third=c;
		fourth=d;
	}
	Vec4(){
		first=0;
		second=0;
		third=0;
		fourth=0;
	}
	double first,second,third,fourth;
};
struct Point{
    Point(double x,double y){
        this->x=x;
        this->y=y;
    }
    
    // ¹éÒ»»¯º¯Êý
    Point normalize() const {
        double length = std::sqrt(x*x + y*y);
        if(length > 0) {
            return Point(x/length, y/length);
        }
        return *this;
    }

    double x,y;
};
namespace Vector3{
	const Vec3 up=Vec3(0,1,0);
	const Vec3 right=Vec3(1,0,0);
	const Vec3 front=Vec3(0,0,1);
	const Vec3 zero=Vec3(0,0,0);
}
#endif
