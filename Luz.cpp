#include <cstdlib>

#include "Luz.h"

std::tuple<bool, float> Luz::interseccion(const Rayo& rayo) const {
  auto [rayIntersects, distanciaAlPuntoDeInterseccion, puntoDeInterseccion,
        normalAlPuntoDeInterseccion] = e1.interseccion(rayo);
  if (rayIntersects) {
    double distX = puntoDeInterseccion.x - this->centro.x;
    double distY = puntoDeInterseccion.y - this->centro.y;
    float dist = sqrt(distX * distX + distY * distY);
    float normalizedDist = 1 - abs((dist) / -rI);
    return std::make_tuple(true, normalizedDist > 0.5 ? 1 : normalizedDist);
  } else {
    return std::make_tuple(false, 0);
  }
  // if (rayIntersects) {
  //   return std::make_tuple(true, 1.0f);
  // } else {
  //   auto [secondRayIntersects, t, pI, N] = e2.interseccion(rayo);
  //   if (secondRayIntersects) {
  //     double distX = pI.x - this->centro.x;
  //     double distY = pI.y - this->centro.y;
  //     float dist = sqrt(distX * distX + distY * distY);
  //     float normalizedDist = abs((dist - rI) / (rI - rE));
  //     printf(" %f ", (1 - normalizedDist));
  //     return std::make_tuple(true, (1 - normalizedDist));
  //   } else {
  //     return std::make_tuple(false, 0);
  //   }
  // }
}