#include <cmath>
#include "random_direction.h"


// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
Eigen::Vector2d random2(Eigen::Vector3d st) {
	int a;

	Eigen::Vector2d S = Eigen::Vector2d(st.dot(Eigen::Vector3d(127.1, 311.7, 783.089)), st.dot(Eigen::Vector3d(269.5, 183.3, 173.542)));

	S(0) = sin(S(0)) * 43758.5453123;
	a = floor(S(0));
	S(0) = S(0) - a;

	S(1) = sin(S(1)) * 43758.5453123;
	a = floor(S(1));
	S(1) = S(1) - a;

	return S;
}

Eigen::Vector3d random_direction(Eigen::Vector3d seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
// permutation array store integer from 0 to 255
Eigen::Vector2d a,b,c ;
Eigen::Vector3d ret;
float total ;

a = random2(seed) ;
b = random2(seed) ;
c = random2(seed) ;

  total = pow(2*a(0)-1,2)+pow(2*b(0)-1,2)+pow(2*c(0)-1,2) ;
  if ( total > 1) {
      a(0) = (2*a(0)-1) / sqrt(total) ;
      b(0) = (2*b(0)-1) / sqrt(total) ;
      c(0) = (2*c(0)-1) / sqrt(total) ;
  }

  ret = Eigen::Vector3d(a(0), b(0), c(0));

  return  ret.normalized(); 


  /////////////////////////////////////////////////////////////////////////////
}
