#include "Poly_Mesh.h"
#include "Sistema3D.h"
#include "comp3.h"


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

Grafo<Vertice> Poly_Mesh::obtenerGrafo() {
  return this->grafo_figura;
}

void Poly_Mesh::construirGrafo() {
  std::vector<Vertice> vertices_cara;

  for (int i = 0; i < caras.size(); i++) {
    for (int j = 0; j < caras[i].getNum_ver(); j++) {

        for (int k = 0; k < ver.size(); k++) {
          if (caras[i].getInd_caras()[j] == ver[k].getInd_ver()) {
            vertices_cara.push_back(ver[k]);
            grafo_figura.insertarVertice(ver[k]);
          }
        }
    }

    for (int j = 0; j < caras[i].getNum_ver(); j++) {
        //Tomar un vertice x y crear una arista dirigida con el x+1
        if (j == (caras[i].getNum_ver() - 1)) {
          grafo_figura.insAristaNoDir(vertices_cara[j], vertices_cara[0], vertices_cara[j].distanciaEuclidiana(vertices_cara[0]));
        } else {
          grafo_figura.insAristaNoDir(vertices_cara[j], vertices_cara[j+1], vertices_cara[j].distanciaEuclidiana(vertices_cara[j+1]));
        }
    }

    // std::cout << "Recorrido para la cara: ";
    // for (int j = 0; j < caras[i].getNum_ver(); j++) {
    //   std::cout << caras[i].getInd_caras()[j] << " ";
    // } 
    // std::cout << std::endl;

    vertices_cara.clear();
  }

  // std::cout << "Cantidad Aristas = " << grafo_figura.cantAristas() << std::endl;

  // std::cout << "DFS = ";
  // grafo_figura.DFS(ver[0]);

  // std::cout << "BFS = ";
  // grafo_figura.BFS(ver[0]);
}

Vertice Poly_Mesh::calcularCentroide() {
  Vertice centroide;
  double prom_x = 0, prom_y = 0, prom_z = 0;

  for (int i = 0; i < ver.size(); i++) {
    prom_x += ver[i].getX();
    prom_y += ver[i].getY();
    prom_z += ver[i].getZ();
  }

  prom_x = prom_x/ver.size();
  prom_y = prom_y/ver.size();
  prom_z = prom_z/ver.size();

  centroide.setX(prom_x);
  centroide.setY(prom_y);
  centroide.setZ(prom_z);

  return centroide;
}

void Poly_Mesh::posicionarCentroide(Vertice &centroide) {
  Sistema3D sistema;
  ArbolKD arbolVertices;
  this->construirGrafo();

  arbolVertices.insertarLista(this->getVer());
  NodoKD* VerticeCercano = arbolVertices.vecinoCercano(centroide);

  Vertice vecino_centro = VerticeCercano->obtenerDato();
  centroide.setIndVer(ver.size());
  grafo_figura.insertarVertice(centroide);

  grafo_figura.insAristaNoDir(vecino_centro, centroide, vecino_centro.distanciaEuclidiana(centroide));

  std::cout << "Vertice mas cercano = " << crearStrVertice(vecino_centro) << std::endl
            << "Centroide = " << crearStrVertice(centroide) << std::endl;
}

Vertice Poly_Mesh::buscarVerticeInd(unsigned int ind) {
  Vertice ver_ind;
  for (int i = 0; i < grafo_figura.cantVertices(); i++) {
    if (grafo_figura.obtenerVertices()[i].getInd_ver() == ind) 
      ver_ind = grafo_figura.obtenerVertices()[i];
  }

  return ver_ind;
}