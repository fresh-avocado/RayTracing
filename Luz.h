#ifndef LUZ_H
#define LUZ_H

#include "Objeto.h"
#include "Rayo.h"
#include "vector.h"

class Luz {
 public:
  vec3 centro, color;
  Esfera esfera;
  float radio;
  Luz() = delete;
  Luz(const vec3& centro, const vec3& color, float radio, float rE)
      : centro{centro}, color{color}, radio{radio} {
    esfera = Esfera(this->color, this->centro, this->radio, 0, 0, 0);
  }
  std::tuple<bool, float> interseccion(const Rayo& rayo) const;
};

#endif