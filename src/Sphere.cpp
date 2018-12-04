#include "Sphere.h"
#include "Ray.h"
#include <iostream>
#include <cmath>

#define PI 3.1415926

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double k, t1, t2;
	Eigen::Vector3d d, e, c;
	d = ray.direction;
	e = ray.origin;
	c = center;
	k = (d.dot(e - c)) * (d.dot(e - c)) - d.dot(d) * ((e - c).dot(e - c) - radius * radius);
	//std::cout << "r: " << radius << " k: " << k << std::endl;
	//std::cout << d.dot(e - c) * d.dot(e - c) << "   "<< d.dot(d) << "   " << ((e - c).dot(e - c) - radius*radius) << std::endl;
	if (k < 0) {
		return false;
	}
	else if (k == 0) {
		t = (-d.dot(e - c)) / (d.dot(d));
		if (t >= min_t) {
			n = (e + t * d - c) / radius;
			//std::cout << "k == 0" << std::endl;
			return true;
		}
		else {
			return false;
		}

	}
	else if (k > 0) {
		t1 = (-d.dot(e - c) + std::sqrt(std::pow(d.dot(e - c), 2) - d.dot(d) * ((e - c).dot(e - c) - radius * radius))) / (d.dot(d));
		t2 = (-d.dot(e - c) - std::sqrt(std::pow(d.dot(e - c), 2) - d.dot(d) * ((e - c).dot(e - c) - radius * radius))) / (d.dot(d));
		t = std::min(t1, t2);
		if (t < min_t) {
			t = std::max(t1, t2);
			if (t < min_t) {
				return false;
			}
			else {
				n = (e + t * d - c) / radius;
				//std::cout << "k > 0, max" << std::endl;
				return true;
			}
		}
		else {
			n = (e + t * d - c) / radius;
			//std::cout << "k > 0, min" << std::endl;
			return true;
		}
	}

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

Eigen::Vector3d Sphere::set_texture_color(
  Eigen::Vector3d p) const
{

	double u, v;
	double ratio;

	if (texture_width == 0) {
		//std::cout << "shpere has no texture\n";
		return material->kd;
	}

	ratio = 0.5/radius;

	p = ratio * (p - center + Eigen::Vector3d(0, radius, 0));

	if (p(0) > 0 && p(2) > 0) {  // first region
		u = texture_width * (asin(p(2) / sqrt(pow(p(0), 2) + pow(p(2), 2)))) / (2*PI);
	}
	else if (p(0) < 0 && p(2) > 0) { // second region
		u = texture_width * (PI - asin(p(2) / sqrt(pow(p(0), 2) + pow(p(2), 2)))) / (2*PI);
	}
	else if (p(0) < 0 && p(2) < 0) {
		u = texture_width * (3*PI/2 + asin(p(2)/sqrt(pow(p(0), 2) + pow(p(2), 2)))) / (2 * PI);
	}
	else if (p(0) > 0 && p(2) < 0) { // fouth region
		u = texture_width * (2*PI + asin(p(2) / sqrt(pow(p(0), 2) + pow(p(2), 2)))) / (2 * PI);
	}

	v = p(1)*(texture_height);

	double r, g, b;
	int x, y;
	x =  floor(u);
	y =  floor(v);
	r = texture_data[y*texture_width * 4 + x * 4]/ 255.0;
	g = texture_data[y*texture_width * 4 + x * 4 + 1]/ 255.0;
	b = texture_data[y*texture_width * 4 + x * 4 + 2]/ 255.0;
	//std::cout << "x, y" << x << " " << y << " " << texture_width <<" "<<texture_height<< "\n";
	return Eigen::Vector3d(r, g, b);
	//return this->material->kd;
}

