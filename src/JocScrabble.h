// Fisier: JocScrabble.h
#pragma once
#include "TablaScrabble.h"
#include "PungaLitere.h"
#include "Jucator.h"

class JocScrabble { // Clasa JocScrabble -> Responsabila pentru coordonarea jocului si gestionarea jucatorilor
private:
    TablaScrabble tabla;                 // Instanta a clasei TablaScrabble
    PungaLitere punga;                   // Instanta a clasei PungaLitere
    std::vector<Jucator> jucatori;       // Vector cu instante ale clasei Jucator
    int scorTotal;                       // Scorul total al jocului

public:
    JocScrabble();
    void incepeJoc();                    // Initializeaza jocul, distribuie litere si stabileste primul jucator
    void adaugaJucator(Jucator jucator); // Adauga un jucator nou
    void mutaJucator();                  // Gestioneaza mutarea unui jucator, permite plasarea unui cuvant pe tabla sau schimbul de litere
    void finalizeazaJoc();               // Declara castigatorul jocului
};
