#ifndef Protium_Clock_hh_
#define Protium_Clock_hh_

#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <vector>

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
			inline clock_t Get() const{
				return fClock;
			}
			static clock_t CPS(){
				return CLOCKS_PER_SEC;
			}

			ClockPrimitive(const ClockPrimitive& other){
				this->fClock = other.fClock;
			}

			ClockPrimitive& operator=(const ClockPrimitive& other){
				this->fClock = other.fClock;
				return *this;
			}
			bool operator==(const ClockPrimitive& other){
				return (this->fClock == other.fClock );
			}


			ClockPrimitive& operator-(const ClockPrimitive& other){
				this->fClock - other.fClock;
				return *this;				
			}

		};

		/**
			Defines functions for clocking certain times
		**/
		class SingleClocker{
			ClockPrimitive fStart;
			ClockPrimitive fStop;
		public:
			SingleClocker() {}
			inline void Start(){fStart.Set();}
			inline void Stop(){fStop.Set();}
			inline clock_t GetTime(){return fStop.Get() - fStart.Get();}
		};


		class RepeatClocker{
			ClockPrimitive fStart;
			//* Every Time we 
			std::vector<ClockPrimitive> fData;
		public:
			RepeatClocker(){}
			inline void Clock(){
				fData.push_back( ClockPrimitive() );
			}
			unsigned GetNClocks() const {
				return fData.size();
			}
			clock_t GetStart(){
				return fStart.Get();
			}
			clock_t Get(const unsigned& i=0)const {
				return fData[i].Get();
			}
			clock_t GetOffset(const unsigned& i=0)const {
				return fData[i].Get() - fStart.Get();
			}

		};
	}
}

#endif //File Guardian