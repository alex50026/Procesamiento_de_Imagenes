# Sistema de Procesamiento de Imágenes en Escala de Grises con Estructuras de Datos
Este proyecto implementa un sistema para el procesamiento de imágenes en escala de grises utilizando diversas estructuras de datos y algoritmos. 
El sistema permite cargar, manipular, comprimir y segmentar imágenes en formato PGM (Portable GrayMap), así como trabajar con volúmenes 3D compuestos por múltiples imágenes.

## Tabla de Contenidos
- [Descripción del Proyecto](#descripción-del-proyecto)
- [Componentes](#componentes)
- [Instalación y Configuración](#instalación-y-configuración)
- [Uso](#uso)
- [Autores](#autores)

## Descripción del Proyecto
El objetivo de este proyecto es desarrollar un sistema integral para el procesamiento de imágenes en escala de grises, implementando tres componentes principales:

- **Proyección de imágenes**: Permite generar representaciones 2D a partir de volúmenes 3D de imágenes utilizando diferentes criterios de proyección.
- **Codificación de imágenes**: Implementa el algoritmo de Huffman para comprimir y descomprimir imágenes sin pérdida de información.
- **Segmentación de imágenes**: Utiliza grafos y el algoritmo de Dijkstra para dividir imágenes en regiones significativas basadas en semillas proporcionadas por el usuario.

## Componentes

El proyecto está compuesto por los siguientes módulos principales:

- **TAD Imagen**: Maneja la carga, almacenamiento y manipulación de imágenes en formato PGM.
- **TAD Volumen**: Gestiona series de imágenes que conforman volúmenes 3D.
- **TAD Árbol de Huffman**: Implementa la codificación y decodificación de imágenes.
- **TAD Grafo**: Utilizado para la segmentación de imágenes basada en regiones.
- **TAD Sistema**: Coordina la interacción entre los diferentes componentes y la interfaz de usuario.

## Instalación y Configuración

- **Requisitos Previos**
  - Compilador GNU g++ (versión 4.0.0 o superior)
  - Sistema operativo Linux (recomendado) o Windows con entorno de desarrollo compatible
  - Make (opcional, para compilación automatizada)
    
1. **Pasos para la Configuración**
Clona el repositorio del proyecto:
    ```bash
    git clone https://github.com/tu-usuario/procesamiento-imagenes-estructuras.git
    cd procesamiento-imagenes-estructuras

2. **Compila el proyecto**
   ```bash
   g++ -std=c++11 *.cpp -o procesamiento_imagenes
   
3.**Ejecuta el programa**
    ```bash
    ./procesamiento_imagenes

## Uso

El sistema se controla mediante comandos en una interfaz de línea de comandos. Al iniciar el programa, aparecerá el indicador $ donde se pueden ingresar los siguientes comandos:

- **Comandos básicos**
  
  - **ayuda**: Muestra la lista de comandos disponibles.
  - **ayuda <comando>**: Muestra información detallada sobre un comando específico.
  - **salir**: Termina la ejecución del programa.

- **Componente 1**: Proyección de imágenes
  
  - **cargar_imagen <nombre_imagen.pgm>**: Carga una imagen PGM en memoria.
  - **cargar_volumen <nombre_base> <n_im>**: Carga una serie de imágenes como volumen 3D.
  - **info_imagen**: Muestra información sobre la imagen cargada.
  - **info_volumen**: Muestra información sobre el volumen cargado.
  - **proyeccion2D <dirección> <criterio> <nombre_archivo.pgm>**: Genera una proyección 2D del volumen.

- **Componente 2**: Codificación de imágenes
  - **codificar_imagen <nombre_archivo.huf>**: Codifica la imagen actual usando Huffman.
  - **decodificar_archivo <nombre_archivo.huf> <nombre_imagen.pgm>**: Decodifica un archivo .huf a imagen PGM.

- **Componente 3**: Segmentación de imágenes
  - **segmentar <salida_imagen.pgm> <sx1 sy1 l1 sx2 sy2 l2 ...>**: Segmenta la imagen actual basada en semillas.

## Autores

- **Alexander Aponte Largacha**
- **Diego Fernando Castrillón Cortés**
- **Sara Ocampo Feria**
   
