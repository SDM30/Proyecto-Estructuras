#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "JSDUtils.h"
#include "comp2.h"
#include "Sistema3D.h"
#include "ArbolKD.h"
#include "comp1.h"


void v_cercano(char *px, char *py, char *pz, char *nombre_objeto) {

  //Prueba
  //std::cout << "comando v_cercano" << std::endl;

  if ( !esNumero(px) || !esNumero(py) || !esNumero(pz) ) {

    std::cout << "Error: Los parametros deben ser un numero" << std::endl;
    return;
    
  }

  if (px == nullptr || py == nullptr || pz == nullptr) {

    std::cout << "Error: el comando esperaba las coordenadas del punto completas"
         << std::endl;
    return;
    
  }

  Sistema3D sysFiguras;
  Vertice punto(0,std::stod(px),std::stod(py), std::stod(pz));

  if (nombre_objeto == nullptr) {

    //Prueba
    // std::cout << "comando v_cercano sin param objeto" << std::endl;
    // std::cout << "Parametro:" << px << std::endl;
    // std::cout << "Parametro:" << py << std::endl;
    // std::cout << "Parametro:" << pz << std::endl;

    if (sysFiguras.figs3D.empty()){
      std::cout<<"Ningun objeto ha sido cargado en memoria."<<std::endl;
      return;
    }

    Vertice cercano;
    std::map<double, std::string> mejorVertice;
    std::vector<Poly_Mesh>::iterator it = sysFiguras.figs3D.begin();
    for (;it != sysFiguras.figs3D.end(); it++) {
      ArbolKD arbolAux;
      arbolAux.insertarLista(it->getVer());
      NodoKD* vecino = arbolAux.vecinoCercano(punto);
      
      if (vecino != nullptr) {
          // Calcular la distancia y usarla como clave
          double distancia = vecino->obtenerDato().distanciaEuclidiana(punto);
          //std::cout << "Distancia: " << distancia << " para la malla: " << it->getNombre_mesh() << std::endl;
          mejorVertice[distancia] = it->getNombre_mesh();  // Asignar la distancia y el nombre de la malla
      }
    }

    if (!mejorVertice.empty()) {
      std::map<double, std::string>::iterator mallaCercana = mejorVertice.begin();
      Poly_Mesh figuraCercana = sysFiguras.buscarRetMalla(mallaCercana->second);
      //Prueba
      //std::cout << "MALLA ENCONTRADA = " << mallaCercana->second << std::endl;
      //Buscar vertice con la misma distancia
      //std::cout << "DISTANCIA A BUSCAR = " << mallaCercana->first << std::endl;

      for (int i = 0; i < figuraCercana.getN_vertices(); i++) {
        // std::cout << figuraCercana.getVer()[i].getInd_ver() << " "
        //           << figuraCercana.getVer()[i].getX() << " " << figuraCercana.getVer()[i].getY()
        //           << " " << figuraCercana.getVer()[i].getZ() << std::endl;
        double distVer = figuraCercana.getVer()[i].distanciaEuclidiana(punto);
        //std::cout << "Distancia vertice actual =" << distVer << std::endl;
        if (mallaCercana->first == distVer) {
            cercano = figuraCercana.getVer()[i];
            break;
        }
      }

      std::cout << "El vertice " << cercano.getInd_ver() 
                << " ("
                << cercano.getX() << ", "
                << cercano.getY() << ", "
                << cercano.getZ() << ") "
                << "del objeto " << figuraCercana.getNombre_mesh()
                << " es el mas cercano al punto ("
                << punto.getX() << ", "
                << punto.getY() << ", "
                << punto.getZ() << "), "
                << "a una distancia " 
                << cercano.distanciaEuclidiana(punto) << std::endl;          
    }
    

  } else {

    // std::cout << "comando v_cercano con param" << std::endl;
    // std::cout << "Parametro:" << px << std::endl;
    // std::cout << "Parametro:" << py << std::endl;
    // std::cout << "Parametro:" << pz << std::endl;
    // std::cout << "Parametro:" << nombre_objeto << std::endl;

    if (!sysFiguras.buscarMalla(nombre_objeto)){
      std::cout<<"El objeto "<<nombre_objeto<<"no ha sido cargado en memoria"<<std::endl;
      return;
    }

    Poly_Mesh figura = sysFiguras.buscarRetMalla(nombre_objeto);
    ArbolKD arbolVertices;
    arbolVertices.insertarLista(figura.getVer());
    NodoKD* VerticeCercano = arbolVertices.vecinoCercano(punto); 

    if (VerticeCercano != nullptr) {
        std::cout << "El vertice " << VerticeCercano->obtenerDato().getInd_ver() << " (" 
                << VerticeCercano->obtenerDato().getX() << ", "
                << VerticeCercano->obtenerDato().getY() << ", "
                << VerticeCercano->obtenerDato().getZ()<< ") del objeto "
                << nombre_objeto << " es el mas cercano al punto ("
                << punto.getX() << ", "
                << punto.getY() << ", "
                << punto.getZ() << ")" << std::endl;
        std::cout << VerticeCercano->obtenerDato().distanciaEuclidiana(punto)<<std::endl;
    } else {
        std::cout << "No se encontró un vecino cercano." << std::endl;
    }
    
  }
}

void v_cercanos_caja(char *nombre_objeto) {

  Sistema3D sysFiguras;

  if (nombre_objeto == nullptr) {
    std::cout << "Error: el comando esperaba un objeto" << std::endl;
    return;
  }

  // std::cout << "comando v_cercano_caja" << std::endl;
  // std::cout << "Parametro:" << nombre_objeto << std::endl;

  // Buscar objeto
  if (!sysFiguras.buscarMalla(nombre_objeto)) {
    std::cout << "El objeto" << nombre_objeto << "no ha sido cargado en memoria" << std::endl;
    return;
  }

  Poly_Mesh fig = sysFiguras.buscarRetMalla(nombre_objeto);
  Poly_Mesh figEnv = crearEnvolvente(fig);

  std::cout << std::left
          << std::setw(30) << "Esquina" 
          << std::setw(30) << "Vertice"
          << std::setw(20) << "Distancia" << std::endl;
  ArbolKD arbolVertices;
  arbolVertices.insertarLista(fig.getVer());
  Vertice VerticeCercano[8];

  for (int i = 0; i < 8; i++) {
    NodoKD* cercano = arbolVertices.vecinoCercano(figEnv.getVer()[i]);
    VerticeCercano[i] = cercano->obtenerDato();
  }

  for (int i = 0; i < 8; i++) {
    std::string strEnv = crearStrVerticeFigura(figEnv, i);
    std::string strVerCercano = crearStrVerticeCercano(VerticeCercano, i);
    std::cout << std::left << std::setw(30) << strEnv;
    std::cout << std::left << std::setw(30) << strVerCercano;
    std::cout << std::left << std::setw(20) << figEnv.getVer()[i].distanciaEuclidiana(VerticeCercano[i]) << std::endl;
  }
  
}

std::string crearStrVerticeFigura(Poly_Mesh& fig, int indice) {
  std::ostringstream ss;
  ss << fig.getVer()[indice].getInd_ver() 
     << " ("
     << fig.getVer()[indice].getX() << ", "
     << fig.getVer()[indice].getY() << ", "
     << fig.getVer()[indice].getZ() << ")";
  return ss.str();
}

std::string crearStrVerticeCercano(Vertice verticeCercano[], int indice) {
  std::ostringstream ss;
  ss  << verticeCercano[indice].getInd_ver()
      << " ("
      << verticeCercano[indice].getX() << ", "
      << verticeCercano[indice].getY() << ", "
      << verticeCercano[indice].getZ() << ")";
  return ss.str();
}