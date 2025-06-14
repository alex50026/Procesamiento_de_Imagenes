#ifndef GRAFO_CXX
#define GRAFO_CXX
#include <queue>

#include <cmath>
#include <vector>

#include "nodog.h"
#include "grafo.h"


void Grafo::construir(const std::vector<std::vector<int>>& imagen) {
    alto = imagen.size();
    ancho = (alto > 0 ? imagen[0].size() : 0);
    nodos.resize(alto, std::vector<NodoG>(ancho));
    for (int y = 0; y < alto; ++y)
        for (int x = 0; x < ancho; ++x)
            nodos[y][x] = NodoG(x, y, imagen[y][x]);
}

std::vector<std::pair<int, int>> Grafo::obtenerVecinos(int x, int y, int ancho, int alto) {
    std::vector<std::pair<int, int>> vecinos;
    // Ejemplo: vecinos 4-conexos
    if (x > 0) vecinos.push_back({x-1, y});
    if (x < ancho-1) vecinos.push_back({x+1, y});
    if (y > 0) vecinos.push_back({x, y-1});
    if (y < alto-1) vecinos.push_back({x, y+1});
    return vecinos;
}

void Grafo::segmentar(const std::vector<std::tuple<int, int, int>>& semillas) {
    typedef std::tuple<long long, int, int, int> Entrada; // (costo, x, y, etiqueta)
    std::priority_queue<Entrada, std::vector<Entrada>, std::greater<Entrada>> pq;

    for (size_t i = 0; i < semillas.size(); ++i) {
        int x = std::get<0>(semillas[i]);
        int y = std::get<1>(semillas[i]);
        int etiqueta = std::get<2>(semillas[i]);
        nodos[y][x].setCosto(0);
        nodos[y][x].setEtiqueta(etiqueta);
        pq.push(std::make_tuple(0, x, y, etiqueta));
    }

    while (!pq.empty()) {
        Entrada actual = pq.top(); pq.pop();
        long long costo = std::get<0>(actual);
        int x = std::get<1>(actual);
        int y = std::get<2>(actual);
        int etiqueta = std::get<3>(actual);

        NodoG& nodo_actual = nodos[y][x];
        if (nodo_actual.isVisitado()) continue;
        nodo_actual.setVisitado(true);

        std::vector<std::pair<int, int>> vecinos = obtenerVecinos(x, y, ancho, alto);
        for (size_t i = 0; i < vecinos.size(); ++i) {
            int nx = vecinos[i].first;
            int ny = vecinos[i].second;
            NodoG& vecino = nodos[ny][nx];
            long long peso = std::abs(nodo_actual.getIntensidad() - vecino.getIntensidad());
            if (nodo_actual.getCosto() + peso < vecino.getCosto()) {
                vecino.setCosto(nodo_actual.getCosto() + peso);
                vecino.setEtiqueta(etiqueta);
                pq.push(std::make_tuple(vecino.getCosto(), nx, ny, etiqueta));
            }
        }
    }
}

std::vector<std::vector<int>> Grafo::getEtiquetas() const {
    std::vector<std::vector<int>> etiquetas(alto, std::vector<int>(ancho));
    for (int y = 0; y < alto; ++y)
        for (int x = 0; x < ancho; ++x)
            etiquetas[y][x] = nodos[y][x].getEtiqueta() ;
    return etiquetas;
}

#endif // GRAFO_HXX

