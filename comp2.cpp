#include <iostream>
using namespace std;

#include "JSDUtils.h"
#include "comp2.h"
#include "Sistema3D.h"
#include "ArbolKD.h"

void v_cercano(char *px, char *py, char *pz, char *nombre_objeto) {

  cout << "comando v_cercano" << endl;

  if ( !esNumero(px) || !esNumero(py) || !esNumero(pz) ) {

    cout << "Error: Los parametros deben ser un numero" << endl;
    return;
    
  }

  if (px == nullptr || py == nullptr || pz == nullptr) {

    cout << "Error: el comando esperaba las coordenadas del punto completas"
         << endl;
    return;
    
  }

  Sistema3D sysFiguras;
  Vertice punto(0,stod(px),stod(py), stod(pz));

  if (nombre_objeto == nullptr) {

    cout << "comando v_cercano sin param objeto" << endl;
    cout << "Parametro:" << px << endl;
    cout << "Parametro:" << py << endl;
    cout << "Parametro:" << pz << endl;

  } else {

    cout << "comando v_cercano con param" << endl;
    cout << "Parametro:" << px << endl;
    cout << "Parametro:" << py << endl;
    cout << "Parametro:" << pz << endl;
    cout << "Parametro:" << nombre_objeto << endl;

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
    } else {
        std::cout << "No se encontró un vecino cercano." << std::endl;
    }
    
  }
}

void v_cercanos_caja(char *nombre_objeto) {

  if (nombre_objeto == nullptr) {

    cout << "Error: el comando esperaba un objeto" << endl;
    return;
    
  }

  cout << "comando v_cercano_caja" << endl;
  cout << "Parametro:" << nombre_objeto << endl;
  
}