#ifndef SPHERE_H
#define SPHERE_H

#include "Sphere.h"
#include "Object.h"
#include <Eigen/Core>

class Sphere : public Object
{
  public:
    Eigen::Vector3d center;
    double radius;
	std::string texture;
	std::vector<unsigned char> texture_data;
	int texture_width, texture_height;
  public:
    // Intersect sphere with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    bool intersect(
      const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const;
	Eigen::Vector3d set_texture_color(Eigen::Vector3d p) const;
};


#endif
