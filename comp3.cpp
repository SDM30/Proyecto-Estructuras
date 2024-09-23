#include <cstring>
#include <iostream>
using namespace std;

#include "JSDUtils.h"
#include "comp3.h"

void ruta_corta(char *i1, char *i2, char *nombre_objeto) {

  if (!esNumero(i1) || !esNumero(i2)) {

    cout << "Error: Los parametros deben ser un numero" << endl;
    return;
  }

  cout << "comando r_cercana" << endl;
  if (i1 == nullptr || i2)

    if (nombre_objeto == nullptr)

      cout << "El nombre del objeto no ha sido cargado" << endl;

    else if (strcmp(i1, i2) == 0) {

      cout << "Los indices son iguales" << endl;
      cout << "Parametro:" << i1 << endl;
      cout << "Parametro:" << i2 << endl;

    } else {

      cout << "Parametro:" << i1 << endl;
      cout << "Parametro:" << i2 << endl;
      cout << "Parametro:" << nombre_objeto << endl;
    }
}

void ruta_corta_centro(char *i1, char *nombre_objeto) {

  if ( !esNumero(i1) ) {

    cout << "Error: Los parametros deben ser un numero" << endl;
    return;
  }

  cout << "comando r_cercana_centro" << endl;
  if (nombre_objeto == nullptr)

    cout << "El nombre del objeto no ha sido cargado" << endl;

  else {

    cout << "Parametro:" << i1 << endl;
    cout << "Parametro:" << nombre_objeto << endl;
  }
}