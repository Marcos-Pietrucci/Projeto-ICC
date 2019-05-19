#include <stdio.h>
#include <SDL.h>
#include "SDL_opengl.h"
struct usuario{

    char nome[50];
    int idPersonagem;
    int vitorias;
    int derrotas;
};
FILE *arq;
bool arquivo = false; //!CUIDADO AO MANIPULAR ESTA VARIÁVEL
//Indica se o arquivo esta aberto
struct usuario Jogador;
struct usuario Jogador2;

void abrir_arq(const char *modo) //Abre o arquivo no modo especificado
{
    //existem varios modos de abrir um arquivo, include o arquivo pode ser binario
    //modo a+ permite leitura e escrita
	if((arq = fopen("Arquivo_SNUNS.bin", modo)) == NULL)
    {
        printf("\nErro na abertura do arquivo");
	}
	else
	{
        printf("\nAbertura bem sucedida");
    }
}

void salvaDados_Jogador(struct usuario alvo) //Salva no arquivo as inforamções do Jogador
{
    abrir_arq("ab+");
    arquivo = true;
    if(fwrite(&alvo, sizeof(struct usuario), 1, arq) != 1) //Escreve, em uma linha do arquivo, a struct inteira do Jogador
    {
        printf("Erro na escrita do arquivo");
	}
	else
    {
        //Dados foram escritos corretamente
        fflush(arq);//descarrega o buffer no disco
        rewind(arq);//Volta o ponteiro do arquivo para seu inicio
	}
}

void alteraDados_Jogador(struct usuario *alvo) //Atualiza as informações do Jogador
{
    //Esta é um pouco mais complicada. Vou ter que procurar no arquivo a linha cujo nome gravado é o mesmo do atual jogador
    //Feito isso, devo *salvar o local* deste registro, o "numero da linha", para alterar tudo exatamente nesta linha.
    //PS: Essa função já subentende que todas as devidas alterações no estagio e pontos já foram feitas

    struct usuario Jogador_aux;
    int encontrou = 0;
    long posicao_arq;
    abrir_arq("rb+"); //Permite alterações fora do final do arquivo!!
    arquivo = true;
    // no modo ab+ funções como fseek sao ignoradas!!!!
    do{

        fread(&Jogador_aux,sizeof(Jogador_aux),1,arq); //Aqui, mais do que nunca, é bom usarmos uma variavel auxiliar
        if(!(strcmp(Jogador_aux.nome, alvo->nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            posicao_arq = ftell(arq); //ftell retorna a *posição atual do ponteiro* neste arquivo, ou seja
            //como se fosse a linha do arquivo
            fseek (arq, posicao_arq - (sizeof(struct usuario)), SEEK_SET); //Aqui a mágica é feita!!! Posiciona o ponteiro do arquivo exatamente na linha cujo nome foi encontrado!!!
            //Na verdade essa função mexe com bytes e umas coisas estranhas, não sei EXATAMENTE como funciona, mas funciona
            //posicionado o ponteiro basta escrevermos!
            if(fwrite(alvo, sizeof(struct usuario), 1, arq) != 1) //Escreve, em uma linha do arquivo, a struct inteira do Jogador
            {
                printf("Erro na escrita do arquivo");
            }
            else
            {
                //Dados foram escritos corretamente
                fflush(arq);//descarrega o buffer no disco
                rewind(arq);//Volta o ponteiro do arquivo para seu inicio
            }
        }
    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo
}

void carregaDados_Jogador(char nome[50], struct usuario *alvo) //Carrega informações do Jogador, cujo nome é "nome"
{
    int encontrou = 0;
    struct usuario Jogador_aux; //uma variavel teste que recebera os valores
    //Crio essa variavel pois, ao final da leitura, se usasse a variavel Jogador (original), esta conteria informações da ultima linha
    abrir_arq("ab+");
    arquivo = true;
    do{

        fread(&Jogador_aux,sizeof(Jogador_aux),1,arq); //Aponta o poteiro para a proxima linha e carrega todas as informações automaticamente na variavel struct Jogador_aux
        if(!(strcmp(Jogador_aux.nome, nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            //Encontrou um registro com o mesmo nome!
            *alvo = Jogador_aux; //Ja que sao variaveis do mesmo tipo, esta operação é completamente viavel
            //Carregando todas as informações do "Jogador_aux" para o jogador original

        }

    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo

}

void exibe_dados_DEV(struct usuario alvo) //função de teste
{
    printf("\nNome: %s", alvo.nome);
    printf("\nId_personagem: %d", alvo.idPersonagem);
    printf("\nVitorias: %d", alvo.vitorias);
    printf("\nDerrotas: %d", alvo.derrotas);
}
void salva_dados_DEV(struct usuario *alvo,char nome[50], int b,int d, int e) //função de teste
{
    strcpy(alvo->nome,nome);
    alvo->idPersonagem = b;
    alvo->vitorias = d;
    alvo->derrotas = e;
}

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
    SDL_WM_SetCaption("ULTIMATE NARUTO SIMULATOR", NULL);

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
