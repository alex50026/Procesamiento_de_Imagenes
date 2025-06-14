#include "Imagen.h"
#include <fstream>
#include <sstream>
#include <stdexcept>  // Para heredar de std::exception



using namespace std; 

// Constructor por defecto
Imagen::Imagen() : ancho(0), alto(0) {}

// Constructor con dimensiones
Imagen::Imagen(int ancho, int alto) : ancho(ancho), alto(alto), pixeles(alto, std::vector<int>(ancho, 0)) {}

// Getters
int Imagen::getAncho() const { return ancho; }
int Imagen::getAlto() const { return alto; }
std::string Imagen::getNombreArchivo() const { return nombreArchivo; }
int Imagen::getValorMaximo() const { return valorMaximo; }
// Setters
void Imagen::setAncho(int ancho) { this->ancho = ancho; }
void Imagen::setAlto(int alto) { this->alto = alto; }
void Imagen::setNombreArchivo(const std::string& nombre) { nombreArchivo = nombre; }
void Imagen::setValorMaximo(int& value){
  valorMaximo = value;
}

void Imagen::setPixeles(const std::vector<std::vector<int>>& pixeles) {
  this->pixeles = pixeles; 
}

std::vector<std::vector<int>> Imagen :: getPixeles() const {
    return pixeles;
}
// Método para obtener un píxel
int Imagen::getPixel(int x, int y) const {
  if (x < 0 || x >= ancho || y < 0 || y >= alto) {
      throw SistemaException("Coordenadas de píxel fuera de rango.");
  }
  return pixeles[y][x];
}

// Método para establecer un píxel
void Imagen::setPixel(int x, int y, int valor) {
  if (x < 0 || x >= ancho || y < 0 || y >= alto) {
      throw SistemaException("Coordenadas de píxel fuera de rango.");
  }
  if (valor < 0 || valor > 255) {
      throw InvalidPixelValueException(x, y, valor);
  }
  pixeles[y][x] = valor;
}



// Método para cargar una imagen desde un archivo
void Imagen::cargarImagen(const string& nombreArchivo) {
  ifstream file(nombreArchivo);
  if (!file) {
      throw FileNotFoundException(nombreArchivo);  // Lanza una excepción si el archivo no existe
  }

  string type;
  file >> type;
  if (type != "P2") {
      throw InvalidImageFormatException("Se esperaba formato PGM (P2).");  // Lanza una excepción si el formato no es válido
  }

  file >> ancho >> alto >> valorMaximo;

  if (ancho <= 0 || alto <= 0 || valorMaximo > 255) {
      throw InvalidImageFormatException("Dimensiones o valor máximo de intensidad no válidos.");  // Lanza una excepción si las dimensiones o el valor máximo son inválidos
  }

  pixeles.resize(alto, vector<int>(ancho, 0));  // Redimensiona la matriz de píxeles

  for (int y = 0; y < alto; ++y) {
      for (int x = 0; x < ancho; ++x) {
          int valor;
          file >> valor;
          if (valor < 0 || valor > 255) {
              throw InvalidPixelValueException(x, y, valor);  // Lanza una excepción si un píxel tiene un valor inválido
          }
          pixeles[y][x] = valor;  // Almacena el valor del píxel
      }
  }

  this->nombreArchivo = nombreArchivo;  // Guarda el nombre del archivo
}



// Método para mostrar información de la imagen
void Imagen::infoImagen() const {
    std::cout << "Imagen: " << nombreArchivo << "\n";
    std::cout << "Dimensiones: " << ancho << "x" << alto << "\n";
}

// Método para guardar una imagen en un archivo
void Imagen::guardarImagen(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
      throw FileNotFoundException(nombreArchivo);
        //std::cerr << "Error: No se pudo guardar la imagen en " << nombreArchivo << "\n";
        // return;
    }
    archivo << "P2\n" << ancho << " " << alto << "\n255\n";
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            archivo << pixeles[i][j] << " ";
        }
        archivo << "\n";
    }

    archivo.close();
}  


void Imagen::pruebaInfoImagen(){
  for (vector<vector<int>>::iterator fila = pixeles.begin(); fila != pixeles.end(); ++fila) {
    for (vector<int>::iterator columna = fila->begin(); columna != fila->end(); ++columna) {
        cout << *columna << " "; // Imprimir cada elemento
    }
    cout << endl; // Salto de línea al finalizar cada fila
  }
}

void Imagen::limpiar() {
  alto = 0;
  ancho = 0;
  valorMaximo = 0;
  pixeles.clear();
  nombreArchivo.clear();
}