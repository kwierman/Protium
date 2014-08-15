#ifndef Protium_Assert_h_
#define Protium_Assert_h_

#include <stdlib.h>
#include <iostream>

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
    {if(!expr) std::cerr<<##msg<<std::endl; abort();}

#endif //Protium_Assert_h_
