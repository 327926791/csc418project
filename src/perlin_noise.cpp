#include "perlin_noise.h"

// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise(Eigen::Vector3d st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
Eigen::Vector3d rand_v ;
float u, v, w, nk[2], nj[2], ni[2], noise ;
int ii, jj, kk ;

// get the bottom-left point of unit cubic
// the point of st is in the cubic
   ii = (st(0) > 0) ? floor(st(0)) : floor(st(0) -1 ) ; 
   jj = (st(1) > 0) ? floor(st(1)) : floor(st(1) -1 ) ;
   kk = (st(2) > 0) ? floor(st(2)) : floor(st(2) - 1);

// hermite interpolation
for (int i=ii; i<=ii+1; i++) {
    for (int j=jj; j<=jj+1; j++) {
        for (int k=kk; k<=kk+1; k++) {
           v = smooth_step(st(2)-kk);
           // get random vection, then dot with vector(x-i,y-j,z-k)
           // then, mutiple with smooth values
           rand_v = random_direction(Eigen::Vector3d(i,j,k)) ;
           nk[k-kk] = rand_v.dot(Eigen::Vector3d(st(0)-i, st(1)-j, st(2)-k)) ;
         }
         // interpolation
         u = smooth_step(st(1)-jj) ;
         nj[j-jj] = (1-v)*nk[0] +v*nk[1] ;         
    }
    w = smooth_step(st(0)-ii) ;
    ni[i-ii] = (1-u)*nj[0] + u*nj[1]  ;
    
}
noise = (1-w)*ni[0] + w * ni[1] ;
noise=smooth_step(noise);

if (noise < -1)
   noise= -1 ;
if (noise > 1)
    noise = 1 ;
noise = (noise + 1) / 4;
return noise ;  /////////////////////////////////////////////////////////////////////////////
}

