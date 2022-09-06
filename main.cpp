#include <iostream>

#include "Camara.h"
#include "Mundo.h"

int main() {
  //   float fov,
  //   float w,
  //   float h,
  //   float _near,
  //   const vec3& eye,
  //   const vec3& center,
  //   const vec3& up,
  Camara c(60, 600, 400, 3, vec3(3, 20, 30), vec3::origin(), vec3(0, 1, 0));
  // Camara c(60, 600, 400, 4, vec3(3, 20, 30), vec3(0, 4, 0), vec3(0, 1, 0));

  Mundo mundo(c);

  // mundo.scene1();

  mundo.scene2();

  // mundo.scene3();

  return 0;
}
