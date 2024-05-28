// Fisier: Jucator.h
#pragma once
#include "TablaScrabble.h"
#include "PungaLitere.h"
#include "Cuvant.h"

class Jucator {                            // Clasa Jucator -> Reprezinta un jucator individual
private:
    std::string nume;                                       // Numele jucatorului
    std::vector<char> suport;                               // Lista literelor pe care le are jucatorul
    int scor;                                               // Scorul curent al jucatorului

public:
    Jucator(std::string nume);
    void joacaCuvant(Cuvant cuvant, TablaScrabble& tabla);  // Jucatorul joaca un cuvant pe tabla
    void schimbaLitere(PungaLitere& punga);                 // Jucatorul schimba literele cu cele din punga
};
