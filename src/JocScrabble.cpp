// Fisier: JocScrabble.cpp
#include "JocScrabble.h"
#include <iostream>

// Constructor implicit
JocScrabble::JocScrabble() : scorTotal(0) {}

// Inițializează jocul, distribuie litere și stabilește primul jucător
void JocScrabble::incepeJoc() {
    // Implementarea logicii pentru a începe jocul
}

// Adaugă un jucător nou
void JocScrabble::adaugaJucator(Jucator jucator) {
    jucatori.push_back(jucator);
}

// Gestionează mutarea unui jucător, permite plasarea unui cuvânt pe tablă sau schimbul de litere
void JocScrabble::mutaJucator() {
    // Implementarea logicii pentru mutarea unui jucător
}

// Declară câștigătorul jocului
void JocScrabble::finalizeazaJoc() {
    // Implementarea logicii pentru a declara câștigătorul jocului
}
