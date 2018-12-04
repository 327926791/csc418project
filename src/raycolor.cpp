#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>

bool raycolor(
	const Ray & ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> > & objects,
	const std::vector< std::shared_ptr<Light> > & lights,
	const int num_recursive_calls,
	Eigen::Vector3d & rgb, int flag)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	rgb = Eigen::Vector3d(0, 0, 0);


	int hit_id = 0;
	double t;
	Eigen::Vector3d n, km, ref, refRGB;
	Ray refRay;

	if (first_hit(ray, min_t, objects, hit_id, t, n, flag)) {
		rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights,flag);
		//std::cout << "hit object, normal " << n << " rgb:" << rgb << "\n";
		// get reflect color
		
		
		km = objects[hit_id]->material->km;    //reflect coefficence ;
		if (km != Eigen::Vector3d(0, 0, 0)) {  
			if (num_recursive_calls < 2) {
				// get reflect ray
				ref = reflect(ray.direction, n);
				refRay.direction = ref;
				refRay.origin = ray.origin + t * ray.direction;

				raycolor(refRay, 0.01, objects, lights, num_recursive_calls+1, refRGB,1);
				refRGB(0) = refRGB(0)*km(0);
				refRGB(1) = refRGB(1)*km(1);
				refRGB(2) = refRGB(2)*km(2);
				rgb = rgb + refRGB;
			}
		} 
		
		return true;
	}
    return false;
  ////////////////////////////////////////////////////////////////////////////
}
