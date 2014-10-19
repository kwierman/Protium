#include "Protium/Math/Random.hh"

#include <iostream>


int main(int argc, char* argv[]){

	std::cout<<"Calculating Pi"<<std::endl;

	Protium::Math::Random rand;

	std::cout<<"\tWith Seed: "<<rand.getSeed()<<std::endl;

	double nSquare=0;
	double nCircle =0;
	double radius = 1.0;
	double realPi = 3.14159265359;
	double error = 1.e-6;

	int iter=0;
	while(true){
		iter++;
		double x = rand.nextDouble(0.,radius);
		double y = rand.nextDouble(0,radius);
		if( (x*x+y*y<=radius*radius) )
			nSquare+=1;
		nCircle+=1;
		double calcPi = 4.0*nSquare/nCircle;
		if(calcPi<= realPi+error && calcPi>realPi-error){
			std::cout<<"Calculated Pi with: "<<std::endl;
			std::cout<<"\tIterations: "<<iter<<std::endl;
			std::cout<<"Value: "<<calcPi<<std::endl;
			std::cout<<"Error: "<<realPi-calcPi<<std::endl;
			break;
		}
	}


}