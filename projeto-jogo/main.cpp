#include<stdio.h>
#include"SDL/SDL_opengl.h"
#include<string.h>
#include<SDL/SDL.h> //PARA LINUX
//#include<SDL.h> //PARA WINDOWS --------------- ALTERE DE ACORDO COM SEU SISTEMA
// PARA ARQUIVOS BINARIOS:
struct usuario{

    char nome[50];
    int pontos;
    int idPersonagem;
    int estagio;
};
FILE *arq;
struct usuario Jogador;

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

void salvaDados_Jogador() //Salva no arquivo as inforamções do Jogador
{
    if(fwrite(&Jogador, sizeof(Jogador), 1, arq) != 1) //Escreve, em uma linha do arquivo, a struct inteira do Jogador
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

void alteraDados_Jogador() //Atualiza as informações do Jogador
{
    //Esta é um pouco mais complicada. Vou ter que procurar no arquivo a linha cujo nome gravado é o mesmo do atual jogador
    //Feito isso, devo *salvar o local* deste registro, o "numero da linha", para alterar tudo exatamente nesta linha.
    //PS: Essa função já subentende que todas as devidas alterações no estagio e pontos já foram feitas

    struct usuario Jogador_aux;
    int encontrou = 0;
    long posicao_arq;
    abrir_arq("rb+"); //Permite alterações fora do final do arquivo!!
    // no modo ab+ funções como fseek sao ignoradas!!!!
    do{

        fread(&Jogador_aux,sizeof(Jogador_aux),1,arq); //Aqui, mais do que nunca, é bom usarmos uma variavel auxiliar
        if(!(strcmp(Jogador_aux.nome, Jogador.nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            posicao_arq = ftell(arq); //ftell retorna a *posição atual do ponteiro* neste arquivo, ou seja
            //como se fosse a linha do arquivo
            fseek (arq, posicao_arq - (sizeof(Jogador)), SEEK_SET); //Aqui a mágica é feita!!! Posiciona o ponteiro do arquivo exatamente na linha cujo nome foi encontrado!!!
            //Na verdade essa função mexe com bytes e umas coisas estranhas, não sei EXATAMENTE como funciona, mas funciona
            //posicionado o ponteiro basta escrevermos!
            salvaDados_Jogador();
        }
    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo
}

void carregaDados_Jogador(char nome[50]) //Carrega informações do Jogador, cujo nome é "nome"
{
    int encontrou = 0;
    struct usuario Jogador_aux; //uma variavel teste que recebera os valores
    //Crio essa variavel pois, ao final da leitura, se usasse a variavel Jogador (original), esta conteria informações da ultima linha
    abrir_arq("ab+");
    do{

        fread(&Jogador_aux,sizeof(Jogador_aux),1,arq); //Aponta o poteiro para a proxima linha e carrega todas as informações automaticamente na variavel struct Jogador_aux
        if(!(strcmp(Jogador_aux.nome, nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            //Encontrou um registro com o mesmo nome!
            Jogador = Jogador_aux; //Ja que sao variaveis do mesmo tipo, esta operação é completamente viavel
            //Carregando todas as informações do "Jogador_aux" para o jogador original

        }

    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem não chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcançado
    //ou seja, enquanto o fim do arquivo não for alcançado devemos lê-lo

}

void exibe_dados_DEV() //função de teste
{
    printf("\nNome: %s", Jogador.nome);
    printf("\nPontos: %d", Jogador.pontos);
    printf("\nId_personagem: %d", Jogador.idPersonagem);
    printf("\nFase: %d\n", Jogador.estagio);
}
void salva_dados_DEV(char nome[50], int a, int b, int c) //função de teste
{
    strcpy(Jogador.nome,nome);
    Jogador.estagio = a;
    Jogador.idPersonagem = b;
    Jogador.pontos = c;

}
int main(int argc, char* args[])
{
    abrir_arq("ab+");
    /*scanf("%50[^\n]s", nome_inicial);*/
    //OBS: quando eu falo "informações do jogador" quero dizer tudo que esta na struct usuario chamada Jogador

    fclose(arq);
    return 0;
}


