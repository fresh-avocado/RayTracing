//
// Created by hgallegos on 17/08/2022.
//

#include "vector.h"

vec3 operator/(float f, const vec3& v) {
  if (v.x == 0 || v.y == 0 || v.z == 0) {
    // std::cout << "Hay cero";
  }
  float tx = (v.x == 0) ? f / 0.01 : f / v.x;
  float ty = (v.y == 0) ? f / 0.01 : f / v.y;
  float tz = (v.z == 0) ? f / 0.01 : f / v.z;

  return vec3(tx, ty, tz);
}
vec3 operator*(float f, const vec3& v) {
  return vec3(f * v.x, f * v.y, f * v.z);
}