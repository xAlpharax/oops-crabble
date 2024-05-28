// Fisier: PungaLitere.h
#pragma once
#include <vector>

class PungaLitere {                 // Clasa PungaLitere -> Responsabila pentru distribuirea si gestionarea literelor disponibile
private:
    std::vector<char> litere;                            // Vector cu litere disponibile

public:
    PungaLitere();
    void distribuieLitere(std::vector<char>& suport);    // Distribuie litere catre un jucator
    void inlocuiesteLitere(std::vector<char>& suport);   // Inlocuieste literele unui jucator
};
