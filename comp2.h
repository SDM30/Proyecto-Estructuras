#ifndef __COMP2__H__
#define __COMP2__H_

#include "Poly_Mesh.h"

void v_cercano(char *px, char *py, char *pz, char *nombre_objeto);
void v_cercanos_caja(char *nombre_objeto);
std::string crearStrVerticeFigura(Poly_Mesh& fig, int indice);
std::string crearStrVerticeCercano(Vertice VerticeCercano[], int indice);

#endif // COMPONENTE DOS