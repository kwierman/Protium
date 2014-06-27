#ifndef Protium_NullTypes_h
#define Protium_NullTypes_h

namespace Protium{

	namespace Design{
	    ///Dummy Null Class
	    struct NullType{};
	    class EmptyType {};
	        
	    inline bool operator==(const EmptyType&, const EmptyType&){return true;}   

	    inline bool operator<(const EmptyType&, const EmptyType&){return false;}

	    inline bool operator>(const EmptyType&, const EmptyType&){return false;}

	    template <int v>
	    struct IntType{
	        enum { value = v };
	    };
	    
	    template <typename T>
	    struct TypeType{
	        typedef T OType;
	    };

	    template <typename T, typename U>
	    struct SameType
	    {
	        enum { value = false };
	    };
	    
	    template <typename T>
	    struct SameType<T,T>
	    {
	        enum { value = true };
	    };

	    template <class H, class T>
	    struct Typelist{
	       typedef H Head;
	       typedef T Tail;
	    };        


	}
}

#endif //File Guardian