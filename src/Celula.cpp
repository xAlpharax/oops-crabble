// src/Celula.cpp
#include "Celula.h"

Celula::Celula(EfectSpecial efect, char litera) : efectSpecial(efect), litera(litera) {}

EfectSpecial Celula::getEfectSpecial() const {
    return efectSpecial;
}

char Celula::getLitera() const {
    return litera;
}

void Celula::setLitera(char litera) {
    this->litera = litera;
}

void Celula::setEfectSpecial(EfectSpecial efect) {
    this->efectSpecial = efect;
}

bool Celula::esteGoala() const {
    return litera == ' ';
}
