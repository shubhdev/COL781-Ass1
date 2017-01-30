#ifndef RAY_H
#define RAY_H 
#include "vector.h"
class Ray {
 public:
  Vector p;
  Vector dir;
  Ray(const Vector& pt, const Vector& d): p(pt), dir(d) {
    dir /= dir.mag();
  }
};

ostream& operator<<(ostream& out, const Ray& r) {
  out << "(" << r.p << ", " << r.dir << ")";
}
#endif