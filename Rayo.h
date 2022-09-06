#ifndef RAYO_H
#define RAYO_H

#include "vector.h"

class Rayo {
 public:
  vec3 origen, direccion;
  Rayo() = default;
  Rayo(const vec3& origen);
  Rayo(const vec3& origen, const vec3& direccion);
};

#endif
