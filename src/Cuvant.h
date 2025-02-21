#ifndef CUVANT_H
#define CUVANT_H

#include <vector>
#include <string>

class TablaScrabble; // Forward declaration

enum class Directie {
    Orizontal,
    Vertical
};

class Cuvant {
public:
    Cuvant(const std::string& cuvant, int x, int y, Directie directie);

    const std::string& getCuvant() const;
    int getX() const;
    int getY() const;
    Directie getDirectie() const;
    bool verificaValiditate(const TablaScrabble& tabla) const; // Added tabla parameter
    int calculeazaScor(const TablaScrabble& tabla) const;

private:
    std::string litere;
    int x;
    int y;
    Directie directie;
};

#endif
