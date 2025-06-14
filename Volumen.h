#ifndef VOLUMEN_H
#define VOLUMEN_H

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include "Imagen.h"

class Volumen {
private:
    std::vector<Imagen> imagenes;
    int cantImagenes;
    std::string nombreBase;
    int alto, ancho;

public:
    Volumen();
    Volumen(int cantImagenes);
    void limpiar();

    int getCantImagenes() const;
    void setCantImagenes(int cantImagenes);

    void setNombreBase(const std::string& nom);
    std::string getNombreBase() const;

    void agregarImagen(const Imagen& img);
    Imagen getImagen(size_t index) const;

    void infoVolumen() const;

    static Imagen proyeccion2D(Volumen& vol, const std::string& direccion, const std::string& criterio, const string& nomArchivo);
    int crit(std::vector<int>& valores, const std::string& criterio) const;
};

#endif