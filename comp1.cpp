#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#include "comp1.h"

void cargar(char *nombre_archivo) {
    
  if(nombre_archivo == nullptr){
  
    cout<<"Error: el comando un archivo existente como parametro"<<endl;
    return;
    
  }

  cout << "comando cargar" << endl;
  cout << "Parametro:" << nombre_archivo << endl;
  ifstream entrada(nombre_archivo);

  // Archivo vacío o incompleto
  if (entrada.peek() == EOF /*|| incompleto*/) {
    
    cout << "El archivo esta vacio o incompleto" << endl;
    return;
    
  }
  // Archivo no existe
  if (!entrada.is_open()) {
    
    printf("El archivo %s no existe o es ilegible\n", nombre_archivo);
    return;
    
  }
  // Objeto ya existe

  // Resultado exitoso
  
}

void listado() { cout << "comando listado" << endl; }

void envolvente(char *nombre_objeto) {
  
  if (nombre_objeto == nullptr) {
    
    cout << "comando envolvente sin param" << endl;
    
  } else {
    
    cout << "comando envolvente con param" << endl;
    cout << "Parametro:" << nombre_objeto << endl;
    
  }
  
}

void descargar(char *nombre_objeto) {

  if(nombre_objeto == nullptr){

    cout<<"Error: el comando un archivo existente como parametro"<<endl;
    return;
    
  }
  
  cout << "comando descargar" << endl;
  cout << "Parametro:" << nombre_objeto << endl;
  
}

void guardar(char *nombre_objeto, char *nombre_archivo) {
  
  if(nombre_objeto == nullptr || nombre_archivo == nullptr){

    cout<<"Error: el comando esperaba dos parametros"<<endl;
    return;
    
  }
  
  cout << "comando guardar" << endl;
  cout << "Parametro:" << nombre_objeto << endl;
  cout << "Parametro:" << nombre_archivo << endl;
}

void ayuda(char *param) {
  if (param == nullptr) {

    printf("Lista de comandos disponibles:\n"
           "\tcargar\n"
           "\tlistado\n"
           "\tenvolvente\n"
           "\tdescargar\n"
           "\tguardar\n"
           "\tsalir\n"
           "\tv_cercano\n"
           "\tv_cercano_caja\n"
           "\truta_corta\n"
           "\truta_corta_centro\n");

  } else if (strcmp(param, "cargar") == 0) {

    printf(
        "comando: cargar nombre_archivo\n"
        "descripción: Carga en memoria la información del objeto nombre_objeto "
        "contenida en el archivo identificado por nombre_archivo.\n\n"
        "Posibles salidas de pantalla:\n"
        "Archivo vacío o incompleto: El archivo nombre_archivo no contiene un "
        "objeto 3D válido.\n"
        "Archivo no existe: El archivo nombre_archivo no existe o es "
        "ilegible.\n"
        "Objeto ya existe: El objeto nombre_objeto ya ha sido cargado en "
        "memoria\n"
        "Resultado exitoso: El objeto nombre_objeto ha sido cargado "
        "exitosamente desde el archivo\n");

  } else if (strcmp(param, "listado") == 0) {

    printf("comando: listado\n"
           "descripción: Lista los objetos cargados actualmente en memoria, "
           "junto con la información básica "
           "de cada uno: cantidad de puntos, de aristas y de caras.\n\n"
           "Posibles salidas de pantalla:\n"
           "Memoria vacía: Ningun objeto ha sido cargado en memoria.\n"
           "Resultado exitoso: Hay n objetos en memoria:\n"
           "nombre_objeto_1 contiene n_1 vertices, a_1 aristas y c_1 caras.\n"
           "nombre_objeto_2 contiene n_2 vertices, a_2 aristas y c_2 caras.\n"
           "...\n");

  } else if (strcmp(param, "envolvente") == 0) {

    printf("comando: envolvente nombre_objeto\n"
           "descripción: Calcula la caja envolvente del objeto identificado "
           "por nombre_objeto. "
           "La caja envolvente se agrega como un nuevo objeto en memoria, "
           "asignándole automáticamente el "
           "nombre env_nombre_objeto , para distinguirla de los demás objetos "
           "en memoria.\n\n"
           "Posibles salidas de pantalla:\n"
           "Resultado exitoso: La caja envolvente del objeto nombre_objeto se "
           "ha generado con "
           "el nombre env_nombre_objeto y se ha agregado a los objetos en "
           "memoria.\n\n");

    printf(
        "comando: envolvente\n"
        "descripción: Calcula la caja envolvente que incluye a todos los "
        "objetos cargados actualmente en memoria. "
        "La caja envolvente se agrega como un nuevo objeto en memoria, "
        "asignándole automáticamente el nombre env_global, "
        "para distinguirla de los demás objetos en memoria.\n\n"
        "Posibles salidas de pantalla:\n"
        "Memoria vacía: Ningun objeto ha sido cargado en memoria.\n"
        "Resultado exitoso:  La caja envolvente de los objetos en memoria se "
        "ha generado con "
        "el nombre env_global y se ha agregado a los objetos en memoria\n\n");

  } else if (strcmp(param, "descargar") == 0) {
    cout << "comando descargar" << endl;

    printf("comando: descargar nombre_objeto\n"
           "descripción: Descarga de la memoria toda la información básica "
           "(vértices, aristas, caras) del objeto "
           "identificado por nombre_objeto.\n\n"
           "Posibles salidas de pantalla:\n"
           "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
           "memoria.\n"
           "Resultado exitoso: El objeto nombre_objeto ha sido eliminado de la "
           "memoria de trabajo.\n");

  } else if (strcmp(param, "guardar") == 0) {
    cout << "comando guardar" << endl;

    printf("comando: guardar nombre_objeto nombre_archivo\n"
           "descripción: Escribe en un archivo de texto, identificado por "
           "nombre_archivo, la información "
           "básica (vértices y caras) del objeto identificado por "
           "nombre_objeto.\n\n"
           "Posibles salidas de pantalla:\n"
           "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
           "memoria.\n"
           "Resultado exitoso: La información del objeto nombre_objeto ha sido "
           "guardada exitosamente "
           "en el archivo nombre_archivo.\n");

  } else if (strcmp(param, "salir") == 0) {

    printf("comando: salir\n"
           "descripción: Termina la ejecución de la aplicación.\n\n"
           "Posibles salidas de pantalla:\n"
           "(No tiene salida por pantalla)\n");

  } else if (strcmp(param, "v_cercano") == 0) {

    printf("comando: v_cercano px py pz nombre_objeto\n"
           "descripción: Identifica el vértice del objeto nombre_objeto más "
           "cercano (en términos de la distancia euclidiana) "
           "al punto indicado por las coordenadas px, py y pz. Informa en "
           "pantalla el índice del vértice, los valores "
           "actuales de sus coordenadas, y la distancia a la cual se encuentra "
           "del punto dado.\n\n"
           "Posibles salidas en pantalla:\n"
           "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
           "memoria.\n"
           "Resultado exitoso: El vertice i (vx, vy, vz) del objeto "
           "nombre_objeto es el más cercano al punto (px, py, pz), "
           "a una distancia de valor_distancia.\n\n");

    printf("comando: v_cercano px py pz\n"
           "descripción: Identifica, entre todos los objetos cargados en "
           "memoria, el vértice más cercano (en\n"
           "términos de la distancia euclidiana) al punto indicado por las "
           "coordenadas px, py y pz. Informa\n"
           "en pantalla el objeto al que pertenece, el índice del vértice, los "
           "valores actuales de sus coordenadas,\n"
           "y la distancia a la cual se encuentra del punto dado.\n\n"
           "Posibles salidas en pantalla:\n"
           "(Memoria vacía) Ningun objeto ha sido cargado en memoria.\n"
           "(Resultado exitoso) El vertice i (vx, vy, vz) del objeto "
           "nombre_objeto es el más cercano\n"
           "al punto (px, py, pz), a una distancia de valor_distancia.\n");

  } else if (strcmp(param, "v_cercano_caja") == 0) {

    printf("comando: v_cercanos_caja nombre_objeto\n"
           "descripción: Identifica los vértices del objeto nombre_objeto más "
           "cercanos (en términos de la "
           "distancia euclidiana) a los puntos (vértices) que definen la "
           "respectiva caja envolvente del objeto. "
           "Informa en pantalla, en una tabla, las coordenadas de cada una de "
           "las esquinas de la caja envolvente, "
           "y para cada una de ellas, el índice del vértice más cercano, los "
           "valores actuales de sus coordenadas, "
           "y la distancia a la cual se encuentra de la respectiva esquina.\n\n"
           "Posibles salidas en pantalla:\n"
           "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
           "memoria.\n"
           "Resultado exitoso: Los vértices del objeto nombre_objeto más "
           "cercanos a las esquinas de su caja envolvente son:\n"
           "Esquina\tVertice\tDistancia\n"
           "1 (e1x, e1y, e1z)\ti1 (v1x, v1y, v1z)\tvalor_distancia_1\n"
           "2 (e2x, e2y, e2z)\ti2 (v2x, v2y, v2z)\tvalor_distancia_2\n"
           "...\n"
           "8 (e8x, e8y, e8z)\ti8 (v8x, v8y, v8z)\tvalor_distancia_8\n");

  } else if (strcmp(param, "ruta_corta") == 0) {

    printf(
        "comando: ruta_corta i1 i2 nombre_objeto\n"
        "descripción: Identifica los índices de los vértices que conforman la "
        "ruta más corta entre los vértices dados para"
        "el objeto nombre_objeto. La distancia entre los vértices está medida "
        "en términos de la distancia"
        "euclidiana. Informa, además, la distancia total de la ruta "
        "calculada.\n\n"
        "Posibles salidas en pantalla:\n"
        "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
        "memoria.\n"
        "Índices iguales: Los índices de los vértices dados son iguales.\n"
        "Índices no existen: Algunos de los índices de vértices están fuera de "
        "rango para el objeto nombre_objeto.\n"
        "Resultado exitoso: La ruta más corta que conecta los vértices i1 y i2 "
        "del objeto nombre_objeto pasa "
        "por: i1, v1, v2, ..., vn, i2; con una longitud de valor_distancia.\n");

  } else if (strcmp(param, "ruta_corta_centro") == 0) {

    printf("comando: ruta_corta_centro i1 nombre_objeto\n"
           "descripción: Identifica los índices de los vértices que conforman "
           "la ruta más corta entre el vértice dado y el "
           "centro del objeto nombre_objeto. El vértice centro del objeto se "
           "identifica calculando el centroide (coordenadas "
           "promedio) de todos los vértices del objeto, este punto es agregado "
           "entonces a la representación del objeto. Luego,"
           "se busca el vértice del objeto más cercano a ese centroide, y se "
           "conecta con el centroide por medio de una arista."
           " Finalmente, se utiliza el mismo proceso del comando anterior para "
           "buscar la ruta más corta entre el centroide (ya"
           " conectado dentro del objeto) y el vértice dado. La distancia "
           "entre los vértices está medida en términos de la "
           "distancia euclidiana. Informa, además, la distancia total de la "
           "ruta calculada.\n\n"
           "Posibles salidas en pantalla:\n"
           "Objeto no existe: El objeto nombre_objeto no ha sido cargado en "
           "memoria.\n"
           "Índice no existe: El índice de vértice está fuera de rango para el "
           "objeto nombre_objeto.\n"
           "Resultado exitoso: La ruta más corta que conecta el vértice i1 con "
           "el centro del objeto nombre_objeto, ubicado en "
           "ct (ctx, cty, ctz), pasa por: i1, v1, v2, ..., ct; con una "
           "longitud de valor_distancia.\n");
  } else {

    printf("Comando no reconocido. Escribe 'ayuda' para ver la lista de "
           "comandos disponibles.\n");
  }
}