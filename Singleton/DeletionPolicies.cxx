#include "ProtiumSingletonDeletionPolicies.h"


//! A function that 
void Protium::Singleton::AtExiFn(){

	delete DeletionTrackers.pop_back();
}