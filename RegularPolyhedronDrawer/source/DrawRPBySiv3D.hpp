//  DrawRPBySiv3D.hpp

#ifndef DrawRPBySiv3D_hpp
#define DrawRPBySiv3D_hpp

#include <Siv3D.hpp>
#include "RPRotation.hpp"


class RPDrawer{
public:
    Point origin;
    int size;

    RPDrawer(int x=0, int y=0, int s = 100);

    void drawLine(Line3 line);

    void drawRP(RegularPolyhedron rp);
};

String FormatMatrix3x3(Matrix3x3&); //Matrix3x3をString型に変換する。
String FormatVector3(Vector3& vec);

Vector3 mouseLDistance();
Vector3 mouseRDistance();

#endif /* DrawRPBySiv3D_hpp */
