#include "Camara.h"
#include "Luz.h"
#include "Objeto.h"

void Camara::renderizar(const std::vector<Objeto*>& depthObjects,
                        const std::vector<Luz*>& lightSources) {
  CImgDisplay dis_img(*pImg, "Basic RayTracing");
  // Algoritmo de Ray Tracing
  Rayo rayo(eye);
  Luz luz(vec3(10, 30, 20), vec3(1, 1, 1));

  // para cada pixel lanzar un rayo desde el ojo
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      // TODO: explicación de la fórmula de 'dirección'?
      rayo.direccion =
          -f * ze + a * (y / h - 0.5) * ye + b * (x / w - 0.5) * xe;
      rayo.direccion.normalize();
      vec3 color = calcularColor(rayo, depthObjects, lightSources, 1);
      paintPixel(x, y, color);
    }
    dis_img.render(*pImg);
    dis_img.paint();
  }
  while (!dis_img.is_closed()) {
    dis_img.wait();
  }
}

vec3 Camara::calcularColor(const Rayo& rayo,
                           const std::vector<Objeto*>& objetos,
                           const std::vector<Luz*>& luces,
                           int prof) {
  vec3 color = vec3::black();
  if (prof > 7) {
    return color;
  }
  float minT = std::numeric_limits<float>::max();
  vec3 N = vec3::origin();
  bool intersects = false;
  Objeto* objInterseccionado = nullptr;

  for (auto obj : objetos) {
    auto [rayIntersects, distanciaAlPuntoDeInterseccion, puntoDeInterseccion,
          normalAlPuntoDeInterseccion] = obj->interseccion(rayo);
    if (rayIntersects) {
      if (distanciaAlPuntoDeInterseccion < minT) {
        intersects = true;
        minT = distanciaAlPuntoDeInterseccion;
        N = normalAlPuntoDeInterseccion;
        objInterseccionado = obj;
        continue;
      }
    }
  }
  if (intersects) {
    // TODO: iterar sobre todas las fuentes de luz
    // punto de intersección
    vec3 pInterseccion = rayo.origen + minT * rayo.direccion;

    // vector a la fuente de luz
    vec3 L = luces[0]->origen - pInterseccion;
    L.normalize();

    // componente de luz ambiente
    vec3 componenteAmbiente = vec3(0.1, 0.1, 0.1) * objInterseccionado->kd;

    // calculo de sombra

    // TODO: por qué 0.01?
    Rayo sombra(pInterseccion + N * 0.01, L);

    bool shadow = false;
    vec3 v = -rayo.direccion;
    v.normalize();

    for (auto obj : objetos) {
      auto [rayIntersects, distanciaAlPuntoDeInterseccion, puntoDeInterseccion,
            normalAlPuntoDeInterseccion] = obj->interseccion(sombra);
      if (rayIntersects) {
        shadow = true;
        break;
      }
    }

    vec3 componenteDifusa, componenteEspecular;
    if (!shadow) {
      // componente difusa
      float factorDifuso = N.punto(L);

      if (factorDifuso > 0.0f) {
        componenteDifusa =
            luces[0]->color * objInterseccionado->kd * factorDifuso;
      }
      // componente especular
      vec3 r = 2 * ((L.punto(N)) * N) - L;
      r.normalize();
      float factorEspecular = r.punto(v);
      if (factorEspecular > 0.0f) {
        componenteEspecular = luces[0]->color * objInterseccionado->ks *
                              pow(factorEspecular, objInterseccionado->n);
      }
    }

    vec3 colorReflexivo, colorRefractivo;
    float kr = objInterseccionado->ks;
    float kt = 0;
    bool outside = rayo.direccion.punto(N) < 0;
    vec3 bias = 0.001 * N;

    if (objInterseccionado->refractionIndex > 0.0f) {
      kr = fresnel(rayo.direccion, N, objInterseccionado->refractionIndex);
      if (kr < 1) {
        kt = 1 - kr;
        Rayo rayoRefractivo(
            outside ? pInterseccion - bias : pInterseccion + bias,
            refractar(rayo.direccion, N, objInterseccionado->refractionIndex));
        rayoRefractivo.direccion.normalize();
        colorRefractivo =
            calcularColor(rayoRefractivo, objetos, luces, prof + 1);
      }
    }

    if (kr > 0.0f) {
      Rayo rayo_reflexivo(outside ? pInterseccion - bias : pInterseccion + bias,
                          2 * (v.punto(N)) * N - v);
      rayo_reflexivo.direccion.normalize();
      colorReflexivo = calcularColor(rayo_reflexivo, objetos, luces, prof + 1);
    }

    color = objInterseccionado->color *
            (componenteAmbiente + componenteDifusa + componenteEspecular);
    color = color + colorReflexivo * kr + colorRefractivo * kt;
    color.maxToOne();

    return color;
  } else {
    // si no intersecta, entonces significa que el ojo está viendo
    // al fondo y por lo tanto pintar pixel del background color
    return color;
  }
}

inline void Camara::paintPixel(int x, int y, const vec3& color) {
  int newY = h - 1 - y;
  (*pImg)(x, newY, 0) = (BYTE)(color.x * 255);
  (*pImg)(x, newY, 1) = (BYTE)(color.y * 255);
  (*pImg)(x, newY, 2) = (BYTE)(color.z * 255);
}