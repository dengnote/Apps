//  RPRotation.hpp

#ifndef RPRotation_hpp
#define RPRotation_hpp

#include "RPDMath.hpp"



class RegularPolyhedron{
public:
    Line3 line[30];
    bool haveLine[30];

    //Vec3 point[20];
    //bool havePoint[20];

    RegularPolyhedron();
    RegularPolyhedron& operator=(const RegularPolyhedron& rp);
};

class RP4:public RegularPolyhedron{
public:
    RP4();
};

class RP6:public RegularPolyhedron{
public:
    RP6();
};

class RP8:public RegularPolyhedron{
public:
    RP8();
};

class RP12:public RegularPolyhedron{
public:
    RP12();    //正十二面体の各辺の座標を格納する。
};

class RP20:public RegularPolyhedron{
public:
    RP20();
};

class View{
public:
    Vector3 viewpointX;
    Vector3 viewpointY;
    Vector3 viewpointZ;

    Matrix3x3 viewpoint; //value[a][b]。a:画面出力のX,Y,Z軸のいずれであるかを示す。b:画面出力のX,Y,Z軸の単位ベクトルの座標。

    RegularPolyhedron originalRp;
    RegularPolyhedron viewRp;

    View();
    void resetViewpoint();

    void xyzToMat();    //viewpointX,Y,Zを変更したときにvewpointを更新する。
    void matToXyz();    //vewpointを変更したときにviewpointX,Y,Zを更新する。

    void rotateViewpoint(Vector3& rotateVec);
    void operateViewRp();

    void changeRP(int changeNum);

    /* 
    Vector3 getViewpointX(){return viewpointX;}
    Vector3 getViewpointY(){return viewpointY;}
    Vector3 getViewpointZ(){return viewpointZ;}
    Matrix3x3 getViewpoint(){return viewpoint;}
     */
};

#endif /* RPRotation_hpp */
