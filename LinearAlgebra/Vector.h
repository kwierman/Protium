#ifndef Protium_Vector_h_
#define Protium_Vector_h_

#include <vector>
#include <cmath>

namespace Protium{

	namespace LinearAlgebra{

		template<typename T, int n> class Vector;

		template<typename T,int n>
		struct SubVectorHelper{
			Vector<T,n-1> GetSubVector(int i, const Vector<T,n>& vec){
				Vector<T,n-1> temp;
				int index=0;
				for(int j=0; j< n;j++)
					if(j!=i){
						temp[index++] = vec.At(j);
					}
					return temp;
			};
		};

		template <typename T, int n=3>
		class Vector {
		protected:
			std::vector<T> fComponents;
			typedef typename std::vector<T>::iterator Titer;
		public:
			Vector(const T& amplitude=1){
				for(int i=0; i<n; i++){
					fComponents.push_back( T(0) );
				}
				this->Normalize( amplitude );
			}
			Vector(const Vector<T,n>& other){
				for(int i=0; i<n; i++){
					fComponents.push_back( other.At(i) );
				}
			}

			virtual ~Vector(){
				fComponents.clear();
			}

			static int NDimensions(){
				return n;
			}

		    virtual T Norm() {
		      return sqrt( (*this)*(*this) );
		    }

		    virtual T Normalize(const T& norm){
		    	T old_norm = this->Norm();
		    	if(old_norm ==0) return 0;
		    	for(Titer it = fComponents.begin(); it!=fComponents.end();++it )
		    		(*it) *= (norm/old_norm);
		    	return this->Norm();
		    }

		    Vector<T,n-1> GetSubVector(const int& i){
		    	SubVectorHelper<T,n> helper;
		    	return helper.GetSubVector(i, (*this) ); 
		    }

		    T& operator[](const int& index){
		    	return fComponents[index];
		    }

		    //const access, instead of []operator
		    T At(const int& index) const{
		    	return fComponents[index];
		    }

			Vector& operator+=(const Vector& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

			Vector& operator*=(const Vector& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs.At(i);
	    		return *this;
	  		}

			Vector& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}


			Vector& operator-=(const Vector& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		const Vector operator+(const Vector& rhs) const {
	    		return Vector(*this) += rhs;
	  		}
	  		const Vector operator-(const Vector& rhs) const {
	    		return Vector(*this) -= rhs;
	  		}
	  		const T operator*(const Vector& rhs) const {
	  			double ret=0;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					ret+= this->At(i) * rhs.At(i);

	    		return ret;
	  		}

			const Vector operator*(const double& rhs) const {
	  			return Vector(*this) *=rhs;
	  		}

	  		bool operator==( const Vector &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}
		  	bool operator!=( const Vector &rhs) const {
	    		return !(*this == rhs);
	  		}

		};

		typedef Vector<double, 2> TwoVector;
		typedef Vector<double, 3> ThreeVector;
		typedef Vector<double, 4> FourVector;
	}
}


#endif //File Guardian

