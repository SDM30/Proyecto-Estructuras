#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

#include "Cara.h"
#include "Poly_Mesh.h"
#include "Sistema3D.h"
#include "Vertice.h"
#include "comp1.h"

/*****
 * 1. Procesar nombre de malla
 * 2. Procesar numero de vertices
 * 3. Procesar cada vertice
 * 4. procesar caras
 *  4.1. procesar numer de vertices de la cara
 *  4.2. ordenar carra por cara
 * 5. revisar finalización del archivo
 *****/
void cargar(char *nombre_archivo) {

  Sistema3D sysFiguras;
  // Coleccion temporal para agregar fig
  std::vector<Poly_Mesh> tempFig;

  if (nombre_archivo == nullptr) {
    std::cout
        << "Error: el comando esperaba un archivo existente como parametro"
        << std::endl;
    return;
  }

  std::cout << "comando cargar" << std::endl;
  std::cout << "Parametro:" << nombre_archivo << std::endl;
  std::ifstream entrada(nombre_archivo);

  // Archivo no existe
  if (!entrada.is_open()) {
    printf("El archivo %s no existe o es ilegible\n", nombre_archivo);
    return;
  }

  // Archivo vacío
  if (entrada.peek() == EOF) {
    std::cout << "El archivo " << nombre_archivo << " no existe o es ilegible"
              << std::endl;
    return;
  }

  // Datos de malla
  std::string nombre_mesh = "";
  unsigned int n_vertices = 0;
  std::vector<Vertice> vertices;
  std::vector<Cara> caras;
  bool repetidas = false;

  // Archivo esta incompleto si algun elemento
  // no se puede leer de forma correcta
  while (entrada >> nombre_mesh) {

    vertices.clear();
    caras.clear();

    entrada >> n_vertices;

    // Verificar lectura de n_vertices
    if (entrada.fail()) {
      std::cout << "El archivo " << nombre_archivo
                << " no contiene un objeto 3D valido: No se pudo leer el "
                   "número de vértices"
                << std::endl;
      return;
    }

    for (int i = 0; i < n_vertices; i++) {
      double x, y, z;
      entrada >> x >> y >> z;

      // Verificar lectura de x, y, z
      if (entrada.fail()) {
        std::cout << "El archivo " << nombre_archivo
                  << " no contiene un objeto 3D valido: No se pudo leer el "
                     "X, Y, Z del vértice"
                  << std::endl;
        return;
      }

      Vertice ver(i, x, y, z);
      vertices.push_back(ver);
    }

    int num_ver_cara;
    while (entrada >> num_ver_cara && num_ver_cara != -1) {

      std::vector<unsigned int> ind_caras;
      for (int i = 0; i < num_ver_cara; i++) {

        int indice;
        entrada >> indice;

        // Verificar lectura de indice
        if (entrada.fail()) {
          std::cout << "El archivo " << nombre_archivo
                    << " no contiene un objeto 3D valido: No se pudo leer el "
                       "índice de la cara"
                    << std::endl;
          return;
        }

        ind_caras.push_back(indice);
      }

      Cara cara(num_ver_cara, ind_caras);
      caras.push_back(cara);
    }

    // Verificar lectura de finalArchivo
    if (num_ver_cara == -1) {
      std::cout << "Fin figura " << nombre_mesh << std::endl;
    } else {
      std::cout << "El archivo " << nombre_archivo
                << " no contiene un objeto 3D valido: No se pudo leer el final "
                   "de la malla poligonal"
                << std::endl;
      return;
    }

    // Buscar si el objeto ya existe
    if (sysFiguras.buscarMalla(nombre_mesh)) {
      std::cout << "El objeto " << nombre_mesh
                << " ya ha sido cargado en memoria" << std::endl;
    } else {
      // Resultado exitoso
      std::cout << "El objeto " << nombre_mesh
                << " cargado exitosamente desde el archivo " << nombre_archivo
                << std::endl;

      Poly_Mesh mesh(nombre_mesh, n_vertices, vertices, caras);
      Sistema3D::figs3D.push_back(mesh);

      // PRUEBA
      std::cout << mesh.getNombre_mesh() << std::endl;
      std::cout << mesh.getN_vertices() << std::endl;
      for (int i = 0; i < mesh.getN_vertices(); i++) {
        std::cout << mesh.getVer()[i].getInd_ver() << " "
                  << mesh.getVer()[i].getX() << " " << mesh.getVer()[i].getY()
                  << " " << mesh.getVer()[i].getZ() << std::endl;
      }

      std::cout << "INFORMACION CARA:" << std::endl;

      for (int i = 0; i < mesh.getCaras().size(); i++) {
        std::cout << mesh.getCaras()[i].getNum_ver() << " ";
        for (int j = 0; j < mesh.getCaras()[i].getNum_ver(); j++) {
          std::cout << mesh.getCaras()[i].getInd_caras()[j] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}

/********
 * Imprimir elementos en figs3D
 *********/
void listado() {
  // PRUEBA
  std::cout << "comando listado" << std::endl;

  // Revisa si la lista esta vacia
  if (Sistema3D::figs3D.empty()) {
    std::cout << "Ningun objeto ha sido cargado en memoria" << std::endl;
  } else {

    // Resultado exitoso
    std::vector<Poly_Mesh>::iterator itPoly;
    for (itPoly = Sistema3D::figs3D.begin(); itPoly != Sistema3D::figs3D.end();
         itPoly++) {
      std::cout << itPoly->getNombre_mesh() << " contiene "
                << itPoly->getN_vertices() << " vertices, "
                << itPoly->sumAristas() << " aristas y "
                << itPoly->getCaras().size() << " caras" << std::endl;
    }
  }
}

/********
 * 1. Obtener x, y, z mas grandes (pMax) del objeto
 * 2. Obtener x, y, z mas pequeños (pMin) del objeto
 * 3. Obtener de cada cara los pMin y pMax
 * 4. Formar caras de envolvente
 * (xmin, ymin, zmax), (xmax, ymax, zmax)
 * (xmin, ymin, zmin), (xmax, ymax, zmin)

 (xmin, ymin, zmax) +--------------+ (xmax, ymax, zmax)
                    |              |
                    |              |
                    |              |
                    |              |
                    |              |
 (xmin, ymin, zmin) +--------------+ (xmax, ymax, zmin)

 *********/

void envolvente(char *nombre_objeto) {

  Sistema3D sys3D;

  if (nombre_objeto == nullptr) {

    if (Sistema3D::figs3D.empty()) {

      std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;

    } else {

      std::cout << "comando envolvente sin param" << std::endl;
      Poly_Mesh envGlobal = crearEnvolventeGlobal(Sistema3D::figs3D);

      Sistema3D::figs3D.push_back(envGlobal);

      std::cout
          << "La caja envolvente de los objetos en memoria se ha generado con "
             "el nombre env_global y se ha agregado a los objetos en memoria."
          << std::endl;

      // PRUEBA
      std::cout << envGlobal.getNombre_mesh() << std::endl;
      std::cout << envGlobal.getN_vertices() << std::endl;
      for (int i = 0; i < envGlobal.getN_vertices(); i++) {
        std::cout << envGlobal.getVer()[i].getInd_ver() << " "
                  << envGlobal.getVer()[i].getX() << " "
                  << envGlobal.getVer()[i].getY() << " "
                  << envGlobal.getVer()[i].getZ() << std::endl;
      }

      std::cout << "INFORMACION CARA:" << std::endl;

      for (int i = 0; i < envGlobal.getCaras().size(); i++) {
        std::cout << envGlobal.getCaras()[i].getNum_ver() << " ";
        for (int j = 0; j < envGlobal.getCaras()[i].getNum_ver(); j++) {
          std::cout << envGlobal.getCaras()[i].getInd_caras()[j] << " ";
        }
        std::cout << std::endl;
      }
    }
  } else {

    // Buscar objeto
    bool objetoExiste = sys3D.buscarMalla(nombre_objeto);

    if (!objetoExiste) {
      std::cout << "El objeto " << nombre_objeto
                << " no ha sido cargado en memoria" << std::endl;
      return;

    } else {

      // Buscar figura en memoria
      Poly_Mesh figura = sys3D.buscarRetMalla(nombre_objeto);
      Poly_Mesh envolvente = crearEnvolvente(figura);

      Sistema3D::figs3D.push_back(envolvente);

      std::cout << "comando envolvente con param" << std::endl;
      std::cout << "Parametro:" << nombre_objeto << std::endl;
      std::cout << "La caja envolvente del objeto " << nombre_objeto
                << " se ha generado con el nombre "
                << envolvente.getNombre_mesh()
                << " y se ha agregado a los objetos en memoria" << std::endl;

      // PRUEBA
      std::cout << envolvente.getNombre_mesh() << std::endl;
      std::cout << envolvente.getN_vertices() << std::endl;
      for (int i = 0; i < envolvente.getN_vertices(); i++) {
        std::cout << envolvente.getVer()[i].getInd_ver() << " "
                  << envolvente.getVer()[i].getX() << " "
                  << envolvente.getVer()[i].getY() << " "
                  << envolvente.getVer()[i].getZ() << std::endl;
      }

      std::cout << "INFORMACION CARA:" << std::endl;

      for (int i = 0; i < envolvente.getCaras().size(); i++) {
        std::cout << envolvente.getCaras()[i].getNum_ver() << " ";
        for (int j = 0; j < envolvente.getCaras()[i].getNum_ver(); j++) {
          std::cout << envolvente.getCaras()[i].getInd_caras()[j] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}

Poly_Mesh crearEnvolvente(Poly_Mesh figura) {
  // Crear la figura envolvente
  std::string env_nombre_objeto = "env_" + figura.getNombre_mesh();
  unsigned int n_vertices = 8;
  std::vector<Vertice> ver_env;
  std::vector<Cara> car_env;

  Vertice ver_max = figura.obtenerVerticeMax(),
          ver_min = figura.obtenerVerticeMin();

  double xmin = ver_min.getX();
  double ymin = ver_min.getY();
  double zmin = ver_min.getZ();

  double xmax = ver_max.getX();
  double ymax = ver_max.getY();
  double zmax = ver_max.getZ();

  ver_env.push_back(Vertice(0, xmin, ymin, zmin)); // Vértice 0
  ver_env.push_back(Vertice(1, xmax, ymin, zmin)); // Vértice 1
  ver_env.push_back(Vertice(2, xmax, ymax, zmin)); // Vértice 2
  ver_env.push_back(Vertice(3, xmin, ymax, zmin)); // Vértice 3

  // Cara superior de la caja
  ver_env.push_back(Vertice(4, xmin, ymin, zmax)); // Vértice 4
  ver_env.push_back(Vertice(5, xmax, ymin, zmax)); // Vértice 5
  ver_env.push_back(Vertice(6, xmax, ymax, zmax)); // Vértice 6
  ver_env.push_back(Vertice(7, xmin, ymax, zmax)); // Vértice 7

  // Crear caras
  /****
  4 0 1 2 3
  4 4 5 6 7
  4 0 1 5 4
  4 3 2 6 7
  4 0 3 7 4
  4 1 2 6 5
  ****/
  car_env.push_back(Cara(4, {0, 1, 2, 3}));
  car_env.push_back(Cara(4, {4, 5, 6, 7}));
  car_env.push_back(Cara(4, {0, 1, 5, 4}));
  car_env.push_back(Cara(4, {3, 2, 6, 7}));
  car_env.push_back(Cara(4, {0, 3, 7, 4}));
  car_env.push_back(Cara(4, {1, 2, 6, 5}));

  Poly_Mesh envolvente(env_nombre_objeto, n_vertices, ver_env, car_env);
  return envolvente;
}

Poly_Mesh crearEnvolventeGlobal(std::vector<Poly_Mesh> figuras) {

  double xmaxGlobal = std::numeric_limits<double>::lowest(),
         ymaxGlobal = std::numeric_limits<double>::lowest(),
         zmaxGlobal = std::numeric_limits<double>::lowest();

  double xminGlobal = std::numeric_limits<double>::max(),
         yminGlobal = std::numeric_limits<double>::max(),
         zminGlobal = std::numeric_limits<double>::max();

  std::vector<Poly_Mesh>::iterator it;
  for (it = figuras.begin(); it != figuras.end(); it++) {

    int xmaxFig = it->obtenerVerticeMax().getX(),
        ymaxFig = it->obtenerVerticeMax().getY(),
        zmaxFig = it->obtenerVerticeMax().getZ();

    if (xmaxFig > xmaxGlobal) {
      xmaxGlobal = xmaxFig;
    }

    if (ymaxFig > ymaxGlobal) {
      ymaxGlobal = ymaxFig;
    }

    if (zmaxFig > zmaxGlobal) {
      zmaxGlobal = zmaxFig;
    }

    int xminFig = it->obtenerVerticeMin().getX(),
        yminFig = it->obtenerVerticeMin().getY(),
        zminFig = it->obtenerVerticeMin().getZ();

    if (xminFig < xminGlobal) {
      xminGlobal = xminFig;
    }
    if (yminFig < yminGlobal) {
      yminGlobal = yminFig;
    }
    if (zminFig < zminGlobal) {
      zminGlobal = zminFig;
    }
  }

  // Prueba
  std::cout << "Pmax Global" << std::endl;
  std::cout << xmaxGlobal << " " << ymaxGlobal << " " << zmaxGlobal
            << std::endl;
  std::cout << "Pmin Global" << std::endl;
  std::cout << xminGlobal << " " << yminGlobal << " " << zminGlobal
            << std::endl;

  std::string env_nombre_objeto = "global";
  unsigned int n_vertices = 8;
  std::vector<Vertice> ver_env;
  std::vector<Cara> car_env;
  ver_env.push_back(Vertice(0, xminGlobal, yminGlobal, zminGlobal));
  ver_env.push_back(Vertice(1, xmaxGlobal, ymaxGlobal, zmaxGlobal));

  Poly_Mesh envolventeGlobal = crearEnvolvente(
      Poly_Mesh(env_nombre_objeto, n_vertices, ver_env, car_env));

  return envolventeGlobal;
}

void descargar(char *nombre_objeto) {

  Sistema3D sys3D;

  if (!sys3D.buscarMalla(nombre_objeto)) {

    std::cout << "El objeto " << nombre_objeto
              << " no ha sido cargado en memoria" << std::endl;
    return;

  } else {

    std::cout << "comando descargar" << std::endl;
    std::cout << "Parametro:" << nombre_objeto << std::endl;

    std::vector<Poly_Mesh>::iterator itF;
    for (itF = Sistema3D::figs3D.begin(); itF != Sistema3D::figs3D.end();
         itF++) {

      if (strcmp(itF->getNombre_mesh().c_str(), nombre_objeto) == 0) {
        std::cout << "El objeto " << nombre_objeto
                  << " ha sido eliminado de la memoria de trabajo."
                  << std::endl;
        break;
      }
    }
    Sistema3D::figs3D.erase(itF);
  }
}

void guardar(char *nombre_objeto, char *nombre_archivo) {

  if (nombre_objeto == nullptr || nombre_archivo == nullptr) {
    std::cout << "Error: el comando esperaba dos parametros" << std::endl;
    return;
  }

  // Instancia de Sistema3D para acceder a las mallas cargadas
  Sistema3D sys3D;

  // Buscar si el objeto existe en memoria
  bool objetoExiste = sys3D.buscarMalla(nombre_objeto);

  if (!objetoExiste) {
    std::cout << "El objeto " << nombre_objeto
              << " no ha sido cargado en memoria." << std::endl;
    return;
  }

  // Obtener la malla del objeto
  Poly_Mesh malla = sys3D.buscarRetMalla(nombre_objeto);

  strcat(nombre_archivo, ".txt");

  // Abrir el archivo de salida
  std::ofstream salida(nombre_archivo);
  if (!salida.is_open()) {
    std::cout << "No se pudo abrir el archivo " << nombre_archivo
              << " para escritura." << std::endl;
    return;
  }

  // Escribir la información de la malla en el archivo
  salida << malla.getNombre_mesh() << std::endl; // Nombre de la malla
  salida << malla.getN_vertices() << std::endl;  // Número de vértices

  // Escribir los vértices
  for (int i = 0; i < malla.getN_vertices(); i++) {
    Vertice v = malla.getVer()[i];
    salida << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
  } // Nose si esto funciona bien o no

  std::vector<Cara> caras = malla.getCaras(); // Copiar el vector de caras

  // Escribir las caras
  for (size_t i = 0; i < caras.size(); i++) {
    Cara &c = caras[i];              // Obtener la cara
    salida << c.getNum_ver() << " "; // Número de vértices en la cara
    for (unsigned int indice : c.getInd_caras()) {
      salida << indice << " "; // Índices de los vértices que forman la cara
    }
    salida << std::endl;
    if (i == caras.size() - 1) {
      salida << "-1";
    }
  }

  salida.close();

  std::cout << "comando guardar" << std::endl;
  std::cout << "Parametro:" << nombre_objeto << std::endl;
  std::cout << "Parametro:" << nombre_archivo << std::endl;
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