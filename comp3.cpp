#include "comp3.h"


void ruta_corta(char *i1, char *i2, char *nombre_objeto) {

  Sistema3D sistema;

  if (!sistema.buscarMalla(nombre_objeto)) {
    std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
    return;
  }

  Poly_Mesh figura = sistema.buscarRetMalla(nombre_objeto);
  //prueba
  figura.construirGrafo();  

  if (!esNumero(i1) || !esNumero(i2)) {

    std::cout << "Error: Los parametros deben ser un numero" << std::endl;
    return;
  }

  std::cout << "comando r_cercana" << std::endl;
  if (i1 == nullptr || i2)

    if (nombre_objeto == nullptr)

      std::cout << "El nombre del objeto no ha sido cargado" << std::endl;

    else if (strcmp(i1, i2) == 0) {

      std::cout << "Los indices son iguales" << std::endl;
      std::cout << "Parametro:" << i1 << std::endl;
      std::cout << "Parametro:" << i2 << std::endl;

    } else {

      std::cout << "Parametro:" << i1 << std::endl;
      std::cout << "Parametro:" << i2 << std::endl;
      std::cout << "Parametro:" << nombre_objeto << std::endl;
    }
}

void ruta_corta_centro(char *i1, char *nombre_objeto) {

  if ( !esNumero(i1) ) {

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
}