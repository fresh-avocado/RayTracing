#include "Mundo.h"

void Mundo::scene1() {
  addObj(new Esfera(vec3::green(), vec3(12, 7, -10), 2, 0.9, 0.1, 8));
  addObj(new Esfera(vec3::blue(), vec3(-15, 7, -10), 2, 0.9, 0.1, 32));
  addObj(new Esfera(vec3::white(), vec3(-22, 7, -10), 2, 0.9, 0.1, 32));
  // red que está más atrás
  addObj(new Esfera(vec3::yellow(), vec3(3, 7, -10), 2, 0.9, 0.1, 32));
  addObj(new Esfera(vec3::pink(), vec3(19, 7, -10), 2, 0.9, 0.1, 32));

  addObj(new Esfera(vec3::green(), vec3(12, 7, -5), 2, 0.9, 1, 8));
  addObj(new Esfera(vec3::blue(), vec3(-15, 7, -5), 2, 0.9, 1, 32));
  addObj(new Esfera(vec3::white(), vec3(-22, 7, -5), 2, 0.9, 1, 32));
  addObj(new Esfera(vec3::red(), vec3(-5, 7, -5), 2, 0.9, 1, 32));
  addObj(new Esfera(vec3::yellow(), vec3(3, 7, -5), 2, 0.9, 1, 32));
  addObj(new Esfera(vec3::pink(), vec3(19, 7, -5), 2, 0.9, 1, 32));

  addObj(new Esfera(vec3::green(), vec3(12, 7, 0), 2, 0.1, 1, 8));
  addObj(new Esfera(vec3::blue(), vec3(-15, 7, 0), 2, 0.1, 1, 32));
  addObj(new Esfera(vec3::white(), vec3(-22, 7, 0), 2, 0.1, 1, 32));
  addObj(new Esfera(vec3::red(), vec3(-5, 7, 0), 2, 0.1, 1, 32));
  addObj(new Esfera(vec3::yellow(), vec3(3, 7, 0), 2, 0.1, 1, 32));
  addObj(new Esfera(vec3::pink(), vec3(19, 7, 0), 2, 0.1, 1, 32));

  addObj(new Esfera(vec3::green(), vec3(12, 7, 5), 2, 0.1, 0.1, 8));
  addObj(new Esfera(vec3::blue(), vec3(-15, 7, 5), 2, 0.1, 0.1, 32));
  addObj(new Esfera(vec3::white(), vec3(-22, 7, 5), 2, 0.1, 0.1, 32));
  addObj(new Esfera(vec3::red(), vec3(-5, 7, 5), 2, 0.1, 0.1, 32));
  addObj(new Esfera(vec3::yellow(), vec3(3, 7, 5), 2, 0.1, 0.1, 32));
  addObj(new Esfera(vec3::pink(), vec3(19, 7, 5), 2, 0.1, 0.1, 32));

  addObj(new Esfera(vec3::green(), vec3(12, 7, 10), 2, 0.5, 0.5, 8));
  addObj(new Esfera(vec3::blue(), vec3(-15, 7, 10), 2, 0.5, 0.5, 32));
  addObj(new Esfera(vec3::white(), vec3(-22, 7, 10), 2, 0.5, 0.5, 32));
  addObj(new Esfera(vec3::red(), vec3(-5, 7, 10), 2, 0.5, 0.5, 32));
  addObj(new Esfera(vec3::yellow(), vec3(3, 7, 10), 2, 0.5, 0.5, 32));
  addObj(new Esfera(vec3::pink(), vec3(19, 7, 10), 2, 0.5, 0.5, 32));

  addObj(new Plano(vec3::blue(), vec3(0, 1, 0), 2, 0.7, 0, 0));

  addObj(new Esfera(vec3::red(), vec3(-5, 7, -10), 2, 0.9, 0.1, 32));
  addLightSource(new Luz(vec3(3, 17, 10), vec3::white(), 1.5));

  camara.renderizar(depthObjects, lightSources);
}

void Mundo::scene2() {
  // addObj(new Esfera(vec3::blue(), vec3(5, 7, 10), 4, 0.9, 0.1, 32, 1));
  // addObj(new Esfera(vec3::blue(), vec3::origin(), 4, 0.9, 0.1, 32, 1));

  // addObj(new Esfera(vec3::yellow(), vec3(-5, 7, 5), 2, 0.9, 0.1, 32));
  addObj(new Esfera(vec3::red(), vec3(0, 7, 0), 4, 0.9, 0.1, 32, 1, 0.1));
  // addObj(new Esfera(vec3::yellow(), vec3(5, 5, 1), 2, 0.9, 0.1, 32));

  addObj(new Plano(vec3(0.4, 0.5, 0.2), vec3(0, 1, 0), 2, 0.7, 0, 0));
  // addObj(new Disk(vec3(10, 10, 10), vec3(1, 1, 1), 5));

  // addLightSource(new Luz(vec3(3, 17, 10), vec3::white(), 1.5));

  camara.renderizar(depthObjects, lightSources);
}

void Mundo::scene3() {
  addObj(new Esfera(vec3(1, 1, 0), vec3(6, 1, 7), 3, 0.9, 0.5, 40));
  addObj(new Esfera(vec3(1, 0.3, 0), vec3(-2, 0, 13), 0.5, 0.9, 0.5, 80));
  addObj(new Esfera(vec3(0.1, 0.7, 1), vec3(-3, -2, 10), 2.5, 0.9, 0.5, 30));
  addObj(new Esfera(vec3(0.5, 0.9, 0.7), vec3(1, 2, 0), 5, 0.9, 0.5, 30));
  addObj(new Esfera(vec3(0.2, 0.2, 0.7), vec3(-2, 10, 6), 3, 0.9, 0.9, 30));
  addObj(new Plano(vec3(0.5, 0.9, 0.9), vec3(0, 1, 0), 2, 0.7, 0, 0));
  // addLightSource(new Luz(vec3(3, 17, 10), vec3::white(), 1.5));

  camara.renderizar(depthObjects, lightSources);
}

void Mundo::scene4() {
  addObj(new Plano(vec3::blue(), vec3(0, 1, 0), 2, 0.7, 0.2, 0));

  addObj(new Cilindro(vec3(0, -4, 10), vec3(0, 8, 10), 7));
  addObj(new Cilindro(vec3(0, -4, 10), vec3(0, 8, 10), 6.5));
  addObj(new Esfera(vec3::red(), vec3(12, 2, 15), 2, 0.1, 0.1, 2, 0, 0));

  addLightSource(new Luz(vec3(0, 1, 10), vec3(1, 1, 0.3), 1.5));
  // addLightSource(new Luz(vec3(10, 15, 10), vec3::white(), 1.5));

  camara.renderizar(depthObjects, lightSources);
}

Mundo::~Mundo() {
  for (auto object : depthObjects) {
    printf("deleting obj...\n");
    delete object;
  }
  for (auto light : lightSources) {
    printf("deleting lightSource...\n");
    delete light;
  }
}