#include <cstring>
#include <iostream>
using namespace std;

#include "comp1.h"
#include "comp2.h"
#include "comp3.h"

void interfazConsola();
int contarParametros(char *comando);

int main() { interfazConsola(); }

void interfazConsola() {

  char palabra[100];

  while (strcmp(palabra, "salir") != 0) {

    cout << "$";
    cin.getline(palabra, 100);
    int numParametros = contarParametros(palabra);
    char *comando = strtok(palabra, " ");

    if (strcmp(comando, "cargar") == 0) {

      if (numParametros > 1) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 1);

      } else {

        char *nombre_archivo = strtok(nullptr, " ");
        cargar(nombre_archivo);
      }

    } else if (strcmp(comando, "listado") == 0) {

      if (numParametros > 0) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 0);

      } else {

        listado();
      }

    } else if (strcmp(comando, "envolvente") == 0) {

      if (numParametros > 1) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 1);

      } else {

        char *nombre_objeto = strtok(nullptr, " ");
        envolvente(nombre_objeto);
      }

    } else if (strcmp(comando, "descargar") == 0) {

      if (numParametros > 1 || numParametros == 0) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 1);

      } else {

        char *nombre_objeto = strtok(nullptr, " ");
        descargar(nombre_objeto);
      }

    } else if (strcmp(comando, "guardar") == 0) {

      if (numParametros > 2) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 2);

      } else {

        char *nombre_objeto = strtok(nullptr, " ");
        char *nombre_archivo = strtok(nullptr, " ");
        guardar(nombre_objeto, nombre_archivo);
      }

    } else if (strcmp(comando, "salir") == 0) {

    } else if (strcmp(comando, "v_cercano") == 0) {

      if (numParametros > 4) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 4);

      } else {

        char *px = strtok(nullptr, " ");
        char *py = strtok(nullptr, " ");
        char *pz = strtok(nullptr, " ");
        char *nombre_objeto = strtok(nullptr, " ");
        v_cercano(px, py, pz, nombre_objeto);
      }

    } else if (strcmp(comando, "v_cercanos_caja") == 0) {

      if (numParametros > 1) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 1);

      } else {

        char *nombre_objeto = strtok(nullptr, " ");
        v_cercanos_caja(nombre_objeto);
      }

    } else if (strcmp(comando, "ruta_corta") == 0) {

      if (numParametros != 3) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 3);

      } else {

        char *i1 = strtok(nullptr, " ");
        char *i2 = strtok(nullptr, " ");
        char *nombre_objeto = strtok(nullptr, " ");
        ruta_corta(i1, i2, nombre_objeto);
      }

    } else if (strcmp(comando, "ruta_corta_centro") == 0) {

      if (numParametros > 2) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 2);

      } else {

        char *i1 = strtok(nullptr, " ");
        char *nombre_objeto = strtok(nullptr, " ");
        ruta_corta_centro(i1, nombre_objeto);
      }

    } else if (strcmp(comando, "ayuda") == 0) {

      if (numParametros > 2) {

        printf("Error en comando %s: numero de parametros aceptados %d\n",
               comando, 2);

      } else {

        char *param = strtok(nullptr, " ");
        ayuda(param);
      }

    } else {

      printf(
          "El comando %s no existe, para ver la lista de comandos use ayuda\n",
          comando);
    }
  }
}

int contarParametros(char *comando) {

  int contador = 0;
  char comandocpy[100];
  strcpy(comandocpy, comando);

  char *token = strtok(comandocpy, " ");

  while (token != nullptr) {

    token = strtok(nullptr, " ");
    contador++;
  }

  return contador - 1;
}