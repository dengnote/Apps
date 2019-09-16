//  library.hpp  ver.0.9
#ifndef library_hpp
#define library_hpp

#include <stdlib.h>
#include <time.h>
#include <random>

void srandamInt();      //randamInt()の初期化
inline int randamInt(int a){return (rand() % a);}   //0~(a-1)の範囲のランダムな整数値を返す
int randamInt7(int flag=0); //7回1セットとし、1セットのうちに必ず1~7が1個ずつ含まれるようにする。
                            //flag=1で7回のセットをリセットする。

int mtRandomInt(int range);   //非決定的な乱数。0~(range-1)の値を返す。
int mtRandom100();  //非決定的な乱数。0~99の値を返す。

#endif /* library_hpp */
