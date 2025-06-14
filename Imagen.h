#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>
#include <vector>
#include <string>
#include "Excepciones.h"  // Incluye las excepciones comunes

using namespace std; 

class Imagen {
private:
    int ancho;
    int alto;
    std::vector<std::vector<int>> pixeles;
    std::string nombreArchivo;
    int valorMaximo;

public:
    // Constructores
    Imagen();
    Imagen(int ancho, int alto);
    
    // Métodos de acceso (getters)
    int getAncho() const;
    int getAlto() const;
    std::string getNombreArchivo() const;
    int getValorMaximo() const;
    std::vector<std::vector<int>> getPixeles() const;

    // Métodos de modificación (setters)
    void setAncho(int ancho);
    void setAlto(int alto);
    void setNombreArchivo(const std::string& nombre);
    void setValorMaximo(int& value);
    void setPixeles(const std::vector<std::vector<int>>& pixeles);


    // Métodos de procesamiento
    void cargarImagen(const std::string& nombreArchivo);
    void infoImagen() const;  // Se añadió `const` para compatibilidad con `Volumen`

    // Método para obtener un píxel
    int getPixel(int x, int y) const;

    // Método para establecer un píxel
    void setPixel(int x, int y, int valor);

    // Método para guardar la imagen
    void guardarImagen(const std::string& nombreArchivo) const;
    void pruebaInfoImagen();

    void limpiar();
};

#endif // IMAGEN_H
