#ifndef Protium_Threads_h_
#define Protium_Threads_h_

#include "Protium/Design/Assert.h"

//Note that at this point, threads belong exclusively to pthreads
#include <pthread.h>
#include <cassert>

namespace Protium{
    namespace Threads{

        //Definitions of mutex level functions
        //-----------------------------------------------------------------
        class Mutex{
            Mutex(const Mutex&);
            Mutex & operator=(const Mutex& );
            pthread_mutex_t fMtx;
            bool fIsLocked;
        public:
            Mutex();
            void Lock();
            void Unlock();
            bool IsLocked();
        };
        //-----------------------------------------------------------------


        //-----------------------------------------------------------------
        template<class Derived, class Host, class MutexClass=Mutex>
        class ThreadingPolicyProtoType {

            static int AtomicAdd(volatile int& lhs, const int rhs);
            static int AtomicSubtract(volatile int& lhs, const int rhs) ;
            static int AtomicAdd(volatile int& lhs, const int rhs) ;
            static int AtomicMultiply(volatile int& lhs, const int rhs) ;
            static int AtomicDivide(volatile int& lhs, const int rhs) ;

            static int AtomicIncrement(volatile int& lhs);
            static int AtomicDecrement(volatile int& lhs);
            static int AtomicAssign(volatile int& lhs);
        };

        //-----------------------------------------------------------------
        template<class Host, class MutexClass=Mutex>
        class InSingleThread : ThreadingPolicyProtoType<InSingleThread, Host, MutexClass >{
        };

        template<class Host, class MutexClass=Mutex>
        class InMultiThread : ThreadingPolicyProtoType<InMultiThread, Host, MutexClass> {
            static Mutex fAtomicOPerationsMutex;                        
        public:
            static int AtomicMultiply(volatile int& lval, const int val){                                                                
                fAtomicOPerationsMutex.Lock();                      
                lval *= val;
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                                                                                  
            static int AtomicDivide(volatile int& lval, const int val) {                                                                
                fAtomicOPerationsMutex.Lock();                      
                lval /= val;                                                 
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                         
            static int AtomicIncrement(volatile int& lval)           
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                ++lval;                                                      
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicDecrement(volatile int& lval)           
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                --lval;                                                      
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                             
            static void AtomicAssign(volatile int& lval, const int val) 
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                lval = val;                                                  
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                             
            static void AtomicAssign(int& lval, volatile const int& val) 
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                lval = val;                                                  
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicIncrement(volatile int& lval, const int compare, bool & matches ) 
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                ++lval;                                                      
                matches = ( compare == lval );                               
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicDecrement(volatile int& lval, const int compare, bool & matches ) 
            {                                                                
                fAtomicOPerationsMutex.Lock();                      
                --lval;                                                      
                matches = ( compare == lval );                               
                fAtomicOPerationsMutex.UnLock();                    
                return lval;                                                 
            }                                                                
            static int AtomicMultiply(volatile int& lval, const int val, const int compare, bool & matches ) 
            {                                                               
                fAtomicOPerationsMutex.Lock();                     
                lval *= val;                                                
                matches = ( lval == compare );                              
                fAtomicOPerationsMutex.UnLock();                   
                return lval;                                                
            }                                                               
                                                                            
            static int AtomicDivide(volatile int& lval, const int val, const int compare, bool & matches ) 
            {                                                               
                fAtomicOPerationsMutex.Lock();                     
                lval /= val;                                                
                matches = ( lval == compare );                              
                fAtomicOPerationsMutex.UnLock();                   
                return lval;                                                
            }            
        };
        //-----------------------------------------------------------------

        //-----------------------------------------------------------------
        template<class Host, class MutexClass=Mutex>
        class LocksByObject : public InMultiThread<Host, Mutex>{

        };
        template<class Host, class MutexClass=Mutex>
        class LocksByClass : public InMultiThread<Host, Mutex>{

        };
        //-----------------------------------------------------------------
    }
}


























	template<class Derived, class MutexClass=Mutex>
	class InSingleThread{

        typedef Derived DerivedType;
        
		struct Lock{
			Lock(){}
			explicit Lock(const InSingleThread&){}
			explicit Lock(const InSingleThread*){}
		};

	};





    template <class Derived, class MutexClass = Mutex>
    class LockByObject{
        mutable MutexClass fMtx;
        //statically lock all of the same objects
        static pthread_mutex_t fMathMutex;
        typedef Derived DerivedType;

    public:
        LockByObject() : fMtx() {}

        LockByObject(const LockByObject&) : fMtx() {}

        ~LockByObject() {}

        class Lock;
        friend class Lock;

        class Lock{
        	Lock();
        	Lock(const Lock&);
        	Lock& operator=(const Lock&);
        	const LockByObject& fOwner;
        public:

            explicit Lock(const LockByObject& own) : fOwner(own) {
                fOwner.fMtx.Lock();
            }

            explicit Lock(const LockByObject* own) : fOwner(*own){
                fOwner.fMtx.Lock();
            }

            ~Lock(){
                fOwner.fMtx.Unlock();
            }
        }; 

    };

	template <class Derived, class MutexClass>
    pthread_mutex_t LockByObject<Derived, MutexClass>::fMathMutex = PTHREAD_MUTEX_INITIALIZER;



   template <class Derived, class MutexClass = Mutex >
    class ClassLevelLockable
    {
        struct Initializer{
            bool fIsInit;
            MutexClass fMtx;

            Initializer() : fIsInit(false), fMtx()
            {
                fIsInit = true;
            }

            ~Initializer()
            {
                assert(fIsInit);
            }
        };

        static Initializer fInit;
        static pthread_mutex_t fMathMutex;
        typedef Derived DerivedType;


    public:

        class Lock;
        friend class Lock;

        ///  \struct Lock
        ///  Lock class to lock on class level
        class Lock
        {
        public:

            /// Lock class
            Lock()
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Lock class
            explicit Lock(const ClassLevelLockable&)
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Lock class
            explicit Lock(const ClassLevelLockable*)
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Unlock class
            ~Lock()
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Unlock();
            }

        private:
            Lock(const Lock&);
            Lock& operator=(const Lock&);
        };

    };

}


#endif //Protium_Threads_h_