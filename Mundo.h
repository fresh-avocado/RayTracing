#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include <vector>

#include "Camara.h"
#include "Luz.h"
#include "Objeto.h"

class Mundo {
 public:
  std::vector<Objeto*> depthObjects;
  std::vector<Luz*> lightSources;
  Camara camara;

  Mundo(const Camara& camara) : camara{camara} {}

  void addObj(Objeto* obj) { depthObjects.push_back(obj); }

  void addLightSource(Luz* luz) { lightSources.push_back(luz); }

  void scene1();
  void scene2();
  void scene3();

  ~Mundo();
};

#endif