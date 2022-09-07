//
// Created by hgallegos on 17/08/2022.
//

#ifndef INC_20222_RAYTRACING_VECTOR_H
#define INC_20222_RAYTRACING_VECTOR_H

#include <math.h>
#include <algorithm>

class vec3 {
 public:
  float x, y, z;

  vec3() { x = y = z = 0; }

  vec3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  static vec3 red() { return vec3(1, 0, 0); }
  static vec3 green() { return vec3(0, 1, 0); }
  static vec3 blue() { return vec3(0, 0, 1); }
  static vec3 origin() { return vec3(0, 0, 0); }
  static vec3 pink() { return vec3(1, 0, 1); }
  static vec3 black() { return vec3(0, 0, 0); }
  static vec3 white() { return vec3(1, 1, 1); }
  static vec3 yellow() { return vec3(1, 1, 0); }

  vec3 operator+(const vec3& v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
  }

  vec3 abs() const {
    return {
        std::abs(x),
        std::abs(y),
        std::abs(z),
    };
  }

  vec3 operator-() const { return vec3(-x, -y, -z); }

  vec3 operator*(const vec3& v) const {
    return vec3(x * v.x, y * v.y, z * v.z);
  }

  vec3 operator*(float f) const { return vec3(x * f, y * f, z * f); }
  vec3 operator/(float f) const { return vec3(x / f, y / f, z / f); }

  vec3 cruz(const vec3& v) const {
    return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }

  float punto(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }

  inline float modulo() const { return sqrt(x * x + y * y + z * z); }

  // volver el vector unitario
  void normalize() {
    float m = modulo();
    x /= m;
    y /= m;
    z /= m;
  }

  // TODO: para qué?
  // para los colores
  void maxToOne() {
    float maxVal = std::max({x, y, z});
    if (maxVal > 1) {
      x /= maxVal;
      y /= maxVal;
      z /= maxVal;
    }
  }

  vec3 operator-(const vec3& v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
  }
};

vec3 operator/(float f, const vec3& v);
vec3 operator*(float f, const vec3& v);
vec3 abs(const vec3& v);
vec3 step(const vec3& v1, const vec3& v2);
vec3 sign(const vec3& v);
template <typename T>
int sgn(const T& val) {
  return (T(0) < val) - (val < T(0));
}

#endif  // INC_20222_RAYTRACING_VECTOR_H
