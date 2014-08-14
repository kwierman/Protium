#ifndef Protium_DataType_h_
#define Protium_DataType_h_

namespace Protium{
	namespace Containers{

		template< typename Type>
		struct Data1D{
			Type xValue;
		};

		template< typename Type>
		struct Data2D{
			Type xValue;
			Type yValue;
		};

		template<typename Type>
		struct Data3D{
			Type xValue;
			Type yValue;
			Type ZValue;
		};
	}
}

#endif //File Guardian
