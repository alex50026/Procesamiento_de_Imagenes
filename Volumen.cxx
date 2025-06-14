#include "Volumen.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>

using namespace std;

// Constructores
Volumen::Volumen() : imagenes(), cantImagenes(0), nombreBase("") {}

Volumen::Volumen(int cantImagenes) : imagenes(cantImagenes), cantImagenes(cantImagenes), nombreBase("") {}

void Volumen::limpiar() {
    imagenes.clear();
    cantImagenes = 0;
    nombreBase = "";
}

// Getters y setters
int Volumen::getCantImagenes() const {
    return cantImagenes;
}

void Volumen::setCantImagenes(int cantImagenes) {
    this->cantImagenes = cantImagenes;
}

void Volumen::setNombreBase(const string& nom) {
    nombreBase = nom;
}

string Volumen::getNombreBase() const {
    return nombreBase;
}

// Manejo de imágenes
void Volumen::agregarImagen(const Imagen& img) {
    imagenes.push_back(img);
    cantImagenes = imagenes.size();
}

Imagen Volumen::getImagen(size_t index) const {
    if (index < imagenes.size()) {
        return imagenes[index];
    }
    throw out_of_range("Índice de imagen fuera de rango");
}

// Información del volumen
void Volumen::infoVolumen() const {
    if (imagenes.empty()) {
        cout << "Volumen vacío\n";
        return;
    }

    cout << "Nombre del volumen: " << nombreBase << "\n"
         << "Cantidad de imágenes: " << cantImagenes << "\n"
         << "Dimensiones (ancho x alto): " << imagenes[0].getAncho() 
         << " x " << imagenes[0].getAlto() << "\n";
}

Imagen Volumen::proyeccion2D(Volumen& vol, const string& direccion, const string& criterio, const string& nomArchivo) {
    if (vol.imagenes.empty()) {
        cerr << "Error: Volumen vacío\n";
        return Imagen();
    }

    const size_t prof = vol.imagenes.size();
    const int ancho = vol.imagenes[0].getAncho();
    const int alto = vol.imagenes[0].getAlto();

    Imagen resultado;

    if (direccion == "z") {
        resultado = Imagen(ancho, alto);
    }
    else if (direccion == "x") {
        resultado = Imagen(prof, alto);
    }
    else if (direccion == "y") {
        resultado = Imagen(ancho, alto); // Cambiado para usar plano XY en y
    }
    else {
        cerr << "Dirección inválida. Use 'x', 'y' o 'z'\n";
        return Imagen();
    }

    try {
        if (direccion == "z") {
            for (int y = 0; y < alto; ++y) {
                for (int x = 0; x < ancho; ++x) {
                    vector<int> valores;
                    valores.reserve(prof);
                    for (size_t z = 0; z < prof; ++z) {
                        valores.push_back(vol.imagenes[z].getPixel(x, y));
                    }
                    resultado.setPixel(x, y, vol.crit(valores, criterio));
                }
            }
        }
        else if (direccion == "x") {
            for (size_t z = 0; z < prof; ++z) {
                for (int y = 0; y < alto; ++y) {
                    vector<int> valores;
                    valores.reserve(ancho);
                    for (int x = 0; x < ancho; ++x) {
                        valores.push_back(vol.imagenes[z].getPixel(x, y));
                    }
                    for (int z = 0; z < ancho; z++){
                        for (int y = 0; y < alto; y++){
                        resultado.setPixel(z, y, vol.crit(valores, criterio));
                        }
                    }
                }
            }
        }
        else if (direccion == "y") {
            for (int y = 0; y < alto; ++y) {
                for (int x = 0; x < ancho; ++x) {
                    vector<int> valores;
                    valores.reserve(prof);
                    for (size_t z = 0; z < prof; ++z) {
                        valores.push_back(vol.imagenes[z].getPixel(x, y));
                    }
                    resultado.setPixel(x, y, vol.crit(valores, criterio));
                }
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error durante la proyección: " << e.what() << endl;
        return Imagen();
    }

    cout << "Proyección 2D completada con éxito.\n";
    resultado.guardarImagen(nomArchivo);
    return resultado;
}
// Criterios de proyección
int Volumen::crit(vector<int>& valores, const string& criterio) const {
    if (valores.empty()) return 0;

    if (criterio == "minimo") {
        return *min_element(valores.begin(), valores.end());
    }
    else if (criterio == "maximo") {
        return *max_element(valores.begin(), valores.end());
    }
    else if (criterio == "promedio") {
        int suma = accumulate(valores.begin(), valores.end(), 0);
        return suma / static_cast<int>(valores.size());
    }
    else if (criterio == "mediana") {
        sort(valores.begin(), valores.end());
        size_t mid = valores.size() / 2;
        if (valores.size() % 2 == 0) {
            return (valores[mid-1] + valores[mid]) / 2;
        }
        return valores[mid];
    }

    cerr << "Criterio inválido. Usando valor 0\n";
    return 0;
}


