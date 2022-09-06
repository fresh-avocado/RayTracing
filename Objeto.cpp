//
// Created by hgallegos on 18/08/2022.
//

#include <cmath>
#include <limits>
#include <tuple>

#include "Objeto.h"

std::tuple<bool, float, vec3, vec3> Esfera::interseccion(
    const Rayo& rayo) const {
  vec3 d = rayo.direccion;
  vec3 o_c = rayo.origen - this->centro;

  float a = d.punto(d);
  float b = 2.0f * d.punto(o_c);
  float c = o_c.punto(o_c) - this->radio * this->radio;

  float det = b * b - 4 * a * c;
  if (det >= 0) {
    float sqrtDet = sqrt(det);
    float aTimesTwo = (2 * a);
    float t1 = (-b - sqrtDet) / aTimesTwo;
    float t2 = (-b + sqrtDet) / aTimesTwo;
    // obtener la raíz más cercana al rayo
    float t = std::fmin(t1, t2);
    if (t <= 0) {
      return std::make_tuple(false, t, vec3::origin(), vec3::origin());
    }
    // porque la interseccion está a
    vec3 puntoDeInterseccion = rayo.origen + t * rayo.direccion;
    vec3 normal = puntoDeInterseccion - centro;
    normal.normalize();
    return std::make_tuple(true, t, puntoDeInterseccion, normal);
  }
  return std::make_tuple(false, std::numeric_limits<float>::min(),
                         vec3::origin(), vec3::origin());
}

std::tuple<bool, float, vec3, vec3> Plano::interseccion(
    const Rayo& rayo) const {
  float t = -(normal.punto(rayo.origen) + d) / normal.punto(rayo.direccion);
  if (t > 0) {
    vec3 puntoDeInterseccion = rayo.origen + 2 * t * rayo.direccion;
    // la normal del plano es igual a la normal del punto de interseccion
    // `normal` es la direccion del vector normal
    return std::make_tuple(true, t, puntoDeInterseccion, normal);
  } else {
    return std::make_tuple(false, std::numeric_limits<float>::max(),
                           vec3::origin(), vec3::origin());
  }
}

// TODO: vec3 debería ser origen, direccion y getPointAtDistance(float t) ->
// point3d