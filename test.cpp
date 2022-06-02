#include <iostream>
#include <fstream>
int width = 10;
int height = 10;
int fun () {

  /*  for (int pix = 0; pix<width*height; pix++) { // actual rendering loop
        float dir_x =  (pix%width + 0.5) -  width/2.;
        float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
        float dir_z = -height/(2.*tan(fov/2.));
        framebuffer[pix] = cast_ray(vec3{0,0,0}, vec3{dir_x, dir_y, dir_z}.normalized());
    }
*/
    std::cout << "shit";
    
    std::ofstream ofs("./out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < 100 * 3; i++) {
        for (int chan : {0,1,2})
            ofs << (char)(123);
    }
    return 0;
}