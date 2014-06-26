#ifndef Protium_Vector_h_
#define Protium_Vector_h_

#include <vector>

namespace Protium{

	namespace LinearAlgebra{


		class VectorPrototype{
			VectorPrototype(){}
			virtual ~VectorPrototype(){};
		};


		<typename T, int n=3>
		class Vector{
			std::vector<T> fComponents;
			typedef std::vector<T>::iterator Titer;
		public:
			Vector(){
				for(int i=0; i<n; i++){
					fComponents.push_back( T(0) );
				}
				this->Normalize( T(1) );
			}
			virtual ~Vector(){
				fComponents.clear();
			}

			int NDimensions(){
				return n;
			}

		    T Norm() const{
		      return sqrt(this*this);
		    }

		    T Normalize(const T& norm){
		    	T old_norm = this->Norm();
		    	for(Titer it = fComponents.begin(); it!=fComponents.end();++it )
		    		(*it) *= (norm/old_norm);
		    	return this->Norm();
		    }

		    T& Vector::operator[](const int& index){
		    	if(index>=n)
		    		return 0;
		    	return fComponents[index];
		    }

			Vector& Vector::operator+=(const Vector& rhs) {
				PROTIUM_STATIC_ASSERT(this->NDimensions() == rhs->NDimensions(),
										"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					this[i] +=rhs[i];
	    		return *this;
	  		}
			Vector& Vector::operator*=(const Vector& rhs) {
	   			PROTIUM_STATIC_ASSERT(this->NDimensions() == rhs->NDimensions(),
										"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					this[i] *=rhs[i];
	    		return *this;
	  		}
			Vector& Vector::operator-=(const Vector& rhs) {
	   			this->fX -= rhs->fX;
				 this->fY -= rhs->fY;
				this->fZ -= rhs->fZ; 		
	    		return *this;
	  		}

	  		const Vector Vector::operator+(const Vector &other) const {
	    		return Vector(*this) += other;
	  		}
	  		const Vector Vector::operator-(const Vector &other) const {
	    		return Vector(*this) -= other;
	  		}
	  		const T Vector::operator*(const Vector &other) const {
	    		return (this->fX*rhs->fX)+(this->fY*rhs->fY)+(this->fZ*rhs->fZ);
	  		}
	  		bool Vector::operator==(const Vector &other) const {
	    		return (this->fX == rhs->fX) && (this->fY == rhs->fY) && (this->fZ == rhs->fZ);
	  		}
		  	bool Vector::operator!=(const Vector &other) const {
	    		return !(*this == other);
	  		}

		};
	}
}


#endif //File Guardian

