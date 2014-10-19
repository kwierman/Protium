#ifndef Protium_Random_hh_
#define Protium_Random_hh_

#include <ctime>
#include <cassert>

namespace Protium{
    namespace Math{
        class Random{
            unsigned fSeed;
        public:
            Random(unsigned seed=0);
            unsigned short nextShort();
            unsigned getSeed();
            unsigned int nextUint();
            unsigned int nextUint(unsigned int high);
            double nextDouble(double low, double high);
        };
    }
}



#endif //File Guardian


