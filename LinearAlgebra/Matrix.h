#ifndef Protium_Matrix_h_
#define Protium_Matrix_h_

#include "Protium/LinearAlgebra/Vector.h"

namespace Protium{
	namespace LinearAlgebra{

		//forward def for the helpers
		template<typename T, int n, int m> class Matrix;


		template<typename T, int n, int m>
		struct SubMatrixHelper{
			//Get a submatrix omitting row i, column j.
			Matrix<T,n-1,m-1> GetSubMatrix(int i, int j, const Matrix<T,n,m>& mat){
				Matrix<T,n-1,m-1> temp;
				int current_index1 =0;
				int current_index2 =0;
				for(int k=0;k<i;k++){
					if(k!=i){
						for(int l=0;l<j;l++){
							if(l!=j)
								temp[current_index1][current_index2++] = mat.At(k,l);
						}
					current_index1++;
					current_index2=0;
					}
				}
				return temp;
			}
		};


		/*
		//helpers for the determinant
		template<typename T, int n>
		struct SubMatrixHelper<T, n,n>{
			Matrix<T,n-1, n-1> GetSubMatrix(const int& i, const int& j, const Matrix<T,n,n>& mat){
				Matrix<T,n-1, n-1> temp;
				int current_index1=0;
				int current_index2=0;

				for(int k=0; k<n;k++){
					if(k!=i){
						for(int l=0; l<n;l++){
							if( l!=j )
								temp[current_index1][current_index2++] = mat.At(k,l);
						}
						current_index1++;
						current_index2=0;
					}
				}
				return temp;
			}
		};

		template<typename T>
		struct SubMatrixHelper<T,2,2>{
			Matrix<T,1,1> GetSubMatrix(const int& i, const int& j, const Matrix<T,2,2>& mat){
				Matrix<T,1,1> temp;
				int current_index1=0;
				int current_index2=0;

				for(int k=0; k<2;k++){
					if(k!=i){
						for(int l=0; l<2;l++){
							if( l!=j )
								temp[current_index1][current_index2++] = mat.At(k,l);
						}
						current_index1++;
						current_index2=0;
					}
				}
				return temp;
			}
		};
		*/

		template<typename T, int n>
		struct DeterminantHelper{
			T Determinant(const Matrix<T,n,n>& mat){
				T det=0.;
				DeterminantHelper<T,n-1> helper;
				for(int i=0; i<n;i++){
					det-=mat.At(0,i)* (helper.Determinant( mat.GetSubMatrix(0,i) ));
				}
				return det;
			}
		};

		template<typename T>
		struct DeterminantHelper<T,1>{
			T Determinant(const Matrix<T,1,1>& mat){
				return -mat.At(0,0);
			}
		};


		template<typename T, int n, int m>
		class Matrix {
			std::vector< Vector<T,m> > fComponents;
			typedef typename std::vector< Vector<T,m> >::iterator Titer;

		public:
			Matrix(){
				for(int i=0; i<n;i++)
					fComponents.push_back(Vector<T,m>());
			}
			Matrix(const Matrix<T,n,m>& other){
				for(int i=0; i<n;i++)
					fComponents.push_back(Vector<T,m>(other.At(i) ));
			}


			virtual ~Matrix(){fComponents.clear(); }

			//Produces the transpose of this
			Matrix& Transpose() const{
				Matrix<T,m,n> ret;
				for(int i=0;i<n;i++)for(int j=0; j<m;j++)
					ret[j][i] = this->At(i,j);
				return ret;
			}

			Vector<T,n>& operator[](const int& index){
		    	return fComponents[index];
		    }

		    Vector<T,n> At(const int& i) const{
		    	Vector<T,n>& temp = fComponents[i];
		    	return temp;
		    }

		    T At(const int& i, const int& j) const{
		    	const Vector<T,n>& temp = fComponents[i];
		    	return temp.At(j);
		    }

		    Matrix<T,n-1,m-1> GetSubMatrix(const int& i, const int& j)const {
		    	SubMatrixHelper<T,n,m> helper;
		    	return helper.GetSubMatrix(i,j, (*this) );
		    }

/*
			double Determinant() const{
				if(n==1 && m==1)
					return this->At(0,0);
				DeterminantHelper<T,n> helper;
				return helper.Determinant( (*this) );
			}

/*


			Matrix& operator+=(const Matrix& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

	  		//only want to be able to multiply by 
			Matrix& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}

	  		Vector<T,m> operator*=(const Vector<T,n>& rhs) {
	  			Vector<T,n> ret;
	  			for(int i=0; i<n;i++)
	  				ret[i] = (*this)[i] * rhs;
	  			return ret;
	  		}

	  		Matrix& operator*=(const Matrix& rhs){
	  			for(int i=0; i<n;i++)
	  				for(int j=0; j<n;j++)
	  					(*this)[i][j] *= rhs.At(i,j);
	  			return (*this);
	  		}

			Matrix& operator-=(const Matrix& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		const Matrix operator+(const Matrix& rhs) const {
	    		return Matrix(*this) += rhs;
	  		}
	  		const Matrix operator-(const Matrix& rhs) const {
	    		return Matrix(*this) -= rhs;
	  		}

	  		const Matrix operator*(const Matrix& rhs) const {
	    		return Matrix(this) *= rhs;
	  		}

			const Matrix operator*(const T& rhs) const {
	  			return Matrix(*this) *=rhs;
	  		}

	  		bool operator==( const Matrix &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}
		  	bool operator!=( const Matrix &rhs) const {
	    		return !(*this == rhs);
	  		}

	  			*/


		};

		typedef Matrix<double, 2,2> TwoMatrix;
		typedef Matrix<double,3,3> ThreeMatrix;
		typedef Matrix<double,4,4> FourMatrix;
	}
}


#endif //File Guardian