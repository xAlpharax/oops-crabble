// Fisier: TablaScrabble.cpp
#include "TablaScrabble.h"

// Constructor implicit
TablaScrabble::TablaScrabble() {
    // Inițializarea tablei de joc
    tabla.resize(15, std::vector<Celula>(15));
}

// Verifică dacă un cuvânt este valid și poate fi plasat pe tablă
bool TablaScrabble::verificaCuvant(Cuvant cuvant) {
    // Implementarea logicii pentru verificarea unui cuvânt
    return true; // Placeholder
}

// Adaugă un cuvânt valid pe tablă și actualizează scorul
void TablaScrabble::adaugaCuvant(Cuvant cuvant) {
    // Implementarea logicii pentru a adăuga un cuvânt pe tablă
}
