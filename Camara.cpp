#include <omp.h>

#include "Camara.h"
#include "Luz.h"
#include "Objeto.h"

void Camara::renderizar(const std::vector<Objeto*>& depthObjects,
                        const std::vector<Luz*>& lightSources) {
  CImgDisplay dis_img(*pImg, "Basic RayTracing");
  // Algoritmo de Ray Tracing

  int x, y;
  // para cada pixel lanzar un rayo desde el ojo
#pragma omp parallel for private(x, y)
  {
    for (y = 0; y < h; y++) {
      for (x = 0; x < w; x++) {
        // TODO: explicación de la fórmula de 'dirección'?
        Rayo rayo(eye,
                  -f * ze + a * (y / h - 0.5) * ye + b * (x / w - 0.5) * xe);
        // TODO: qué luz está más cerca?
        vec3 color;
        for (auto luz : lightSources) {
          auto [intersectsLight, factor] = luz->interseccion(rayo);
          if (intersectsLight) {
            color = luz->color * factor +
                    calcularColor(rayo, depthObjects, lightSources, 1) *
                        (1 - factor);
            break;
          } else {
            color = calcularColor(rayo, depthObjects, lightSources, 1);
          }
        }
        paintPixel(x, y, color);
      }
    }
  }
  dis_img.render(*pImg);
  dis_img.paint();
  while (!dis_img.is_closed()) {
    dis_img.wait();
  }
}

vec3 Camara::calcularColor(const Rayo& rayo,
                           const std::vector<Objeto*>& objetos,
                           const std::vector<Luz*>& luces,
                           int prof) {
  vec3 color = vec3::black();
  // FIXME: con `prof > 7` muere: significa que se queda rebotanod mucho
  if (prof > 5) {
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
    // vec3 colores[luces.size()];
    // componente de luz ambiente
    vec3 componenteAmbiente = vec3(0.1, 0.1, 0.1) * objInterseccionado->kd;
    vec3 componenteDifusa, componenteEspecular;
    vec3 v = -rayo.direccion;
    v.normalize();

    for (auto luz : luces) {
      // vector a la fuente de luz
      vec3 L = luz->centro - pInterseccion;
      float longitudLuz = L.modulo();
      L.normalize();

      // calculo de sombra
      Rayo sombra(pInterseccion + N * 0.01, L);
      bool shadow = false;

      for (auto obj : objetos) {
        auto [rayIntersects, distanciaAlPuntoDeInterseccion,
              puntoDeInterseccion, normalAlPuntoDeInterseccion] =
            obj->interseccion(sombra);
        if (rayIntersects) {
          if (obj->refractionIndex == 0.0f &&
              distanciaAlPuntoDeInterseccion <= longitudLuz) {
            shadow = true;
            break;
          }
        }
      }

      if (!shadow) {
        // componente difusa
        float factorDifuso = N.punto(L);
        if (factorDifuso > 0.0f) {
          componenteDifusa = luz->color * objInterseccionado->kd * factorDifuso;
        }

        // componente difuso si es transparente
        if (objInterseccionado->refractionIndex > 0.0f) {
          factorDifuso = (-N).punto(L);
          if (factorDifuso > 0.0f) {
            componenteDifusa = componenteDifusa + luz->color *
                                                      objInterseccionado->kd *
                                                      factorDifuso;
          }
        }

        // componente especular
        vec3 r = 2 * ((L.punto(N)) * N) - L;
        r.normalize();
        float factorEspecular = r.punto(v);
        if (factorEspecular > 0.0f) {
          componenteEspecular = luz->color * objInterseccionado->ks *
                                pow(factorEspecular, objInterseccionado->n);
        }

        if (objInterseccionado->refractionIndex > 0.0f) {
          r = 2 * (L.punto(-N)) * (-N) - L;
          r.normalize();
          factorEspecular = r.punto(v);
          if (factorEspecular > 0.0f) {
            componenteEspecular =
                componenteEspecular +
                luz->color * objInterseccionado->ks *
                    pow(factorEspecular, objInterseccionado->n);
          }
        }
      } else {
        // TODO: está en sombra
      }
      float kr = objInterseccionado->ks;
      float kt = 0;
      bool outside = rayo.direccion.punto(N) < 0;
      vec3 bias = 0.001f * N;
      vec3 colorReflexivo, colorRefractivo;

      if (objInterseccionado->refractionIndex > 0.0f) {
        kr = fresnel(rayo.direccion, N, objInterseccionado->refractionIndex);
        if (kr < 1) {
          kt = 1 - kr;
          Rayo rayoRefractivo(
              outside ? pInterseccion - bias : pInterseccion + bias,
              refractar(rayo.direccion, N,
                        objInterseccionado->refractionIndex));
          rayoRefractivo.direccion.normalize();
          colorRefractivo =
              calcularColor(rayoRefractivo, objetos, luces, prof + 1);
        }
      }

      if (kr > 0.0f) {
        Rayo rayoReflexivo(
            outside ? pInterseccion - bias : pInterseccion + bias,
            2 * (v.punto(N)) * N - v);
        rayoReflexivo.direccion.normalize();
        colorReflexivo = calcularColor(rayoReflexivo, objetos, luces, prof + 1);
      }
      color = color +
              objInterseccionado->color *
                  (componenteAmbiente + componenteDifusa + componenteEspecular);
      color = color + colorReflexivo * kr + colorRefractivo * kt;
      color.maxToOne();
    }

    // TODO: quizás necesite lo de abajo
    // vec3 sum;
    // for (auto& colore : colores) {
    //   sum = sum + colore;
    // }
    // color = sum / luces.size();
    // sum.maxToOne();
  }
  return color;
}

inline void Camara::paintPixel(int x, int y, const vec3& color) {
  int newY = h - 1 - y;
  (*pImg)(x, newY, 0) = (BYTE)(color.x * 255);
  (*pImg)(x, newY, 1) = (BYTE)(color.y * 255);
  (*pImg)(x, newY, 2) = (BYTE)(color.z * 255);
}