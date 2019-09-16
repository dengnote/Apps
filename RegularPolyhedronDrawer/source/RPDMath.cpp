//  RPDMath.cpp

#include "RPDMath.hpp"


//Matrix3x3クラスのメンバ関数の定義
Matrix3x3::Matrix3x3()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            value[i][j] = 0.0;
        }
    }
}
string Matrix3x3::outputString()
{
    string tmpstring = "";
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpstring += value[rowi][columni];
            tmpstring += ' ';
        }
        tmpstring += '\n';
    }
    return tmpstring;
}
void Matrix3x3::setVectorInRow(Vector3& vec, int row)
{
    if(0 <= row && row < 3){
        value[row][0] = vec.x;
        value[row][1] = vec.y;
        value[row][2] = vec.z;
    }
}
void Matrix3x3::setVectorInColumn(Vector3& vec, int column)
{
    if(0 <= column && column < 3){
        value[0][column] = vec.x;
        value[1][column] = vec.y;
        value[2][column] = vec.z;
    }
}
double Matrix3x3::determinant()
{
    double det = 0.0;
    det += value[0][0]*value[1][1]*value[2][2];
    det += value[0][1]*value[1][2]*value[2][0];
    det += value[0][2]*value[1][0]*value[2][1];
    det -= value[0][2]*value[1][1]*value[2][0];
    det -= value[0][0]*value[1][2]*value[2][1];
    det -= value[0][1]*value[1][0]*value[2][2];
    return det;
}
Matrix3x3 Matrix3x3::inverse()  //掃き出し法による逆行列の計算
{
    Matrix3x3 tmpmat;
    if(determinant() != 0){
        //単位行列を加えた拡大行列
        double augment[3][6];
        for(int rowi=0;rowi<3;rowi++){
            for(int columni=0;columni<3;columni++){
                augment[rowi][columni] = value[rowi][columni];
                augment[rowi][columni + 3] = (rowi == columni)?1:0;
            }
        }

        int topRow;
        for(int rowi=0;rowi<3;rowi++){
            //rowi行目のrowi列目が0でなくなるように行を入れ替える
            topRow = rowi;
            while(!augment[topRow][rowi]){
                topRow++;
            }
            if(topRow){
                for(int i=0;i<6;i++){
                    double tmp;
                    tmp = augment[rowi][i];
                    augment[rowi][i] = augment[topRow][i];
                    augment[topRow][i] = tmp;
                }
            }

            //rowi行目のrowi列目が1になるように行を割る
            double divisor = augment[rowi][rowi];
            for(int i=0;i<6;i++){
                augment[rowi][i] /= divisor;
            }

            //rowi行目以外のrowi列目が0になるように、各行からrowi行目を引く
            for(int rowj=0;rowj<3;rowj++){
                if(rowj != rowi){
                    double coefficient = augment[rowj][rowi] / augment[rowi][rowi];
                    for(int i=rowi;i<6;i++){
                        augment[rowj][i] -= coefficient * augment[rowi][i];
                    }
                }
            }
        }

        //拡大行列から逆行列を抽出する
        for(int rowi=0;rowi<3;rowi++){
            for(int columni=0;columni<3;columni++){
                tmpmat.value[rowi][columni] = augment[rowi][columni + 3];
            }
        }
    }
    return tmpmat;
}
Matrix3x3 Matrix3x3::transpose()
{
    Matrix3x3 tmpmat;
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpmat.value[rowi][columni] = value[columni][rowi];
        }
    }
    return tmpmat;
}

//Matrix3x3クラスのoperator関数の定義
Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat)
{
    if(this != &mat){
        for(int rowi=0;rowi<3;rowi++){
            for(int columni=0;columni<3;columni++){
                value[rowi][columni] = mat.value[rowi][columni];
            }
        }
    }
    return *this;
}
Matrix3x3 operator+(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
    Matrix3x3 tmpmat;
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpmat.value[rowi][columni] = mat1.value[rowi][columni] + mat2.value[rowi][columni];
        }
    }
    return tmpmat;
}
Matrix3x3 operator-(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
    Matrix3x3 tmpmat;
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpmat.value[rowi][columni] = mat1.value[rowi][columni] - mat2.value[rowi][columni];
        }
    }
    return tmpmat;
}
Matrix3x3 operator*(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
    Matrix3x3 tmpmat;
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            tmpmat.value[rowi][columni] = 0;
            for(int i=0;i<3;i++){
                tmpmat.value[rowi][columni] += mat1.value[rowi][i] * mat2.value[i][columni];
            }
        }
    }
    return tmpmat;
}
Matrix3x3 operator*(const Matrix3x3&, double f)
{
    Matrix3x3 tmpmat;
    for(int rowi=0;rowi<3;rowi++){
        for(int columni=0;columni<3;columni++){
            for(int i=0;i<3;i++){
                tmpmat.value[rowi][columni] *= f;
            }
        }
    }
    return tmpmat;
}

//Vector3クラスのメンバ関数の定義
double Vector3::absolute()
{
    double tmp;
    tmp = sqrt(x*x + y*y + z*z);
    return tmp;
}

//Vector3クラスのフレンド関数の定義
Vector3 operator*(const Matrix3x3& mat, const Vector3& vec)
{
    Vector3 tmpvec;

    tmpvec.x = mat.value[0][0] * vec.x + mat.value[0][1] * vec.y + mat.value[0][2] * vec.z;
    tmpvec.y = mat.value[1][0] * vec.x + mat.value[1][1] * vec.y + mat.value[1][2] * vec.z;
    tmpvec.z = mat.value[2][0] * vec.x + mat.value[2][1] * vec.y + mat.value[2][2] * vec.z;
    
    return tmpvec;
}
Vector3 operator*(const Vector3& vec, const double f)
{
    Vector3 tmpvec;

    tmpvec.x = vec.x * f;
    tmpvec.y = vec.y * f;
    tmpvec.z = vec.z * f;
    
    return tmpvec;
}

//Line3のメンバ関数の定義
Line3::Line3(double x1, double y1, double z1, double x2, double y2, double z2)
{
    startPoint.setxyz(x1, y1, z1);
    endPoint.setxyz(x2, y2, z2);
}

