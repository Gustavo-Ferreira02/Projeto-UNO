#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

class Mao_Joagador
{
private:
    /* data */
public:
    vector<string> cartas;
    Mao_Joagador();

    void addCartas(string carta );
};

Mao_Joagador::Mao_Joagador()
{}
void Mao_Joagador::addCartas(string carta){
cartas.push_back(carta);
}


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
                string cor;
                cout << '\n' << "Qual cor quer escolher? Escreva a inicial (Opcoes: A, V, L, C)" <<'\n';
                cin >> cor;
                pilha.push(cor);
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
                string cor;
                cout << '\n' << "Qual cor quer escolher? Escreva a inicial (Opcoes: A, V, L, C)" <<'\n';
                cin >> cor;
                pilha.push(cor);
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
                string cor;
                cout << '\n' << "Qual cor quer escolher? Escreva a inicial (Opcoes: A, V, L, C)" <<'\n';
                cin >> cor;
                pilha.push(cor);
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
                string cor;
                cout << '\n' << "Qual cor quer escolher? Escreva a inicial (Opcoes: A, V, L, C)" <<'\n';
                cin >> cor;
                pilha.push(cor);
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

        
        if (maos_dos_jogadores[jogador_atual-1].size() == 0)
        {
            cout << '\n' <<"O jogador " << jogador_atual << " venceu!!!" << '\n'
            << "playing fogos_de_artificio.mp4";
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



int main()
{
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << '\n'
<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&#BGGPPPGBB#&&&@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&#PJ7~^::...::^~7YG#&&@@@@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#G?~:...............:!5#&&@@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#B?:......:^~!!!~^:......~5#&@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&#BGG&&@@@&#G!.....:~?5PGGP55YJ7~:.....?B#&@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&#PY?~^::P#&&#BB?:....^JG#####BGGP55Y7^.:...7B#&@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#G57^::::.~G##BBP^....:?B#&&&&&&&##G5PP?^:::::Y#&@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&#&&@@@@@@&#PYY!^.....!BBB#Y^    :Y#&@@@@@@@&###GB57^^^~^~B#&@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&#BPY?!^75B#&&@@&##PYY!:.....?BBBY~    .?##&@@@@@@@@###BB7~~~~~:G#&@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@@@&&&#BPYGBGY~:......:!YG#&&&##P5Y!. . ..Y#GP7: ...:5#&@@@@@@@@&###G~~~~~~^G#&@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@@&#GJ7~^:.!BYY7~.......  .~JP####PG5!.   .:PGPJ!::::::Y#&&@@@@@@&##G!^~~~~~?B#@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@@@&BPJ~^.....?BYY7^.......    .^?P##GBY~.....^PJJ?!^^^^^:!5B#&&&&#BPJ~^!~~~~7G#&@@"<< '\n'<<
"@@@@@@&&&#BG#&&@@@@@##PYJ!:.....YGJJ!^....:~^.      ^?5PBJ~:::^:~5J?77!~~~~^^^!7??7!~^^~!~~~!?G#&@@@"<< '\n'<<
"@@@&#B5J7~^:?##&@@@@&##5Y?~.....:PPJJ!:    :7J!^:......:!J7~^^~~:?P????7!~~~~~~~~~~~~!~~~~!?PB#&@@@@"<< '\n'<<
"@@&BGY~:....:Y#&@@@@@&#B5Y?^.....^G5YJ~. ...:?5YJ7!^:^^^^^^~~~~~~:YB5JYYYJ?7!!!~~~~~~~!!7YPB#&@@@@@@"<< '\n'<<
"@&#BPPJ~:....^5#&@@@@@&#B557^... .~B55J~::::::YP55YY?7!~~~~~~~~~~~^P&BGP55YYYYYJJJJJY5PGB##&@@@@@@@@"<< '\n'<<
"@@&#BPP?~:...:~G#&@@@@@&#BPP7: ....7BPP?~:^^^^~BBGPPPP5J?!!~~~~!!!~~P###BGGGGBBBBB######&&@@@@@@@@@@"<< '\n'<<
"@@@&#B557^:.. :!B#&@@@@&##GPP7^::::.JBPG7~~~~~^!B###BGGGGPY?7!!~~~~~~G#&&&&########&&&&@@@@@@@@@@@@@"<< '\n'<<
"@@@@##G55!^... :7B#&@@@@&##GGP!^^~^^:GBGG7~~~~~:7B#####BBBBGP5J7!7?JJP#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@&##G5Y!:... :J#&@@@@@&##BBJ!^~~~:?&GGP!~~!!~:J#&&&&####BBBGPPPGGB#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@&##PPJ!^^^:::Y#&@@@@@&##BJ~~~~~^!##GB5!!~~~~:Y#&@@@@&&##BB####&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@&##PPJ7^^^^^:JB#&&&&##BJ^~~~~~^JB##BBY!~!7???B#&@@@@@@&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@&#B5?77~^^~^:~?Y55YJ7^^~~~~~~7B####BBYYPPGGB#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@&#G?JJ7~~~~~^^^^^^^^~~~~~~!YB#&&&#BBBB####&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@&#B5YJJ7!~~~~~~~~~~~~!7?5G#&@@@@&##&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@@&##GPPP5YJ?77777??J5PB##&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@@@&&##BBBBBBBGGGBBB####&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@&&###########&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'<<
"@@@@@@@@@@@@@@@@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< '\n'
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
    else if(escolha == "konami"){
        cout << '\n' << "༼つಠ益ಠ༽つ ─=≡ΣO)) HADOUKEN" << '\n';
        goto ESCOLHA;
    }
    else
    {
        cout << '\n'<<"Entrada invalida, favor re-insira (Opcoes: jogar, tutorial)"<<'\n';
        goto ESCOLHA;
    }
    return 0;
}
