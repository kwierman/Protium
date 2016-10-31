#include "Protium/Threads/Thread.hh"
namespace Protium{
    namespace Threads{
        namespace Private{
            void* threadingFunction(void* thread){
                Thread* t = static_cast<Thread*>(thread);
                t->start();
                return NULL;
            }
        }
    }
}
