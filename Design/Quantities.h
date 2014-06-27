#ifndef Protium_Quantities_h_
#define Protium_Quantities_h_ 

#include "Protium/Design/Assert.h"
#include "Protium/Design/"
#include "Dimensions.h"

namespace Protium{

	namespace Design{

		template <typename T, class Dimensions>
		struct Quantity{
		    explicit Quantity(T x) : fValue(x) {}

		    template<class OtherDimensions>
		    Quantity(const OtherDimensions& rhs ) :fValue(rhs.Value()){
		    	PROTIUM_STATIC_ASSERT( (SameType< Dimensions , OtherDimensions >::value),
		    							ERROR_QUANTITIES_NOT_EQUAL_DIMENSIONS() );
		    }

		    T Value() const { return fValue; }
		    const T& ConstValue() const {return fValue;}
		 private:
		    T fValue;
		};

		template <class T, class D>
		Quantity<T,D> operator+(Quantity<T,D> x, Quantity<T,D> y) {
			return Quantity<T,D>(x.Value() + y.Value());
		}

		template <class T, class D>
		Quantity<T,D> operator-(Quantity<T,D> x, Quantity<T,D> y) {
			return Quantity<T,D>(x.Value() - y.Value());
		}

		template <class T, class D1, class D2>
		Quantity< T, typename DimensionAdd<D1,D2>::Type >  operator*(Quantity<T,D1> x, Quantity<T,D2> y) {
	    	typedef typename DimensionAdd<D1,D2>::Type dim;
	    	return Quantity<T,dim>( x.Value() * y.Value() );
		}

		//Division
		template <class T, class D1, class D2>
		Quantity< T, typename DimensionSubtract<D1,D2>::Type > operator/(Quantity<T,D1> x, Quantity<T,D2> y) {
	    	typedef typename DimensionSubtract<D1,D2>::Type dim;
	    	return Quantity<T,dim>( x.Value() / y.Value() );
		}

	}

	//everything in double, since that's the limit that we're calculating to
#ifdef PROTIUM_DEBUG
	typedef Design::Quantity<double, Design::scalar> Scalar;
	typedef Design::Quantity<double, Design::mass> Mass;
	typedef Design::Quantity<double, Design::length> Length;
	typedef Design::Quantity<double, Design::time> Time;
	typedef Design::Quantity<double, Design::charge> Charge;
	typedef Design::Quantity<double, Design::temperature> Temperature;
	typedef Design::Quantity<double, Design::intensity> Intensity;
	typedef Design::Quantity<double, Design::angle> Angle;

	//Derived quantities (To be partially speciallized on mec change)
	typedef Design::Quantity<double, Design::velocity> Velocity;
	typedef Design::Quantity<double, Design::rate> Rate;
	typedef Design::Quantity<double, Design::energy> Energy;
	typedef Design::Quantity<double, Design::action> Action;
	typedef Design::Quantity<double, Design::fermiDimension> FermiQuantity;
	typedef Design::Quantity<double, Design::magneticFluxDensity> MagneticFluxDensity;
	typedef Design::Quantity<double, Design::eleccFluxDensity> EleccFluxDensity;
#else
	typedef double Scalar;
	typedef double Mass;
	typedef double Length;
	typedef double Time;
	typedef double Charge;
	typedef double Temperature;
	typedef double Intensity;
	typedef double Angle;

	//Derived quantities (To be partially speciallized on mec change)
	typedef double Velocity;
	typedef double Rate;
	typedef double Energy;
	typedef double Action;
	typedef double FermiQuantity;
	typedef double MagneticFluxDensity;
	typedef double EleccFluxDensity;	
#endif
}

#endif //Protium_Quantities_h_