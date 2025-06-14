#ifndef NODOG_H
#define NODOG_H

class NodoG {
private:
    int x, y;
    int intensidad;
    int etiqueta;
    long long costo;
    bool visitado;

public:
    int getX() const { return x; };
    int getY() const { return y; };
    int getIntensidad() const { return intensidad; };
    int getEtiqueta() const { return etiqueta; };
    long long getCosto() const { return costo; };
    bool isVisitado() const { return visitado; };
    void setX(int x_) { x = x_; };
    void setY(int y_) { y = y_; };
    void setIntensidad(int intensidad_) { intensidad = intensidad_; };
    void setEtiqueta(int etiqueta_) { etiqueta = etiqueta_; };
    void setCosto(long long costo_) { costo = costo_; };
    void setVisitado(bool visitado_) { visitado = visitado_; };
    NodoG();
    NodoG(int x_, int y_, int intensidad_);
};

#endif // NODOG_H
