#ifndef Protium_Assert_hh_
#define Protium_Assert_hh_

#include <stdlib.h>
#include <iostream>

/** \file Assert.hh
	\author Kevin Wierman
	\date April 12th, 2014
	\brief Defines static and runtime assertions.

	These are to be used as follows:

	~~~~~~~~
        PROTIUM_RUNTIME_ASSERT(true, ThisIsATrueStatement);
        PROTIUM_RUNTIME_ASSERT(false, ThisIsAFalseStatement);
	~~~~~~~~

	\note The second argument must be a single word, or else it will be interpreted as several arguements.
**/


//! Body-less template
template<int> 
struct CompileTimeError;

//! Fully-defined template
template<> 
struct CompileTimeError<true> {};

//! Use for performing static assertion
#define PROTIUM_STATIC_ASSERT(expr, msg) \
    { CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 
    
//! Use for runtime assertions
#define PROTIUM_RUNTIME_ASSERT(expr, msg)\
    {if(!expr) std::cerr<<#msg<<std::endl; abort();}

#endif //Protium_Assert_h_
