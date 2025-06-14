#ifndef __NODO_H__
#define __NODO_H__

#include <string>


class Nodo {
private:
    int valor;               // Valor del píxel o símbolo
    unsigned long frecuencia; // Frecuencia del símbolo
    Nodo* hijoIzq;           // Hijo izquierdo
    Nodo* hijoDer;           // Hijo derecho

public:
    // Constructores
    Nodo();  // Constructor por defecto
    Nodo(int val, unsigned long freq); // Constructor con valor y frecuencia
    Nodo(Nodo* izq, Nodo* der); // Constructor para nodos internos (combina dos nodos)

    ~Nodo();

    // Getters
    int obtenerValor();
    unsigned long obtenerFrecuencia();
    std::string obtenerCodigo();
    Nodo* obtenerHijoIzq();
    Nodo* obtenerHijoDer();

    // Setters
    void fijarValor(int val);
    void fijarFrecuencia(unsigned long freq);
    void fijarCodigo(std::string cod);
    void fijarHijoIzq(Nodo* izq);
    void fijarHijoDer(Nodo* der);

    // Métodos auxiliares
    bool esHoja(); // Verifica si es un nodo hoja

};
#endif