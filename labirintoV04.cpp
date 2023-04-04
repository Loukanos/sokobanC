/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.4 (Lucas)
    notas: nessa versão foram implementados os objetivos e o menu foi desenvolvido. 
    O código também foi organizado em funções.
*/
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;

void menu();//protótipo da função menu para poder realizar a chamada

void desligaCursor(){//para desligar o cursor (=
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
}

void reposicionaCursor(){//faz o que ta escrito ali embaixo
        //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}    

void imprime (int m[8][9], int x, int y, int a, int b, int c, int d, int e, int f){//imprime o mapa
    ///Posiciona a escrita no início do console
        reposicionaCursor();

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<8;i++){
            for(int j=0;j<9;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0:if ((i==a && j ==b) || (i==c && j ==d) || (i ==e && j==f))
                        {
                            cout<<char(158);break;
                        }
                        else{
                         cout<<" "; break; //caminho
                        }
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<char(177);break;//caixa
                        //default: cout<<"-"; //erro
                    } //fim switch

                }
            }
            cout<<"\n";
        } //fim for mapa
}


void contaMovimento(int &movimentos){//adiciona ao contador de movimentos,usando variável movimentos da função fase. Usado na fç jogo


    cout<<"           Movimentos:"<<movimentos;

    movimentos++;


}
void movimento(int m[8][9], int &x, int &y, bool &game, int &movimentos){//movimenta o player e as caixas, com colisão 
    
        ///executa os movimentos. Att(lucas): ifs adicionados para detectar caixas e paredes
        char tecla;//variável para tecla pressionada
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
    case 72: case 'w': //cima
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2) {//se a próxima posição é vazia ou tem uma caixa
            if (m[x - 1][y] == 2 && (m[x - 2][y] == 0)) {//se a posição tem uma caixa e a posição depois está vazia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                x--;//mover jogador
                contaMovimento(movimentos);
            }
            else if (m[x - 1][y] == 0) {//se estiver vazia, andar
                x--;
                contaMovimento(movimentos);
            }
        }
        break;
    case 80: case 's': //baixo
        if (m[x + 1][y] == 0 || m[x + 1][y] == 2) {
            if (m[x + 1][y] == 2 && (m[x + 2][y] == 0 )) {
                m[x + 2][y] = 2;
                m[x + 1][y] = 0;
                x++;
                contaMovimento(movimentos);
            }
            else if (m[x + 1][y] == 0) {
                x++;
                contaMovimento(movimentos);
            }
        }
        break;
    case 75:case 'a': //esquerda
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2) {
            if (m[x][y - 1] == 2 && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                m[x][y - 1] = 0;
                y--;
                contaMovimento(movimentos);
            }
            else if (m[x][y - 1] == 0) {
                y--;
                contaMovimento(movimentos);
            }
        }
        break;
    case 77: case 'd': //direita
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2) {
            if (m[x][y + 1] == 2 && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                m[x][y + 1] = 0;
                y++;
                contaMovimento(movimentos);
            }
            else if (m[x][y + 1] == 0) {
                y++;
                contaMovimento(movimentos);
            }
        }
        break;
    case 49://voltar ao menu principal
            system("cls");
            menu();
            game = false;
    break;
            }
         }


}


bool checarVitoria(int m[8][9], int a, int b, int c, int d, int e, int f) {//checar se existe uma caixa nos objetivos

    int pararLoop = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 9; j++) {
            if((m[a][b] == 2) && (m[c][d] == 2) && (m[e][f] ==2)) {

                while(pararLoop <2){//while para que o contador não fique aumentando infinitamente(Estamos num loop)
                    pararLoop++;
                }

                if(pararLoop !=0)//if para que a mensagem seja escrita apenas uma vez
                {
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<"Fase Completa!";
                }
                return true;

                

            }
        }
    }
    return false;
}


void rodarFase(){//roda a fase selecionada

    int m[8][9  ]={ 1,1,1,1,1,0,0,0,0,
                    1,0,0,0,1,1,1,1,1,
                    1,0,2,0,1,0,0,0,1,
                    1,0,0,0,1,2,1,0,1,
                    1,1,1,2,0,0,0,0,1,
                    0,1,0,0,0,1,1,1,1,
                    0,1,0,0,0,0,0,1,0,
                    0,1,1,1,1,1,1,1,0 };


    cout<<"\n\n\n\n\n\n\n\n\n"<<"1-Voltar ao menu";

    //Posi��o inicial do personagem no console
    int x=6, y=3;
    //Posição dos objetivos
    int a = 6, b = 4, c = 6 , d = 5, e = 6 ,f = 6 ;

    int movimentos =1;

    bool game = true;

    while(game == true){
        //imprime
        imprime(m,x,y,a,b,c,d,e,f);
        movimento(m,x,y,game, movimentos);
        checarVitoria(m,a,b,c,d,e,f);
        
    } //fim do laço do jogo    
}

void sobre(){//submenu "sobre"


    char teclaSobre;
    int lacoSobre =0;

    cout<<"Desenvolvedor: Lucas Iago Adriano"<<endl;
    cout<<"Marco, 2023"<<endl;
    cout<<"Felski, algoritmos e programacao 2"<<endl;
    cout<<"aqui vou botar as regras"<<endl;
    cout<<endl<<"1-Voltar";

    while(lacoSobre == 0){
            if ( _kbhit() ){

            teclaSobre = getch();
            switch (teclaSobre)
            {
            case 49:
                system("cls");
                menu();
                lacoSobre++;
                break;
            
            }
        }
    }//fim do laço sobre

}

void menu(){//menu principal

    char teclaMenu;
    int lacoMenu = 0;

    desligaCursor();
    cout<<"MENU PRINCIPAL"<<endl;
    cout<<"1-Novo Jogo"<<endl;
    cout<<"2-Continuar"<<endl;
    cout<<"3-Sobre"<<endl;
    cout<<"4-Fim"<<endl;


   while (lacoMenu == 0){
    
    if ( _kbhit() ){

        teclaMenu = getch();
        switch (teclaMenu)
        {
        case 49://novo jogo
            system("cls");
            rodarFase();
            lacoMenu++;
            break;
        
        case 50://continuar
            system("cls");
            lacoMenu++;
            break;

        case 51://Sobre
            system("cls");
            sobre();
            lacoMenu++;
            break;
        case 52://fim
            lacoMenu++;
            break;
        
        }
    }
   }//fim laço do menu    

}

int main()
{

    menu();

    return 0;
} //fim main
