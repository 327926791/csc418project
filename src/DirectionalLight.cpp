#include "DirectionalLight.h"
#include <limits>
#include <iostream>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
	d = -(DirectionalLight::d);
	d = d / sqrt(d.dot(d));
	max_t = 999999;
  ////////////////////////////////////////////////////////////////////////////
}

