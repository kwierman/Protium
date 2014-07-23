#ifndef Protium_SmallObject_h_
#define Protium_SmallObject_h_

#include "Protium/Allocation/SmallObjectAllocator.h"
#include "Protium/Singleton/DeletionPolicies.h"
#include "Protium/Threads/ThreadingPolicy.h"


namespace Protium{

    namespace Allocation{

        template< template <class, class> class ThreadPolicy,
            std::size_t chunkSize,
            std::size_t maxSmallObjectSize,
            std::size_t objectAlignSize,
            template <class> class LifetimePolicy,
            class MutexPolicy>
        class SmallObjectBase{
        public:
            typedef Protium::Allocation::SmallObjectAllocator< ThreadPolicy, chunkSize,
                maxSmallObjectSize, objectAlignSize, LifetimePolicy > ObjAllocator;
        
        private:

            typedef ThreadPolicy< ObjAllocator, MutexPolicy > ThreadType;
            typedef typename ObjAllocator::AllocatorSingleton AllocatorSingleton;
            
        public:

            static void * operator new ( std::size_t size ) throw ( std::bad_alloc ){
                typename ThreadType::Lock lock;
                (void)lock;
                return AllocatorSingleton::Instance().Allocate( size, true );
            }

            static void * operator new ( std::size_t size, const std::nothrow_t & ) throw () {
                typename ThreadType::Lock lock;
                (void)lock;
                return AllocatorSingleton::Instance().Allocate( size, false );
            }

            inline static void * operator new ( std::size_t size, void * place ) {
                return ::operator new( size, place );
            }

            static void operator delete ( void * p, std::size_t size ) throw () {
                typename ThreadType::Lock lock;
                (void)lock;
                AllocatorSingleton::Instance().Deallocate( p, size );
            }

            static void operator delete ( void * p, const std::nothrow_t & ) throw() {
                typename ThreadType::Lock lock;
                (void)lock; // get rid of warning
                AllocatorSingleton::Instance().Deallocate( p );
            }

            inline static void operator delete ( void * p, void * place ) {
                ::operator delete ( p, place );
            }

            static void * operator new [] ( std::size_t size ) throw ( std::bad_alloc ) {
                typename ThreadType::Lock lock;
                (void)lock; // get rid of warning
                return AllocatorSingleton::Instance().Allocate( size, true );
            }

            static void * operator new [] ( std::size_t size, const std::nothrow_t & ) throw () {
                typename ThreadType::Lock lock;
                (void)lock; // get rid of warning
                return AllocatorSingleton::Instance().Allocate( size, false );
            }

            inline static void * operator new [] ( std::size_t size, void * place ) {
                return ::operator new( size, place );
            }

            static void operator delete [] ( void * p, std::size_t size ) throw () {
                typename ThreadType::Lock lock;
                (void)lock; // get rid of warning
                AllocatorSingleton::Instance().Deallocate( p, size );
            }

            static void operator delete [] ( void * p, const std::nothrow_t & ) throw(){
                typename ThreadType::Lock lock;
                (void)lock; // get rid of warning
                AllocatorSingleton::Instance().Deallocate( p );
            }

            inline static void operator delete [] ( void * p, void * place ) {
                ::operator delete ( p, place );
            }

        protected:
            inline SmallObjectBase( void ) {}
            inline SmallObjectBase( const SmallObjectBase & ) {}
            inline SmallObjectBase & operator = ( const SmallObjectBase & )
            { return *this; }
            inline ~SmallObjectBase() {}
        };

        template
        <
            template <class, class> class ThreadingModel = Protium::Threads::InSingleThread,
            std::size_t chunkSize = 4096,
            std::size_t maxSmallObjectSize = 256,
            std::size_t objectAlignSize = 4,
            template <class> class LifetimePolicy = Protium::Singleton::DeleteLast,
            class MutexPolicy =  Protium::Threads::Mutex
        >
        class SmallObject : public SmallObjectBase< ThreadingModel, chunkSize,
                maxSmallObjectSize, objectAlignSize, LifetimePolicy, MutexPolicy >
        {

        public:
            virtual ~SmallObject() {}
        protected:
            inline SmallObject( void ) {}

        private:
            SmallObject( const SmallObject & );
            SmallObject & operator = ( const SmallObject & );
        };

        template< template <class, class> class ThreadingModel = Protium::Threads::InSingleThread,
            std::size_t chunkSize = 4096,
            std::size_t maxSmallObjectSize = 256,
            std::size_t objectAlignSize = 4,
            template <class> class LifetimePolicy = Protium::Singleton::DeleteLast,
            class MutexPolicy = Protium::Threads::Mutex >
        class SmallValueObject : public SmallObjectBase< ThreadingModel, chunkSize,
                maxSmallObjectSize, objectAlignSize, LifetimePolicy, MutexPolicy >
        {
        protected:
            inline SmallValueObject( void ) {}
            inline SmallValueObject( const SmallValueObject & ) {}
            inline SmallValueObject & operator = ( const SmallValueObject & )
            { return *this; }
            inline ~SmallValueObject() {}
        }; // end class SmallValueObject

        typedef SmallObject<> DefaultSmallObject;
        typedef SmallValueObject<> DefaultSmallValueObject;

    }
}

#include "Protium/Allocation/STLAdapter.h"

#endif //Protium_SmallObject_h_