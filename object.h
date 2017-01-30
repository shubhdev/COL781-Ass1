#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "ray.h"
class Object {
 public:
  bool is_reflective;
  bool is_refractive;
  double refraction_coeff;
  double specular_exp;
  Color color;
  virtual double closest_intersection(const Ray& ray) const = 0;
  virtual Vector getNormal(const Vector& p) const = 0; // Return normal to the object at point p.
};
#endif