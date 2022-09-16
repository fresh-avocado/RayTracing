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
  float ks, kd, kr, n, refractionIndex;
  // { inter, distInter, ptInter, normalPtInter }
  virtual std::tuple<bool, float, vec3, vec3> interseccion(
      const Rayo& rayo) const = 0;
  virtual ~Objeto() noexcept = default;
};

class Esfera : public Objeto {
 public:
  vec3 centro;
  float radio;
  Esfera() = default;
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
         float refractionIndex,
         float kr)
      : centro{centro}, radio{radio} {
    this->color = color;
    this->kd = kd;
    this->ks = ks;
    this->n = n;
    this->refractionIndex = refractionIndex;
    this->kr = kr;
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

class Disk : public Objeto {
  vec3 c, normal;
  float r;

 public:
  Disk(const vec3& c, const vec3& normal, float r)
      : c{c}, normal{normal}, r{r} {
    this->color = vec3::green();
    this->ks = 0.1;
    this->kd = 0.9;
    this->n = 32;
    this->refractionIndex = 0;
  }
  std::tuple<bool, float, vec3, vec3> interseccion(const Rayo& rayo) const;
};

class Cilindro : public Objeto {
  vec3 pa, pb;
  float ra;

 public:
  Cilindro(const vec3& pa, const vec3& pb, float ra) : pa{pa}, pb{pb}, ra{ra} {
    this->color = vec3::white();
    this->ks = 0.1;
    this->kd = 0.9;
    this->n = 30;
    this->refractionIndex = 1;
    this->kr = 0.1;  // FIXME: quizas cambiar
  }
  std::tuple<bool, float, vec3, vec3> interseccion(const Rayo& rayo) const;
};

class Luciernaga : public Objeto {
 public:
  Luciernaga() {}
  std::tuple<bool, float, vec3, vec3> interseccion(const Rayo& rayo) const;
};

#endif
