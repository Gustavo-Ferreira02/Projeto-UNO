#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include "JogoUno.hpp"
#include "Mao_Jogador.hpp"
using namespace std;
void JogoUno::Jogo(int numero_jogadores)
{
    stack<string> pilha;
    //Carta aleatoria é definida como carta na mesa (jogada na pilha)
    this->numero_jogadores = numero_jogadores;
    srand ( time(NULL) );
    int index = rand() % Baralho.size();
    //cout << numero_jogadores << " Jogadores" << '\n'
    //<< "Carta na mesa: " << '\n' << Baralho[index];
    pilha.push(Baralho[index]);
    this->Baralho.erase(this->Baralho.begin() - 1 + index);

    //Como a primeira carta da mesa nao pode ser uma especial adicionamos ela depois
    vector<string> Especiais = {"W", "W", "W", "W", "Q", "Q", "Q", "Q", "AB", "AB", "VB", "VB", "LB", "LB"
    , "CB", "CB", "AR", "AR", "VR", "VR", "LR", "LR", "CR", "CR"
    , "AD", "AD", "VD", "VD", "LD", "LD", "CD", "CD"};
    Baralho.insert(end(Baralho), begin(Especiais), end(Especiais));

    //Parte abaixo distribui aleatoriamente as cartas paras os jogadores
    vector <vector<string>> maos_dos_jogadores;
    Mao_Joagador deck;
    for (int i = 0; i < numero_jogadores; i++)
    {
        for (int o = 0; o < 7; o++)
        {
            index = rand() % Baralho.size();
            deck.addCartas(this->Baralho[index]);
            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
        }
        maos_dos_jogadores.push_back(deck.cartas);
        deck.cartas.clear();
    }
    /*
    for (int o = 0; o < numero_jogadores; o++)
    {
        cout << '\n' << "---------------------" << '\n' << "Cartas j" << o + 1 << ":" <<'\n';
    for (int i = 0; i < maos_dos_jogadores[o].size(); i++)
    {
        cout << maos_dos_jogadores[o][i] << " ";
    }
    }*/
    cout << '\n' 
    <<"digite o numero da carta que quer jogar, se nao tiver nenhuma digite 0 para pular sua vez"
    << '\n' << "pular fara com que voce automaticamente compre uma carta!" << '\n' ;
    int jogador_atual = 1;
    bool is_reversed = false;
    bool is_blocked = false;

    //Aqui comeca o loop do jogo
    while (true)
    {
        cout << "---------------------" << '\n' << "J" << jogador_atual << ", eh seu turno!" << '\n';
        cout << "Carta na mesa atualmente: " << '\n' <<pilha.top() << '\n'
        << '\n'
        << "Cartas j" << jogador_atual << ":" << '\n';
        for (int i = 0; i < maos_dos_jogadores[jogador_atual-1].size(); i++)
    {
        cout << maos_dos_jogadores[jogador_atual-1][i] << " ";
    }
        int n_carta;
        CARTA: cin >> n_carta;

        //Aqui fica a opção de se pular a vez
        if (n_carta == 0)
        {
            index = rand() % Baralho.size();
            maos_dos_jogadores[jogador_atual-1].push_back(this->Baralho[index]);
            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
        }
        if (n_carta < 0)
        {
            cout << '\n' << "Carta invalida! Escolha outra" << '\n';
            goto CARTA;
        }
        if (n_carta > maos_dos_jogadores[jogador_atual-1].size() )
        {
            cout << '\n' << "Carta invalida! Escolha outra" << '\n';
            goto CARTA;
        }
        

        //Aqui ficam os comandos quando um jogador escolhe uma carta
        if (n_carta <= maos_dos_jogadores[jogador_atual-1].size() and n_carta > 0)
        {
            //Se a carta escolhida for Q
            if (maos_dos_jogadores[jogador_atual-1][n_carta-1][0] == 'Q')
            {
                int contador = 1;
                if (is_reversed == false & jogador_atual == numero_jogadores ) //se nao estar invertido e o jogador é o ultimo
                {
                    pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                for (int i = 0; i < 4; i++)
                {
                    index = rand() % Baralho.size();
                     maos_dos_jogadores[0].push_back(this->Baralho[index]);
                    this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                }
                }

                if (is_reversed == false & jogador_atual != numero_jogadores) //se nao estar inverteido e o jogador nao é o ultimo
                {
                    pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                for (int i = 0; i < 4; i++)
                {
                    index = rand() % Baralho.size();
                     maos_dos_jogadores[jogador_atual].push_back(this->Baralho[index]);
                    this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                }
                }

                if (is_reversed == true & jogador_atual != 1)  //se esta invertido e o jogador nao é o primeiro
                {
                    pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                for (int i = 0; i < 4; i++)
                {
                    index = rand() % Baralho.size();
                     maos_dos_jogadores[jogador_atual-2].push_back(this->Baralho[index]);
                    this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                }
                }

                if (is_reversed == true & jogador_atual == 1) // se esta invertido e o jogador é o primeiro
                {
                    pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                    maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                for (int i = 0; i < 4; i++)
                {
                    index = rand() % Baralho.size();
                     maos_dos_jogadores[numero_jogadores-1].push_back(this->Baralho[index]);
                    this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                }
                }
            }

            else if (maos_dos_jogadores[jogador_atual-1][n_carta-1][0] == 'W') //se a carta escolhida for o WILD
            {
                maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                string cor;
                cout << '\n' << "Qual cor quer escolher? Escreva a inicial (Opcoes: A, V, L, C)" <<'\n';
                cin >> cor;
                pilha.push(cor);
            }
            
            else if (maos_dos_jogadores[jogador_atual-1][n_carta-1][0] != 'W' or maos_dos_jogadores[jogador_atual-1][n_carta-1][0] != 'Q') //se a carta escolhida nao for nem +4 nem WILD
            {
                if (maos_dos_jogadores[jogador_atual-1][n_carta-1][0] == pilha.top()[0] or maos_dos_jogadores[jogador_atual-1][n_carta-1][1] == pilha.top()[1]) // se a carta escolhida tem mesma cor ou numero que a da pilha
                {
                    if (maos_dos_jogadores[jogador_atual-1][n_carta-1][1] != 'B' or maos_dos_jogadores[jogador_atual-1][n_carta-1][1] != 'R' or maos_dos_jogadores[jogador_atual-1][n_carta-1][1] != 'D') //se a carta escolhida nao ser especial
                    {
                        pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                    }

                    if (maos_dos_jogadores[jogador_atual-1][n_carta-1][1] == 'B') //se a carta escolhida for o block
                    {
                        pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        is_blocked = true;
                    }

                    if ( (maos_dos_jogadores[jogador_atual-1][n_carta-1][1] == 'R') )//se a carta escolhida for reverse
                    {
                        pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        if (is_reversed == false)// se nao esta reverso fica reverso; se esta reverso deixa de ficar
                        {
                            is_reversed = true;
                        }
                        else{is_reversed == false;}
                    }

                    if ((maos_dos_jogadores[jogador_atual-1][n_carta-1][1] == 'D')) // Se a carta for mais dois
                    {
                        pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        if (is_reversed == false & jogador_atual == numero_jogadores ) //se nao estar invertido e o jogador é o ultimo
                        {
                            pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        for (int i = 0; i < 2; i++)
                        {
                            index = rand() % Baralho.size();
                            maos_dos_jogadores[0].push_back(this->Baralho[index]);
                            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                        }
                        }

                        if (is_reversed == false & jogador_atual != numero_jogadores) //se nao estar inverteido e o jogador nao é o ultimo
                        {
                            pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        for (int i = 0; i < 2; i++)
                        {
                            index = rand() % Baralho.size();
                            maos_dos_jogadores[jogador_atual].push_back(this->Baralho[index]);
                            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                        }
                        }

                        if (is_reversed == true & jogador_atual != 1)  //se esta invertido e o jogador nao é o primeiro
                        {
                            pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                        maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        for (int i = 0; i < 2; i++)
                        {
                            index = rand() % Baralho.size();
                            maos_dos_jogadores[jogador_atual-2].push_back(this->Baralho[index]);
                            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                        }
                        }

                        if (is_reversed == true & jogador_atual == 1) // se esta invertido e o jogador é o primeiro
                        {
                            pilha.push(maos_dos_jogadores[jogador_atual-1][n_carta-1]);
                            maos_dos_jogadores[jogador_atual-1].erase(std::next(maos_dos_jogadores[jogador_atual-1].begin()) - 2 + n_carta );
                        for (int i = 0; i < 2; i++)
                        {
                            index = rand() % Baralho.size();
                            maos_dos_jogadores[numero_jogadores-1].push_back(this->Baralho[index]);
                            this->Baralho.erase(std::next(this->Baralho.begin()) - 1 + index);
                        }
                        }
                    }
                    
                }
                else{cout << '\n' <<"Carta invalida escolha outra!" << '\n';
                goto CARTA;}
                
            }
             
        }
        
        if (Baralho.size() == 0)
        {
            cout << '\n' <<"Baralho acabou, fim de jogo";
            std::cin.ignore();
            abort();
        }
        



        //A parte abaixo faz a rotacao dos jogadores        
        if (is_reversed == false & is_blocked == false)
        {
            if (jogador_atual == numero_jogadores)
            {
                jogador_atual = 1;
            }
            else{jogador_atual++;}
        }
        
        if (is_reversed == true & is_blocked == false)
        {
            if (jogador_atual == 1)
            {
                jogador_atual = numero_jogadores;
            }
            else{jogador_atual--;}
        }
        
        if (is_reversed == false & is_blocked == true)
        {
            if (jogador_atual == numero_jogadores - 1)
            {
                jogador_atual = 1;
                is_blocked = false;
            }
            else if (jogador_atual == numero_jogadores)
            {
                jogador_atual = 2;
                is_blocked = false;
            }
            else{jogador_atual = jogador_atual + 2;
            is_blocked = false;}
        }
        
        if (is_reversed == true & is_blocked == true)
        {
            if (jogador_atual == 1)
            {
                jogador_atual = numero_jogadores -1;
                is_blocked = false;
            }
            else if (jogador_atual == 2)
            {
                jogador_atual = numero_jogadores;
                is_blocked = false;
            }
            else{jogador_atual = jogador_atual -2;
            is_blocked = false;}
        }

    }
    
}
