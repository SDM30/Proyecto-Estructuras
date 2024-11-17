#include <cstring>
#include <iostream>

#include "comp3.h"
#include "JSDUtils.h"
#include "comp1.h"
#include "comp2.h"
#include "Sistema3D.h"
#include "Grafo.h"


void ruta_corta(char *i1, char *i2, char *nombre_objeto) {

  Sistema3D sistema;

  if (!sistema.buscarMalla(nombre_objeto)) {
    std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
    return;
  }

  if (strcmp(i1, i2) == 0) {
    std::cout << "Los indices son iguales" << std::endl;
    return;
  }

  if (!esNumero(i1) || !esNumero(i2)) {
    std::cout << "Error: Los parametros deben ser un numero" << std::endl;
    return;
  }

  Poly_Mesh figura = sistema.buscarRetMalla(nombre_objeto);

  int ind_inicio = std::stoi(i1);
  int ind_fin = std::stoi(i2);

  if ((ind_inicio < 0 || ind_inicio > figura.getN_vertices()) || 
      (ind_fin < 0 || ind_fin > figura.getN_vertices())) {
    std::cout << "Algunos de los indices de vertices estan fuera de rango para el objeto " << nombre_objeto << "." << std::endl;
  }
  
  figura.construirGrafo();
  Grafo<Vertice> grafo_figura = figura.obtenerGrafo();

  Vertice ver_inicio = grafo_figura.obtenerVertices()[ind_inicio];
  Vertice ver_destino = grafo_figura.obtenerVertices()[ind_fin];

  std::vector<Vertice*> pred = grafo_figura.Dijkstra(ver_inicio);
  std::vector<Vertice> ruta = grafo_figura.caminoDijkstra(ver_destino, pred);
  double long_dist = 0;

  for (int i = 0; i < ruta.size() - 1; i++) {
    long_dist += grafo_figura.buscarArista(ruta[i], ruta[i + 1]);
  }

  std::cout << "La ruta más corta que conecta los vertices i1 y i2 del objeto nombre_objeto pasa por: ";
  for (int i = 0; i < ruta.size(); i++) {
    if (i != ruta.size() - 1) {
      std::cout << ruta[i] << ", ";
    } else {
      std::cout << ruta[i] << "; ";
    }
  }
  std::cout << "con una longitud de " << long_dist << "." << std::endl; 
}

void ruta_corta_centro(char *i1, char *nombre_objeto) {

  Sistema3D sistema;

  if (!sistema.buscarMalla(nombre_objeto)) {
    std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
    return;
  }

  if (!esNumero(i1)) {
    std::cout << "Error: Los parametros deben ser un numero" << std::endl;
    return;
  }

  std::cout << "comando r_cercana_centro" << std::endl;
  if (nombre_objeto == nullptr)

    std::cout << "El nombre del objeto no ha sido cargado" << std::endl;

  else {

    std::cout << "Parametro:" << i1 << std::endl;
    std::cout << "Parametro:" << nombre_objeto << std::endl;
  }

  // //Calcular centroide prueba
  // Vertice centro = figura.calcularCentroide();
  
  // std::cout << centro.getInd_ver() 
  //           << " ("
  //           << centro.getX() << ", "
  //           << centro.getY() << ", "
  //           << centro.getZ() << ")" << std::endl;
}

std::string crearStrVertice(Vertice v) {
  std::ostringstream ss;
  ss  << v.getInd_ver()
      << " ("
      << v.getX() << ", "
      << v.getY() << ", "
      << v.getZ() << ")";
  return ss.str();
}