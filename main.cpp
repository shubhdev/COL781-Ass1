#include "vector.h"
#include "object.h"
#include "sphere.h"
#include "constants.h"
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

class Renderer {
  public:
  int MAX_DEPTH;
  Vector eye;
  Renderer(): MAX_DEPTH(5) {}
  double getFirstIntersection(const Ray& ray, const vector<Object*> objects,
                              Object** cobj) {
    double t = INF;
    for(Object* obj : objects) {
      double ti = obj->closest_intersection(ray);
      if(ti < 0) continue;
      if(ti < t) {
        t = ti;
        if(cobj != nullptr) *cobj = obj;
      }
    }
    return t;
  }

  Color getPointColor(const Vector& point, Object const* cobj, const Vector& light_source,
                      const vector<Object*>& objects) {
    Ray light_ray(point, light_source - point);
    light_ray.p += light_ray.dir*EPS; // increment the point slightly ahead.
    if(getFirstIntersection(light_ray, objects, nullptr) < INF) return cobj->color*0.1;
    Vector n = cobj->getNormal(point);
    double dshade = max(0.0,n*light_ray.dir);
    Vector h = (eye - point);
    h.normalize();
    h += light_ray.dir;
    h.normalize();
    double specshade = pow(max(0.0,n*h),10);
    return cobj->color*(0.2 + dshade*0) + Color(1,1,1)*(specshade);
  }

  Ray get_reflected_ray(const Vector& in, const Vector& normal, const Vector& poi) {
    double c = -(normal*in);
    return Ray(poi, in + normal*(2*c));
  }

  Ray get_refracted_ray(const Vector& in, const Vector& normal, const Vector& poi) {

  }
  Color getColor(const Ray& ray, const vector<Object*>& objects, const Vector& light_source, int depth = 0) {
    Object *cobj = nullptr;
    double t = getFirstIntersection(ray, objects, &cobj);
    if(cobj == nullptr) {
      return Color(0.3,0.3,0.3);  // Background color.
    }
    Vector intersc = ray.p + ray.dir*t;
    Color final_color = getPointColor(intersc, cobj, light_source, objects);
    int n_color = 1;
    if(depth < MAX_DEPTH) {
      if(cobj->is_reflective) {
        Ray reflected_ray = get_reflected_ray(ray.dir, cobj->getNormal(intersc), intersc);
        reflected_ray.p += reflected_ray.dir*EPS;
        final_color = getColor(reflected_ray, objects, light_source, depth+1);
      }
    }
    return final_color;
  }

  vector<vector<Color>> createScene(double Z, double fovx, double fovy,
                                    const vector<Object*>& objects,
                                    const Vector& light_source,
                                    pair<int,int> res) {
    vector<vector<Color>> rendered_scene;
    eye = {0,0,-Z};
    double width = abs(Z)*tan(fovx*0.5);
    double height = abs(Z) *tan(fovy*0.5);
    double xmin = -width;
    double xmax = width;
    double ymin = -height;
    double ymax = height;
    double xstep = (xmax-xmin)/res.first;
    double ystep = (ymax-ymin)/res.second;
    double y,x;
    int i,j;
    rendered_scene.resize(res.second);
    for(i = 0, x = xmin; i < res.first; i++, x += xstep) {
      rendered_scene[i].resize(res.first);
      for(j = 0, y = ymax; j < res.second; j++, y -= ystep) {
        Ray r(eye, {x,y,Z});
        rendered_scene[i][j] = getColor(r, objects, light_source);
      }
    }
    return rendered_scene;
  }
};
int main() {
  vector<Object*> objects;
  Sphere s1({-25,0,-50}, 25), s2({30,0,-50}, 25), s3({30,50,-50}, 15);
  s1.color = {0,0,1};
  s2.color = {0,1,0};
  s1.is_reflective = true;
  objects.push_back(&s1);
  s1.specular_exp = 10;
  objects.push_back(&s2);  
  objects.push_back(&s3);  

  Renderer rengine;
  // cout << rengine.getColor(Ray({0,0,-200}, {0,0.5,200}), objects, {0,200,0}) << endl;
  vector<vector<Color>> scene = rengine.createScene(-200, 60.0*PI/180.0f, 60.0*PI/180.0f,
                                                    objects, {-50,0,-20}, {600,600});
  cout << 600 << " " << 600 << endl;
  for(int i = 0; i < 600; i++) {
    for(int j = 0; j < 600; j++) {
      cout << scene[i][j].x << " " << scene[i][j].y << " " << scene[i][j].z << "\n";
    }
  }
}