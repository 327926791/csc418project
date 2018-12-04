#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, product;
	vp1 = normal[0];
	vp2 = normal[1];
	vp3 = normal[2];
	n1 = point[0];
	n2 = point[1];
	n3 = point[2];
	v1 = ray.direction[0];
	v2 = ray.direction[1];
	v3 = ray.direction[2];
	m1 = ray.origin[0];
	m2 = ray.origin[1];
	m3 = ray.origin[2];
	product = v1 * vp1 + v2 * vp2 + v3 * vp3;

	if (product == 0) {
		return false;
	}
	else {
		t = ((n1 - m1)*vp1 + (n2 - m2)*vp2 + (n3 - m3)*vp3) / product;
		if (t < min_t)
			return false;
		else {
			//std::cout << normal[0] <<" " << normal[1] << " " << normal[2] << " " << std::endl;
			n = normal;
			//std::cout << " true. t= " << t << std::endl;
			return true;
		}
	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

Eigen::Vector3d Plane::set_texture_color(
	Eigen::Vector3d p) const
{
	if (texture_width == 0 ) {
		return this->material->kd;
	}


	double x, y, z, u, v, r, g, b, ratio_u, ratio_v;
	int i, j;

	if (normal(0) != 0) {
		x = p(0);
		y = p(1);
		z = p(2)+10;
		if (z>20 || y>5 ||z<0 ||y<0)
			return material->kd;

		ratio_u = texture_width / 20;
		ratio_v = texture_height / 5;
	}
	
	if (normal(1) != 0) {
		x = p(0) + 10 ;
		y = p(1);
		z = p(2) + 10;
		//std::cout << "x,y,z:" << x << " " << z << " " << y << "\n";

		if (x > 20 || z > 20 || x < 0 || z < 0) {
			std::cout << "out of bound:  "<<x<<" "<<z<< "\n";
			return this->material->kd;
		}
		ratio_u = texture_width / 20;
		ratio_v = texture_height / 20;
	}

	if (normal(2) != 0) {
		x = p(0) + 10;
		y = p(1) + 2;
		z = p(2);
		if (x > 20 || y > 7 || x < 0 || y < 0) {
			std::cout << "out of bound" << x << " " << y << "\n";
			return material->kd;
		}

		ratio_u = texture_width / 20;
		ratio_v = texture_height / 7;
	}
	//std::cout << x<<" "<<y<<"  "<<z<<"\n";
	//return material->kd;

	if (normal(0) != 0) {
		u = z *  ratio_u;
		v = y * ratio_v;
	}
	else if (normal(1) != 0) {
		u = x * ratio_u;
		v = z * ratio_v;
	}
	else if (normal(2) != 0) {
		u = x * ratio_u;
		v = y * ratio_v;
	}
	i = floor(u);
	j = floor(v);
	//i = texture_width - i-1;
	//j = texture_height - j-1;
	r = texture_data[j*texture_width * 4 + i * 4] / 255.0;
	g = texture_data[j*texture_width * 4 + i * 4 + 1] / 255.0;
	b = texture_data[j*texture_width * 4 + i * 4 + 2] / 255.0;

	return Eigen::Vector3d(r, g, b);

}
