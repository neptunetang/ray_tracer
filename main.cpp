#include "ray.h"
#include <iostream>
#include<fstream>

float hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin_point() - center;
    auto a = r.direction().squared_lenght();
    auto half_b = dot(oc, r.direction());
    auto c = oc.squared_lenght() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

vec3 color(const ray& r) {
    auto t = hit_sphere(vec3(0,0,-1), 0.5, r);
    if (t > 0.0){
        vec3 normal = unit_vec(r.point_at(t) - vec3(0,0,-1));
        return 0.5*vec3(normal.x()+1, normal.y()+1, normal.z()+1);
    }
    vec3 unit_direction = unit_vec(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int width=400, height=200;
    ofstream img ("4.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            auto u = double(i) / width;
            auto v = double(j) / height;
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = static_cast<int>(255.999 * col[0]);
            int ig = static_cast<int>(255.999 * col[1]);
            int ib = static_cast<int>(255.999 * col[2]);
            img << ir << ' ' << ig << ' ' << ib << endl;
        }
    }
}