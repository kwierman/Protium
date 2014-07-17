#ifndef Protium_Deleter_h_
#define Protium_Deleter_h_

namespace Protium{

	namespace Lifetime{
        template <typename T>
        struct Deleter
        {
            typedef void (*Type)(T*);
            static void Delete(T* pObj)
            { delete pObj; }
        };
	}
}


#endif //File Guardian