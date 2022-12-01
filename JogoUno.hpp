#ifndef JOGOUNO_H
#define JOGOUNO_H

#include <iostream>
#include <string>
#include <vector>

class JogoUno
{
private:
    int numero_jogadores;
public:
    vector<string> Baralho = {"A0", "V0", "L0", "C0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9"
     , "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9"
     , "V1", "V2", "B3", "V4", "V5", "V6", "V7", "V8", "V9"
     , "V1", "V2", "B3", "V4", "V5", "V6", "V7", "V8", "V9"
     , "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9"
     , "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9"
     , "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9"
     , "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9"};
    void Jogo(int numero_jogadores);
};

#endif
