//I have taken the logic flow from the websites: https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/pollardsRho.html (general program logic flow) and https://en.wikipedia.org/wiki/Trial_division (line 28: the count stops at sqrt(number) for the looping) for my program
#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int argc, char** argv){
    unsigned long long starting_integer = strtoull(argv[1], NULL, 10);
    unsigned long long ending_integer = strtoull(argv[2], NULL, 10);
    unsigned long long number;
    bool first = true;
    unsigned long long count = 3;

    for (unsigned long long i = starting_integer; i <= ending_integer; i++){
        first = true;
        number = i;
        std::cout << number << "=";
        while ( number%2 == 0){
            if (!first){
                std::cout << ' ' << 2;
            }else{
                std::cout << 2;
                first = false;
            } 
            number /= 2;
        }
        count = 3;
        while(count <= sqrt(number)){           //the trial factors need go no further than sqrt {n} because, if n is divisible by some number p, then n = p × q and if q were smaller than p, n would have been detected earlier as being divisible by q or by a prime factor of q.

            while ( number%count == 0){
                if(!first){
                    std::cout << ' ' << count;
                }else{
                    std::cout << count;
                    first = false;
                }
                number/=count;
            }
            count+=2;
        }

        if (number > 2){
        if(!first)std::cout << "*"; 
        std::cout << number;
        }

        if ( i < ending_integer ) std::cout << std::endl;
    }
    return 0;

}