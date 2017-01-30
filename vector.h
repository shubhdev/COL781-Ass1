#ifndef VECTOR_H
#define VECTOR_H
#include "constants.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
using namespace std;

class Vector{
 public:
  double x;
  double y;
  double z;
  Vector() {
    x = y = z = 0;
  }
  Vector(double _x, double _y, double _z):x(_x),y(_y),z(_z){}
  Vector(const Vector& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
  }
  Vector operator+(const Vector& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }
  Vector operator-(const Vector& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }
  double operator*(const Vector& other) const {
    return x*other.x + y*other.y +  z*other.z;
  }
  Vector& operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  Vector& operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  Vector operator*(double scalar) const {
    return {x*scalar, y*scalar, z*scalar};
  }
  Vector& operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }
  Vector operator/(double scalar) const {
    assert((abs(scalar) > EPS) && "Division of vector by 0!");
    return {x/scalar, y/scalar, z/scalar};
  }
  Vector& operator/=(double scalar) {
    assert((abs(scalar) > EPS) && "Division of vector by 0!");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }
  double magsq() const {
    return (x*x + y*y + z*z);
  }
  double mag() const {
    return sqrt(magsq());
  }
  void normalize() {
    double m = mag();
    assert(m > EPS);
    x /= m;
    y /= m;
    z /= m;
  }

};
ostream& operator<<(ostream& out, const Vector& vec) {
  out << "<" << vec.x << "," << vec.y << "," << vec.z << ">";
  return out;
}
#endif