#include "Sistema.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <optional>


using namespace std;

enum Comandos {
    CARGAR_IMAGEN, CARGAR_VOLUMEN, INFO_IMAGEN, INFO_VOLUMEN,
    PROYECCION_2D, CODIFICAR_IMAGEN, DECODIFICAR_ARCHIVO, SEGMENTAR,
    AYUDA, SALIR, COMANDO_INVALIDO
};

// Función para asignar un número a cada comando
int Sistema :: obtenerCodigoComando(const string &comando) {
    if (comando == "cargar_imagen") return CARGAR_IMAGEN; //int?
    if (comando == "cargar_volumen") return CARGAR_VOLUMEN;
    if (comando == "info_imagen") return INFO_IMAGEN;
    if (comando == "info_volumen") return INFO_VOLUMEN;
    if (comando == "proyeccion_2d") return PROYECCION_2D;
    if (comando == "codificar_imagen") return CODIFICAR_IMAGEN;
    if (comando == "decodificar_archivo") return DECODIFICAR_ARCHIVO;
    if (comando == "segmentar") return SEGMENTAR;
    if (comando == "ayuda") return AYUDA;
    if (comando == "salir") return SALIR;
    return -1;
}

// Función para mostrar ayuda
void Sistema:: mostrarAyuda(const string &comando) {
    if (comando.empty()) {
        cout << "\nComandos disponibles:\n";
        cout << " cargar_imagen: Carga una imagen PGM en memoria.\n";
        cout << " cargar_volumen: Carga una serie ordenada de imagenes PGM.\n";
        cout << " info_imagen: Muestra informacion de la imagen cargada.\n";
        cout << " info_volumen: Muestra informacion del volumen cargado.\n";
        cout << " proyeccion_2D: Genera una proyección 2D del volumen.\n";
        cout << " codificar_imagen: Codifica la imagen en memoria con Huffman.\n";
        cout << " decodificar_archivo: Decodifica un archivo .huf a PGM.\n";
        cout << " segmentar: Segmenta la imagen en memoria.\n";
        cout << " ayuda: Muestra la lista de comandos disponibles.\n";
        cout << " salir: Cierra el programa.\n";
        cout << "\nPara más información sobre un comando, usa: ayuda [comando]\n";
        return;
    }

string comando_lower = comando;
transform(comando_lower.begin(), comando_lower.end(), comando_lower.begin(), ::tolower);

switch (obtenerCodigoComando(comando_lower)) {
    case CARGAR_IMAGEN:
        cout << "\ncomando: cargar_imagen nombre_imagen.pgm\nsalida en pantalla:\n(proceso satisfactorio) La imagen nombre_imagen.pgm ha sido cargada.\n(mensaje de error) La imagen nombre_imagen.pgm no ha podido ser cargada.\ndescripción: El comando debe cargar en memoria (en la estructura más adecuada) la imagen identificada con el nombre_imagen.pgm . Una vez cargada la información en memoria, el comando debe mostrar el  mensaje de carga satisfactoria. Si por alguna razón no es posible cargar la imagen (nombre de archivo erróneo o no existe), el comando debe mostrar el mensaje de error. Solo es posible cargar una única imagen por sesión, de tal forma que si el comando es llamado nuevamente con otro nombre de archivo,  la nueva imagen sobre escribe en memoria a la que ya estaba cargada anteriormente.\n";
        break;
    case CARGAR_VOLUMEN:
        cout << "\ncomando: cargar_volumen nombre_base n_im\nsalida en pantalla:\n(proceso satisfactorio) El volumen nombre_base ha sido cargado.\n(mensaje de error) El volumen nombre_base no ha podido ser cargado.\ndescripción: El comando debe cargar en memoria (en la estructura más adecuada) la serie ordenada de imágenes identificada con el nombre_base y cuyo tamaño corresponde a n_im imágenes (la serie podrá tener máximo 99 imágenes). Todas las imágenes de la serie deben estar nombradas como nombre_base xx.pgm, donde xx corresponde a dos dígitos de identificación de la posición de la imagen en la serie (varía en el rango 01 - n_im ). Una vez cargada toda la información en memoria, el comando debe mostrar el mensaje de carga satisfactoria. Si por alguna razón no es posible cargar completamente la serie ordenada de imágenes (nombre de base erróneo, cantidad de imágenes no corresponde, error en alguna imagen), el comando debe mostrar el mensaje de error. Solo es posible cargar un único volumen por sesión, de tal forma que si el comando es llamado nuevamente con otro nombre base, el nuevo volumen sobreescribe en memoria al que ya estaba cargado anteriormente.\n";
        break;
    case INFO_IMAGEN:
        cout << "\ncomando: info_imagen\nsalida en pantalla:\n(proceso satisfactorio) Imagen cargada en memoria: nombre_imagen.pgm , ancho: W , alto: H .\n(mensaje de error) No hay una imagen cargada en memoria.\ndescripción: El comando debe mostrar en pantalla la información básica de la imagen actualmente cargada en memoria: nombre de archivo, ancho en pixeles y alto en pixeles. Si no se ha cargado aún una imagen en memoria, el comando debe mostrar el mensaje de error.\n";
        break;
    case INFO_VOLUMEN:
        cout << "\ncomando: info_volumen\nsalida en pantalla:\n(proceso satisfactorio) Volumen cargado en memoria: nombre_base , tamaño: n_im , ancho:W , alto: H .\n(mensaje de error) No hay un volumen cargado en memoria.\ndescripción: El comando debe mostrar en pantalla la información básica del volumen (serie de imágenes) cargado actualmente en memoria: nombre base, cantidad de imágenes, ancho en pixeles y alto en pixeles. Si no se ha cargado aún un volumen en memoria, el comando debe mostrar el mensaje de error.\n";
        break;
    case PROYECCION_2D:
        cout << "\ncomando: proyeccion2D dirección criterio nombre_archivo.pgm\nsalida en pantalla:\n(proceso satisfactorio) La proyección 2D del volumen en memoria ha sido generada y almacenada\nen el archivo nombre_archivo.pgm .\n(mensajes de error)\nEl volumen aún no ha sido cargado en memoria.\nLa proyección 2D del volumen en memoria no ha podido ser generada.\ndescripción: El comando debe tomar la serie ordenada de imágenes (ya cargada en memoria), y de acuerdo a la dirección especificada por el usuario, debe recorrer cada posición en el plano perpendicular a la dirección dada, y para cada una de esas posiciones debe colapsar toda la información existente en la dirección dada utilizando el criterio especificado. Esto genera un único valor de píxel para cada posición del plano perpendicular, generando así una imagen 2D con la proyección de la información en el volumen. La dirección puede ser una entre x (en dirección de las columnas), y (en dirección de las filas) o z (en dirección de la profundidad). El criterio puede ser uno entre minimo (el valor mínimo de intensidad), maximo (el valor máximo de intensidad), promedio (el valor promedio de intensidad) o mediana (el valor mediana de intensidad). Una vez generada la proyección, debe guardarse como imagen en formato PGM como nombre_archivo.pgm . Es importante anotar que este comando solo puede funcionar sobre volúmenes (series de imágenes).\n";
        break;
    case CODIFICAR_IMAGEN:
        cout << "\ncomando: codificar_imagen nombre_archivo.huf\nsalida en pantalla:\n(proceso satisfactorio) La imagen en memoria ha sido codificada exitosamente y almacenada\nen el archivo nombre_archivo.huf .\n(mensaje de error) No hay una imagen cargada en memoria.\ndescripción: El comando debe generar el archivo de texto con la correspondiente codificación de Huffman para la imagen que se encuentre actualmente cargada en memoria, almacenándolo en disco bajo el nombre nombre_archivo.huf . Si no se ha cargado aún una imagen en memoria, el comando debe mostrar el mensaje de error.\n";
        break;
    case DECODIFICAR_ARCHIVO:
        cout << "\ncomando: decodificar_archivo nombre_archivo.huf nombre_imagen.pgm\nsalida en pantalla:\n(proceso satisfactorio) El archivo nombre_archivo.huf ha sido decodificado exitosamente, y la imagen correspondiente se ha almacenado en el archivo nombre_imagen.pgm . \n(mensaje de error) El archivo nombre_archivo.huf no ha podido ser decodificado. \ndescripción: El comando debe cargar en memoria (en la estructura más adecuada) la información de codificación contenida en el archivo nombre_archivo.huf y luego debe generar la correspondiente imagen decodificada en formato PGM, almacenándola en disco bajo el nombre nombre_imagen.pgm . Si por alguna razón no es posible cargar la información de codificación (nombre de archivo erróneo o no existe), o no es posible realizar el proceso de decodificación (mal formato del archivo), el comando debe mostrar el mensaje de error.\n";
        break;
    case SEGMENTAR:
        cout << "\ncomando: segmentar salida_imagen.pgm sx1 sy1 sl1 sx2 sy2 sl2 ...\nsalida en pantalla:\n(proceso satisfactorio) La imagen en memoria fue segmentada correctamente y almacenada en el archivo salida_imagen.pgm .\n(mensaje de error)\nNo hay una imagen cargada en memoria.\nLa imagen en memoria no pudo ser segmentada.\ndescripción: El comando debe cargar la información del conjunto de semillas correspondiente a la imagen cargada en memoria, para luego proceder a su segmentación de acuerdo al algoritmo presentado anteriormente. El usuario puede ingresar un máximo de 5 semillas en el comando. La imagen con las etiquetas debe quedar guardada en salida_imagen.pgm . Si no se ha cargado aún una imagen en memoria, o por alguna razón no es posible realizar el proceso de segmentación (semillas mal ubicadas, problemas en la construcción del grafo), el comando debe mostrar el mensaje de error.\n";
        break;
    default:
        cout << "(Error) Comando no reconocido. Usa 'ayuda' para ver los comandos disponibles.\n";
 }
}

void Sistema::reiniciarSistema() {
    // Resetear la imagen y el volumen
    img.limpiar();
    vol.limpiar();
    imagenCargada = false;
    volumenCargada = false;
    cout << "Datos borrados del sistema, hasta pronto!\n";
}

// Función para validar si un archivo existe
bool Sistema ::validarArchivoExiste(const string &nombre) {
    ifstream archivo(nombre.c_str());
    return archivo.good();
}

// Función para cargar una imagen
void Sistema :: cargarImagen(const string &nombre_archivo) {
    if (imagenCargada) {
        std::cerr << "Ya hay una imagen cargada en memoria. Por favor, usa 'info_imagen' para ver la informacion de la imagen actual.\n";
        return;
    }

    try {
        img = leerImagen(nombre_archivo);
    } catch (const std::exception& e){
        img.limpiar(); 
        imagenCargada = false;
        throw SistemaException("Error al cargar la imagen: " + std::string(e.what()));

    }
    std :: cout << "Imagen cargada con exito: " << nombre_archivo << std::endl;
    imagenCargada = true; // Set flag to indicate image is loaded
    img.pruebaInfoImagen();
}


Imagen Sistema::leerImagen(const std::string& nombreArchivo) {
    
    if (nombreArchivo.empty()) {
        throw SistemaException("Debes especificar un nombre de archivo. Ejemplo: cargar_imagen foto.pgm");
    }

    if (!validarArchivoExiste(nombreArchivo)) {
        throw FileNotFoundException(nombreArchivo);
    }

    std::ifstream file(nombreArchivo.c_str(), std::ios::binary);
    if (!file) {
        throw SistemaException("(Error) No se pudo abrir el archivo " + nombreArchivo + ".");
    }


    std::string type;

    file >> type;
    if (type != "P2") {
        file.close();
        throw InvalidImageFormatException("(Error) El archivo " + nombreArchivo + " no es un archivo PGM valido.");
    }


    std :: string prueba;
    bool comentario = true;
    int width, height, max_value;

    while(comentario){
        file >> prueba;
        if (prueba[0] == '#') { // Si es un comentario, lo ignoramos
            std::getline(file, prueba); // Leer el comentario completo
        } else {
            comentario = false; // Si no es un comentario, salimos del bucle
            width = std::stoi(prueba); // Convertir el valor a entero
        }
    }

    file >> height >> max_value;
    if (width <= 0 || height <= 0 || max_value <= 0 || max_value > 255) {
        std :: cout << "Valores inválidos en la cabecera del archivo." << std::endl;
        file.close();
        throw InvalidImageFormatException("(Error) La cabecera del archivo " + nombreArchivo + " es inválida.");
    }

    Imagen aux;
    aux.setAlto(height);
    aux.setAncho(width);
    aux.setValorMaximo(max_value);
    aux.setNombreArchivo(nombreArchivo);

    // Leer la imagen en una matriz
    std::vector<std::vector<int>> image(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!(file >> image[y][x])) {
                file.close();
                throw SistemaException("(Error) Problema al leer los datos de la imagen. Faltan datos o formato incorrecto.");
            }
            if(image[y][x]<0){
                file.close();
                throw SistemaException("(Error) La imagen contiene valores negativos.");
            }
            if(image[y][x] > max_value){
                file.close();
                throw SistemaException("(Error) Valor de píxel fuera del rango permitido.");
            }
        }
    }
    if (file >> prueba){
        file.close();
        throw SistemaException("(Error) El archivo " + nombreArchivo + " contiene datos adicionales después de los píxeles.");
    }

    aux.setPixeles(image);
    file.close();
    
    return aux;
}

void Sistema::cargarVolumen(const std::string& nombreBase, int cantImagenes){
    if(volumenCargada){
        std::cerr << "Ya hay un volumen cargado en memoria. Por favor, usa 'info_volumen' para ver la informacion del volumen actual.\n";
        return;
    }
    
    try {
        vol = leerVolumen(nombreBase, cantImagenes);
        if(vol.getCantImagenes() != cantImagenes) {
            vol.limpiar();
            volumenCargada = false;
            // limpiar el volumen cargado
            throw SistemaException("Existio un error al cargar el volumen.");
        }
        
        cout << "Volumen cargado con exito. Nombre base: " << nombreBase << ", Cantidad de imágenes: " << cantImagenes << endl;
        volumenCargada = true;
        
    } catch (const std::exception& e) {
        vol.limpiar(); // Limpiar el volumen en caso de error
        volumenCargada = false; 
        SistemaException("Error al cargar el volumen: " + std::string(e.what()));
    }
    
    vol.infoVolumen();
}
Volumen Sistema::leerVolumen(const std::string& nombreBase, int cantImagenes) {
    if (nombreBase.empty() || cantImagenes <= 0) {
        std::cerr << "Debes proporcionar un nombre base y un número de imágenes válidos." << std::endl;
        return Volumen();  // Devuelve un volumen vacío
    }

    Volumen aux;
    int anchoReferencia = -1;
    int altoReferencia = -1;

    for (int i = 1; i <= cantImagenes; i++) {
        std::ostringstream oss;
        oss << nombreBase << std::setw(2) << std::setfill('0') << i << ".pgm";
        std::string nombreArchivo = oss.str();

        std::cout << "Archivo: " << nombreArchivo << "\n";

        if (!validarArchivoExiste(nombreArchivo)) {
            std::cerr << "Error: El archivo " << nombreArchivo << " no existe." << std::endl;
            throw SistemaException("Error: El archivo " + nombreArchivo + " no existe.");
        }

        try {
            Imagen img = leerImagen(nombreArchivo);

            // Si es la primera imagen, guardamos sus dimensiones de referencia
            if (i == 1) {
                anchoReferencia = img.getAncho();
                altoReferencia = img.getAlto();
            } else {
                // Validamos que coincidan con la referencia
                if (img.getAncho() != anchoReferencia || img.getAlto() != altoReferencia) {
                    throw SistemaException("Error: La imagen " + nombreArchivo +
                        " tiene dimensiones diferentes a las de la primera imagen.");
                }
            }

            aux.agregarImagen(img);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw SistemaException("Error al leer el archivo " + nombreArchivo + ": " + e.what());
        }
    }

    aux.setNombreBase(nombreBase);
    aux.setCantImagenes(cantImagenes);
    return aux;
}

void Sistema::infoImagen() {
    if (!imagenCargada) {
        throw SistemaException("No hay una imagen cargada en memoria.");
    }

    cout << "Informacion de la imagen cargada en memoria \n";
    img.infoImagen();
}


void Sistema :: infoVolumen() {
    if( !volumenCargada) {
        throw SistemaException("No hay un volumen cargado en memoria.");
    }

    cout << "Informacion del volumen cargado en memoria \n";
    vol.infoVolumen();
}

void Sistema :: proyeccion_2D(const string &direccion, const string &criterio, const string &nombre_archivo) {
    cout << "Llamando a proyeccion...\n";
    vol.proyeccion2D(vol, direccion, criterio, nombre_archivo);
}

void Sistema::codificar_imagen(const string& nombreArchivo) {
    if (!imagenCargada) {
        throw SistemaException("No hay imagen cargada para codificar.");
    }

    // Calcular frecuencias de los píxeles
    map<int, unsigned int> frecuencias;
    for (int y = 0; y < img.getAlto(); ++y) {
        for (int x = 0; x < img.getAncho(); ++x) {
            if (frecuencias.find(img.getPixeles()[y][x]) != frecuencias.end()) {
                frecuencias[img.getPixeles()[y][x]]++;
            } else {
                frecuencias[img.getPixeles()[y][x]] = 1;
            }
        }
    }

    // Construir árbol de Huffman
    arbolHuff.construirArbol(frecuencias);
    arbolHuff.generarCodigos();

    for (const auto& par : frecuencias) {
        std::cout << "Valor: " << par.first << " -> Código: " << par.second << std::endl;
    }
    
    std::cout << "Códigos de Huffman:" << std::endl;
    std::unordered_map<int, std::string> codigos = arbolHuff.getTablaCodigos();
    for (const auto& par : codigos) {
        std::cout << "Valor: " << par.first << " -> Código: " << par.second << std::endl;
    }
    // Comprimir imagen
    arbolHuff.comprimirImagen(nombreArchivo, 
                         img.getAncho(), 
                         img.getAlto(), 
                         img.getValorMaximo(),  // valor máximo para imágenes PGM
                         frecuencias, img.getPixeles());

    cout << "Imagen codificada y guardada en " << nombreArchivo << endl;
}




void Sistema::decodificar_archivo(const string& nombreEntrada, const string& nombreSalida) {
    try {
        std::vector<std::vector<int>> pixeles = img.getPixeles();
        int ancho = img.getAncho();
        int alto = img.getAlto();
        int valorMaximo = img.getValorMaximo();
        arbolHuff.descomprimirImagen(nombreEntrada, pixeles, ancho, alto, valorMaximo);
    }
    catch (const exception& e) {
        throw SistemaException(string("Error al decodificar archivo: ") + e.what());
    }    
}


void Sistema::segmentar(const string& salida_imagen, const vector<tuple<int, int, int>>& semillas) {
    if (!imagenCargada) {
        throw SistemaException("No hay imagen cargada en memoria.");
    }
    if (semillas.empty()) {
        throw SistemaException("Debes proporcionar al menos una semilla para la segmentación.");
    }

    if (!imagenCargada) {
        throw SistemaException("No hay imagen cargada en memoria.");
    }
    // Validación básica de semillas
    int ancho = img.getAncho();
    int alto = img.getAlto();
    for (const auto& s : semillas) {
        int x = get<0>(s);
        int y = get<1>(s);
        int etiqueta = get<2>(s);
        if (x < 0 || x >= ancho || y < 0 || y >= alto) {
            throw SistemaException("Una de las semillas está fuera de los límites de la imagen.");
        }
        if (etiqueta > 255) {
            throw SistemaException("La etiqueta de una semilla es mayor a 255.");
        }
    }

    // Construcción del grafo y segmentación
    Grafo grafo;
    grafo.construir(img.getPixeles());
    grafo.segmentar(semillas);
    vector<vector<int>> etiquetas = grafo.getEtiquetas();

    // Crear nueva imagen con las etiquetas
    Imagen salida(ancho, alto);
    salida.setPixeles(etiquetas);
    int valorMax = img.getValorMaximo();
    salida.setValorMaximo(valorMax);
    salida.setNombreArchivo(salida_imagen);
    salida.guardarImagen(salida_imagen);

    cout << "La imagen en memoria fue segmentada correctamente y almacenada en el archivo " << salida_imagen << "." << endl;
}