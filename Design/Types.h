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


	    template<	class T1=NullType,
	    			class T2=NullType,
	    			class T3=NullType,
	    			class T4=NullType,
	    			class T5=NullType,
	        		class T6=NullType,
	    			class T7=NullType,
	    			class T8=NullType,
	    			class T9=NullType,
	    			class T10=NullType,
			        class T11=NullType,
	      			class T12=NullType,
	       			class T13=NullType,
	       			class T14=NullType,
	       			class T15=NullType,
	       			class T16=NullType,
	    			class T17=NullType,
	    			class T18=NullType,
	    			class T19=NullType,
	    			class T20=NullType
	  			>
	    struct Sequence{
	    private:
	        typedef typename Sequence<	T2,
        			 					T3,
        			 					T4,
        			 					T5,
        			 					T6,
        			 					T7,
        			 					T8,
        			 					T9,
        			 					T10,
        			 					T11,
										T12,
										T13,
										T14,
										T15,
										T16,
										T17,
										T18,
										T19,
                             			T20	>::Type TailResult;
	    public:
	        typedef Typelist<T1, TailResult> Type;
	    };
	        
	    template<>
	    struct Sequence<>{
	        typedef NullType Type;
	    };

	}
}

#endif //File Guardian