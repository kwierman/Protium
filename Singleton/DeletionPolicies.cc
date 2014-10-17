#include "Protium/Singleton/DeletionPolicies.hh"


#include <assert.h>

//! A function that 
void Protium::Singleton::AtExitFn(){

    assert( !TrackerList.empty());
    
    // Pick the element at the top of the stack
    DeletionTracker* pTop = TrackerList.back();
    
    // Remove that object off the stack _before_ deleting pTop
    TrackerList.pop_back();
    
    // Destroy the element
    delete pTop;
}