#include "nodog.h"
#include <climits>

NodoG::NodoG() : x(0), y(0), intensidad(0), etiqueta(0), costo(LLONG_MAX), visitado(false) {}
NodoG::NodoG(int x_, int y_, int intensidad_) : x(x_), y(y_), intensidad(intensidad_), etiqueta(0), costo(LLONG_MAX), visitado(false) {}
