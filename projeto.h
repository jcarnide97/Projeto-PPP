#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#define MAX_NOME 50
#define MAX_MORADA 100
#define MAXTELEFONE 9
#define MAXLINHA 300
#define MAXCIDADE 100
#define MAXHORARIO 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char ITEM_TYPE;
typedef struct lnode* List;
typedef struct lnode{
    ITEM_TYPE info[MAXCIDADE];
    int pop;
    List next;
}List_node;


typedef struct auxCidade{
    char cidade[MAXCIDADE];
    char local[MAXCIDADE];
}Escolhe;


typedef struct lno* Viagem;
typedef struct lno{
    char cidade[MAXCIDADE];
    char ponto[MAXCIDADE];
    char descricao[MAXLINHA];
    char entrada[MAXHORARIO];
    char saida[MAXHORARIO];
    int popularidade;
    Viagem next;
}Viagem_no;


typedef struct travel* Travel;
typedef struct travel{
    char p1[MAXCIDADE];
    Travel next;
}Travel_no;


typedef struct aluno{
    char nome[MAX_NOME];
    char morada[MAX_MORADA];
    int dia, mes, ano;
    int telefone;
    char cidade[MAXCIDADE];
    char pdi[MAXCIDADE];
    char city1[MAXCIDADE];
    char pc11[MAXCIDADE];
    char pc12[MAXCIDADE];
    char pc13[MAXCIDADE];
    char city2[MAXCIDADE];
    char pc21[MAXCIDADE];
    char pc22[MAXCIDADE];
    char pc23[MAXCIDADE];
    char city3[MAXCIDADE];
    char pc31[MAXCIDADE];
    char pc32[MAXCIDADE];
    char pc33[MAXCIDADE];
}Utilizador;


void utilizador();
int registar();
void inicia(Utilizador *atual);
void gravaUtilizador(Utilizador *novo);
int consultaNome(char nome[]);
int confirma(Utilizador *confirma);
int login(Utilizador *check);
int verificaCidade(char cidade[],char pdi[] ,char aux, char pasta[]);
int checkCity(char cidade[]);
int verifica(List lista,char city[]);
List ordemAlfa(List lista);
List leficheiro(List lista);
Viagem alfa(Viagem viagem, char cidade[]);
Viagem gera_viagem(Viagem viagem, char cidade[]);
void print_viagem(Viagem lista);
void print_lista(List lista);
void acabaLocais(char pasta1[],char pastinha[]);
void alteraNum(char pastinha[],long int position, int num);
void aumentaPopCidade(long int pos, int num, char cidade[]);
void retiraPopCidade(Utilizador *atual);
void retiraPop(Utilizador *atual);
void guardaPdi(Escolhe * ponto);
void apagaFichU();
void guardaUti(Utilizador * atual, Escolhe * paraGuardar);
void prefer(Utilizador *atual);
void escolhe_cidade_alfa(List listaPop, Viagem viagem);
Travel cria_viagem3(Utilizador *atual,Viagem viagem,Travel via);
Travel cria_viagem2(Utilizador *atual,Viagem viagem,Travel via);
Travel cria_viagem1(Utilizador *atual,Viagem viagem,Travel via);
Travel cria_viagem(Utilizador *atual,Viagem viagem,Travel via);
Viagem choice3(Viagem viagem,Utilizador *atual);
Viagem choice2(Viagem viagem,Utilizador *atual);
Viagem choice1(Viagem viagem,Utilizador *atual);
Viagem choice(Viagem viagem,Utilizador *atual);
void escolhe_cidade(List listaPop, Viagem viagem);
void guardaPrefeCidade(Utilizador * atual);
void alteraNumero(char pastinha[],long int pos, int num);
void retiraPopularidade(Utilizador *atual);
void aumentaPopularidade(Utilizador *atual);
void preferCidade(Utilizador *atual);
int totalUtilizadores();
int localUtilizador(Utilizador * atual);
int hotPdi(Travel via,char cidade[]);
int procuraPop(char nome[]);
int totalPreferencias(Utilizador * atual);
int contaPontos();
void print_via(Travel lista);


#endif
