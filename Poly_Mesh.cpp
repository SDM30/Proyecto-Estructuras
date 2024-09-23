#include "Poly_Mesh.h"
#include <limits>

// Implementación del constructor
Poly_Mesh::Poly_Mesh(std::string nombre_mesh, unsigned int n_vertices,
                     std::vector<Vertice> ver, std::vector<Cara> caras) {
  this->nombre_mesh = nombre_mesh;
  this->n_vertices = n_vertices;
  this->ver = ver;
  this->caras = caras;
}

Poly_Mesh::Poly_Mesh() { this->nombre_mesh = "Sin nombre"; };

// Implementación de los getters
std::string Poly_Mesh::getNombre_mesh() { return nombre_mesh; }

unsigned int Poly_Mesh::getN_vertices() { return n_vertices; }

std::vector<Vertice> Poly_Mesh::getVer() { return ver; }

std::vector<Cara> Poly_Mesh::getCaras() { return caras; }

unsigned int Poly_Mesh::sumAristas() {

  // Matriz de booleanos para marcar las aristas.
  std::vector<std::vector<bool>> aristas_marcadas(
      n_vertices, std::vector<bool>(n_vertices, false));
  unsigned int num_aristas = 0;

  std::vector<Cara>::iterator it = caras.begin();

  for (; it != caras.end(); it++) {
    std::vector<unsigned int> indices = it->getInd_caras();
    unsigned int num_ver = it->getNum_ver();

    for (unsigned int i = 0; i < num_ver; i++) {
      unsigned int v1 = indices[i];
      // Juntar pares de vertices adyacentes
      unsigned int v2 = indices[(i + 1) % num_ver];

      // Si la arista no ha sido marcada, se cuenta y se marca.
      // Se marca la arista en ambos sentidos.
      if (!aristas_marcadas[v1][v2] && !aristas_marcadas[v2][v1]) {
        aristas_marcadas[v1][v2] = true;
        aristas_marcadas[v2][v1] = true;
        num_aristas++;
      }
    }
  }

  return num_aristas;
}

Vertice Poly_Mesh::obtenerVerticeMax() {

  double max_X = std::numeric_limits<double>::lowest();
  double max_Y = std::numeric_limits<double>::lowest();
  double max_Z = std::numeric_limits<double>::lowest();

  std::vector<Vertice>::iterator it;
  for (it = ver.begin(); it != ver.end(); it++) {

    if (it->getX() > max_X) {
      max_X = it->getX();
    }

    if (it->getY() > max_Y) {
      max_Y = it->getY();
    }

    if (it->getZ() > max_Z) {
      max_Z = it->getZ();
    }
  }

  Vertice pMax(0, max_X, max_Y, max_Z);
  return pMax;
}

Vertice Poly_Mesh::obtenerVerticeMin() {

  // Inicializar con valores muy grandes
  double min_X = std::numeric_limits<double>::max();
  double min_Y = std::numeric_limits<double>::max();
  double min_Z = std::numeric_limits<double>::max();

  std::vector<Vertice>::iterator it;
  for (it = ver.begin(); it != ver.end(); it++) {

    if (it->getX() < min_X) {
      min_X = it->getX();
    }

    if (it->getY() < min_Y) {
      min_Y = it->getY();
    }

    if (it->getZ() < min_Z) {
      min_Z = it->getZ();
    }
  }

  Vertice pMin(0, min_X, min_Y, min_Z);
  return pMin;
}

