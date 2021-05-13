// -*- coding: utf-8 -*-

/*
Created on Thursday may 5 09:07:52 2021
@author: Lucas Victor Silva Pereira
*/


#include <iostream>
#include <stdlib.h>

using namespace std;

bool acabou = false;
#define MAXNUMESTADOS 10000
#define MINNUMNIVEIS 3

struct Info {
    int nNiveis;     // Numero de niveis (linhas) do tabuleiro triangular;
    int nPosicoes;   // Numero de posicoes do tabuleiro;
    int * niveisPos; // Arranjo onde cada posicao exibe em que nivel está aquela posicao.

                     /*Exemplo de tabuleiro: --> posição com 0 é a posição vazia.
                     linha 0:1
                     linha 1:1 1
                     linha 2:1 0 1
                     linha 3:1 1 1 1
                     linha 4:1 1 1 1 1

                     linha 0:    1
                     linha 1:   1 1
                     linha 2:  1 0 1
                     linha 3: 1 1 1 1
                     linha 4:1 1 1 1 1
                     */
};

/*
Essa função desenha o tabuleiro:
    0: posição vazia do tabuleiro;
    1: posição com peça no tabuleiro.
É necessário que o usuário entre com os 0's e 1's e "desenhe o tabuleiro" dado para agente solucionar.
*/
bool* leTabuleiro( Info& info ) {
    bool * tab;
    int nivel = 1, nElemNivel = 0;
    tab = new bool[ info.nPosicoes ]; // aloca de acordo com o numero de posicoes do tabuleiro
    info.niveisPos = new int[ info.nPosicoes ]; // aloca o arranjo que guarda os niveis de cada posicao
    cout << "Desenhe o tabuleiro por linhas (1 posicao com peca e 0 posicao sem peca):\n";
    for ( int i = 0; i < info.nPosicoes; i++ ) {
        nElemNivel++;
        cin >> tab[i]; // le conteudo da posicao i
        info.niveisPos[i] = nivel; // guarda nivel da posicao i
        if ( nElemNivel == nivel )
            nivel++; nElemNivel=0; // verifica se mudou de nivel
    }
    return tab;
} // leTabuleiro

/*
Essa função desenha o tabuleiro. Entretanto, diferentemente da função leTabuleiro, aqui o usuário deve apenas entrar
com a posição vazia do tabuleiro e todas as outras são preenhidas com 1's representando posições com peças.
*/
bool* leTabuleiro1( Info& info ) {
    bool * tab;
    int nivel = 1, nElemNivel = 0;
    tab = new bool[ info.nPosicoes ]; // aloca de acordo com o numero de posicoes do tabuleiro
    info.niveisPos = new int[ info.nPosicoes ]; // aloca o arranjo que guarda os niveis de cada posicao
    for ( int i = 0; i < info.nPosicoes; i++ ) {
        nElemNivel++;
        tab[i] = true; // salva na posição i o valor true
        info.niveisPos[i] = nivel; // guarda nivel da posicao i
        if ( nElemNivel == nivel )
            nivel++; nElemNivel=0; // verifica se mudou de nivel
    }
    int posV, qntP;
    cout << "Quantas posições vazia o tabuleiro possui: ";
    cin >> qntP;
    cout << "Digite cada posicao que inicia vazia (topo e posicao 0 e os valores crescem linha e depois coluna) e em sigida aperte enter:\n";
    bool notOk;
    for( int i = 0; i < qntP; i++ ){
        do{
            notOk = false;
            cin >> posV;
            if ( posV >= info.nPosicoes ){
                cout << "Posição invalida pois excede o tamanho do tabuleiro. Entre com um valor menor que " << info.nPosicoes << "\n";
                notOk = true;
            }
            tab[posV] = false;
        } while(notOk);
    }

    return tab;
} // leTabuleiro1


void printTabuleiro( bool * tab, int nNiveis ) {
    int p=0;
    for ( int i = 1; i <= nNiveis; i++ ) { // para cada linha
        for ( int j = 1; j <= nNiveis-i; j++ ) // imprimindo espacos antes do primeiro elemento da linha
            cout << " ";
        for ( int k = 1; k <= i; k++ ) { // imprimindo elementos da linha
            cout << tab[p] << " ";
            p++;
        }
        cout << endl;
    }
} // printTabuleiro

void processaSolucao(bool* a[], int k, Info info) {
    // Sinaliza que acabou e imprime passos do inicio ao fim.
    acabou = true;
    cout << "Solucao..." << endl;
    delete [] a[0];
    for ( int i = 1; i < k; i++ ) {
        cout << "Passo " << i << ":\n";
        printTabuleiro( a[i], info.nNiveis );
        cout << "\n";
        delete [] a[i];
    }
    // NOTE QUE HOUVE O CUIDADO DE DESALOCAR O QUE FOI DINAMICAMENTE ALOCADO.
} // processaSolucao


bool ehUmaSolucao(bool* a[], int k, Info info) {
    int cont = 0;

    for ( int i = 0; i < info.nPosicoes; i++ ) {
        cont += a[k - 1][i];
        if ( cont > 1 ) return false; // Se hah mais de 1 peca no tabuleiro, entao ainda nao eh fim
    }

    return true;
} // ehUmaSolucao


void enumeraCandidatos(bool* a[], int k, Info info, bool* c[],int& nCandidatos) {
// Esta parte eh a que compoe praticamente todo o trabalho que vc deverah fazer.
//  Colocar em c (e incrementar nCandidatos de acordo) todos os estados possiveis
//  de serem gerados a partir do ultimo estado em a[] (que estah na posicao k-2 de a[])
//	cout << "===============================================================================" << endl;
//	printTabuleiro(a[k-2],info.nNiveis);
	int i;
	nCandidatos =0;
	for( i = 0; i < info.nPosicoes; i++ ) {
		//cout << i << endl;
		int n= info.niveisPos[i];
		//cout << n << endl;
		if((info.niveisPos[i + 2] == n) && (a[k - 2][i]!=a[k - 2][i + 2]) && (a[k - 2][i + 1])) {	
//			cout << i << " -->" << endl;
			c[nCandidatos] = new bool[info.nPosicoes];
			for( int j = 0; j < info.nPosicoes; j++ )
                c[nCandidatos][j]=a[k - 2][j]; 
			c[nCandidatos][i]= !c[nCandidatos][i];
			c[nCandidatos][i + 1]= !c[nCandidatos][i + 1];
			c[nCandidatos][i + 2]= !c[nCandidatos][i + 2];
			nCandidatos++;
		}
		//cout << "t-b" << endl;
		if(((i + (2 * n) + 1) < info.nPosicoes) && (a[k - 2][i] != a[k - 2][i + (2 * n ) + 1]) && (a[k - 2][ i + n])) {
//			cout << i << " \\/" << endl;
			c[nCandidatos] = new bool[info.nPosicoes];
			for( int j = 0; j < info.nPosicoes; j++ )
                c[nCandidatos][j]=a[k - 2][j]; 
			c[nCandidatos][i]= !c[nCandidatos][i];
			c[nCandidatos][i + n]= !c[nCandidatos][i + n];
			c[nCandidatos][i + (2 * n) + 1]= !c[nCandidatos][i+(2 * n) + 1];
			nCandidatos++;
		}
		//cout << "t-bd" << endl;
		if(((i + (2 * n) + 3) < info.nPosicoes) && (a[k - 2][i] != a[k - 2][i + (2 * n) + 3]) && (a[k - 2][i + n + 1])) {
//			cout << i << " --> \\/" << endl;
			c[nCandidatos] = new bool[info.nPosicoes];
			for( int j = 0; j < info.nPosicoes; j++ )
                c[nCandidatos][j]=a[k - 2][j]; 
			c[nCandidatos][i]= !c[nCandidatos][i];
			c[nCandidatos][i + n + 1]= !c[nCandidatos][i + n + 1];
			c[nCandidatos][i + (2 * n) + 3]= !c[nCandidatos][i + (2 * n) + 3];
			nCandidatos++;
		}
	}
//	for(int j = 0; j<nCandidatos; j++)
//	{
//		cout << j << "-------------------------------------------------------------------------" << endl;
//		printTabuleiro(c[j], info.nNiveis);
//	}
//	cout << "===============================================================================" << endl;
} // enumeraCandidatos


void backtrack(bool* a[], int k, Info info) {
    bool* c[MAXNUMESTADOS]; // Posicoes candidatas para o proximo movimento.
    int nCandidatos; // Numero de candidatos gerados.
    int i;

    if ( ehUmaSolucao( a, k, info ) )
        processaSolucao( a, k, info );
    else {
        k++;
        enumeraCandidatos(a, k, info, c, nCandidatos);
        for ( i = 0; i < nCandidatos; i++ ) {
            a[k - 1] = c[i];
            if( i > 0 )
                delete [] c[i - 1];
            backtrack( a, k, info ); // ONDE ENTRARAH(AO) O(S) DELETE(S) PARA DESALOCAR OS CANDIDATOS GERADOS???
            if (acabou)   {
                //for(;i<nCandidatos;i++) delete [] c[i];
                return; // Para ter a possibilidade de terminar mais cedo.
            }
        }
    } // else
	delete [] c[nCandidatos - 1];
} // backtrack


int main() {
    bool* vet[MAXNUMESTADOS]; // Arranjo que guardarah todos os estados do tabuleiro
                              // ateh o estado final de 1 peca. Cada posicao do arranjo representa um estado.
                              // Um estado, por sua vez, eh um arranjo de booleans, onde true na posicao
                              // i quer dizer que hah uma peca em i e false quer dizer que nao hah peca em i.
    bool* iniTab; // Arranjo que representa o estado inicial.
    Info info;

    cout << "           ###           JOGO RESTA 1 com tabuleiro TRIANGULAR.           ###\n\n";
    cout << "Entre com o ALTURA do tabuleiro (o menor tabuleiro tem ALTURA 3): ";
    cin >> info.nNiveis; // Usuario deve informar primeiro o numero de niveis do tabuleiro triangular.
                         // Com isto infere-se o numero de posicoes do tabuleiro e o proximo passo eh ler 
                         // o conteudo de cada posicao.
    // Mas número de niveis tem que ser maior ou igual a minimo.
    if ( info.nNiveis < MINNUMNIVEIS ) {
        cout << "Numero de niveis deve ser pelo menos " << MINNUMNIVEIS << ". Abortando programa...\n";
        exit(1);
    }

    info.nPosicoes = info.nNiveis * ( info.nNiveis + 1 ) / 2; // Inferindo numero de posicoes no tabuleiro.
    
    char op;
    bool novamente;
    do{
        cout << "\nDeseja \"desenhar\" TODO o tabuleiro (digite d ou D) ou seja escolher apenas as posicoes vazias (digite v ou V): ";
        cin >> op;
        novamente = false;
            // Le tabuleiro e guarda em que nivel cada posicao do tabuleiro se encontra.
        switch (op){
            case 'D':
            case 'd':
            {
                iniTab = leTabuleiro( info ); // A funcao leTabuleiro retorna o arranjo  escolhido pelo usuário de booleans
                                              // alocado dinamicamente que representa a configuracao inicial.
                break;
            }
            case 'V':
            case 'v':
            {
                iniTab = leTabuleiro1( info ); // A funcao leTabuleiro retorna o arranjo  escolhido pelo usuário de booleans
                                              // alocado dinamicamente que representa a configuracao inicial.
                break;
            }
            default:
            {
                cout << "Valor invalido.\nPor favor, escolher uma opcao valida.\n";
                novamente = true;
            }
        }
    } while(novamente);
    // Imprimeiro tabuleiro inicial
    cout << "\nTabuleiro inicial:\n" << endl;
    printTabuleiro( iniTab, info.nNiveis );
    cout << endl;

    // COMPILE COMO ESTAH E RODE PARA VER O QUE ACONTECE.
    // DAI, PARA COMECAR O TRABALHO COM O BACKTRACKING, DESCOMENTE AS DUAS LINHAS ABAIXO:
    vet[0] = iniTab; // Estado inicial do problema eh colocado na posicao inicial do vetor que vai guardar
                                     // a sequencia de estados ateh o estado final de 1 peca.
    backtrack( vet, 1, info ); // Eh passado 1 para k pois jah hah 1 tabuleiro definido (o inicial).
                                                             // backtrack explorarah deste tabuleiro inicial para frente.

    if(!acabou)
        cout << "O Tabuleiro dado como entrada NAO possui solucao.\n";

    return EXIT_SUCCESS;
    system("pause"); //para pessoas que executam no windows;
} // main
