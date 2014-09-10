#ifndef Protium_Time_h_
#define Protium_Time_h_

#include <ctime>

namespace Protium{
	namespace Time{

		/**
			Wrapper Functionality for C-Style Time
		**/
		class TimePrimitive{
		protected:
			//! Data
			time_t fTime;
		public:
			TimePrimitive(const time_t& t) : fTime(t) {}
			virtual ~ TimePrimitive(){}
			inline time_t GetTime() const {return fTime;}
			inline void SetTime(const time_t& t) {fTime=t;}
			static TimePrimitive Now(){
				return TimePrimitive( std::time(NULL) );
			}
			TimePrimitive& operator-=(const TimePrimitive& other){
				this->fTime-=other.fTime;
				return *this;
			}

		};
		class Time : public TimePrimitive{
			tm fTM;
		public:
			Time(	const int& sec=0, 
					const int& min=0, 
					const int& hour =0, 
					const int& day=0, 
					const int& month=0,
					const int& year=0,
					const int& weekday=0,
					const bool& dst=false ) : TimePrimitive( std::time(NULL) ) {
				fTM.tm_sec = sec;
				fTM.tm_min = min;
				fTM.tm_hour = hour;
				fTM.tm_mday = day;
				fTM.tm_mon = month;
				fTM.tm_year = year;
				fTM.tm_wday = weekday;
				fTM.tm_isdst = dst? 1 : 0;
				fTime = mktime(&fTM); 
			}
			Time(const Time& other) : TimePrimitive(std::time(NULL) ) {
				this->fTM = other.fTM;
				this->fTime = mktime(&fTM);
			}

			inline time_t GetTimeLocal() const {return fTime ;}
			inline time_t GetTimeGM() const {return mktime(std::gmtime(&fTime)) ;}
		};
	}
}


#endif //File Guardian