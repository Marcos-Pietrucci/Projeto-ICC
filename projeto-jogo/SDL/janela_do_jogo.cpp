#include <stdio.h>
#include <SDL.h>
#include "SDL_opengl.h"

int main(int argc, char* args[]){

    SDL_Init(SDL_INIT_EVERYTHING);

    //MEMÓRIA // CONFIGURAÇÕES PADRÃO!

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // CORES
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //TRANSPARÊNCIA
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //BUFFER
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //DEPTH
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //NOME DA JANELA DO JOGO!
    SDL_WM_SetCaption("Projeto-ICC", NULL);

    //TAMANHO DA JANELA
    SDL_SetVideoMode(600, 400, 32, SDL_OPENGL);

    //COR DA JANELA
    glClearColor(1, 1, 1, 1); //red, green, blue, alpha

    //ÁREA EXIBIDA
    glViewport(0, 0, 600, 400); //COORDENADAS DOS PONTOS OPOSTOS DA DIAGONAL SECUNDARIA

    //SOMBRA
    glShadeModel(GL_SMOOTH);

    // 2D
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); //DESENHO GEOMETRICO

    //3D
    glDisable(GL_DEPTH_TEST);

    //ALGUMAS VARIAVEIS
    bool executando = true;

    SDL_Event eventos;

    //LOOP DO JOGO
    while(executando == true)
    {
        //EVENTOS
        while(SDL_PollEvent(&eventos))
        {
            //FECHA COM O X DA JANELA
            if(eventos.type == SDL_QUIT)
            {
                executando = false;
            }

            //FECHAR A JANELA COM O ESC
            if(eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE)
            {
                executando = false;
            }

        }

        //RENDERIZACAO
        glClear(GL_COLOR_BUFFER_BIT); //LIMPA O BUFFER

        //ANIMACAO
        SDL_GL_SwapBuffers();

        }

    glDisable(GL_BLEND);

    SDL_Quit();

return 0;

}
