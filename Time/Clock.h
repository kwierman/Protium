#ifndef Protium_Clock_h_
#define Protium_Clock_h_

#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

namespace Protium{
	namespace Time{

		/**
			Class for defining methods of retrieving machine clock cycles
		**/
		class ClockPrimitive{
			clock_t fClock;
		public:
			ClockPrimitive(){
				Set();
			}
			inline void Set(){
				fClock = clock();
			}
			inline clock_t Get(){
				return fClock;
			}
		};

		/**
			Defines functions for clocking certain times
		**/
		class SingleClocker{
			ClockPrimitive fStart;
			ClockPrimitive fStop;
		public:
			MachineClocker : fStart() , fStop() {}
			inline void Start(){fStart.Set();}
			inline void Stop(){fStop.Set();}
			inline clock_t GetTime(){return fStop.Get() - fStart.Get();}
		};

		class RepeatClocker{
			//* Every Time we 
			std::vector<ClockPrimitive> fData;
		};
	}
}

#endif //File Guardian