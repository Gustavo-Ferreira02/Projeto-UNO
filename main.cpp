#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
#include "Mao_jogador.hpp"
#include "JogoUno.hpp"

int main()
{
    cout <<"Bem vindo ao UNO!" << '\n'
    <<"Para ver o tutorial digite tutorial" << '\n'
    <<"Para jogar digite jogar" <<'\n';
    string escolha;
    int n_jogadores;
    ESCOLHA: cin >> escolha;
    if (escolha == "tutorial")
    {
        cout << '\n' << "No jogo uno temos cartas com cores e numeros." << '\n'
        << "O objetivo eh ficar sem nenhuma carta em maos" << '\n'
        << "Para os jogos nao demorarem demais o jogo tambem acaba se nao houver cartas sobrando para compra"
        << '\n' 
        << "As cores sao azul, verde, laranja e cinza. Jah os numeros vao de 0 a 9." << '\n'
        << "So se pode jogar uma carta na mesa se essa tiver mesma cor e/ou numero que a da mesa" << '\n'
        << "Portanto no jogo as cartas sao representadas da seguinte forma" << '\n'
        << "(inicial da cor)(numero da carta) ou seja:" << '\n'
        << "A4 = Azul numero 4, C4 = Cinza numero 4, L9 = Laranja numero 9, etc..." << '\n' << '\n'
        << "Tambem existem as cartas especiais" << '\n'
        << "Elas sao o Block, o Reverse, o mais dois, o mais 4 e a Wild" << '\n'
        << "O Block impede o proximo jogador de jogar" << '\n'
        << "O Reverse inverte o sentido de quem joga, ou seja " << '\n'
        << "a ordem se inverte de j1>j2>j3... para ...j1<j2<j3" << '\n'
        << "O mais dois adiciona 2 cartas na mao do proximo jogador" << '\n'
        << "O mais quatro adiciona 4 cartas na mao do proximo jogador" << '\n'
        << "O wild permite mudar a cor das cartas que serao jogadas" << '\n'
        << "As tres primeiras cartas especiais (Block Reverse +2) tem cor" << '\n'
        << "E sao representadas por (cor)B, (cor)R, (cor)D" << '\n'
        << "Já as duas ultimas (+4 e wild) nao tem cor e sao representadas por Q e W"<< '\n' << '\n'
        << "O jogo comecara com uma carta nao especial aleatoria na mesa e cada jogador tera 7 cartas"<< '\n'
        << "Digite jogar para jogar, ou tutorial para ver o tutorial de novo"<<'\n';
        goto ESCOLHA;
    }
    else if (escolha == "jogar")
    {
      NJOGADOR:  cout << '\n' << "Quantos jogadores irao jogar (2 a 9 jogadores)" << '\n';
        cin >> n_jogadores;
        try
        {
            if(n_jogadores <2 or n_jogadores >9){
            throw std::invalid_argument("Quantidade de jogadores inseridos invalida, re-insira o numero de jogadores");}
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            goto NJOGADOR;
        }
        cout << "Iniciando UNO..." << '\n';
        JogoUno uno;
        uno.Jogo(n_jogadores);
    }
    else
    {
        cout << '\n'<<"Entrada invalida, favor re-insira (Opcoes: jogar, tutorial)"<<'\n';
        goto ESCOLHA;
    }
    return 0;
}
