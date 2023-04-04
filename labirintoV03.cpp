/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.3 (Lucas)
    notas:nessa versão foi implementado um menu rudimentar.
*/
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;

void cursor(){
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    

}

void rodarJogo(){


        //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.

    int m[8][9  ]={ 1,1,1,1,1,0,0,0,0,
                    1,0,0,0,1,1,1,1,1,
                    1,0,2,0,1,0,0,0,1,
                    1,0,0,0,1,2,1,0,1,
                    1,1,1,2,0,0,0,0,1,
                    0,1,0,0,0,1,1,1,1,
                    0,1,0,0,3,3,3,1,0,
                    0,1,1,1,1,1,1,1,0 };

    //Posi��o inicial do personagem no console
    int x=6, y=3;
    //Vari�vel para tecla precionada
    char tecla;

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<8;i++){
            for(int j=0;j<9;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<char(177);break;//caixa
                        case 3: cout<<char(158);break;//objetivo
                        //default: cout<<"-"; //erro
                    } //fim switch

                }
            }
            cout<<"\n";
        } //fim for mapa
        
        ///executa os movimentos. Att(lucas): ifs adicionados para detectar caixas e paredes
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
    case 72: case 'w': //cima
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2 || m[x - 1][y] == 3 ) {//se a próxima posição é vazia ou tem uma caixa ou tem objtivo
            if (m[x - 1][y] == 2 && (m[x - 2][y] == 0 || m[x - 2][y] == 3 )) {//se a posição tem uma caixa e a posição depois está vazia ou temo obj
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                x--;//mover jogador
            }
            else if (m[x - 1][y] == 0 || m[x - 1][y] == 3) {//se estiver vazia ou com objetivo, andar
                x--;
            }
        }
        break;
    case 80: case 's': //baixo
        if (m[x + 1][y] == 0 || m[x + 1][y] == 2 ||  m[x + 1][y] == 3) {
            if (m[x + 1][y] == 2 && (m[x + 2][y] == 0 ||m[x + 2][y] == 3 )) {
                m[x + 2][y] = 2;
                m[x + 1][y] = 0;
                x++;
            }
            else if (m[x + 1][y] == 0 || m[x + 1][y] == 3) {
                x++;
            }
        }
        break;
    case 75:case 'a': //esquerda
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2 ||  m[x][y - 1] == 3) {
            if (m[x][y - 1] == 2 && (m[x][y - 2] == 0 || m[x][y - 2] == 3)) {
                m[x][y - 2] = 2;
                m[x][y - 1] = 0;
                y--;
            }
            else if (m[x][y - 1] == 0 || m[x][y - 1] == 3) {
                y--;
            }
        }
        break;
    case 77: case 'd': //direita
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2 ||m[x][y + 1] == 3) {
            if (m[x][y + 1] == 2 && (m[x][y + 2] == 0 || m[x][y + 2] == 3)) {
                m[x][y + 2] = 2;
                m[x][y + 1] = 0;
                y++;
            }
            else if (m[x][y + 1] == 0 || m[x][y + 1] == 3) {
                y++;
            }
        }
        break;
            }
         }

        
    } //fim do laço do jogo    
}


void sobre(){

    cout<<"Desenvolvedor: Lucas Iago Adriano"<<endl;
    cout<<"Marco, 2023"<<endl;
    cout<<"Felski, algoritmos e programacao 2"<<endl;
    cout<<"aqui vou botar as regras"<<endl;
    system("PAUSE");

}

void menu(){

    char teclaMenu;
    int lacoMenu = 0;

    cursor();
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
            rodarJogo();
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
            system("cls");
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
