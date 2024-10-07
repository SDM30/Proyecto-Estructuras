#include <iostream>
#include "JSDUtils.h"
#include "comp2.h"
#include "Sistema3D.h"
#include "ArbolKD.h"

void v_cercano(char *px, char *py, char *pz, char *nombre_objeto) {

  std::cout << "comando v_cercano" << std::endl;

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

    std::cout << "comando v_cercano sin param objeto" << std::endl;
    std::cout << "Parametro:" << px << std::endl;
    std::cout << "Parametro:" << py << std::endl;
    std::cout << "Parametro:" << pz << std::endl;

    if (sysFiguras.figs3D.empty()){
      
    }

  } else {

    std::cout << "comando v_cercano con param" << std::endl;
    std::cout << "Parametro:" << px << std::endl;
    std::cout << "Parametro:" << py << std::endl;
    std::cout << "Parametro:" << pz << std::endl;
    std::cout << "Parametro:" << nombre_objeto << std::endl;

    if (!sysFiguras.buscarMalla(nombre_objeto)){
      std::cout<<"El objeto "<<nombre_objeto<<"no ha sido cargado en memoria"<<std::std::endl;
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
    } else {
        std::cout << "No se encontró un vecino cercano." << std::endl;
    }
    
  }
}

void v_cercanos_caja(char *nombre_objeto) {

  if (nombre_objeto == nullptr) {

    std::cout << "Error: el comando esperaba un objeto" << std::endl;
    return;
    
  }

  std::cout << "comando v_cercano_caja" << std::endl;
  std::cout << "Parametro:" << nombre_objeto << std::endl;
  
}