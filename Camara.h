//
// Created by hgallegos on 17/08/2022.
//

#ifndef INC_20222_RAYTRACING_CAMARA_H
#define INC_20222_RAYTRACING_CAMARA_H

#include <cmath>
#include <map>
#include <vector>

#include "CImg.h"
#include "Luz.h"
#include "Objeto.h"
#include "vector.h"

using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
 public:
  // fov: ángulo de apertura de la cámara
  // w: ancho en píxeles de la pantalla
  // h: alto en píxeles de la pantalla
  // _near: distancia de la cámara a la pantalla
  float fov, w, h, _near;
  // center: a qué punto de la pantalla la cámara está mirando
  // eye: coordenada de dónde está la cámara
  // up: giro en un eje sobre 'center'
  vec3 eye, center, up;
  // f: _near
  // a: alto real de la pantalla en unidades de _near
  // b: ancho real de la pantalla en unidades de _near
  float f, a, b;
  // xe:
  // ye:
  // ze:
  vec3 xe, ye, ze;
  // pImg: lo que la cámara ve
  CImg<BYTE>* pImg;

  Camara(float fov,
         float w,
         float h,
         float _near,
         const vec3& eye,
         const vec3& center,
         const vec3& up)
      : fov{fov}, w{w}, h{h}, _near{_near}, eye{eye}, center{center}, up{up} {
    f = _near;
    a = 2 * f * tan(fov * M_PI / 360);
    b = w / h * a;
    ze = eye - center;
    ze.normalize();
    xe = up.cruz(ze);
    xe.normalize();
    ye = ze.cruz(xe);
    // TODO: qué es (1, 10)
    pImg = new CImg<BYTE>(w, h, 1, 10);
  }
  Camara(const Camara& other) = default;
  void renderizar(const std::vector<Objeto*>& depthObjects,
                  const std::vector<Luz*>& lightSources);
  inline void paintPixel(int x, int y, const vec3& color);
  vec3 calcularColor(const Rayo& rayo,
                     const std::vector<Objeto*>& objetos,
                     const std::vector<Luz*>& luces,
                     int prof);
  float clamp(float min, float max, float x) const {
    if (x > max)
      return max;
    if (x < min)
      return min;
    return x;
  }
  vec3 refractar(const vec3& I, const vec3& N, float ior) {
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0) {
      cosi = -cosi;
    } else {
      std::swap(etai, etat);
      n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3(0, 0, 0) : eta * I + (eta * cosi - sqrtf(k)) * n;
  }
  float fresnel(const vec3& I, const vec3& N, float ior) {
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    if (cosi > 0) {
      std::swap(etai, etat);
    }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    float kr;
    // Total internal reflection
    if (sint >= 1) {
      kr = 1;
    } else {
      float cost = sqrtf(std::max(0.f, 1 - sint * sint));
      cosi = fabsf(cosi);
      float Rs =
          ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
      float Rp =
          ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
      kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given
    // by: kt = 1 - kr;
    return kr;
  }
};

#endif  // INC_20222_RAYTRACING_CAMARA_H
