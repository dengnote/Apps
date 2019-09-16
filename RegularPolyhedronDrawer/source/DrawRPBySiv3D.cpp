//  DrawRPBySiv3D.cpp

#include "DrawRPBySiv3D.hpp"

//RPDrawerのメンバ関数の定義
RPDrawer::RPDrawer(int x, int y, int s)
{
    origin = Point(x, y);
    size = s;
}
void RPDrawer::drawLine(Line3 line)
{
    Line(line.startPoint.x * size + origin.x, line.startPoint.y * size + origin.y, line.endPoint.x * size + origin.x, line.endPoint.y * size + origin.y).draw(2, Palette::Black);
}
void RPDrawer::drawRP(RegularPolyhedron rp)
{
    for(int line_i=0;line_i<30;line_i++){
        if(rp.haveLine[line_i]){
            drawLine(rp.line[line_i]);
        }
    }
}

String FormatMatrix3x3(Matrix3x3& mat)
{
    String tmpstring = U"";
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpstring += Format(mat.value[rowi][columni]);
            tmpstring += U" ";
        }
        tmpstring += U"\n";
    }
    return tmpstring;
}

String FormatVector3(Vector3& vec)
{
    String tmpstring = U"";
    tmpstring += Format(vec.x);
    tmpstring += U" ";
    tmpstring += Format(vec.y);
    tmpstring += U" ";
    tmpstring += Format(vec.z);
    tmpstring += U" ";
    
    return tmpstring;
}

Vector3 mouseLDistance()
{
    Vector3 vec;
    Vec2 tmpvec;
    if(MouseL.pressed() && !MouseL.down()){
        tmpvec = Cursor::DeltaF();
        vec.x = tmpvec.x;
        vec.y = tmpvec.y;
        vec.z = 0;
    }
    return vec;
}
Vector3 mouseRDistance()
{
    Vector3 vec;
    Vec2 tmpvec;
    if(MouseR.pressed() && !MouseR.down()){
        tmpvec = Cursor::DeltaF();
        vec.x = tmpvec.x;
        vec.y = tmpvec.y;
        vec.z = 0;
    }
    return vec;
}
