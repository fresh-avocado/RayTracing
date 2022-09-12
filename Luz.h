#ifndef LUZ_H
#define LUZ_H

#include "Objeto.h"
#include "Rayo.h"
#include "vector.h"

class Luz {
 public:
  vec3 centro, color;
  Esfera e1, e2;
  float rI, rE;
  Luz() = delete;
  Luz(const vec3& centro, const vec3& color, float rI, float rE)
      : centro{centro}, color{color}, rI{rI}, rE{rE} {
    e1 = Esfera(this->color, this->centro, this->rI, 0, 0, 0);
    e2 = Esfera(this->color, this->centro, this->rE, 0, 0, 0);
  }
  std::tuple<bool, float> interseccion(const Rayo& rayo) const;
};

#endif