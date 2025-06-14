#ifndef __ARBOLHUFFMAN_H__
#define __ARBOLHUFFMAN_H__

#include "Nodo.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <string>

class ArbolHuffman {
private:
    Nodo* raiz;
    std::unordered_map<int, std::string> tablaCodigos;

public:
    ArbolHuffman();
    ~ArbolHuffman();

    std::unordered_map<int, std::string> getTablaCodigos();
    bool esVacio() const;
    Nodo* getRaiz();

    // Métodos principales (simplificados)
    void construirArbol(const std::map<int, unsigned int>& frecuencias);
    void generarCodigos();

    std::string codificarDato(int dato);
void comprimirImagen(std :: string nomArch, int ancho, int alto, int vMaximo, std :: map<int, unsigned int> frec, std :: vector <std::vector<int>> pixeles);

    int decodificarSecuencia(const std::string& bits, size_t& pos);
    void descomprimirImagen(const std::string& nomArch, std::vector<std::vector<int>>& pixeles, int& ancho, int& alto, int& maxVal);


private:
    // Métodos privados (estilo de tu ejemplo)
    void generarCodigosRec(Nodo* nodo, const std::string& camino);
    void liberarArbol(Nodo* nodo);

};

#endif