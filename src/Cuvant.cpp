// Fisier: Cuvant.cpp
#include "Cuvant.h"

// Constructor
Cuvant::Cuvant(std::string litere, std::pair<int, int> pozitie, std::string directie)
    : litere(litere), pozitie(pozitie), directie(directie) {}

// Verifică validitatea cuvântului
bool Cuvant::verificaValiditate(TablaScrabble& tabla) {
    // Implementarea logicii pentru verificarea validității cuvântului
    return true; // Placeholder
}

// Calculează scorul pentru cuvântul jucat
int Cuvant::calculeazaScor(TablaScrabble& tabla) {
    int scor = 0;
    // Implementarea logicii pentru calcularea scorului
    return scor; // Placeholder
}
