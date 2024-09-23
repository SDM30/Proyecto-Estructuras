#ifndef __SISTEMA3D__H__
#define __SISTEMA3D__H__

#include "Poly_Mesh.h"

class Sistema3D {

public:
  static std::vector<Poly_Mesh> figs3D;
  bool buscarMalla(std::string nombre_mesh);
  Poly_Mesh buscarRetMalla(std::string nombre_mesh);
};

#endif