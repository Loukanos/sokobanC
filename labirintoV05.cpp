/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.5 (Lucas)
    Notas: Nessa versão o botão continuar do menu principal será implementado
    e mais 2 mapas serão adicionados.
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

void imprime (int m[8][9], int x, int y, int a, int b, int c, int d, int e, int f, int g, int h, int k, int l){//imprime o mapa
    ///Posiciona a escrita no início do console
        reposicionaCursor();

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<8;i++){
            for(int j=0;j<9;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0:if ((i==a && j ==b) || (i==c && j ==d) || (i ==e && j==f)|| (i==g && j==h) ||(i==k && j==l))
                        {
                            cout<<char(158);
                        }
                        else{
                         cout<<" "; 
                        }
                        break;
                        case 1: cout<<char(219); break; //parede
                        case 2:
                        if((i == a && j == b) || (i == c && j == d) || (i == e && j == f) ||(i==g && j==h) ||(i==k && j==l)){//mudar a caixa se estiver no objetivo
                            cout<<char(33);

                        }
                        else{
                            cout<<char(177);
                        }
                        
                         break;//caixa
                        //default: cout<<"-"; //erro
                    } //fim switch

                }
            }
            cout<<"\n";
        } //fim for mapa

        //cout<<"\n\na "<<a<<" b "<<b<<" c "<<c<<" d "<<d<<" e "<<e<<" f "<<f<<" x "<<x<<" y "<<y;//apenas para debug
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


bool checarVitoria(int m[8][9], int a, int b, int c, int d, int e, int f, int g, int h, int k, int l, int escolha) {//checar se existe uma caixa nos objetivos

if(escolha ==1){
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
}

if(escolha==2){

    int pararLoop = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 9; j++) {
            if((m[a][b] == 2) && (m[c][d] == 2) && (m[e][f] ==2) && (m[g][h] == 2)) {

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
}

if(escolha ==3){

    int pararLoop = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 9; j++) {
            if((m[a][b] == 2) && (m[c][d] == 2) && (m[e][f] ==2) && (m[g][h] == 2) && (m[k][l]==2)) {

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
}

return false;

}


void iniciaFase(int &a,int &b, int &c, int &d, int &e, int &f, int &g, int&h, int &k, int &l, int &x, int &y, int &movimentos, bool &game, int escolha){
    
    movimentos =1;//setar os movimentos em 1
    
if(escolha==1){//posicoes fase 1
    //Posi��o inicial do personagem no console
    x=6, y=3;
    //Posição dos objetivos
     a = 6;b = 4; c = 6 ; d = 5; e = 6 ;f = 6 ;g=50;h=50;k=50;l=50;//valores altos para não pegar na matriz(essa fase não precisa de tantos objetivos)

}

if(escolha==2){//fase 2
    x=3,y=1;
    a =3,b=3,c=4,d=3,e=3,f=4,g=4,h=4,k=50;l=50;

}

if(escolha==3){//fase 3
    x=5,y=5;
    a=3,b=1,c=1,d=3,e=3,f=5,g=5,h=3,k=3,l=3;

}




}

void rodarFase(int &a,int &b, int &c, int &d, int &e, int &f,int &g, int &h, int &k, int &l, int &x, int &y, int &movimentos, bool &game, int m[8][9],int escolha,int m2[8][9], int m3[8][9]){//roda a fase selecionada


    game = true;


    
                    

    cout<<"\n\n\n\n\n\n\n\n\n"<<"1-Voltar ao menu";

if(escolha == 1){

    while(game == true){
        //imprime
        imprime(m,x,y,a,b,c,d,e,f,g,h,k,l);
        movimento(m,x,y,game, movimentos);
        checarVitoria(m,a,b,c,d,e,f,g,h,k,l,escolha);
        
    } //fim do laço do jogo
}

if(escolha == 2){

    while(game == true){
        //imprime
        imprime(m2,x,y,a,b,c,d,e,f,g,h,k,l);
        movimento(m2,x,y,game, movimentos);
        checarVitoria(m2,a,b,c,d,e,f,g,h,k,l,escolha);
        
    } //fim do laço do jogo
}

if(escolha == 3){

    while(game == true){
        //imprime
        imprime(m3,x,y,a,b,c,d,e,f,g,h,k,l);
        movimento(m3,x,y,game, movimentos);
        checarVitoria(m3,a,b,c,d,e,f,g,h,k,l,escolha);
        
    } //fim do laço do jogo
}


}


void sobre(){//submenu "sobre"


    char teclaSobre;
    int lacoSobre =0;

    cout<<"Desenvolvedor: Lucas Iago Adriano"<<endl;
    cout<<"Marco, 2023"<<endl;
    cout<<"Felski, algoritmos e programacao 2"<<endl;
    cout<<"Como jogar: O jogador deve empurrar as caixas ate os objetivos 'x'. caixas em cima do objetivo sao marcadas como '!'."<<endl;
    cout<<"Nem o jogador nem as caixas podem atravessar as paredes. O jogador nao tem forca para empurrar 2 caixas simultaneamente."<<endl;
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


void reinicializaMatriz(int matriz[8][9],int escolha){


if(escolha==1){
    int valores[8][9] = { {1,1,1,1,1,0,0,0,0},
                          {1,0,0,0,1,1,1,1,1},
                          {1,0,2,0,1,0,0,0,1},
                          {1,0,0,0,1,2,1,0,1},
                          {1,1,1,2,0,0,0,0,1},
                          {0,1,0,0,0,1,1,1,1},
                          {0,1,0,0,0,0,0,1,0},
                          {0,1,1,1,1,1,1,1,0} };

    for(int i=0; i<8; i++){
        for(int j=0; j<9; j++){
            matriz[i][j] = valores[i][j];
        }
    }
}

if(escolha==2){

int valores[8][9]={ 0,0,1,1,1,1,0,0,0,//fase 2
                    0,0,1,0,0,1,0,0,0,
                    1,1,1,0,2,1,1,1,1,
                    1,0,2,0,0,0,2,0,1,
                    1,0,0,0,2,0,0,0,1,
                    1,1,1,0,0,1,1,1,1,
                    0,0,1,0,0,1,0,0,0,
                    0,0,1,1,1,1,0,0,0 };

    for(int i=0; i<8; i++){
        for(int j=0; j<9; j++){
            matriz[i][j] = valores[i][j];
        }
    }



}

if(escolha==3){

int valores[8][9]={ 1,1,1,1,1,1,1,0,0,//fase 3
                    1,0,0,0,0,1,1,0,0,
                    1,0,2,0,2,0,1,0,0,
                    1,0,0,2,0,0,1,0,0,
                    1,0,2,0,2,0,1,0,0,
                    1,1,0,0,0,0,1,0,0,
                    1,1,1,1,1,1,1,0,0,
                    0,0,0,0,0,0,0,0,0 };

    for(int i=0; i<8; i++){
        for(int j=0; j<9; j++){
            matriz[i][j] = valores[i][j];
        }
    }



}


}

int randomizaEscolha(){

    srand(time(0)); // inicializa o gerador de números aleatórios com o tempo atual
    return (rand() % 3) + 1; // retorna um número aleatório entre 1 e 3

}

void menu(){//menu principal

    static int a,b,c,d,e,f,g,h,k,l,y,x; //solução: transformar em vetor(São coordenadas dos objetivos)
    bool game = false;//fechar laço do jogo, encerrar partida
    static int movimento;//variavel para contar movimentos
    static bool continua;//variavel para checar se tinha jogo em andamento
    static int escolha;//variavel para checar escolha de fase

static int m[8][9]={1,1,1,1,1,0,0,0,0,//fase 1
                    1,0,0,0,1,1,1,1,1,
                    1,0,2,0,1,0,0,0,1,
                    1,0,0,0,1,2,1,0,1,
                    1,1,1,2,0,0,0,0,1,
                    0,1,0,0,0,1,1,1,1,
                    0,1,0,0,0,0,0,1,0,
                    0,1,1,1,1,1,1,1,0 };


static int m2[8][9]={ 0,0,1,1,1,1,0,0,0,//fase 2
                    0,0,1,0,0,1,0,0,0,
                    1,1,1,0,2,1,1,1,1,
                    1,0,2,0,0,0,2,0,1,
                    1,0,0,0,2,0,0,0,1,
                    1,1,1,0,0,1,1,1,1,
                    0,0,1,0,0,1,0,0,0,
                    0,0,1,1,1,1,0,0,0 };

static int m3[8][9]={ 1,1,1,1,1,1,1,0,0,//fase 3
                    1,0,0,0,0,1,1,0,0,
                    1,0,2,0,2,0,1,0,0,
                    1,0,0,2,0,0,1,0,0,
                    1,0,2,0,2,0,1,0,0,
                    1,1,0,0,0,0,1,0,0,
                    1,1,1,1,1,1,1,0,0,
                    0,0,0,0,0,0,0,0,0 };



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
        cout<<"[a]Fase 1"<<endl;
        cout<<"[b]Fase 2"<<endl;
        cout<<"[c]Fase 3"<<endl;
        cout<<"[d]Aleatorio"<<endl;
        cout<<"[e]Voltar"<<endl;
        switch(getch())
        {
            case 97://caso fase 1(a), e assim por diante
                escolha = 1;
                reinicializaMatriz(m,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;
            break;
            case 98:
                escolha = 2;
                reinicializaMatriz(m2,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;
            break;
            case 99:
                escolha = 3;
                reinicializaMatriz(m3,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;    

            break;
            case 100://randomizar
            escolha =randomizaEscolha();
            if(escolha ==1){
                reinicializaMatriz(m,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;

            }
            if(escolha==2){
                reinicializaMatriz(m2,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;
            }
            if(escolha ==3){
                reinicializaMatriz(m3,escolha);
                continua = true;
                system("cls");
                iniciaFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,escolha);
                rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
                lacoMenu++;    

            }
            break;


            case 101:
            system("cls");
            menu();

            break;
        }
        break;
        
        case 50://continuar
        if(continua == true){

        
            system("cls");
            rodarFase(a,b,c,d,e,f,g,h,k,l,x,y,movimento,game,m,escolha,m2,m3);
            lacoMenu++;
        }
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
} //fim main//fases: boxxle 2: #1, #2 e #3.
//o que melhorar no código?
//Principamente, remover variáveis estáticas
//Nas coordenadas, professor sugeriu vetorizar
//para as matrizes, ele sugeriu fazer uma função separada para a declaração de mapas
//no mais, ele disse que o tamanho das funções está bom
//não é necessário explicar o código do cursor
//fazer melhorias em uma outra versão