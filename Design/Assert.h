#ifndef Protium_Assert_h_
#define Protium_Assert_h_

#include <stdlib.h>
#include <iostream>

template<int> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

#define PROTIUM_STATIC_ASSERT(expr, msg) \
    { CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 
    

#define PROTIUM_RUNTIME_ASSERT(expr, msg)\
    {if(!expr) std::cerr<<##msg<<std::endl; abort();}

#endif //Protium_Assert_h_
