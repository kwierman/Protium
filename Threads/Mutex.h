/*! \file Mutex.h
    \brief Defines mutexes and policies to be used by threaded objects.
    \author Kevin Wierman
 */

#ifndef Protium_Threads_h_
#define Protium_Threads_h_

#include "Protium/Design/Assert.h" //For compile-time assertions

#include <pthread.h> //For access to pthreads
#include <cassert> //For static-assertions

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
            /*! Checks to see if the  mutex if locked
            *   \return True if the mutex is locked elsewhere. False otherwise.
            */
            bool IsLocked();
        };
    }
}



#endif //Protium_Threads_h_