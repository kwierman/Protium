#ifndef Protium_Time_h_
#define Protium_Time_h_

#include <ctime>

namespace Protium{
	namespace Time{

		/**
			Wrapper Functionality for C-Style Time
		**/
		class TimePrimitive{
			//! Data
			time_t fData;
		public:
			TimePrimitive(const time_t& t) : fData(t) {}
			virtual ~ TimePrimitive(){}
			inline time_t GetTime() const {return fData;}
			inline void SetTime(const time_t& t) {fData=t;}
			static TimePrimitive Now(){
				return TimePrimitive( std::time(NULL) );
			}
		};
		class Time : public TimePrimitive{

		};


/*
					inline time_t GetTimeLocal() const {return time_t(*std::localtime(&fData)) ;}
			inline time_t GetTimeGM() const {return time_t(*std::gmtime(&fData)) ;}
*/
	}
}


#endif //File Guardian