#ifndef __COMP1__H__
#define __COMP1__H__

#include "Poly_Mesh.h"

void cargar(char *nombre_archivo);
void listado();
void envolvente(char *nombre_objeto);
Poly_Mesh crearEnvolvente(Poly_Mesh figura);
Poly_Mesh crearEnvolventeGlobal(std::vector<Poly_Mesh> figuras);
void descargar(char *nombre_objeto);
void guardar(char *nombre_objeto, char *nombre_archivo);
void ayuda(char *param);

#endif // COMPONENTE UNO
