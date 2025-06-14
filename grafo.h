#ifndef GRAFO_H         
#define GRAFO_H

#include "nodog.h"
#include <vector>
#include <tuple>

class Grafo {
private:
    int ancho, alto;
    std::vector<std::vector<NodoG>> nodos;

public:
    void construir(const std::vector<std::vector<int>>& imagen);
    void segmentar(const std::vector<std::tuple<int, int, int>>& semillas);
    std::vector<std::vector<int>> getEtiquetas() const;
    std::vector<std::pair<int, int>> obtenerVecinos(int x, int y, int ancho, int alto);

};

#endif