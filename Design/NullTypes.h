#ifndef TriNull_h_
#define TriNull_h_

namespace Protium {
	namespace Design{

	    ///Dummy Null Class
	    struct NullType{};
	    class EmptyType {};
	        
	    inline bool operator==(const EmptyType&, const EmptyType&){return true;}   

	    inline bool operator<(const EmptyType&, const EmptyType&){return false;}

	    inline bool operator>(const EmptyType&, const EmptyType&){return false;}
	}
}


#endif //TriNull_h_