#include "Sistema.h"
#include <iostream>
#include <sstream>  // Para usar stringstream


// g++ -std=c++11 -o mi_programa *.cpp
using namespace std;

enum Comandos {
    CARGAR_IMAGEN, CARGAR_VOLUMEN, INFO_IMAGEN, INFO_VOLUMEN,
    PROYECCION_2D, CODIFICAR_IMAGEN, DECODIFICAR_ARCHIVO, SEGMENTAR,
    AYUDA, SALIR, COMANDO_INVALIDO
};

int main() {
    string input, comando;
    Sistema sistema;
    int codigoComando;
    cout << endl;
    cout << "Sistema de procesamiento de imagenes en escala de grises.\n" << endl;
    cout << "Escriba 'ayuda' para ver los comandos disponibles.\n\n";

    while (true) {
        cout << "$ ";
        getline(cin, input);
        stringstream ss(input);
        ss >> comando;

        codigoComando = sistema.obtenerCodigoComando(comando);

        try {
            switch (codigoComando) {
                case SALIR:
                    cout << "Saliendo del programa...\n";
                    if(sistema.getImagen().getAncho() > 0 || sistema.getVolumen().getCantImagenes() > 0) {
                        sistema.reiniciarSistema();
                    }
                    return 0;

                case AYUDA: {
                    string parametro;
                    ss >> parametro;
                    sistema.mostrarAyuda(parametro);
                    break;
                }

                case CARGAR_IMAGEN: {
                    string nombreArchivo;
                    if (!(ss >> nombreArchivo)) {
                        cout << "(Error) Debes especificar un nombre de archivo. Ejemplo: cargar_imagen foto.pgm\n";
                    } else {
                        sistema.cargarImagen(nombreArchivo);
                    }
                    break;
                }

                case CARGAR_VOLUMEN: {
                    string nombre_base;
                    int n_im;
                    if (!(ss >> nombre_base >> n_im)) {
                        cout << "(Error) Debes proporcionar un nombre base y un número de imágenes.\n";
                    } else {
                        sistema.cargarVolumen(nombre_base, n_im);
                    }
                    break;
                }

                case INFO_IMAGEN: {
                    sistema.infoImagen();
                    break;
                }

                case INFO_VOLUMEN: {
                    sistema.infoVolumen();
                    break;
                }

                case PROYECCION_2D: {
                    string direccion, criterio, nombre_archivo;
                    if (!(ss >> direccion >> criterio >> nombre_archivo)) {
                        cout << "(Error) Uso incorrecto. Ejemplo: proyeccion2D X max salida.pgm\n";
                    } else {
                        sistema.proyeccion_2D(direccion, criterio, nombre_archivo);
                    }
                    break;
                }

                case CODIFICAR_IMAGEN: {
                    string nombre_archivo;
                    if (!(ss >> nombre_archivo)) {
                        cout << "(Error) Debes especificar un nombre de archivo.\n";
                    } else {
                        sistema.codificar_imagen(nombre_archivo);
                    }
                    break;
                }

                case DECODIFICAR_ARCHIVO: {
                    string nombre_archivo, nombre_imagen;
                    if (!(ss >> nombre_archivo >> nombre_imagen)) {
                        cout << "(Error) Uso incorrecto. Ejemplo: decodificar_archivo archivo.txt salida.pgm\n";
                    } else {
                        sistema.decodificar_archivo(nombre_archivo, nombre_imagen);
                    }
                    break;
                }

                case SEGMENTAR: {
                    string salida_imagen;
                        ss >> salida_imagen;

                        vector<tuple<int, int, int>> semillas;
                        int x, y, etiqueta;

                        while (ss >> x >> y >> etiqueta) {
                            semillas.emplace_back(x, y, etiqueta);
                        }

                        if (semillas.empty()) {
                            cout << "(Error) Debes ingresar al menos una semilla. Ejemplo: segmentar salida.pgm 5 10 100\n";
                        } else if (semillas.size() > 5) {
                            cout << "(Error) Solo se permiten hasta 5 semillas.\n";
                        } else {
                            sistema.segmentar(salida_imagen, semillas);
                        }

                        break;
                }

                default:
                    cout << "(Error) Comando no reconocido. Usa 'ayuda' para ver los comandos disponibles.\n";
            }
        } catch (const SistemaException& e) {
            cerr << "(Error) " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "(Error inesperado) " << e.what() << endl;
        }
    }

    return 0;
}