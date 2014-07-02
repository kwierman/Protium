/*! \file Mutex.h
    \brief Defines mutexes and policies to be used by threaded objects.
    \author Kevin Wierman
 */

#ifndef Protium_Threads_h_
#define Protium_Threads_h_

#include "Protium/Design/Assert.h"

//Note that at this point, threads belong exclusively to pthreads
#include <pthread.h>
#include <cassert>

namespace Protium{
    namespace Threads{

        /*! \class Mutex
            \brief Wrapper class for pthreads-style mutexes
        
            Provides the ability to lock mutexes at the object level
         */
        class Mutex{
            Mutex(const Mutex&);
            Mutex & operator=(const Mutex& );
            pthread_mutex_t fMtx;
            bool fIsLocked;
        public:
            Mutex();
            //! Attempts to lock the mutex and blocks until mutex is available. 
            void Lock();
            //! Unlocks the mutex for the next usage.
            void Unlock();
            /*! Checks to see if the  
            *   \return True if the mutex is locked elsewhere. False otherwise.
            */
            bool IsLocked();
        };


        template<class Derived, class Host, class MutexClass=Mutex>
        class ThreadingPolicyProtoType {

            static int AtomicAdd(volatile int& lhs, const int rhs);
            static int AtomicSubtract(volatile int& lhs, const int rhs) ;
            static int AtomicMultiply(volatile int& lhs, const int rhs) ;
            static int AtomicDivide(volatile int& lhs, const int rhs) ;

            static int AtomicIncrement(volatile int& lhs);
            static int AtomicDecrement(volatile int& lhs);
            static int AtomicAssign(volatile int& lhs);
        };

        //-----------------------------------------------------------------
        template<class Host, class MutexClass=Mutex>
        class InSingleThread : ThreadingPolicyProtoType<InSingleThread, Host, MutexClass >{
            static int AtomicMultiply(volatile int& lval, const int val){                                                                                      
                lval *= val;                   
                return lval;                                                 
            }                                                                                                                                  
            static int AtomicDivide(volatile int& lval, const int val) {                                                                                      
                lval /= val;                                                                    
                return lval;                                                 
            }                                                                
                                                                         
            static int AtomicIncrement(volatile int& lval){                                                                                      
                ++lval;                                                                         
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicDecrement(volatile int& lval){                                                                                      
                --lval;                                                                         
                return lval;                                                 
            }                                                                
                                                                             
            static void AtomicAssign(volatile int& lval, const int val){                                                                                      
                lval = val;                                                                     
                return lval;                                                 
            }                                                                
                                                                             
            static void AtomicAssign(int& lval, volatile const int& val){                                                                                      
                lval = val;                                                                     
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicIncrement(volatile int& lval, const int compare, bool& matches ){                                                                                      
                ++lval;                                                      
                matches = ( compare == lval );                                                  
                return lval;                                                 
            }                                                                
                                                                             
            static int AtomicDecrement(volatile int& lval, const int compare, bool& matches ){                                                                                      
                --lval;                                                      
                matches = ( compare == lval );                                                  
                return lval;                                                 
            }                                                                
            static int AtomicMultiply(volatile int& lval, const int val, const int compare, bool& matches ){                                                                                    
                lval *= val;                                                
                matches = ( lval == compare );                                                
                return lval;                                                
            }                                                               
                                                                            
            static int AtomicDivide(volatile int& lval, const int val, const int compare, bool& matches ){                                                                                    
                lval /= val;                                                
                matches = ( lval == compare );                                                
                return lval;                                                
            }


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

        template <class Derived, class MutexClass>
        pthread_mutex_t InMultiThread<Derived, MutexClass>::fAtomicOPerationsMutex = PTHREAD_MUTEX_INITIALIZER;
        //-----------------------------------------------------------------

        //-----------------------------------------------------------------
        template<class Host, class MutexClass=Mutex>
        class LocksByObject : public InMultiThread<Host, Mutex>{
            class Lock;
            friend class Lock;

            class Lock{
                Lock();
                Lock(const Lock&);
                Lock& operator=(const Lock&);
                const LocksByObject& fOwner;
            public:

                explicit Lock(const LocksByObject& own) : fOwner(own) {
                    fOwner.fMtx.Lock();
                }

                explicit Lock(const LocksByObject* own) : fOwner(*own){
                    fOwner.fMtx.Lock();
                }

                ~Lock(){
                    fOwner.fMtx.Unlock();
                }
            }; 

        };


        template<class Host, class MutexClass=Mutex>
        class LocksByClass : public InMultiThread<Host, Mutex>{

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
        //-----------------------------------------------------------------
    }
}





















}


#endif //Protium_Threads_h_