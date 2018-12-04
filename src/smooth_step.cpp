#include "smooth_step.h"

// Filter an input value to perform a smooth step. This function should be a
// cubic polynomial with smooth_step(0) = 0, smooth_step(1) = 1, and zero first
// derivatives at f=0 and f=1. 
//
// Inputs:
//   f  input value
// Returns filtered output value
float smooth_step( float f)
{
/////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
 // smooth_step = -2x^3 + 3x^2 ; 

 float ret ;

 ret = -2 * pow(f,3) + 3 * pow(f,2) ;

 return ret ;
  /////////////////////////////////////////////////////////////////////////////
}

