#include "TriangleSoup.h"
#include "Triangle.h"
#include "first_hit.h"
#include <iostream>

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	int hit_id;
	//std::cout << triangles.size() << std::endl;
	//for (int i = 0; i < triangles.size(); i++) {
	if (first_hit(ray, min_t, triangles, hit_id, t, n, 0) == true) {
		//std::cout << "hit id:" << hit_id << "texture width:"<<texture_width<<"\n";
		if (texture_width > 0) {
			material->kd = Eigen::Vector3d(texture_data[hit_id*3]/255.0, texture_data[hit_id*3+1]/255.0, texture_data[hit_id*3+2]/255.0);
			//std::cout << "texture kd: " << material->kd<<"\n";
		}
		return true;
	}
	else {
		return false;
	}
	//}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

Eigen::Vector3d TriangleSoup::set_texture_color(
	Eigen::Vector3d p) const
{
	//std::cout << "retrun kd:" << material->kd << "\n";
	return this->material->kd;
}