// Fisier: TablaScrabble.h
#pragma once
#include "Celula.h"
#include "Cuvant.h"
#include <vector>

class Cuvant; // Forward declaration pentru a putea folosi clasa Cuvant

class TablaScrabble {    // Clasa TablaScrabble -> Responsabila pentru gestionarea tablei de joc si validarea si plasarea cuvintelor
private:
    std::vector<std::vector<Celula>> tabla;     // Vector bidimensional de instante ale clasei Celula, ce reprezinta tabla de joc
    std::vector<Cuvant> cuvinteJucate;          // Vector cu instante ale clasei Cuvant, ce reprezinta lista cuvintelor deja jucate

public:
    TablaScrabble();
    bool verificaCuvant(Cuvant cuvant);         // Verifica daca un cuvant este valid si poate fi plasat pe tabla
    void adaugaCuvant(Cuvant cuvant);           // Adauga un cuvant valid pe tabla si actualizeaza scorul
};
