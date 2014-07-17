#ifndef Protium_CreationPolicies_h_
#define Protium_CreationPolicies_h_

#include <malloc>

namespace Protium{
	namespace Lifetime{
    
	    template <class T> 
		struct CreateUsingNew
	    {
	        static T* Create()
	        { return new T; }
	        
	        static void Destroy(T* p)
	        { delete p; }
	    };

		template< template<class> class Alloc>
	    struct CreateUsingAllocator
	    {
	        template <class T>
	        struct Allocator
	        {
	            static Alloc<T> allocator;

	            static T* Create()
	            {
	                return new ( allocator.allocate(1) ) T;
	            }

	            static void Destroy(T* p)
	            {
	                p->~T();
	                allocator.deallocate(p,1);
	            }
	        };
	    };

	    template <class T> 
	    struct CreateUsingMalloc{
	        static T* Create()
	        {
	            void* p = std::malloc(sizeof(T));
	            if (!p) return 0;
	            return new(p) T;
	        }
	        
	        static void Destroy(T* p)
	        {
	            p->~T();
	            std::free(p);
	        }
	    };


	    template <class T> 
	    struct CreateStatic
	    {
	        
	        union MaxAlign
	        {
	            char t_[sizeof(T)];
	            short int shortInt_;
	            int int_;
	            long int longInt_;
	            float float_;
	            double double_;
	            long double longDouble_;
	            struct Test;
	            int Test::* pMember_;
	            int (Test::*pMemberFn_)(int);
	        };
	        
	        static T* Create()
	        {
	            static MaxAlign staticMemory_;
	            return new(&staticMemory_) T;
	        }
	        
	        static void Destroy(T* p)
	        {
	            p->~T();
	        }
	    };

	}

}


#endif //File Guardian