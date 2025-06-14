#include "Nodo.h"

// Constructor con valor y frecuencia
Nodo::Nodo(int valor, unsigned long frecuencia) {
    this->valor = valor;
    this->frecuencia = frecuencia;
    this->hijoDer = nullptr;
    this->hijoIzq = nullptr;
}

// Constructor para nodos internos (combina dos nodos)
Nodo::Nodo(Nodo* izq, Nodo* der) {
    this->valor = -1;  // Los nodos internos no tienen valor
    this->frecuencia = izq->obtenerFrecuencia() + der->obtenerFrecuencia();
    this->hijoIzq = izq;
    this->hijoDer = der;
}

// Destructor
Nodo::~Nodo() {
    delete this->hijoIzq;
    delete this->hijoDer;
}

// Métodos básicos
unsigned long Nodo::obtenerFrecuencia() {
    return this->frecuencia;
}

Nodo* Nodo::obtenerHijoIzq() {
    return this->hijoIzq;
}

Nodo* Nodo::obtenerHijoDer() {
    return this->hijoDer;
}

int Nodo::obtenerValor() {
    return this->valor;
}

void Nodo::fijarHijoIzq(Nodo* hijo) {
    this->hijoIzq = hijo;
}

void Nodo::fijarHijoDer(Nodo* hijo) {
    this->hijoDer = hijo;
}

// Métodos adicionales (opcionales)
bool Nodo::esHoja() {
    return (this->hijoIzq == nullptr && this->hijoDer == nullptr);
}