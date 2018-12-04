#include <Eigen/Core>
#include<iostream>
Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return Eigen::Vector3d(0,0,0);
	Eigen::Vector3d ray, rec;

	ray = in / sqrt(in.dot(in));
	rec = ray - 2 * n.dot(ray) * n;
	return rec;
  ////////////////////////////////////////////////////////////////////////////
}
