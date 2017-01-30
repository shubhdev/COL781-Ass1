#ifndef SPHERE_H
#define SPHERE_H
#include "object.h"
#include "ray.h"
#include "constants.h"
#include <fstream>
#include <cmath>
#include <cassert>

class Sphere: public Object {
 public:
  Vector center;
  double rad;
  Sphere(const Vector& c, double r): center(c), rad(r) {
    is_reflective = false;
    is_refractive = false;
    specular_exp = 1;
  }
  virtual double closest_intersection(const Ray& ray) const override {
    Vector po = center - ray.p;
    double PB = po*ray.dir;
    double POsq = po.magsq();
    double OBsq = POsq - PB*PB;
    double ABsq = rad*rad - OBsq;
    if(ABsq < 0) return -1;
    if(POsq > rad*rad) {
      if(PB < 0) return -1;
      return (PB - sqrt(ABsq));
    }
    return PB + sqrt(ABsq);
  }
  virtual Vector getNormal(const Vector& p) const override {
    // Assert that the point is indeed on the sphere.
    Vector n = p - center;
    assert(abs(n.magsq() - rad*rad) < EPS);
    n /= n.mag();
    return n;
  }
};
ostream& operator<<(ostream& out, const Sphere& s) {
  out << "(" << s.center << ", " << s.rad << ")";
}
#endif