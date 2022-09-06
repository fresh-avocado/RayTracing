//
// Created by hgallegos on 18/08/2022.
//

#ifndef INC_20222_RAYTRACING_OBJETO_H
#define INC_20222_RAYTRACING_OBJETO_H

#include "Rayo.h"
#include "vector.h"

class Objeto {
 public:
  vec3 color;
  float ks, kd, n, refractionIndex;
  // { inter, distInter, ptInter, normalPtInter }
  virtual std::tuple<bool, float, vec3, vec3> interseccion(
      const Rayo& rayo) const = 0;
  virtual ~Objeto() noexcept = default;
};

class Esfera : public Objeto {
 public:
  vec3 centro;
  float radio;
  Esfera(const vec3& color, const vec3& centro, float radio)
      : centro{centro}, radio{radio} {
    this->color = color;
  }
  Esfera(const vec3& color,
         const vec3& centro,
         float radio,
         float kd,
         float ks,
         float n)
      : centro{centro}, radio{radio} {
    this->color = color;
    this->kd = kd;
    this->ks = ks;
    this->n = n;
    this->refractionIndex = 0;
  }
  Esfera(const vec3& color,
         const vec3& centro,
         float radio,
         float kd,
         float ks,
         float n,
         float refractionIndex)
      : centro{centro}, radio{radio} {
    this->color = color;
    this->kd = kd;
    this->ks = ks;
    this->n = n;
    this->refractionIndex = refractionIndex;
  }
  std::tuple<bool, float, vec3, vec3> interseccion(const Rayo& rayo) const;
};

class Plano : public Objeto {
 public:
  // un vector unitario que define la orientacion del plano
  // el origen del plano es siempre vec3::origin()
  vec3 normal;
  // d es
  float d;
  Plano(const vec3& color,
        const vec3& normal,
        float d,
        float kd,
        float ks,
        float refractionIndex)
      : normal{normal}, d{d} {
    this->color = color;
    this->kd = kd;
    this->ks = ks;
    this->refractionIndex = refractionIndex;
  }
  std::tuple<bool, float, vec3, vec3> interseccion(const Rayo& rayo) const;
};

#endif
