#ifndef Protium_PhysicalValue_h_
#define Protium_PhysicalValue_h_

namespace Protium{
	namespace PhysicalValues{
		template<typename T>
		class PhysicalValue{
			T fValue;
			T fError;
		};
	}
}

#endif //Protium_PhysicalValue_h_