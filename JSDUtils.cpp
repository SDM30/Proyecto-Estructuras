#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#include "JSDUtils.h"

bool esEntero(char *parametro) {

  try {

    stoi(parametro);
    return parametro == to_string(stoi(parametro));

  } catch (const invalid_argument) {

    return false;

  } catch (const out_of_range) {

    return false;
  }
}

bool esRacional(char *parametro) {

  try {

    size_t pos;
    stof(string(parametro), &pos);
    return pos == string(parametro).size();

  } catch (invalid_argument) {

    return false;

  } catch (out_of_range) {

    return false;
  }
}

bool esNumero(char *parametro) {
  if (esEntero(parametro) || esRacional(parametro)) {
    return true;
  }

  return false;
}