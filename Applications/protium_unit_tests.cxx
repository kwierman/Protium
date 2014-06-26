//#include "Protium/Collections/Histogram.h"
//#include "Protium/Collections/Function.h"
//#include "Protium/LinearAlgebra/Vector.h"
#include "Protium/Math/MathFunctions.h"

#include <iostream>
#include <iomanip>

using namespace Protium;
int main(int argc, char* argv[]){


	std::cout<<"Starting Basic Unit Tests"<<std::endl;
	std::cout<<"\tMath tests"<<std::setprecision(16)<<std::endl;
	{
		using namespace Math;
		std::cout<<"\t\tInt factorial (6): "<< 
			factorial<unsigned>(3)<<"\t"<<factorial<int>(3)<<
			"\t"<<factorial<long>(3)<<std::endl;

		std::cout<<"\t\tFloat/Double factorial (6): "<< 
			factorial<float>(3)<<"\t"<<factorial<double>(3)<<
			"\t"<<factorial<long double>(3)<<std::endl;

		std::cout<<"\t\tEuler\'s Number (2.71828182845904523536028747135266249775724709369995): "<<nat<<std::endl;
		std::cout<<"\t\t\tError: "<<2.71828182845904523536028747135266249775724709369995-nat<<std::endl;
		std::cout<<"\t\tPowers: "<<std::endl;
		for(double i=0; i<15;i++)for(double j=0; j<15; j++)
			std::cout<<"\t"<<power(i,j)<<"\t";

	}

}