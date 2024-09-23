#include <iostream>
using namespace std;

#include "JSDUtils.h"
#include "comp2.h"

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