#include "Box.h"
#include "Ray.h"
#include <iostream>
#include <vector>

double min(double a, double b) {
	return a < b ? a : b;
}

double max(double a, double b) {
	return a > b ? a : b;
}

bool Box::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
		double x_min, y_min, z_min, x_max, y_max, z_max, xd, yd, zd, xe, ye, ze;
		double txmin, txmax, tymin, tymax, tzmin, tzmax;
		std::vector<Eigen::Vector3d> normal;
		int n_id, normal_x, normal_y, normal_z;
		//std::cout << "........ray hit box............"<<lb<<"  "<<rt<<"\n";

		normal.push_back(Eigen::Vector3d(-1,0,0));
		normal.push_back(Eigen::Vector3d(1, 0, 0));
		normal.push_back(Eigen::Vector3d(0, -1, 0));
		normal.push_back(Eigen::Vector3d(0, 1, 0));
		normal.push_back(Eigen::Vector3d(0, 0, -1));
		normal.push_back(Eigen::Vector3d(0, 0, 1));


		t = -1;
		x_min = lb(0);
		y_min = lb(1);
		z_min = lb(2);
		x_max = rt(0);
		y_max = rt(1);
		z_max = rt(2);

		xd = ray.direction(0);
		yd = ray.direction(1);
		zd = ray.direction(2);

		xe = ray.origin(0);
		ye = ray.origin(1);
		ze = ray.origin(2);

		//std::cout << "ray:" << ray.direction << " ray org: " << ray.origin << "\n";

		if (xd>0) {
			txmin = (x_min - xe) / xd;
			txmax = (x_max - xe) / xd;
			normal_x = 0;
		}
		else if (xd < 0) {
			txmin = (x_max - xe) / xd;
			txmax = (x_min - xe) / xd;
			normal_x = 1;
		}
		else {
			txmin = 0;
			txmax = 0;
		}

		if (yd>0) {
			tymin = (y_min - ye) / yd;
			tymax = (y_max - ye) / yd;
			normal_y = 2 ;
		}
		else if (yd < 0){
			tymin = (y_max - ye) / yd;
			tymax = (y_min - ye) / yd;
			normal_y = 3;
		}
		else {
			tymin = tymax = 0;
		}

		if (zd>0) {
			tzmin = (z_min - ze) / zd;
			tzmax = (z_max - ze) / zd;
			normal_z = 4;
		}
		else if (zd < 0) {
			tzmin = (z_max - ze) / zd;
			tzmax = (z_min - ze) / zd;
			normal_z = 5;
		}
		else {
			tzmin = tzmax = 0;
		}

		double tmin, tmax;
		if (txmin > tymin) {
			tmin = txmin;
			n_id = normal_x;
		}
		else if (txmin == tymin) {
			tmin = txmin;
			n_id = 6;
		}
		else{
			tmin = tymin;
			n_id = normal_y;
		}

		if (tmin < tzmin) {
			tmin = tzmin;
			n_id = normal_z;
		}
		else if (tmin == tzmin)
			n_id = 7;

		//tmin = max(max(txmin, tymin), tzmin);
		tmax = min(min(txmax, tymax), tzmax);

		if (tmin > tmax || tmax < 0 || tmin < min_t)
			return false;
		else  {
			t = tmin;
			if (n_id == 6) {
				std::cout << "this is edge\n";
				n = normal[normal_x] + normal[normal_y];
			}
			else if (n_id == 7) {
				std::cout << "this is corner\n";
				n = normal[normal_x] + normal[normal_y] + normal[normal_z];
			}
			else 
			    n = normal[n_id];
			n.normalize();
			//std::cout << "hit " << n << " by " << t <<" min_t:"<<min_t<<"\n";
			//std::cout << "xmin " << txmin<<" "<<x_min<<" "<<xe<<" "<<y_min<<" "<<ye <<" "<<xd<<" "<<yd<< " ymin " << tymin << " zmin:" << tzmin << "\n";
			return true;
		}
  ////////////////////////////////////////////////////////////////////////////
}

Eigen::Vector3d Box::set_texture_color(
	Eigen::Vector3d p) const
{
	double x, y, z, h, l, w, r, g, b;
	double u, v;
	int i, j;

	if (texture_data.size() == 0) {
	    return material->kd;
    }


	p = p - lb;          // move lb to (0, 0, 0)
	h = rt(1) - lb(1);   // y coordinate
	w = rt(2) - lb(2);   // z coordinate
	l = rt(0) - lb(0);   // x coordinate
	x = p(0);
	y = p(1);
	z = p(2);

	//std::cout << "h,w,l,x,y,z:  " << h << " " << w << " " << l << " " << x << " " << y << " " << z << "\n";
	double ratio_u = texture_width / (2 * w + 2 * l);
	double ratio_v = texture_height / (2 * w + h);

	if (x >= 0 && x <= l  && z >= 0 && z <= w && y <0.000001) {
		u = (w + x)* ratio_u;
		v = z * ratio_v ;
	}
	else if (abs(x-l)< 0.000001 && y >= 0 && y <= h && z >= 0 && z <= w) {
		u = (l + 2 * w - z)* ratio_u; 
		v = (y + w) * ratio_v;
	}
	else if (x >= 0 && x <= l && y >= 0 && y <= h && abs(z - w) < 0.0001) {
		//std::cout << "...............hit\n";
		u = (w+x) * ratio_u;
		v = (y+w) * ratio_v;
	}
	else if (x < 0.000001 && y >= 0 && y <= h && z >= 0 && z <= w) {
		u = z * ratio_u;
		v = y * ratio_v;
	}
	else if (x >= 0 && x <= l && y >= 0 && y <= h && z < 0.0001) {
		u = (w + x)* ratio_u;
		v = (w - z + h + w) * ratio_v;
	}
	else if (x >= 0 && x <= l  && z >= 0 && z <= w && abs(y- h)<0.0001) {
		u = (2*w +l + l- x) * ratio_u;
		v = (w - z + h + w) * ratio_v;
	}
	else {
		std::cout << " not in the bound\n";
	}

	i = floor(u);
	j = floor(v);
	r = texture_data[j*texture_width * 4 + i* 4] / 255.0;
	g = texture_data[j*texture_width * 4 + i * 4 + 1] / 255.0;
	b = texture_data[j*texture_width * 4 + i * 4 + 2] / 255.0;
	//std::cout << "i, j: " << i << " " << j << "\n";
	//std::cout << "r, g, b:" << r << " " << g << " " << b << "\n";
	return Eigen::Vector3d(r, g, b);
}
