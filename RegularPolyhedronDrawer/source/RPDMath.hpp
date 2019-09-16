//  RPDMath.hpp

#ifndef RPDMath_hpp
#define RPDMath_hpp

#include <string>
#include <cstring>
#include <cmath>
using namespace std;

//#include <Siv3D.hpp>    //デバッグ用

//#define PI 3.141592653589793

//クラスの前方宣言
class Vector3;

//クラスの定義
class Matrix3x3{
public:
    double value[3][3]; //[行][列]の値。

    Matrix3x3();
    string outputString();
    void setVectorInRow(Vector3& vec, int row);
    void setVectorInColumn(Vector3& vec, int column);

    double determinant();
    Matrix3x3 inverse();
    Matrix3x3 transpose();  //転置行列
    
    Matrix3x3& operator=(const Matrix3x3&);
    friend Matrix3x3 operator+(const Matrix3x3&, const Matrix3x3&); //行列の和
    friend Matrix3x3 operator-(const Matrix3x3&, const Matrix3x3&); //行列の差
    friend Matrix3x3 operator*(const Matrix3x3&, const Matrix3x3&); //行列の積
    friend Matrix3x3 operator*(const Matrix3x3&, double);
    friend Matrix3x3 operator*(double f, const Matrix3x3& m){return m * f;}
    friend Matrix3x3 operator/(const Matrix3x3& m, double f){return m * (1.0/f);}
    
};

class Vector3{  //3次元のベクトル（座標）
public:
    double x;
    double y;
    double z;

    Vector3(double argx=0, double argy=0, double argz=0){x=argx;y=argy;z=argz;}
    void setxyz(double argx, double argy, double argz){x=argx;y=argy;z=argz;}
    double absolute();

    friend Vector3 operator*(const Matrix3x3&, const Vector3&); //行列*ベクトルの積
    friend Vector3 operator*(const Vector3&, const double);
    friend Vector3 operator*(const double f, const Vector3& vec){return vec * f;}
    friend Vector3 operator/(const Vector3& vec, const double f){return vec * (1.0/f);}
    
};

class Line3{    //2点の3次元座標で表される直線
public:
    Vector3 startPoint;
    Vector3 endPoint;

    Line3(double x1=0, double y1=0, double z1=0, double x2=0, double y2=0, double z2=0);
};




#endif /* RPDMath_hpp */
