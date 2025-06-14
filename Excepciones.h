#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <stdexcept>
#include <string>

// Clase base para excepciones del sistema
class SistemaException : public std::exception {
private:
    std::string message;
public:
    SistemaException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Excepción para archivos no encontrados
class FileNotFoundException : public SistemaException {
public:
    FileNotFoundException(const std::string& filename)
        : SistemaException("Archivo no encontrado: " + filename) {}
};

// Excepción para formatos de imagen inválidos
class InvalidImageFormatException : public SistemaException {
public:
    InvalidImageFormatException(const std::string& msg)
        : SistemaException("Formato de imagen no válido: " + msg) {}
};

// Excepción para valores de píxeles inválidos
class InvalidPixelValueException : public SistemaException {
public:
    InvalidPixelValueException(int x, int y, int value)
        : SistemaException("Valor de píxel no válido en (" + std::to_string(x) + ", " + std::to_string(y) + "): " + std::to_string(value)) {}
};

#endif // EXCEPCIONES_H