// src/PungaLitere.h
#ifndef PUNGA_LITERE_H
#define PUNGA_LITERE_H

#include <vector>
#include <random>

class PungaLitere {
public:
    PungaLitere();

    void distribuieLitere(std::vector<char>& suport, int numarLitere);
    void inlocuiesteLitere(std::vector<char>& suport);
    bool isEmpty() const;
    int getNumarLitereRamase() const;

private:
    std::vector<char> litere;
    std::mt19937 generator;
};

#endif
