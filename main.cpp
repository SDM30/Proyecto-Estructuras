#include <cstring>
#include <iostream>
using namespace std;

#include "comp1.h"
#include "comp2.h"
#include "comp3.h"

void interfazConsola();

int main() { interfazConsola(); }

void interfazConsola() {

  char palabra[100];

  while (strcmp(palabra, "salir") != 0) {

    cout<<"$";
    cin.getline(palabra, 100);
    char *comando = strtok(palabra," ");

    if (strcmp(comando, "cargar") == 0) {

      char *nombre_archivo = strtok(nullptr," ");
      cargar(nombre_archivo);

    } else if (strcmp(comando, "listado") == 0) {

      listado();

    } else if (strcmp(comando, "envolvente") == 0) {

      char *nombre_objeto = strtok(nullptr," ");
      envolvente(nombre_objeto);

    } else if (strcmp(comando, "descargar") == 0) {

      char *nombre_objeto = strtok(nullptr," ");
      descargar(nombre_objeto);

    } else if (strcmp(comando, "guardar") == 0) {

      char *nombre_objeto = strtok(nullptr," ");
      char *nombre_archivo = strtok(nullptr," ");
      guardar(nombre_objeto, nombre_archivo);

    } else if (strcmp(comando, "salir") == 0) {

    } else if (strcmp(comando, "v_cercano") == 0) {

      char *px = strtok(nullptr," ");
      char *py = strtok(nullptr," ");
      char *pz = strtok(nullptr," ");
      char *nombre_objeto = strtok(nullptr," ");
      v_cercano(px, py, pz, nombre_objeto);

    } else if (strcmp(comando, "v_cercanos_caja") == 0) {

      char *nombre_objeto = strtok(nullptr," ");
      v_cercanos_caja(nombre_objeto);

    } else if (strcmp(comando, "ruta_corta") == 0) {

      char *i1 = strtok(nullptr," ");
      char *i2 = strtok(nullptr," ");
      char *nombre_objeto = strtok(nullptr," ");
      ruta_corta(i1, i2, nombre_objeto);

    } else if (strcmp(comando, "ruta_corta_centro") == 0) {

       char *i1 = strtok(nullptr," ");
       char *nombre_objeto = strtok(nullptr," ");
       ruta_corta_centro(i1, nombre_objeto);

    } else if (strcmp(comando, "ayuda") == 0) {

      char *param = strtok(nullptr," ");
      ayuda(param);

    } else {
      printf(
          "El comando %s no existe, para ver la lista de comandos use ayuda\n",
          comando);
    }
  }
}