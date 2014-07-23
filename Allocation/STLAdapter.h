#ifndef Protium_STLAdapter_h_
#define Protium_STLAdapter_h_

#include "Protium/Allocation/SmallObjectAllocator.h"


namespace Protium{
    namespace Allocation{

        template<typename Host, typename AllocType = SmallObjectAllocator<> >
        class STLAdapter{
        public:

            typedef ::std::size_t size_type;
            typedef ::std::ptrdiff_t difference_type;
            typedef Host * pointer;
            typedef const Host * const_pointer;
            typedef Host & reference;
            typedef const Host & const_reference;
            typedef Host value_type;

            typedef Host* hostPointer;
            typedef const Host* const_hostPointer;
            typedef Host& hostRef;
            typedef const Host& const_hostRef;
            inline STLAdapter() throw() {}
            inline STLAdapter(const STLAdapter& ) throw() {}
            template<typename T>
            inline STLAdapter(const STLAdapter<T>& ) throw() {}
            inline ~STLAdapter() throw() {}

            template<typename T>
            struct rebind{
                typedef STLAdapter<T> other;
            };

            Host* address(Host& elem) const {return &elem;}
            const Host* address(const Host& elem) const {return &elem;}
            Host* allocate(std::size_t count, const void* hint=0){
                (void)hint;
                void* p = AllocType::Instance().Allocate(count*sizeof(Host),true );
                return reinterpret_cast<Host*>(p);
            }

            void deallocate(Host* p, std::size_t size){
                AllocType::Instance().Deallocate(p, size* sizeof(Host));
            }

            std::size_t max_size() const throw(){
                const std::size_t max = std::size_t(-1);
                const std::size_t bytes = max/sizeof(Host);
                return bytes;
            }

            void construct(Host* p, const Host& value){
                new(p) Host(value);
            }

            void destroy(Host* p){
                (void)p;
                p->~Host();
            }
        };

        template<typename Host>
        inline bool operator == (const STLAdapter<Host>&, const STLAdapter<Host>& ){
            return true;
        }

        template < typename Host >
        inline bool operator != ( const STLAdapter< Host > & , const STLAdapter< Host > & )
        {
            return false;
        }

    }
}

#endif //File Guardian