#include<stdio.h>
#include<string.h>
#include<SDL.h>
#include"SDL_opengl.h"
#include<time.h>
// PARA ARQUIVOS BINARIOS:

#define NO_STDIO_REDIRECT
struct usuario{

    char nome[50];
    int idPersonagem;
    int vitorias;
    int derrotas;
};

struct movimento{

    bool esq = false;
    bool dir = false;
    bool up = false;
    bool down = false;
    bool shot = false;
};

FILE *arq;
bool arquivo = false; //Indica se o arquivo esta aberto
bool acabou_jogo = false; //Indica se o jogo acabou ou não
struct usuario Jogador1;
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

void salvaDados_Jogador(struct usuario alvo) //Salva no arquivo as inforamções de um NOVO Jogador
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

void alteraDados_Jogador(struct usuario alvo) //Atualiza as informações do Jogador
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

        fread(&Jogador_aux,sizeof(struct usuario),1,arq); //Aqui, mais do que nunca, é bom usarmos uma variavel auxiliar
        if(!(strcmp(Jogador_aux.nome, alvo.nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            posicao_arq = ftell(arq); //ftell retorna a *posição atual do ponteiro* neste arquivo, ou seja
            //como se fosse a linha do arquivo
            fseek (arq, posicao_arq - (sizeof(struct usuario)), SEEK_SET); //Aqui a mágica é feita!!! Posiciona o ponteiro do arquivo exatamente na linha cujo nome foi encontrado!!!
            //Na verdade essa função mexe com bytes e umas coisas estranhas, não sei EXATAMENTE como funciona, mas funciona
            //posicionado o ponteiro basta escrevermos!
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
    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo
}

int carregaDados_Jogador(char nome[50], struct usuario *alvo) //Carrega informações do Jogador, cujo nome é "nome"
{
    //retorna 1 caso encontrou um jogador com o nome especificado, caso contrário, retorna 0
    struct usuario Jogador_aux; //uma variavel teste que recebera os valores
    //Crio essa variavel pois, ao final da leitura, se usasse a variavel Jogador (original), esta conteria informações da ultima linha
    abrir_arq("ab+");
    arquivo = true;
    do{

        fread(&Jogador_aux,sizeof(struct usuario),1,arq); //Aponta o poteiro para a proxima linha e carrega todas as informações automaticamente na variavel struct Jogador_aux
        if(!(strcmp(Jogador_aux.nome, nome))) //Se o nome lido for igual ao nome procurado
        {
            //Encontrou um registro com o mesmo nome!
            *alvo = Jogador_aux; //Ja que sao variaveis do mesmo tipo, esta operação é completamente viavel
            //Carregando todas as informações do "Jogador_aux" para o jogador original
            return 1;
        }

    }while(!feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo
    return 0;

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
void configurar()
{
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
    SDL_SetVideoMode(800,600, 32,SDL_OPENGL);

    // Cor da janea
    glClearColor(4,5,2,1);


    //Area exibida
    glViewport(0,0,800,600);

    //Define sombra
    glShadeModel(GL_SMOOTH);

    //2D (COOL)
    glMatrixMode(GL_PROJECTION); //Aplica a projeção da matriz atual
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

}

bool colisao(float X1, float Y1, float comp1, float alt1, float X2, float Y2, float comp2, float alt2)
{
    //Detectar colisão em todos os lados
    if(Y1 + alt1 < Y2) //Se colide com a parte de cima
        return false;
    else if(Y1 > Y2 + alt2) //Se colide com a parte de baixo
        return false;
    else if(X1 + comp1 < X2) //Se colide com a frente
        return false;
    else if(X1 > X2 + comp2) //Se colide com a parte de traz
        return false;

    return true;
}

time_t Tick[2];
void movimento(struct movimento *J1, struct movimento *J2, float *J1X, float *J1Y, float *J2X, float *J2Y,
                float **tiros1, float **tiros2, float J1Comp, float J1Alt, float J2Comp, float J2Alt) //Processa todos os movimentos necessários, e retorna os valores das coordernadas
{
    //!LIMITAR OS PERSONAGENS NA TELA
    //!LIMITAR PROJETEIS NA TELA
    int i;

    if(J1->esq && *J1X > 0) //O ponto inicial dele
        *J1X -= 0.1;

    if(J1->dir && *J1X + J1Comp < 400) //Trava o movimento do personagem no quadrado estabelecido
        *J1X += 0.1;

    if(J2->esq && *J2X > 400) //se a tecla A for pressionada
        *J2X -= 0.1;

    if(J2->dir && *J2X + J2Comp < 800) //se a tecla D for pressionada
        *J2X += 0.1;

    if(J1->up && *J1Y > 0)
        *J1Y -= 0.1;

    if(J1->down && *J1Y + J1Alt < 600)
        *J1Y += 0.1;

    if(J2->up && *J2Y > 0)
        *J2Y -= 0.1;

    if(J2->down && *J2Y + J2Alt < 600)
        *J2Y += 0.1;

    if(J1->shot)
    {
        J1->shot = false;
        for(i = 0; i < 100 ; i++)
        {
            if(!tiros1[i][2]) //Se a terceira coluna de uma das linhas de tiro estiver "Vaga" (for igual a zero)
            {
                tiros1[i][0] =  *J1X; //O tiro começa na mesma posição do personagem
                tiros1[i][1] =  *J1Y;
                tiros1[i][2] = 1.0; //indica que ha esse tiro
                i = 100;
            }
        }
    }

    if(J2->shot)
    {
        J2->shot = false;
        for(i = 0; i < 100; i++)
        {
            if(!tiros2[i][2])
            {
                tiros2[i][0] = *J2X;
                tiros2[i][1] = *J2Y;
                tiros2[i][2] = 1.0; //indica que há esse tiro
                i = 100;
            }
        }

    }

}

int main(int argc, char* args[])
{
    float **tiros1; //A primeira coluna é a posição X, a segunda Y, a terceira indica se aquele tiro ainda existe
    float **tiros2; //A primeira coluna é a posição X, a segunda Y, a terceira indica se aquele tiro ainda existe
    int i;

    tiros1 = (float **) calloc(20, sizeof(float *)); //!Acho dificil ter mais de 20 tiros ativos, mas se tiver dando pau pode ser nisso
    tiros2 = (float **) calloc(20, sizeof(float *));

    for(i = 0; i < 20; i++)
    {
        tiros1[i] = (float *) calloc(3, sizeof(float));
        tiros2[i] = (float *) calloc(3, sizeof(float));
    }

    Tick[0] = Tick[1] = time(NULL);

    arquivo = false;
    /*scanf("%50[^\n]s", nome_inicial);*/
    configurar();

    //!------------ LOGICA AQUI EM BAIXO ---------------------
    bool executando = true;

    //Varial que detecta clickes de teclas
    SDL_Event eventos;

    //Iniciando variaveis para elementos e personagens
    float J1X = 50.0;
    float J1Y = 300.0;
    float J1Comp = 50.0;
    float J1Alt = 30.0;

    float TiroComp  = 30;
    float TiroAlt = 20;


    float J2X = 750.0;
    float J2Y = 300.0;
    float J2Comp = J1Comp;
    float J2Alt = J1Alt;

    //Variáveis para movimentar o personagem
    struct movimento J1;
    struct movimento J2;

    //loop do jogo
    while(executando)
    {

        //eventos
        while(SDL_PollEvent(&eventos))
        {
            //Fecha com o X da janela
            if(eventos.type == SDL_QUIT || acabou_jogo)
                executando = false;

            //Detectar movimento

            if(eventos.type == SDL_KEYDOWN) //Se uma tecla foi pressionada!!
            { //enquanto a tecla esta pressionada, movimentar
                if(eventos.key.keysym.sym == SDLK_LEFT) //Apertou seta esquerda
                    J1.esq = true;

                if(eventos.key.keysym.sym == SDLK_RIGHT) //Apertou seta direita
                    J1.dir = true;

                if(eventos.key.keysym.sym == SDLK_a)
                    J2.esq = true;

                if(eventos.key.keysym.sym == SDLK_d)
                    J2.dir = true;

                if(eventos.key.keysym.sym == SDLK_UP)
                    J1.up = true;

                if(eventos.key.keysym.sym == SDLK_DOWN)
                    J1.down = true;

                if(eventos.key.keysym.sym == SDLK_w)
                    J2.up = true;

                if(eventos.key.keysym.sym == SDLK_s)
                    J2.down = true;

                if(eventos.key.keysym.sym == SDLK_SLASH)
                {
                    time_t tempo = time(NULL);
                    if((double) (tempo - Tick[0]) >= 1.5) //A diferença entre o tiro anterior e esse tem que ser maior que 1s
                    {
                        Tick[0] = tempo;
                        J1.shot = true;
                    }
                }
                if(eventos.key.keysym.sym == SDLK_SPACE)
                {

                    time_t tempo = time(NULL);
                    if((double) (tempo - Tick[1]) >= 1.5) //A diferença entre o tiro anterior e esse tem que ser maior que 1s
                    {
                        Tick[1] = tempo;
                        J2.shot = true;
                    }
                }
            }

            else if(eventos.type == SDL_KEYUP)
            { //se a tecla foi solta, para de se mover
                if(eventos.key.keysym.sym == SDLK_LEFT) //Apertou seta esquerda
                    J1.esq = false;

                if(eventos.key.keysym.sym == SDLK_RIGHT) //Apertou seta direita
                    J1.dir = false;

                if(eventos.key.keysym.sym == SDLK_a)
                    J2.esq = false;

                if(eventos.key.keysym.sym == SDLK_d)
                    J2.dir = false;

                if(eventos.key.keysym.sym == SDLK_UP)
                    J1.up = false;

                if(eventos.key.keysym.sym == SDLK_DOWN)
                    J1.down = false;

                if(eventos.key.keysym.sym == SDLK_w)
                    J2.up = false;

                if(eventos.key.keysym.sym == SDLK_s)
                    J2.down = false;

            }
        }


        //!LOGICA DO PROGRAMA -- movimento do personagem
        movimento(&J1, &J2, &J1X, &J1Y, &J2X, &J2Y, tiros1, tiros2, J1Comp, J1Alt, J2Comp, J2Alt); //Processa todo o movimento necessário

        //!!RENDERIZAÇÃO!!
        glClear(GL_COLOR_BUFFER_BIT); //limpa o buffer

        //Inicia Matriz
        glPushMatrix();

        //Configura a matriz
        glOrtho(0, 800, 600, 0, -1, 1);

        //COR
         //vermelho

        //inicia desenho
        glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_TRIANGLE, GL_POLIGON

            glColor4ub(255,0,0, 255);
            //Desenhando jogador1
            glVertex2f(J1X, J1Y); //primeiro ponto
            glVertex2f(J1X + J1Comp, J1Y); //segundo ponto
            glVertex2f(J1X + J1Comp, J1Y + J1Alt);
            glVertex2f(J1X, J1Y + J1Alt);

            //Desenhando Jogador2
            glColor4ub(0,0,255,255);
            glVertex2f(J2X, J2Y); //primeiro ponto
            glVertex2f(J2X + J2Comp, J2Y); //segundo ponto
            glVertex2f(J2X + J2Comp, J2Y + J2Alt);
            glVertex2f(J2X, J2Y + J2Alt);

        for(i = 0; i < 20; i++) //Busca nas duas matrizes de tiro por projeteis que tenham sido atirados
        { //!JOGADOR 1 à esquerda
        //!Jogador 2 à direita
        //!DENHA E FAZ MOVIMENTAR OS PROJETEIS

            //Atualiza as posições dos tiros
            if(tiros1[i][2] != 0.0) // Coordenadas do tiro são (tiro1[i][0] ; tiros1[i][1])
            {
                if(tiros1[i][0] + TiroComp> 800) //Se saiu da tela
                    tiros1[i][2] = 0.0; //Mata o bloco
                //Desenha - atualiza a posição dos tiros

                //Ve se teve colisão
                if(colisao(J2X, J2Y, J2Comp, J2Alt, tiros1[i][0], tiros1[i][1], TiroComp, TiroAlt)) //Colisão com a parte da frente
                    tiros1[i][2] = 0.0;   //Esses números somando são para calibrar a hitbox
                else
                {
                    glColor4ub(123,222,87, 255);
                    glVertex2f(tiros1[i][0], tiros1[i][1]); //primeiro ponto
                    glVertex2f(tiros1[i][0] + TiroComp, tiros1[i][1]); //segundo ponto
                    glVertex2f(tiros1[i][0] + TiroComp, tiros1[i][1] + TiroAlt);
                    glVertex2f(tiros1[i][0], tiros1[i][1] + TiroAlt);
                    tiros1[i][0] += 0.05; //Atualiza a posição do tiro
                }
            }
            if(tiros2[i][2] != 0.0)
            {
                if(tiros2[i][0] < 0)
                    tiros2[i][2] = 0.0;
                //Detectar colisão com os personagens, projetil por projetil!!!!

                //Ve se teve colisão // Some com o tiro, computa o dano
                if(colisao(J1X, J1Y, J1Comp, J1Alt, tiros2[i][0], tiros2[i][1], J2Comp, J2Alt)) //Colisão com a parte da frente
                    tiros2[i][2] = 0.0;
                else
                {
                    glColor4ub(0,0,0, 255);
                    glVertex2f(tiros2[i][0], tiros2[i][1]); //primeiro ponto
                    glVertex2f(tiros2[i][0] + TiroComp, tiros2[i][1]); //segundo ponto
                    glVertex2f(tiros2[i][0] + TiroComp, tiros2[i][1] + TiroAlt);
                    glVertex2f(tiros2[i][0], tiros2[i][1] + TiroAlt);
                    tiros2[i][0] -= 0.05;
                }

            }
        }



        glEnd();
        //Fecha matriz
        glPopMatrix();

        //Animação -- precisa definir mas é meio inutil
        SDL_GL_SwapBuffers();

    }

    //para detectar uma tecla "if(eventos.key.keysym.sym == SDLK_ESCAPE)"


    for(i = 0; i < 20; i++)
    {
        free(tiros1[i]);
        free(tiros2[i]);
    }
    free(tiros1);
    free(tiros2);
    SDL_Quit();

    if(arquivo)
        fclose(arq);

    return 0;
}
