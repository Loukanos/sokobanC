/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.2 (Lucas)
*/
#include<iostream>
#include<windows.h>
#include<conio.h>

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

    int m[10][10]={ 1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,2,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,2,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1 };

    //Posi��o inicial do personagem no console
    int x=5, y=5;
    //Vari�vel para tecla precionada
    char tecla;

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<char(254);break;//caixa
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
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2) {//se a próxima posição é vazia ou tem uma caixa
            if (m[x - 1][y] == 2 && (m[x - 2][y] == 0)) {//se a posição tem uma caixa e a posição depois está vezia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                x--;//mover jogaodr
            }
            else if (m[x - 1][y] == 0) {
                x--;
            }
        }
        break;
    case 80: case 's': //baixo
        if (m[x + 1][y] == 0 || m[x + 1][y] == 2) {
            if (m[x + 1][y] == 2 && (m[x + 2][y] == 0)) {
                m[x + 2][y] = 2;
                m[x + 1][y] = 0;
                x++;
            }
            else if (m[x + 1][y] == 0) {
                x++;
            }
        }
        break;
    case 75:case 'a': //esquerda
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2) {
            if (m[x][y - 1] == 2 && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                m[x][y - 1] = 0;
                y--;
            }
            else if (m[x][y - 1] == 0) {
                y--;
            }
        }
        break;
    case 77: case 'd': //direita
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2) {
            if (m[x][y + 1] == 2 && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                m[x][y + 1] = 0;
                y++;
            }
            else if (m[x][y + 1] == 0) {
                y++;
            }
        }
        break;
            }
         }

        
    } //fim do laço do jogo


    


    
}

int main()
{

    cursor();
    rodarJogo();

    return 0;
} //fim main//peguei o boxxle 2: 1, 2 e 3/checar tabela ascii para ver os caracteres disponíveis(informação não pertinente ao código)