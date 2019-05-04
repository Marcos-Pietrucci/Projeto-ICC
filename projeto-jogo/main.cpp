#include<stdio.h>
#include"SDL/SDL_opengl.h"
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
void carrega_usuario(){} //Carrega informações do usuario
int main(int argc, char* args[])
{
    /*scanf("%50[^\n]s", nome_inicial);*/
    SDL_Init(SDL_INIT_EVERYTHING);

    //memoria
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //transparencia
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //3D - não sei se vamos usar
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //3D - não sei se vamos usar

    //Definir nome para nossa janela
    SDL_WM_SetCaption("Naruto Simulator!", NULL);

    //Tamanho da janela - (x,y, bits/pixel, tipo_janela)
    SDL_SetVideoMode(600,400, 32,SDL_OPENGL);

    // Cor da janea
    glClearColor(4,5,2,1);


    //Area exibida
    glViewport(0,0,600,400);

    //Define sombra
    glShadeModel(GL_SMOOTH);

    //2D (COOL)
    glMatrixMode(GL_PROJECTION); //Aplica a projeção da matriz atual
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    //!------------ LOGICA AQUI EM BAIXO ---------------------


    //!!RENDERIZAÇÃO!!
    glClear(GL_COLOR_BUFFER_BIT); //limpa o buffer

    //Animação -- precisa definir mas é meio inutil
    SDL_GL_SwapBuffers();




    SDL_Delay(5000);

    SDL_Quit();
    return 0;
}
