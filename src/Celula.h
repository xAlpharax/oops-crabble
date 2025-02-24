// src/Celula.h
#ifndef CELULA_H
#define CELULA_H

#include <SFML/Graphics.hpp>
#include <string>

enum class EfectSpecial {
    Normal,
    DubluLitera,
    TripluLitera,
    DubluCuvant,
    TripluCuvant
};

class Celula {
public:
    Celula(EfectSpecial efect = EfectSpecial::Normal, char litera = ' ');

    EfectSpecial getEfectSpecial() const;
    char getLitera() const;
    void setLitera(char litera);
    void setEfectSpecial(EfectSpecial efect);
    bool esteGoala() const;

private:
    EfectSpecial efectSpecial;
    char litera;
};

#endif
