// Fisier: Celula.h
#pragma once

class Celula { // Clasa Celula -> Reprezinta o celula a tablei de joc
private:
    int efectSpecial;          // Efectul special al celulei (dublu/triplu literă/cuvant)
    char litera;               // Litera prezenta in celula

public:
    Celula();
    void aplicaEfect();        // Aplica efectul special
};
