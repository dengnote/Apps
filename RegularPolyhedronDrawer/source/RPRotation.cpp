//  RPRotation.cpp

#include "RPRotation.hpp"

//RegularPolyhedronのメンバ関数の定義
RegularPolyhedron::RegularPolyhedron()
{
    for(int i=0;i<30;i++){
        haveLine[i] = false;
    }
}
RegularPolyhedron& RegularPolyhedron::operator=(const RegularPolyhedron& rp)
{
    if(this != &rp){
        for(int i=0;i<30;i++){
            line[i] = rp.line[i];
            haveLine[i] = rp.haveLine[i];
        }
    }
    return *this;
}

//RP4のメンバ関数の定義
RP4::RP4()
{
    Vector3 point[4];
    point[0].setxyz(1, 1, 1);
    point[1].setxyz(1, -1, -1);
    point[2].setxyz(-1, 1, -1);
    point[3].setxyz(-1, -1, 1);

    //半径1の球に内接するサイズに変更
    double r = point[0].absolute();
    for(int i=0;i<4;i++){
        point[i] = point[i] / r;
    }
    
    int lineNum = 0;
    for(int si=0;si<3;si++){
        for(int ei=si+1;ei<4;ei++){
            line[lineNum].startPoint = point[si];
            line[lineNum].endPoint = point[ei];
            haveLine[lineNum] = true;
            lineNum++;
        }
    }
}

//RP6のメンバ関数の定義
RP6::RP6()
{
    Vector3 point[8];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                Vector3 tmp(1-2*k,1-2*j,1-2*i);
                point[k+2*j+4*i] = tmp;
            }
        }
    }

    //半径1の球に内接するサイズに変更
    double r = point[0].absolute();
    for(int i=0;i<8;i++){
        point[i] = point[i] / r;
    }

    int lineNum = 0;
    for(int i=0;i<4;i++){
        line[lineNum].startPoint = point[i*2];
        line[lineNum].endPoint = point[i*2+1];
        haveLine[lineNum] = true;
        lineNum++;

        line[lineNum].startPoint = point[i];
        line[lineNum].endPoint = point[i+4];
        haveLine[lineNum] = true;
        lineNum++;
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            line[lineNum].startPoint = point[i+4*j];
            line[lineNum].endPoint = point[i+4*j+2];
            haveLine[lineNum] = true;
            lineNum++;
        }
    }
}

//RP8のメンバ関数の定義
RP8::RP8()
{
    Vector3 point[6];
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            int a = 1-2*j;
            Vector3 tmp(a*(i==0), a*(i==1), a*(i==2));
            point[j+2*i] = tmp;
        }
    }

    //半径1の球に内接するサイズに変更
    double r = point[0].absolute();
    for(int i=0;i<6;i++){
        point[i] = point[i] / r;
    }

    int lineNum = 0;
    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            line[lineNum].startPoint = point[i];
            line[lineNum].endPoint = point[j+2];
            haveLine[lineNum] = true;
            lineNum++;
        }
    }

    int c[4] = {2,4,3,5};
    int d[4] = {4,3,5,2};
    for(int i=0;i<4;i++){
        line[lineNum].startPoint = point[c[i]];
        line[lineNum].endPoint = point[d[i]];
        haveLine[lineNum] = true;
        lineNum++;
    }
}

//RP12のメンバ関数の定義
RP12::RP12()
{
    double phi = (1.0+sqrt(5))/2.0;

    Vector3 point[6];
    point[0].setxyz(1/phi, 0, phi);
    point[1].setxyz(-1/phi, 0, phi);
    point[2].setxyz(1, 1, 1);
    point[3].setxyz(1, -1, 1);
    point[4].setxyz(-1, 1, 1);
    point[5].setxyz(-1, -1, 1);

    //半径1の球に内接するサイズに変更
    double r = point[0].absolute();
    for(int i=0;i<6;i++){
        point[i] = point[i] / r;
    }

    int lineNum = 0;
    for(int i=0;i<2;i++){        
        for(int j=0;j<3;j++){
            
            line[lineNum].startPoint = point[0];
            line[lineNum].endPoint = point[1];
            haveLine[lineNum] = true;
            lineNum++;

            for(int k=0;k<2;k++){
                for(int l=0;l<2;l++){
                    line[lineNum].startPoint = point[0+k];
                    line[lineNum].endPoint = point[2+k*2+l];
                    haveLine[lineNum] = true;
                    lineNum++;
                }
            }

            for(int k=0;k<6;k++){
                double newx = point[k].z;
                double newy = point[k].x;
                double newz = point[k].y;
                point[k].setxyz(newx, newy, newz);
            }
        }

        for(int k=0;k<6;k++){
            point[k].z *= -1;
        }
    }
}

//RP12のメンバ関数の定義
RP20::RP20()
{
    double phi = (1.0+sqrt(5))/2.0;

    Vector3 point[4];
    point[0].setxyz(1, 0, phi);
    point[1].setxyz(-1, 0, phi);
    point[2].setxyz(0, phi, 1);
    point[3].setxyz(0, -phi, 1);

    //半径1の球に内接するサイズに変更
    double r = point[0].absolute();
    for(int i=0;i<4;i++){
        point[i] = point[i] / r;
    }

    int lineNum = 0;
    for(int i=0;i<2;i++){        
        for(int j=0;j<3;j++){
            
            line[lineNum].startPoint = point[0];
            line[lineNum].endPoint = point[1];
            haveLine[lineNum] = true;
            lineNum++;

            for(int k=0;k<2;k++){
                for(int l=0;l<2;l++){
                    line[lineNum].startPoint = point[k];
                    line[lineNum].endPoint = point[2+l];
                    haveLine[lineNum] = true;
                    lineNum++;
                }
            }

            for(int k=0;k<4;k++){
                double newx = point[k].z;
                double newy = point[k].x;
                double newz = point[k].y;
                point[k].setxyz(newx, newy, newz);
            }
        }

        for(int k=0;k<4;k++){
            point[k].z *= -1;
        }
    }



}

//Viewクラスのメンバ関数の定義
View::View()
{
    viewpointX.setxyz(1, 0, 0);
    viewpointY.setxyz(0, 1, 0);
    viewpointZ.setxyz(0, 0, 1);

    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            viewpoint.value[rowi][columni] = (rowi == columni)?1:0;
        }
    }
    
    changeRP(4);
    viewRp = originalRp;
}
void View::resetViewpoint()
{
    viewpointX.setxyz(1, 0, 0);
    viewpointY.setxyz(0, 1, 0);
    viewpointZ.setxyz(0, 0, 1);
    xyzToMat();
}
void View::xyzToMat()
{
    viewpoint.value[0][0] = viewpointX.x;
    viewpoint.value[0][1] = viewpointX.y;
    viewpoint.value[0][2] = viewpointX.z;
    viewpoint.value[1][0] = viewpointY.x;
    viewpoint.value[1][1] = viewpointY.y;
    viewpoint.value[1][2] = viewpointY.z;
    viewpoint.value[2][0] = viewpointZ.x;
    viewpoint.value[2][1] = viewpointZ.y;
    viewpoint.value[2][2] = viewpointZ.z;
}
void View::matToXyz()
{
    viewpointX.x = viewpoint.value[0][0];
    viewpointX.y = viewpoint.value[0][1];
    viewpointX.z = viewpoint.value[0][2];
    viewpointY.x = viewpoint.value[1][0];
    viewpointY.y = viewpoint.value[1][1];
    viewpointY.z = viewpoint.value[1][2];
    viewpointZ.x = viewpoint.value[2][0];
    viewpointZ.y = viewpoint.value[2][1];
    viewpointZ.z = viewpoint.value[2][2];
}
void View::rotateViewpoint(Vector3& rotateVec)
{
    Vector3 unitVec;
    double angle = rotateVec.absolute();
    if(angle != 0.0){
        unitVec = rotateVec / rotateVec.absolute();

        Matrix3x3 oldViewpoint, b, c;
        oldViewpoint = viewpoint;

        b.setVectorInRow(unitVec, 0);
        Vector3 tmpVec(unitVec.y, -unitVec.x, 0.0);
        b.setVectorInRow(tmpVec, 1);
        tmpVec.setxyz(0.0, 0.0, 1.0);
        b.setVectorInRow(tmpVec, 2);

        c.value[0][0] = cos(angle);
        c.value[0][1] = 0;
        c.value[0][2] = -sin(angle);
        c.value[1][0] = 0;
        c.value[1][1] = 1;
        c.value[1][2] = 0;
        c.value[2][0] = sin(angle);
        c.value[2][1] = 0;
        c.value[2][2] = cos(angle);
        
        viewpoint = (oldViewpoint.inverse() * b.inverse() * c * b).transpose();
        matToXyz();
    }
}
void View::operateViewRp()
{
    for(int i=0;i<30;i++){
        viewRp.haveLine[i] = originalRp.haveLine[i];
        if(originalRp.haveLine[i]){
            viewRp.line[i].startPoint = viewpoint * originalRp.line[i].startPoint;
            viewRp.line[i].endPoint = viewpoint * originalRp.line[i].endPoint;
        }
    }
}
void View::changeRP(int changeNum)
{
    switch (changeNum){
        case 4:
            {
                RP4 tmp4;
                originalRp = tmp4;
            }
            break;
        case 6:
            {
                RP6 tmp6;
                originalRp = tmp6;
            }
            break;
        case 8:
            {
                RP8 tmp8;
                originalRp = tmp8;
            }
            break;
        case 12:
            {   
                RP12 tmp12;
                originalRp = tmp12;
            }
            break;
        case 20:
            {
                RP20 tmp20;
                originalRp = tmp20;
            }
            break;
        default:
            break;
    }
}

