#include<stdio.h>
#include<string.h>
#include<SDL.h>
// PARA ARQUIVOS BINARIOS:
struct usuario{

    char nome[50];
    int idPersonagem;
    int vitorias;
    int derrotas;
};

FILE *arq;
bool arquivo = false; //!CUIDADO AO MANIPULAR ESTA VARI�VEL
//Indica se o arquivo esta aberto
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

void salvaDados_Jogador(struct usuario alvo) //Salva no arquivo as inforam��es de um NOVO Jogador
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

void alteraDados_Jogador(struct usuario alvo) //Atualiza as informa��es do Jogador
{
    //Esta � um pouco mais complicada. Vou ter que procurar no arquivo a linha cujo nome gravado � o mesmo do atual jogador
    //Feito isso, devo *salvar o local* deste registro, o "numero da linha", para alterar tudo exatamente nesta linha.
    //PS: Essa fun��o j� subentende que todas as devidas altera��es no estagio e pontos j� foram feitas

    struct usuario Jogador_aux;
    int encontrou = 0;
    long posicao_arq;
    abrir_arq("rb+"); //Permite altera��es fora do final do arquivo!!
    arquivo = true;
    // no modo ab+ fun��es como fseek sao ignoradas!!!!
    do{

        fread(&Jogador_aux,sizeof(struct usuario),1,arq); //Aqui, mais do que nunca, � bom usarmos uma variavel auxiliar
        if(!(strcmp(Jogador_aux.nome, alvo.nome))) //Se o nome lido for igual ao nome procurado
        {
            encontrou = 1;
            posicao_arq = ftell(arq); //ftell retorna a *posi��o atual do ponteiro* neste arquivo, ou seja
            //como se fosse a linha do arquivo
            fseek (arq, posicao_arq - (sizeof(struct usuario)), SEEK_SET); //Aqui a m�gica � feita!!! Posiciona o ponteiro do arquivo exatamente na linha cujo nome foi encontrado!!!
            //Na verdade essa fun��o mexe com bytes e umas coisas estranhas, n�o sei EXATAMENTE como funciona, mas funciona
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
    }while(!encontrou && !feof(arq)); //Enquanto nao encountrou o registrou ou tambem n�o chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcan�ado
    //ou seja, enquanto o fim do arquivo n�o for alcan�ado devemos l�-lo
}

int carregaDados_Jogador(char nome[50], struct usuario *alvo) //Carrega informa��es do Jogador, cujo nome � "nome"
{
    //retorna 1 caso encontrou um jogador com o nome especificado, caso contr�rio, retorna 0
    struct usuario Jogador_aux; //uma variavel teste que recebera os valores
    //Crio essa variavel pois, ao final da leitura, se usasse a variavel Jogador (original), esta conteria informa��es da ultima linha
    abrir_arq("ab+");
    arquivo = true;
    do{

        fread(&Jogador_aux,sizeof(struct usuario),1,arq); //Aponta o poteiro para a proxima linha e carrega todas as informa��es automaticamente na variavel struct Jogador_aux
        if(!(strcmp(Jogador_aux.nome, nome))) //Se o nome lido for igual ao nome procurado
        {
            //Encontrou um registro com o mesmo nome!
            *alvo = Jogador_aux; //Ja que sao variaveis do mesmo tipo, esta opera��o � completamente viavel
            //Carregando todas as informa��es do "Jogador_aux" para o jogador original
            return 1;
        }

    }while(!feof(arq)); //Enquanto nao encountrou o registrou ou tambem n�o chegou ao final do arquivo
    //feof retorna 0 se o fim do arquivo vou alcan�ado
    //ou seja, enquanto o fim do arquivo n�o for alcan�ado devemos l�-lo
    return 0;

}

void exibe_dados_DEV(struct usuario alvo) //fun��o de teste
{
    printf("\nNome: %s", alvo.nome);
    printf("\nId_personagem: %d", alvo.idPersonagem);
    printf("\nVitorias: %d", alvo.vitorias);
    printf("\nDerrotas: %d", alvo.derrotas);
}
void salva_dados_DEV(struct usuario *alvo,char nome[50], int b,int d, int e) //fun��o de teste
{
    strcpy(alvo->nome,nome);
    alvo->idPersonagem = b;
    alvo->vitorias = d;
    alvo->derrotas = e;
}
int main(int argc, char* args[])
{
    arquivo = false;
    /*scanf("%50[^\n]s", nome_inicial);*/
    //OBS: quando eu falo "informa��es do jogador" quero dizer tudo que esta na struct usuario chamada Jogador
    abrir_arq("ab+");


    if(arquivo)
        fclose(arq);

    return 0;
}
