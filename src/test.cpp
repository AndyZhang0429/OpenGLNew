#include "random.hpp"
#include <iostream>
#include <cstdio>
int main(){
    Random::srand(12); // Set the seed

    for (int i = 1; i <= 10; i++) {
        printf("%08x%08x\n",Random::getrandbytimes(i)>>32,Random::getrandbytimes(i)); // Generate and print 10 random numbers
        // std::cout << Random::getrandbytimes(i) << std::endl; // Generate and print 10 random numbers
    }
}