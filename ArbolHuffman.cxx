#include "ArbolHuffman.h"
#include <queue>
#include <stdexcept>
#include <fstream>
#include <iostream>

// Estructura comparadora para la priority_queue
struct Comparacion {
    bool operator()(Nodo* a, Nodo* b) {
        return a->obtenerFrecuencia() > b->obtenerFrecuencia();
    }
};

ArbolHuffman::ArbolHuffman() : raiz(nullptr) {}

ArbolHuffman::~ArbolHuffman() {
    liberarArbol(raiz);
}

// Métodos auxiliares
bool ArbolHuffman::esVacio() const {
    return raiz == nullptr;
}

Nodo* ArbolHuffman::getRaiz() {
    return this->raiz;
}

std::unordered_map<int, std::string> ArbolHuffman :: getTablaCodigos(){
    return this->tablaCodigos;
}

// Métodos principales
void ArbolHuffman::construirArbol(const std::map<int, unsigned int>& frecuencias) {
    if(frecuencias.empty()) {
        throw std::invalid_argument("El mapa de frecuencias está vacío");
    }

    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparacion> colaPi;

    // Crear nodos hoja
    for (std::map<int, unsigned int>::const_iterator it = frecuencias.begin(); it != frecuencias.end(); ++it) {
        Nodo* nodo = new Nodo(it->first, it->second);
        colaPi.push(nodo);
    }
    // Construir árbol
    while(colaPi.size() > 1) {
        Nodo* izquierdo = colaPi.top(); 
        colaPi.pop();
        Nodo* derecho = colaPi.top(); 
        colaPi.pop();

        // Crear nodo interno (valor -1 indica nodo interno)
        Nodo* padre = new Nodo(0, izquierdo->obtenerFrecuencia() + derecho->obtenerFrecuencia());
        padre->fijarHijoIzq(izquierdo);
        padre->fijarHijoDer(derecho);

        colaPi.push(padre);
    }

    raiz = colaPi.top();
}

void ArbolHuffman::generarCodigos() {
    tablaCodigos.clear();
    generarCodigosRec(raiz, "");
}

void ArbolHuffman::generarCodigosRec(Nodo* nodo, const std::string& camino) {
    if(!nodo) return;

    if(nodo->esHoja()) {
        tablaCodigos[nodo->obtenerValor()] = camino;
        return;
    }

    generarCodigosRec(nodo->obtenerHijoIzq(), camino + "0");
    generarCodigosRec(nodo->obtenerHijoDer(), camino + "1");
}

std::string ArbolHuffman::codificarDato(int dato) {
    std::unordered_map<int, std :: string> :: const_iterator it = tablaCodigos.find(dato);
    if(it == tablaCodigos.end()) {
        throw std::runtime_error("Dato no encontrado en la tabla de códigos");
    }
    return it->second;
}

void ArbolHuffman :: comprimirImagen(std :: string nomArch, int ancho, int alto, int vMaximo, std :: map<int, unsigned int> frec, std :: vector <std::vector<int>> pixeles){
    std::ofstream archivo(nomArch, std::ios::binary);
    if(!archivo.is_open()){
        std::cout<<"Hubo un error al abrir el archivo.";
        return;
    }
    
    unsigned short anch = ancho;
    unsigned short alt = alto;
    unsigned char valMax = vMaximo;

    archivo.write(reinterpret_cast<const char*>(&anch), sizeof(anch));
    archivo.write(reinterpret_cast<const char*>(&alt), sizeof(alt));
    archivo.write(reinterpret_cast<const char*>(&valMax), sizeof(valMax));

    for (int i = 0; i <= valMax; i++) {
        unsigned long frecuencia = 0;
        if(frec.find(i) != frec.end()){
            frecuencia = frec.at(i); // Convertir de string a unsigned long si es necesario
        }
        archivo.write(reinterpret_cast<const char*>(&frecuencia), sizeof(unsigned long));
    }


    std :: string cad;
    for (std::vector<std::vector<int>>::iterator it = pixeles.begin(); it != pixeles.end(); ++it) {
        for (std::vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            std::unordered_map<int, std::string> :: iterator codigo = tablaCodigos.find(*it2);
            if (codigo != tablaCodigos.end()) {
                cad += codigo->second;  // Accede correctamente al código Huffman
            } else {
                std::cerr << "Error: No se encontró código Huffman para el valor de píxel: " << *it2 << std::endl;
                archivo.close();
                return;
            }
        }
    }

    // Guardamos la cantidad de bits codificados
    unsigned int totalBitsCodificados = cad.length();
    archivo.write(reinterpret_cast<const char*>(&totalBitsCodificados), sizeof(totalBitsCodificados));

    // Convertimos la cadena de bits a bytes
    std::vector<unsigned char> bytes;
    unsigned char byteActual = 0;
    int bitPos = 0;

    for (char bit : cad) {  // Cambia `cadenaDeBits` por `cad`
        byteActual <<= 1;
        if (bit == '1') {
            byteActual |= 1;
        }
        bitPos++;

        if (bitPos == 8) {
            bytes.push_back(byteActual);
            byteActual = 0;
            bitPos = 0;
        }
    }


    // Si quedan bits incompletos, los alineamos y guardamos
    if (bitPos > 0) {
        byteActual <<= (8 - bitPos); // Alineamos los bits restantes a la izquierda
        bytes.push_back(byteActual);
    }

    // Escribimos los bytes en el archivo si hay contenido
    if (!bytes.empty()) {
        archivo.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }

    // Cerramos el archivo y confirmamos el éxito
    archivo.close();
 }


void ArbolHuffman::descomprimirImagen(const std::string& nomArch, std::vector<std::vector<int>>& pixeles, int& ancho, int& alto, int& maxVal) {
    std::ifstream archivo(nomArch, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nomArch << " para decodificar." << std::endl;
        return;
    }

    // Leer encabezado de la imagen
    archivo.read(reinterpret_cast<char*>(&ancho), sizeof(ancho));
    archivo.read(reinterpret_cast<char*>(&alto), sizeof(alto));
    archivo.read(reinterpret_cast<char*>(&maxVal), sizeof(maxVal));

    if (!archivo) {
        std::cerr << "Error al leer el encabezado de la imagen." << std::endl;
        archivo.close();
        return;
    }

    // Inicializar el árbol de Huffman a partir de la frecuencia de píxeles
    std::map<int, unsigned int> frecuencias;
    for (int i = 0; i <= maxVal; i++) {
        unsigned int frec = 0;
        archivo.read(reinterpret_cast<char*>(&frec), sizeof(frec));
        if (archivo) {
            frecuencias[i] = frec;
        }
    }

    ArbolHuffman arbol;
    arbol.construirArbol(frecuencias);

    if (!arbol.getRaiz()) {
        std::cerr << "Error: Árbol Huffman no pudo ser construido." << std::endl;
        archivo.close();
        return;
    }

    // Leer la cantidad de bits codificados
    unsigned int cantidadBits = 0;
    archivo.read(reinterpret_cast<char*>(&cantidadBits), sizeof(cantidadBits));
    if (!archivo) {
        std::cerr << "Error: No se pudo leer la cantidad de bits codificados." << std::endl;
        archivo.close();
        return;
    }

    // Leer los datos binarios de la imagen
    std::vector<unsigned char> bytes((cantidadBits + 7) / 8);
    archivo.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
    archivo.close();

    // Convertir los bytes en una cadena de bits
    std::string cadenaBits;
    cadenaBits.reserve(cantidadBits);

    int bitsLeidos = 0;
    for (unsigned char byte : bytes) {
        for (int j = 7; j >= 0 && bitsLeidos < cantidadBits; --j) {
            cadenaBits += ((byte >> j) & 1) ? '1' : '0';
            bitsLeidos++;
        }
    }

    // Decodificar los bits con el árbol de Huffman
    pixeles.assign(alto, std::vector<int>(ancho));
    Nodo* actual = arbol.getRaiz();
    size_t pos = 0;

    if (!actual) {
        std::cerr << "Error: El árbol Huffman no tiene una raíz válida." << std::endl;
        return;
    }

    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            pixeles[y][x] = arbol.decodificarSecuencia(cadenaBits, pos);
        }
    }

    std::cout << "Imagen decodificada exitosamente desde " << nomArch << "." << std::endl;
}

int ArbolHuffman::decodificarSecuencia(const std::string& bits, size_t& pos) {
    if(!raiz) {
        throw std::runtime_error("Árbol no inicializado");
    }

    Nodo* actual = raiz;
    size_t bits_len = bits.length();

    while(!actual->esHoja() && pos < bits_len) {
        if(bits[pos] == '0') {
            actual = actual->obtenerHijoIzq();
        } else if(bits[pos] == '1') {
            actual = actual->obtenerHijoDer();
        } else {
            throw std::runtime_error("Bit no válido en la secuencia");
        }
        pos++;
    }

    if(!actual->esHoja()) {
        throw std::runtime_error("Secuencia de bits incompleta");
    }

    return actual->obtenerValor();
}



// Método privado para liberar memoria
void ArbolHuffman::liberarArbol(Nodo* nodo) {
    if(nodo) {
        liberarArbol(nodo->obtenerHijoIzq());
        liberarArbol(nodo->obtenerHijoDer());
        delete nodo;
    }
}