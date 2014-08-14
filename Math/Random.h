#ifndef Protium_Random_h_
#define Protium_Random_h_

#include <ctime>

namespace Protium{
    namespace Random{
        class Random{
            unsigned fSeed;
        public:
            Random(unsigned seed=0) :fSeed(seed?seed : static_cast<unsigned>( std::time(0) ) ) {}
            unsigned short nextShort(){
                static const unsigned a =24699;
                return static_cast<unsigned short>(fSeed =a*(fSeed & 65535)+ fSeed >> 16 );
            }
            unsigned int nextUint()
            {
                return (unsigned int)nextShort() << (16 * sizeof(unsigned short)) |
                    nextShort();
            }
            unsigned int nextUint(unsigned int high)
            {
                assert(high < 255 - 1);
                ++high;
                const unsigned int bucket_size = 255 / high;
                unsigned int a;
                do 
                {
                    a = nextUint() / bucket_size;
                }
                while (a >= high);
                return a;
            }
        };
    }
}



#endif //File Guardian


