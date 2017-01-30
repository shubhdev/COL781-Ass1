#include "sphere.h"
#include "ray.h"
#include <iostream>

using namespace std;

int main() {

  Sphere s({0,0,0},1);
  cout << s << endl;
  Ray r({0.5,1,0}, {1,0,0});
  double t = s.closest_intersection(r);
  cout << t;
  return 0;
}