// Fisier: Cuvant.h
#pragma once
#include "TablaScrabble.h"
#include <string>

class TablaScrabble; // Forward declaration pentru a putea folosi clasa TablaScrabble

class Cuvant {                                                      // Clasa Cuvant -> Reprezinta un cuvant jucat pe tabla
private:
    std::string litere;                                                             // Lista literelor ce formeaza cuvantul
    std::pair<int, int> pozitie;                                                    // Coordonatele de start pe tabla
    std::string directie;                                                           // Orientarea cuvantului (orizontal sau vertical)

public:
    Cuvant(std::string litere, std::pair<int, int> pozitie, std::string directie);
    bool verificaValiditate(TablaScrabble& tabla);                                  // Verifica validitatea cuvantului
    int calculeazaScor(TablaScrabble& tabla);                                       // Calculeaza scorul pentru cuvantul jucat
};
