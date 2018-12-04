#include "first_hit.h"
#include <iostream>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n, int flag)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	t = -1;
	hit_id = -1;
	double second_min_t = -1;
	Eigen::Vector3d second_n;
	int second_id;
	
	for (int i = 0; i < objects.size(); i++) {
		//std::cout << "object:" << i << "\n";
		Eigen::Vector3d normal;
		double t1;
		//std::cout << "view ray: " << ray.origin << " dir:" << ray.direction << "\n";
		if (objects[i]->intersect(ray, min_t, t1, normal) == true) {
			//std::cout << "hit " << i <<"normal:"<<normal<<" t:"<<t1<<std::endl;
			if (t == -1) {
				t = t1;
				hit_id = i;
				n = normal;
			}
			else if (t1 < t) {
				t = t1;
				n = normal;
				hit_id = i;
			}
		}
	}

	if (t == -1) {
		hit_id = 0;
		return false;
	}
	else if (flag == 0) {
		return true;
	}
	else if (flag == 1 && t < 1) {
		return true;
	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
