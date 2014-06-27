#ifndef Protium_Dimensions_h
#define Protium_Dimensions_h

#include "Types.h"

namespace Protium{
	namespace Design{
		
		template<class Seq1, class Seq2>
		struct DimensionAdd{
			typedef typename Sequence<int, 	IntType< Seq1::Tail::Head::value + Seq2::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Head::value + Seq2::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >
			 >::Type Type;
		};
		//For Dividing Quantities, subtract dimensions
		template<class Seq1, class Seq2>
		struct DimensionSubtract{
			typedef typename Sequence<int, 	IntType< Seq1::Tail::Head::value - Seq2::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Head::value - Seq2::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >,
										IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >
			 >::Type Type;
		};
		


		//base dimensions
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type scalar;
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0> >::Type charge;
		typedef Sequence<int, IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type mass;
		typedef Sequence<int, IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type length;
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type time;
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0> >::Type temperature;
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0> >::Type intensity;
		typedef Sequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1> >::Type angle;

		//derived dimensions
		
		typedef DimensionSubtract<scalar, time>::Type 					rate;
		typedef DimensionSubtract<length, time>::Type 					velocity;
		typedef DimensionSubtract<velocity, time>::Type 					acceleration;
		typedef DimensionAdd<acceleration, mass >::Type 					force;
		typedef DimensionAdd<mass, velocity>::Type 						momentum;
		typedef DimensionAdd<force, length>::Type 						energy;
		typedef DimensionAdd<energy, time>::Type 						action;
		typedef DimensionSubtract<
				DimensionSubtract<scalar, energy>::Type, energy>::Type 	fermiDimension;
		typedef DimensionSubtract<charge, time>::Type 					current;
		typedef DimensionSubtract< 
				DimensionSubtract<force, current>::Type, current>::Type 	magneticFluxDensity;
		typedef DimensionSubtract<scalar, 
				DimensionAdd<magneticFluxDensity, 
				DimensionAdd<velocity, velocity>::Type>::Type  >::Type 	electricFluxDensity;

	}
}

#endif //Protium_Dimensions_h