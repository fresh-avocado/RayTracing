#include "Rayo.h"
#include "vector.h"

Rayo::Rayo(const vec3& origen) : origen{origen} {}

Rayo::Rayo(const vec3& origen, const vec3& direccion)
    : origen{origen}, direccion{direccion} {
  this->direccion.normalize();
}