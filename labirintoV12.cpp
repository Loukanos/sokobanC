/**
    Estrutura inicial para um jogo de labirinto
    versão: 12 (Lucas)
    Notas:fazer todos os mapas serem lidos por arquivos
*/

#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>

using namespace std;


struct Score {
    string nome;
    int fase;
    int movimentos;
};

bool cmpScore(Score a, Score b) {//funcao para o sort
    if (a.movimentos == b.movimentos) {//se tiverem mesmo numero de movimentos, ordena por fase
        return a.fase < b.fase;//fases menores vem primeiro
    }
    return a.movimentos < b.movimentos;//scores com menos movimento vem primeiro
}

void salvaMovimentos(int &x, int &y,bool game,char tecla){

    ofstream meuArquivo;
    meuArquivo.open("movimentos.txt",ios::app);
    if(meuArquivo.is_open()){
        //meuArquivo<<"houve movimento\n";
        if((tecla == 'w') ||(tecla==72)){
            meuArquivo<<"x--\n";
        }
        if((tecla == 's') ||(tecla==80)){
            meuArquivo<<"x++\n";
        }
        if((tecla == 'a') ||(tecla==75)){
            meuArquivo<<"y--\n";
        }
        if((tecla == 'd') ||(tecla==77)){
            meuArquivo<<"y++\n";
        }
    }
    else{
        cout<<"arquivo não pode ser aberto";
        return;
    }
    meuArquivo.close();
    return;
}

void lerMovimentosLidos(int m[8][9], int &x, int &y, bool &game, int &movimentos, int &retornar){
    
    vector<string> comandos;
    int limite = 0;
    fstream meuArquivo;
    meuArquivo.open("movimentos.txt");
    if(meuArquivo.is_open()){
        string frase;
        while (meuArquivo.eof()==false && limite<retornar)
        {
            getline(meuArquivo,frase);
            if(frase.find("x--") !=string::npos){
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2 ||m[x - 1][y] == 3||m[x - 1][y] == 4 ) {//se a próxima posição é vazia ou tem uma caixa ou tem obj
            if ((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 0)) {//se a posição tem uma caixa ou 4 e a posição depois está vazia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                movimentos++;//adiciona ao contador de movimentos diretamente pra não ter cout
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 3)){//se a posição tem uma caixa ou 4 e a posição depois tem um objetivo
                m[x - 2][y] = 4;//mover caixa(a próxima posição se torna um 4)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                    m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                movimentos++;
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x - 1][y] == 0||m[x - 1][y] == 3 ) {//se estiver vazia, ou com objetivo andar
                x--;
                movimentos++;
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }

            }
            if(frase.find("x++") !=string::npos){

        if (m[x + 1][y] == 0 || m[x + 1][y] == 2|| m[x + 1][y] == 3|| m[x + 1][y] == 4) {
            if ((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 0 )) {
                m[x + 2][y] = 2;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 3 )){
                m[x + 2][y] = 4;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x + 1][y] == 0|| m[x + 1][y] == 3) {
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
                
            }
            if(frase.find("y--") !=string::npos){
                
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2||m[x][y - 1] == 3||m[x][y - 1] == 4) {
            if ((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 3)){
                m[x][y - 2] = 4;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x][y - 1] == 0||m[x][y - 1] == 3) {
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
            }
            if(frase.find("y++") !=string::npos){
                
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2|| m[x][y + 1] == 3|| m[x][y + 1] == 4) {
            if ((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 3)){
                m[x][y + 2] = 4;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x][y + 1] == 0||m[x][y + 1] == 3) {
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
            }
        }
    }

    meuArquivo.close();
    ofstream meuArquivo2;
    meuArquivo2.open("movimentos.txt");
    if(meuArquivo2.is_open()){
        for (const auto& elemento : comandos){
            meuArquivo2 << elemento << "\n";
        }
    }
    else{
        cout<<"arquivo não abriu";
    }
    meuArquivo2.close();
}


void lerMovimentosLidos(int m[30][30], int &x, int &y, bool &game, int &movimentos, int &retornar){
    
    vector<string> comandos;
    int limite = 0;
    fstream meuArquivo;
    meuArquivo.open("movimentos.txt");
    if(meuArquivo.is_open()){
        string frase;
        while (meuArquivo.eof()==false && limite<retornar)
        {
            getline(meuArquivo,frase);
            if(frase.find("x--") !=string::npos){
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2 ||m[x - 1][y] == 3||m[x - 1][y] == 4 ) {//se a próxima posição é vazia ou tem uma caixa ou tem obj
            if ((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 0)) {//se a posição tem uma caixa ou 4 e a posição depois está vazia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                movimentos++;//adiciona ao contador de movimentos diretamente pra não ter cout
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 3)){//se a posição tem uma caixa ou 4 e a posição depois tem um objetivo
                m[x - 2][y] = 4;//mover caixa(a próxima posição se torna um 4)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                    m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                movimentos++;
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x - 1][y] == 0||m[x - 1][y] == 3 ) {//se estiver vazia, ou com objetivo andar
                x--;
                movimentos++;
                limite++;
                comandos.push_back("x--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }

            }
            if(frase.find("x++") !=string::npos){

        if (m[x + 1][y] == 0 || m[x + 1][y] == 2|| m[x + 1][y] == 3|| m[x + 1][y] == 4) {
            if ((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 0 )) {
                m[x + 2][y] = 2;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 3 )){
                m[x + 2][y] = 4;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x + 1][y] == 0|| m[x + 1][y] == 3) {
                x++;
                movimentos++;
                limite++;
                comandos.push_back("x++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
                
            }
            if(frase.find("y--") !=string::npos){
                
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2||m[x][y - 1] == 3||m[x][y - 1] == 4) {
            if ((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 3)){
                m[x][y - 2] = 4;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x][y - 1] == 0||m[x][y - 1] == 3) {
                y--;
                movimentos++;
                limite++;
                comandos.push_back("y--");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
            }
            if(frase.find("y++") !=string::npos){
                
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2|| m[x][y + 1] == 3|| m[x][y + 1] == 4) {
            if ((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 3)){
                m[x][y + 2] = 4;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
            else if (m[x][y + 1] == 0||m[x][y + 1] == 3) {
                y++;
                movimentos++;
                limite++;
                comandos.push_back("y++");
                //salvaMovimentos(m,x,y,game,tecla);
            }
        }
            }
        }
    }

    meuArquivo.close();
    ofstream meuArquivo2;
    meuArquivo2.open("movimentos.txt");
    if(meuArquivo2.is_open()){
        for (const auto& elemento : comandos){
            meuArquivo2 << elemento << "\n";
        }
    }
    else{
        cout<<"arquivo não abriu";
    }
    meuArquivo2.close();
}


void menu(string nome,int m[8][9],int m2[8][9], int m3[8][9], int m4[30][30], int movimento, bool continua, int escolha, int x, int y);//protótipo da função menu para poder realizar a chamada

string menuNome(){
    string nomeJogador;
    cout<<"Insira seu nome: ";
    cin>>nomeJogador;
    system("CLS");
    return nomeJogador;

}


void placar(string nome,bool vitoria, int movimentos, int escolha, bool game){

    fstream meuArquivo;
    if ((vitoria == true) && game == true) {
        meuArquivo.open("placar.txt", ios::in | ios::out);
        if (meuArquivo.is_open()) {
            vector<string> fases;//vetor dinamico de strings
            vector<Score> scores;//vetor dinamico da struct score

            // Ler fases e scores do arquivo
            while (!meuArquivo.eof()) {
                string frase;
                getline(meuArquivo, frase);
                if (frase.find("FASE") != string::npos) {//se encontrar a tag #Fase, vai colocar a linha toda no vetor fase
                    fases.push_back(frase);
                } else if (frase.length() > 0) {//se o comprimento da string for maior que 0
                    Score s;//cria uma string e atribui os devidos valores a partir das flags
                    s.nome = frase.substr(0, frase.find(" terminou a fase"));//o que estiver antes disso será o nome
                    s.fase = stoi(frase.substr(frase.find("em:") -2));//o que estiver antes disso será a fase(do score)
                    s.movimentos = stoi(frase.substr(frase.find(":") + 1));//o que estiver depois disso serão os movimentos
                    scores.push_back(s);//guarda essa struct no vetor dinamico scores
                }
            }

            meuArquivo.close();//fecha arquivo
            meuArquivo.open("placar.txt", ios::out);//abre no modo out

            // Adiciona score atual ao vetor de scores
            Score s;
            s.nome = nome;
            s.fase = escolha;
            s.movimentos = movimentos;
            scores.push_back(s);

            // Ordenar vetor de scores por número de movimentos e fase
            sort(scores.begin(), scores.end(), cmpScore);

            // Imprimir fases e scores no arquivo
            for (int i = 0; i < fases.size(); i++) {
                meuArquivo <<"\n"<< fases[i] << "\n\n";//imprime fases
                for (int j = 0; j < scores.size(); j++) {
                    if (scores[j].fase == i + 1) {
                        meuArquivo << scores[j].nome << " terminou a fase "<< scores[j].fase << " em: " << scores[j].movimentos<< " movimentos\n\n";
                    }
                }
            }
            meuArquivo.close();
        } else {
            cout << "Arquivo não pode ser aberto";
            return;
        }
    }
}


void lerMatriz(int m[8][9], int &x, int &y,int escolha){

    //le matriz do arquivo mapas
    ifstream arquivoMapa;


    if(escolha==1){
        arquivoMapa.open("mapa1.txt");
    }
    if(escolha==2){
        arquivoMapa.open("mapa2.txt");
    }
    if(escolha==3){
        arquivoMapa.open("mapa3.txt");
    }
    if(escolha==4){
        arquivoMapa.open("mapas.txt");
    }
    string matriz;

    //le coordenadas x e y
    string xStr, yStr;
    getline(arquivoMapa, xStr, '=');//comeca ler xstring do igual
    getline(arquivoMapa, xStr, ' ');//ate proximo espaco vazio
    getline(arquivoMapa, yStr, '=');//le y do segundo igual
    getline(arquivoMapa, yStr);//ate final daquela linha

    x = stoi(xStr);
    y = stoi(yStr);

    //le matriz
    if(arquivoMapa.is_open()){
        for(int i=0;i<8;i++){
            for(int j=0;j<9;j++){
                arquivoMapa>>matriz;
                m[i][j]=stoi(matriz);
            }
        }
    }
    arquivoMapa.close();
    cout<<endl;
}

void lerMatrizExtra(int m[30][30], int &x, int &y){

    //le matriz do arquivo mapas
    ifstream arquivoMapa;
    arquivoMapa.open("mapas.txt");
    string matriz;
    string linha;

    getline(arquivoMapa,matriz);
    x=stoi(matriz);
    getline(arquivoMapa,matriz);
    y=stoi(matriz);
    //le coordenadas x e y




    //le matriz

    if (arquivoMapa.is_open()) {
        for (int i = 0; i < 30; i++) {
            getline(arquivoMapa, linha);
            stringstream ss(linha);
            for (int j = 0; j < 30; j++) {
                string valor;
                ss >> valor;
                if (valor.empty()) {
                    m[i][j] = ' ';
                } else {
                    m[i][j] = stoi(valor);
                }
            }
        }
    }
    arquivoMapa.close();

    cout<<endl;
}

void lerPlacar(string nome,int m[8][9],int m2[8][9], int m3[8][9],int m4[30][30], int movimento, bool continua, int escolha,int x, int y){

    int lacoPlacar =0;
    int teclaPlacar;

    ifstream meuArquivo;
    meuArquivo.open("placar.txt");
    string frase;
    while(meuArquivo.eof()==false){
        getline(meuArquivo,frase);
        cout<<frase<<"\n";
    }

    cout<<"1-VOLTAR";

        while(lacoPlacar == 0){
            if ( _kbhit() ){

            teclaPlacar = getch();
            switch (teclaPlacar)
            {
            case 49://1-voltar(ao menu)
                system("cls");
                menu(nome,m,m2,m3,m4, movimento, continua, escolha,x,y);
                lacoPlacar++;
                break;
            
            }
        }
    }//fim do laço sobre
}

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

void imprimeMapa (int m[8][9], int x, int y){//imprimeMapa o mapa
    ///Posiciona a escrita no início do console
        reposicionaCursor();

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<8;i++){//laço para impressão da matriz e elementos importantes
            for(int j=0;j<9;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0:
                         cout<<" "; //imprimeMapa espaço vazio
                        break;
                        case 1: cout<<char(219); break; //parede
                        case 2://caixa
                            cout<<char(177);//caixa normal
                         break;
                        case 3:
                            cout<<char(158);
                        break;
                        case 4:
                            cout<<char(33);
                        break;
            
                        //default: cout<<"-"; //erro
                    } //fim switch

                }
            }
            cout<<"\n";
        } //fim for mapa

        //cout<<"\n\na "<<a<<" b "<<b<<" c "<<c<<" d "<<d<<" e "<<e<<" f "<<f<<" x "<<x<<" y "<<y;//apenas para debug
}


void imprimeMapa (int m[30][30], int x, int y){//imprimeMapa o mapa
    ///Posiciona a escrita no início do console
        reposicionaCursor();

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<30;i++){//laço para impressão da matriz e elementos importantes
            for(int j=0;j<30;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (m[i][j]){
                        case 0:
                         cout<<" "; //imprimeMapa espaço vazio
                        break;
                        case 1: cout<<char(219); break; //parede
                        case 2://caixa
                            cout<<char(177);//caixa normal
                         break;
                        case 3:
                            cout<<char(158);
                        break;
                        case 4:
                            cout<<char(33);
                        break;
            
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
         if ( _kbhit() ){//verifica se há entradas no teclado
            tecla = getch();//retorna a tecla digitada em tecla
            switch(tecla)
            {
    case 72: case 'w': //cima
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2 ||m[x - 1][y] == 3||m[x - 1][y] == 4 ) {//se a próxima posição é vazia ou tem uma caixa ou tem obj
            if ((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 0)) {//se a posição tem uma caixa ou 4 e a posição depois está vazia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 3)){//se a posição tem uma caixa ou 4 e a posição depois tem um objetivo
                m[x - 2][y] = 4;//mover caixa(a próxima posição se torna um 4)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                    m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x - 1][y] == 0||m[x - 1][y] == 3 ) {//se estiver vazia, ou com objetivo andar
                x--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 80: case 's': //baixo
        if (m[x + 1][y] == 0 || m[x + 1][y] == 2|| m[x + 1][y] == 3|| m[x + 1][y] == 4) {
            if ((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 0 )) {
                m[x + 2][y] = 2;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 3 )){
                m[x + 2][y] = 4;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x + 1][y] == 0|| m[x + 1][y] == 3) {
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 75:case 'a': //esquerda
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2||m[x][y - 1] == 3||m[x][y - 1] == 4) {
            if ((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 3)){
                m[x][y - 2] = 4;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x][y - 1] == 0||m[x][y - 1] == 3) {
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 77: case 'd': //direita
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2|| m[x][y + 1] == 3|| m[x][y + 1] == 4) {
            if ((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 3)){
                m[x][y + 2] = 4;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x][y + 1] == 0||m[x][y + 1] == 3) {
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
      }
    }


}

void movimento(int m[30][30], int &x, int &y, bool &game, int &movimentos){//movimenta o player e as caixas, com colisão 
    
        ///executa os movimentos. Att(lucas): ifs adicionados para detectar caixas e paredes
        char tecla;//variável para tecla pressionada
         if ( _kbhit() ){//verifica se há entradas no teclado
            tecla = getch();//retorna a tecla digitada em tecla
            switch(tecla)
            {
    case 72: case 'w': //cima
        if (m[x - 1][y] == 0 || m[x - 1][y] == 2 ||m[x - 1][y] == 3||m[x - 1][y] == 4 ) {//se a próxima posição é vazia ou tem uma caixa ou tem obj
            if ((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 0)) {//se a posição tem uma caixa ou 4 e a posição depois está vazia
                m[x - 2][y] = 2;//mover caixa(a próxima posição se torna uma  caixa)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x - 1][y] == 2 || m[x - 1][y] == 4) && (m[x - 2][y] == 3)){//se a posição tem uma caixa ou 4 e a posição depois tem um objetivo
                m[x - 2][y] = 4;//mover caixa(a próxima posição se torna um 4)
                if(m[x - 1][y] == 4){//se a proxima posicao era um 4
                    m[x - 1][y] = 3;//vai ficar um objetivo
                }
                else{
                    m[x - 1][y] = 0;//e a posição anterior fica vazia
                }
                x--;//mover jogador
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x - 1][y] == 0||m[x - 1][y] == 3 ) {//se estiver vazia, ou com objetivo andar
                x--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 80: case 's': //baixo
        if (m[x + 1][y] == 0 || m[x + 1][y] == 2|| m[x + 1][y] == 3|| m[x + 1][y] == 4) {
            if ((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 0 )) {
                m[x + 2][y] = 2;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x + 1][y] == 2||m[x + 1][y] == 4) && (m[x + 2][y] == 3 )){
                m[x + 2][y] = 4;
                if(m[x + 1][y] == 4){
                    m[x + 1][y] = 3;
                }
                else{
                    m[x + 1][y] = 0;
                }
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x + 1][y] == 0|| m[x + 1][y] == 3) {
                x++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 75:case 'a': //esquerda
        if (m[x][y - 1] == 0 || m[x][y - 1] == 2||m[x][y - 1] == 3||m[x][y - 1] == 4) {
            if ((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 0)) {
                m[x][y - 2] = 2;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x][y - 1] == 2||m[x][y - 1] == 4) && (m[x][y - 2] == 3)){
                m[x][y - 2] = 4;
                if(m[x][y - 1] == 4){
                    m[x][y - 1] = 3;
                }
                else{
                m[x][y - 1] = 0;
                }
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x][y - 1] == 0||m[x][y - 1] == 3) {
                y--;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
    case 77: case 'd': //direita
        if (m[x][y + 1] == 0 || m[x][y + 1] == 2|| m[x][y + 1] == 3|| m[x][y + 1] == 4) {
            if ((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 0)) {
                m[x][y + 2] = 2;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if((m[x][y + 1] == 2||m[x][y + 1] == 4) && (m[x][y + 2] == 3)){
                m[x][y + 2] = 4;
                if(m[x][y + 1] == 4){
                    m[x][y + 1] = 3;
                }
                else{
                    m[x][y + 1] = 0;
                }
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
            else if (m[x][y + 1] == 0||m[x][y + 1] == 3) {
                y++;
                contaMovimento(movimentos);
                salvaMovimentos(x,y,game,tecla);
            }
        }
        break;
      }
    }


}


void voltarMenu(string nome,int m[8][9],int m2[8][9], int m3[8][9],int m4[30][30],bool &game, int movimento, bool continua, int escolha, int x, int y){

//a função abaixo foi utilizada para não entrar em conflito com a função movimento, que já está usando getch e _kbhit
//a função checa se a tecla 1 foi pressionada. caracter 1 argumento da fc,que e comparado com um AND com a mascara 0x8000,
//que representa o bit mais significativo de um numero de 16 bits, que e usada para indicar se a tecla esta pressionada ou não.


if (GetAsyncKeyState('1') & 0x8000) {
  system("cls");
  menu(nome, m, m2, m3,m4,movimento, continua, escolha,x,y);
  game = false;
}




}

bool checarVitoria2(string nome,int m[8][9],int movimentos){

    int pararLoop = 0;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 9; j++) {
                if (m[i][j] == 3) {

                    return false; // Se encontrar um 3, retorna false
                }
            }
        }
    if(pararLoop ==0)//if para que a mensagem seja escrita apenas uma vez
    {
        cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<"Fase Completa!";            
        pararLoop++;
    }
    return true; // Se não encontrar um 3, retorna true(vitoria)
}

bool checarVitoria2(string nome,int m[30][30],int movimentos){

    int pararLoop = 0;

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                if (m[i][j] == 3) {

                    return false; // Se encontrar um 3, retorna false
                }
            }
        }
    if(pararLoop ==0)//if para que a mensagem seja escrita apenas uma vez
    {
        cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<"Fase Completa!";            
        pararLoop++;
    }
    return true; // Se não encontrar um 3, retorna true(vitoria)
}

void iniciaFase(int &x, int &y, int &movimentos, bool &game, int escolha){
    
    movimentos=1;//setar os movimentos em 1
    
    //essa funcao reiniciava a posicao do jogador tambem mas agora que le dos arquivos só serve para resetar o contador de movimento

}

void rodarFase(string nome,int &x, int &y, int &movimentos, bool &game, int m[8][9],int escolha,int m2[8][9], int m3[8][9],int m4[30][30],bool continua,bool &extra,int &retornar){//roda a fase selecionada

    game = true;//iniciando o laco do jogo


    
                    

    cout<<"\n\n\n\n\n\n\n\n\n"<<"1-Voltar ao menu";//para que a qualquer momento o jogador saiba que pode voltar ao menu

    int terminaL=0;//variavel para que o placar não fique em loop
    int teste = 0;

if(escolha == 1){

    while(game == true){
        //imprimeMapa
        imprimeMapa(m,x,y);
        movimento(m,x,y,game, movimentos);
        if((teste==0) && (extra ==true)){
            lerMovimentosLidos(m,x,y,game,movimentos,retornar);
            teste++;
        }
        bool vitoria =checarVitoria2(nome,m,movimentos);
        voltarMenu(nome,m,m2,m3,m4,game, movimentos, continua, escolha,x,y);
        if((vitoria == true)&&terminaL==0){
            placar(nome,vitoria,movimentos,escolha,game);
            terminaL++;
        }
        
    } //fim do laço do jogo
}

if(escolha == 2){

    while(game == true){
        //imprimeMapa
        imprimeMapa(m2,x,y);
        movimento(m2,x,y,game, movimentos);
        if((teste==0) && (extra ==true)){
            lerMovimentosLidos(m2,x,y,game,movimentos,retornar);
            teste++;
        }
        bool vitoria =checarVitoria2(nome,m2,movimentos);
        voltarMenu(nome,m,m2,m3,m4,game, movimentos, continua, escolha,x,y);
        if((vitoria == true)&&terminaL==0){
            placar(nome,vitoria,movimentos,escolha,game);
            terminaL++;
        }
    } //fim do laço do jogo
}

if(escolha == 3){

    while(game == true){
        //imprimeMapa
        imprimeMapa(m3,x,y);
        movimento(m3,x,y,game, movimentos);
        if((teste==0) && (extra ==true)){
            lerMovimentosLidos(m3,x,y,game,movimentos,retornar);
            teste++;
        }
        bool vitoria = checarVitoria2(nome,m3,movimentos);
        voltarMenu(nome,m,m2,m3,m4,game, movimentos, continua, escolha,x,y);
        if((vitoria == true)&&terminaL==0){
            placar(nome,vitoria,movimentos,escolha,game);
            terminaL++;
        }
        
    } //fim do laço do jogo
}

if(escolha == 4){

    while(game == true){
        //imprimeMapa
        imprimeMapa(m4,x,y);
        movimento(m4,x,y,game, movimentos);
        if((teste==0) && (extra ==true)){
            lerMovimentosLidos(m4,x,y,game,movimentos,retornar);
            teste++;
        }
        bool vitoria = checarVitoria2(nome,m4,movimentos);
        voltarMenu(nome,m,m2,m3,m4,game, movimentos, continua, escolha,x,y);
        if((vitoria == true)&&terminaL==0){
            placar(nome,vitoria,movimentos,escolha,game);
            terminaL++;
        }
        
    } //fim do laço do jogo
}

}


void sobre(string nome,int m[8][9],int m2[8][9], int m3[8][9],int m4[30][30], int movimento, bool continua, int escolha,int x, int y){//submenu "sobre"


    char teclaSobre;
    int lacoSobre =0;//para controlar o andamento desse submenu

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
            case 49://1-voltar(ao menu)
                system("cls");
                menu(nome,m,m2,m3,m4, movimento, continua, escolha,x,y);
                lacoSobre++;
                break;
            
            }
        }
    }//fim do laço sobre

}


void reinicializaMatriz(int matriz[8][9],int m4[30][30],int escolha,int &x, int &y){

    if(escolha ==4){
        lerMatrizExtra(m4,x,y);
    }
    else{
        lerMatriz(matriz,x,y,escolha);
    }

}

int randomizaEscolha(){

    srand(time(0)); // inicializa o gerador de números aleatórios com o tempo atual
    return (rand() % 4) + 1; // retorna um número aleatório entre 1 e 4

}

void inicializaJogo(){

    int y,x;
    int movimento;//variavel para contar movimentos
    bool continua;//variavel para checar se tinha jogo em andamento
    int escolha=1;//variavel para checar escolha de fase.
    //escolha inicia em 1 pois se estiver vazio da um erro na leitura de arquivos, e não identifico por que.


    int m[8][9];
    lerMatriz(m,x,y,escolha);


    escolha=2;
    int m2[8][9];
    lerMatriz(m2,x,y,escolha);

    escolha=3;
    int m3[8][9];
    lerMatriz(m3,x,y,escolha);


    escolha=4;
    //int linhas,colunas;
    //tamanhoMapa(x,y,linhas,colunas)
    int mapaArquivo[30][30];
    lerMatrizExtra(mapaArquivo,x,y);

    string nomeJogador;//armazena nome do jogador
    nomeJogador = menuNome();//armazena nome inserido


     menu(nomeJogador,m,m2,m3,mapaArquivo, movimento, continua, escolha,x,y);


}


void menu(string nome,int m[8][9],int m2[8][9], int m3[8][9],int m4[30][30], int movimento, bool continua, int escolha,int x, int y){//menu principal

    bool game = false;//fechar laço do jogo, encerrar partida
    
    char teclaMenu;//variavel para armazenar teclas pressionadas
    int lacoMenu = 0;//controle do laco menu
    int retornar;//movimento para qual o usuario quer retornar
    bool extra;

    desligaCursor();//desligar o cursor ja no comeco do programa



    cout<<"MENU PRINCIPAL"<<endl;
    cout<<"Bem vindo, "<<nome<<endl;
    cout<<"1-Novo Jogo"<<endl;
    cout<<"2-Continuar"<<endl;
    cout<<"3-Sobre"<<endl;
    cout<<"4-Placar"<<endl;
    cout<<"5-Fim"<<endl;


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
        cout<<"[e]Carregar mapa\n"<<endl;
        cout<<"[f]Voltar"<<endl;
        switch(getch())
        {
            case 97://caso fase 1(a), e assim por diante
                extra=false;
                remove("movimentos.txt");//apaga movimentos
                escolha = 1;
                reinicializaMatriz(m,m4,escolha,x,y);//como e o menu de novojogo, a matriz sempre sera reiniciada
                continua = true;//botao continua sera habilitado
                system("cls");//limpa o console
                iniciaFase(x,y,movimento,game,escolha);//reseta posicoes iniciais
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);//roda jogo

                lacoMenu++;//fim do laco menu
            break;
            case 98://[b]fase 2
                extra=false;
                remove("movimentos.txt");//apaga movimentos
                escolha = 2;
                reinicializaMatriz(m2,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;
            break;
            case 99://[c]fase 3
                extra=false;
                remove("movimentos.txt");//apaga movimentos
                escolha = 3;
                reinicializaMatriz(m3,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;    

            break;
            case 100://[d]randomizar
            extra=false;
            remove("movimentos.txt");//apaga movimentos
            escolha =randomizaEscolha();
            if(escolha ==1){//se caiu na escolha 1, fase 1
                reinicializaMatriz(m,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;

            }
            if(escolha==2){//se caiu na escolha 2, fase 2
                reinicializaMatriz(m2,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;
            }
            if(escolha ==3){//se caiu na escolha 3, fase 3
                reinicializaMatriz(m3,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;    

            }
            if(escolha ==4){//se caiu na escolha 4, fase 4
                reinicializaMatriz(m,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;
            }    
            break;


            case 101://[e]carregar mapa
                extra=false;
                remove("movimentos.txt");//apaga movimentos
                escolha = 4;
                reinicializaMatriz(m,m4,escolha,x,y);
                continua = true;
                system("cls");
                iniciaFase(x,y,movimento,game,escolha);
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++; 

            break;
            case 102://[f]voltar ao menu
                system("cls");
                menu(nome,m,m2,m3,m4,movimento, continua, escolha,x,y);
        }
        break;//fim do submenu novo jogo
        
        case 50://2-continuar(menu extra)
        if(continua == true){//checa se uma fase ja havia sido comecada
            
            system("cls");
            cout<<"[a]Continuar\n\n";
            cout<<"[b]Continuar a partir de movimento\n\n";
            switch(getch()){
                case 97://opcao [a]continuar
                system("cls");//segue o mesmo processo, mas sem reinicializar matriz e movimentos
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);
                lacoMenu++;
                break;

                case 98://opcao[b]continuar no movimento selecionado
                system("cls");

                while (true)
                {
                    cout<<"Insira movimento para retornar:";
                    cin>>retornar;
                    if(retornar<movimento){
                        break;
                    }
                }
                
                bool extra = true;

                if(escolha==1){
                reinicializaMatriz(m,m4,escolha,x,y);
                }
                if(escolha==2){
                reinicializaMatriz(m2,m4,escolha,x,y);
                }
                if(escolha==3){
                reinicializaMatriz(m3,m4,escolha,x,y);
                }
                if(escolha==4){
                reinicializaMatriz(m,m4,escolha,x,y);
                }
                
                continua = true;//botao continua sera habilitado
                system("cls");//limpa o console
                iniciaFase(x,y,movimento,game,escolha);//reseta posicoes iniciais
                rodarFase(nome,x,y,movimento,game,m,escolha,m2,m3,m4,continua,extra,retornar);//roda jogo

                lacoMenu++;//fim do laco menu
                
                break;
            }
        }
        break;
        case 51://3-Sobre
            system("cls");
            sobre(nome,m,m2,m3,m4, movimento, continua, escolha,x,y);
            lacoMenu++;
            break;
        case 52://4-placar
            system("cls");
            lerPlacar(nome,m,m2,m3,m4, movimento, continua, escolha,x,y);
            lacoMenu++;
            break;
        case 53://5-fim
            lacoMenu++;
            break;
        }
    }
   }//fim laço do menu    

}



int main()
{

    inicializaJogo();

    return 0;
} //fim main//fases: boxxle 2: #1, #2 e #3.
//ajuste entre m1 e m2

