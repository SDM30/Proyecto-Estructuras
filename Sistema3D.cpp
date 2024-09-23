#include "Sistema3D.h"
std::vector<Poly_Mesh> Sistema3D::figs3D;

bool Sistema3D::buscarMalla(std::string nombre_mesh) {

  bool existe = false;
  std::vector<Poly_Mesh>::iterator it;

  for (it = figs3D.begin(); it != figs3D.end(); it++) {
    if (it->getNombre_mesh() == nombre_mesh) {
      existe = true;
      break;
    }
  }

  return existe;
}

Poly_Mesh Sistema3D::buscarRetMalla(std::string nombre_mesh){
  
  std::vector<Poly_Mesh>::iterator it;
  Poly_Mesh figuraEncontrada;

  for (it = figs3D.begin(); it != figs3D.end(); it++) {
    if (it->getNombre_mesh() == nombre_mesh) {
      figuraEncontrada = *it;
      break;
    }
  }
  

  return figuraEncontrada;
  
}
