#include <stdio.h>
#include <stdlib.h>
struct usuario{

    char nome[50];
    int pontos;
    int idPersonagem;
    int estagio;
};

struct usuario Jogador;

int testa_Usuario(char nome_teste[50])
{
        if(!(strcmp(nome_teste, Jogador.nome)))
            return 1;
        else
            return 0;
}

int main()
{
    char nome_inicial[50];
    printf("Digite seu nome: ");
    scanf("%50[^\n]s", nome_inicial);

    if(testa_Usuario(nome_inicial))
    {
        //Ja existe arquivo salvo com este nome
        //carrega_Dados(); //Carrega os dados do arquivo para o objeto Jogador
    }
    else //Não existe esse jogador, criar novo
    {
     //   cria_Jogador();
    }
    return 0;
}
