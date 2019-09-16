//library.cpp  ver.0.9
#include "library.hpp"

void srandamInt(){
    srand((unsigned int)time(0));
    for(int i=0; i<6; i++){
        rand();         //数回rand()を実行しておくといいらしい。
    }
}
int randamInt7(int flag){
    static int num[7] = {0,0,0,0,0,0,0};
    if(flag){
        for(int i=0; i<7; i++){
            num[i] = 0;
        }
    }
    if(num[0] == 0){
        int choices[7] = {1,2,3,4,5,6,7}; 
        for(int i=0; i<7; i++){
            int tmp = randamInt(7-i);
            num[i] = choices[tmp];
            for(int j=tmp; j<6-i; j++){
                choices[j] = choices[j+1];
            }
            choices[6-i] = 0;
        }
    }
    int ans = num[0];
    for(int i=0; i<6; i++){
        num[i] = num[i+1];
    }
    num[6] = 0;
    return ans;
}

int mtRandomInt(int range)
{
    static std::random_device rnd;
    static std::mt19937 mt(rnd());

    int tmp = mt() % range;
    return tmp;
}
int mtRandom100()
{
    static std::random_device rnd;
    static std::mt19937 mt(rnd());
    static std::uniform_int_distribution<> rand100(0, 99);

    return rand100(mt);
}
