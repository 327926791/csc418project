#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
//#include "write_png.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include "Box.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>

int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  // Read a camera and scene description from given .json file
  read_json(
    argc<=1?"../../shared/data/my.json":argv[1],
    camera,
    objects,
    lights);

  int width =  1920;
  int height = 1080;
  std::vector<unsigned char> rgb_image(3*width*height);
  std::vector<unsigned char> rgba_image(4*width*height);
  std::cout << "...........read json done.........\n";
  // For each pixel (i,j)
  for(unsigned i=0; i<height; ++i) 

  {
    for(unsigned j=0; j<width; ++j)
    {
      // Set background color
      Eigen::Vector3d rgb(0,0,0);
	  Eigen::Vector4d rgba(0, 0, 0, 0);

      // Compute viewing ray
      Ray ray;
      viewing_ray(camera,i,j,width,height,ray);
      
      // Shoot ray and collect color
      raycolor(ray,1.0,objects,lights,0,rgb,0);

      // Write double precision color into image
      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      rgba_image[0+4*(j+width*i)] = 255.0*clamp(rgb(0));
      rgba_image[1+4*(j+width*i)] = 255.0*clamp(rgb(1));
      rgba_image[2+4*(j+width*i)] = 255.0*clamp(rgb(2));
	  rgba_image[3+4 * (j + width*i)] = 255;
	  rgb_image[0 + 3 * (j + width*i)] = 255.0*clamp(rgb(0));
	  rgb_image[1 + 3 * (j + width*i)] = 255.0*clamp(rgb(1));
	  rgb_image[2 + 3 * (j + width*i)] = 255.0*clamp(rgb(2));

    }
  }

  unsigned char *output = (unsigned char*)malloc(width*4*height * sizeof(unsigned char));

  for (int i = 0; i < height*width*4; i++){
	  output[i] = rgba_image[i];
  }

  std::cout << "write rgb to rgb.png \n";
  stbi_write_png("rgb.png", width, height, 4, output, 0);
  //write_ppm("rgb.ppm",rgb_image,width,height,3);
}
