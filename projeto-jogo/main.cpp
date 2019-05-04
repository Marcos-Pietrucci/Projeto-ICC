#include<stdio.h>
#include<string.h>
#include<SDL/SDL.h> //PARA LINUX
//#include<SDL.h> //PARA WINDOWS --------------- ALTERE DE ACORDO COM SEU SISTEMA
struct usuario{

    char nome[50];
    int pontos;
    int idPersonagem;
    int estagio;
};

struct usuario Jogador;
int main(int argc, char* args[])
{
    printf("\nHelooooSDL!!\n");
    /*printf("Digite seu nome: ");
    scanf("%50[^\n]s", nome_inicial);*/
    SDL_Delay(5000);
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Quit();
    return 0;
}
