#ifndef __POLY_MESH__H__
#define __POLY_MESH__H__
#include <string>
#include <vector>
#include <limits>

#include "Cara.h"
#include "Vertice.h"
#include "Grafo.h"
#include "ArbolKD.h"

class Poly_Mesh {

private:
  std::string nombre_mesh;
  unsigned int n_vertices;
  std::vector<Vertice> ver;
  std::vector<Cara> caras;
  Grafo<Vertice> grafo_figura;

public:
  // Constructor
  Poly_Mesh(std::string nombre_mesh, unsigned int n_vertices,
            std::vector<Vertice> ver, std::vector<Cara> caras);
  Poly_Mesh();
  // getters
  std::string getNombre_mesh();
  unsigned int getN_vertices();
  std::vector<Vertice> getVer();
  std::vector<Cara> getCaras();
  unsigned int sumAristas();
  Vertice obtenerVerticeMax();
  Vertice obtenerVerticeMin();
  Grafo<Vertice> obtenerGrafo();
  void construirGrafo();
  Vertice calcularCentroide();
  void posicionarCentroide(Vertice centroide);
};
#endif