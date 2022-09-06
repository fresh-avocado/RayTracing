#ifndef LUZ_H
#define LUZ_H

#include "vector.h"

class Luz {
 public:
  vec3 origen, color;
  Luz(const vec3& origen, const vec3& color) : origen{origen}, color{color} {}
};

#endif