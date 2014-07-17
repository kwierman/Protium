#ifndef RefToValue_h_
#define RefToValue_h_

namespace Protium{


    namespace Design{

        template<class T>
        class RefToValue{
            T& fRef;
            RefToValue();
            RefToValue& operator=(const RefToValue&);
        public:
            RefToValue(T& ref) : fRef(ref) {}
            RefToValue(const RefToValue& rhs) : fRef(rhs.fRef) {}
            operator T& () const{return fRef;}
        };

        template <class T>
        inline RefToValue<T> ByRef(T& t){
            return RefToValue<T>(t);
        }    

    }
}


#endif