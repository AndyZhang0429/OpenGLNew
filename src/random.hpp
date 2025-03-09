#ifndef RANDOM_CPP
#define RANDOM_CPP
unsigned long long __seed = 0;
namespace Random{
    void srand(unsigned long long seed){
        ::__seed = seed;
    }
    unsigned long long rand(){
        __seed = (__seed * 18446744073709551557ull + 2531011);
        return (__seed >> 32) + (__seed<<32);
    }
    unsigned long long getrandbytimes(unsigned times){
        unsigned long long res = __seed; 
        for(unsigned i = 0;i < times;i++){
            res = (res * 18446744073709551557ull + 2531011); 
            res=~((res>>32)^0xf1dc76b2ull+(res<<32)^0x83956ab200000000ull);
        }
        return res;
    }
}
#endif