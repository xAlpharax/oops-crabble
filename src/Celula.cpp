// Fisier: Celula.cpp
#include "Celula.h"

// Constructor implicit
Celula::Celula() {
    efectSpecial = 0; // Initializare efect special cu 0 (fara efect special)
    litera = '_';     // Initializare litera ca un caracter null
}

// Metoda pentru aplicarea efectului special al celulei
void Celula::aplicaEfect() {
    // Logica pentru aplicarea efectului special in functie de valoarea atributului efectSpecial
    // 0 - fara efect special
    // 21 - dublu litera
    // 22 - dublu cuvant
    // 31 - triplu litera
    // 32 - triplu cuvant
    switch (efectSpecial) {
        case 21:
            // Aplica efectul de dublare a valorii literei
            // Exemplu: scor *= 2;
            break;
        case 22:
            // Aplica efectul de triplare a valorii literei
            // Exemplu: scor *= 3;
            break;
        case 31:
            // Aplica efectul de dublare a valorii cuvântului
            // Exemplu: scorCuvant *= 2;
            break;
        case 32:
            // Aplica efectul de triplare a valorii cuvântului
            // Exemplu: scorCuvant *= 3;
            break;
        default:
            // Fără efect special
            break;
    }
}
