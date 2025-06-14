#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdexcept>  // Para heredar de std::exception
#include "Imagen.h"
#include "Volumen.h"
#include "Excepciones.h"  // Incluye las excepciones comunes
#include "ArbolHuffman.h"
#include "grafo.h" 
#include "Nodo.h"

using namespace std; 


class Sistema {
	protected: 
	Imagen img;
	bool imagenCargada = false;
	Volumen vol;
	bool volumenCargada = false;
	ArbolHuffman arbolHuff;

	public:
	
	Imagen getImagen (){
		return img;
	}

	Volumen getVolumen (){
		return vol;
	}

	int obtenerCodigoComando(const std::string &comando);

	// Funciones de ayuda y validaciC3n
	void mostrarAyuda(const string &comando = "");

	// Funciones que ejecutan comandos
	bool validarArchivoExiste(const string &nombre);
	void cargarImagen(const string &nombre_imagen);
	Imagen leerImagen(const std::string& nombreArchivo);
	void cargarVolumen(const std::string& nombreBase, int cantImagenes);
	Volumen leerVolumen(const std::string& nombreBase, int cantImagenes);
	void infoImagen();
	void infoVolumen();
	void proyeccion_2D(const string &direccion, const string &criterio, const string &nombre_archivo);
	void codificar_imagen(const string &nombre_archivo);
	void decodificar_archivo(const string &nombre_archivo, const string &nombre_imagen);
	void segmentar(const string& salida_imagen, const vector<tuple<int, int, int>>& semillas);
	void reiniciarSistema();
};

#endif