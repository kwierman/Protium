#ifndef Protium_Singleton_h_
#define Protium_Singleton_h_

#include <list>

#include "Protium/Lifetime/Deleter.h"

namespace Protium{

	namespace Lifetime{

		typedef void (*AtExitFn)();

        class LifetimeTracker
        {
        public:
            LifetimeTracker(unsigned int x) : longevity_(x) 
            {}
            
            virtual ~LifetimeTracker() = 0;
            
            static bool Compare(const LifetimeTracker* lhs,
                const LifetimeTracker* rhs)
            {
                return lhs->longevity_ > rhs->longevity_;
            }
            
        private:
            unsigned int longevity_;
        };
        
        // Definition required
        inline LifetimeTracker::~LifetimeTracker() {} 
		typedef std::list<LifeTimeTracker*> TrackerArray;


        template <typename T, typename Destroyer>
        class ConcreteLifetimeTracker : public LifetimeTracker
        {
        public:
            ConcreteLifetimeTracker(T* p,unsigned int longevity, Destroyer d)
                : LifetimeTracker(longevity)
                , pTracked_(p)
                , destroyer_(d)
            {}
            
            ~ConcreteLifetimeTracker()
            { destroyer_(pTracked_); }
            
        private:
            T* pTracked_;
            Destroyer destroyer_;
        };

	    template <typename T, typename Destroyer>
	    void SetLongevity(T* pDynObject, unsigned int longevity, Destroyer d) {

	        // manage lifetime of stack manually
	        if(pTrackerArray==0)
	            pTrackerArray = new TrackerArray;

	        // automatically delete the ConcreteLifetimeTracker object when a exception is thrown
	        std::auto_ptr<LifetimeTracker> 
	            p( new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d) );

	        // Find correct position
	        TrackerArray::iterator pos = std::upper_bound(
	            pTrackerArray->begin(), 
	            pTrackerArray->end(), 
	            p.get(), 
	            LifetimeTracker::Compare);
	        
	        // Insert the pointer to the ConcreteLifetimeTracker object into the queue
	        pTrackerArray->insert(pos, p.get());
	        
	        // nothing has thrown: don't delete the ConcreteLifetimeTracker object
	        p.release();
	        
	        // Register a call to AtExitFn
	        std::atexit(AtExitFn);
	    }

	    template <typename T>
	    void SetLongevity(T* pDynObject, unsigned int longevity,
	        typename Private::Deleter<T>::Type d = Private::Deleter<T>::Delete)
	    {
	        SetLongevity<T, typename Private::Deleter<T>::Type>(pDynObject, longevity, d);
	    }

	    template <class T>
	    struct DefaultLifetime
	    {
	        static void ScheduleDestruction(T*, atexit_pfn_t pFun)
	        { std::atexit(pFun); }
	        
	        static void OnDeadReference()
	        { throw std::logic_error("Dead Reference Detected"); }
	    };



	}
}


#endif //File Guardian