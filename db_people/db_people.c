#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[45];
    int idade;
    char sexo;
    char cpf[12];
    char telefone[12];
}pessoa;
//globais
int opcao, indice=0, tamanho_array=2;
pessoa **pessoas;

int procura_cpf(){
    char cpf[12];
    printf("\nInforme o CPF do cadastrado: ");
    scanf("%s", cpf);
    for(int cont=0; cont<indice; cont++){
        if(strcmp(cpf, pessoas[cont]->cpf)==0){
            return cont;
        }
    }
    printf("\nPessoa nao cadastrada.\n");
    return -1;
}

void excluir(){
    pessoa *auxiliar;
    int indice_cpf = procura_cpf();

    if(indice_cpf!=-1){
        for(int cont=indice_cpf; cont < indice-1; cont++){
            auxiliar = pessoas[cont];
            pessoas[cont] = pessoas[cont+1];
            pessoas[cont+1] = auxiliar;
        }
        free(pessoas[indice-1]);
        pessoas[indice-1]=NULL;
        indice--;

        if(indice>2){//
            tamanho_array = indice;
            pessoas=(pessoa**)realloc(pessoas, tamanho_array*sizeof(pessoa**));
            if(pessoas==NULL){
                printf("Erro em alocar memoria.");
                exit(1);
            }
        }
        printf("\nPessoa excluida com sucesso.\n");
    }
}

void alterar(){
    int opcao_altera, indice_cpf=procura_cpf();

    if(indice_cpf!=-1){
        do{
            printf("\nNome: %s | Idade: %d | Sexo: %c | CPF: %s | Fone: %s\n", pessoas[indice_cpf]->nome,
            pessoas[indice_cpf]->idade, pessoas[indice_cpf]->sexo, pessoas[indice_cpf]->cpf, pessoas[indice_cpf]->telefone);

            printf("\n1-Altera nome\n2-Altera idade\n3-Altera sexo\n4-Alterar CPF\n5-Alterar telefone\n0-Sair\n\nOpcao: ");
            scanf("%d", &opcao_altera);
            if(opcao_altera!=0){
                switch(opcao_altera){
                    case 1:
                        printf("\nNome: ");
                        scanf("%s", pessoas[indice_cpf]->nome);
                        break;
                    case 2:
                        printf("Idade: ");
                        scanf("%d", &pessoas[indice_cpf]->idade);
                        break;
                    case 3:
                        printf("Sexo: ");
                        scanf(" %c", &pessoas[indice_cpf]->sexo);
                        break;
                    case 4:
                        printf("CPF: ");
                        scanf("%s", pessoas[indice_cpf]->cpf);
                        break;
                    case 5:
                        printf("Telefone: ");
                        scanf("%s", pessoas[indice_cpf]->telefone);
                        break;
                    default:
                        printf("\nEscolha um opcao valida.\n");
                }
            }
        }while(opcao_altera != 0);
    }
}

void pesquisar(){
    int indice_cpf= procura_cpf();
    if(indice_cpf != -1){
        printf("\nNome: %s | Idade: %d | Sexo: %c | CPF: %s | Fone: %s\n", pessoas[indice_cpf]->nome,
        pessoas[indice_cpf]->idade, pessoas[indice_cpf]->sexo, pessoas[indice_cpf]->cpf, pessoas[indice_cpf]->telefone);
    }
}

void exibir(){
    if(indice==0){
        printf("\nCadastre ao menos uma pessoa.\n");
    }else{
        for(int cont = 0; cont < indice; cont++){
            printf("\nNome: %s | Idade: %d | Sexo: %c | CPF: %s | Fone: %s\n", pessoas[cont]->nome,
            pessoas[cont]->idade, pessoas[cont]->sexo, pessoas[cont]->cpf, pessoas[cont]->telefone);
        }
    }
}

void cadastrar(){
    if(indice == tamanho_array){//limite do tamanho do vetor
        tamanho_array*=2;
        pessoas=(pessoa**)realloc(pessoas, tamanho_array*sizeof(pessoa*));
        if(pessoas==NULL){
            printf("\nErro em alocar memoria.\n");
            exit(1);
        }
    }
    pessoas[indice] = (pessoa*)calloc(1, sizeof(pessoa));
    if(pessoas[indice]==NULL){
        printf("\nErro na alocacao de memoria!");
    }
    printf("\nNome: ");
    scanf("%s", pessoas[indice]->nome);
    printf("Idade: ");
    scanf("%d", &pessoas[indice]->idade);
    printf("Sexo: ");
    scanf(" %c", &pessoas[indice]->sexo);
    printf("CPF: ");
    scanf("%s", pessoas[indice]->cpf);
    printf("Telefone: ");
    scanf("%s", pessoas[indice]->telefone);
    printf("\nPessoa cadastrada com sucesso.\n");
    indice++;
}
int main(void){
    pessoas=(pessoa**)malloc(tamanho_array*sizeof(pessoa*));
    do{
        printf("\n1-Cadastrar\n2-Exibir\n3-Pesquisar\n4-Alterar\n5-Excluir\n0-Encerrar\n\nOpcao: ");
        scanf("%d", &opcao);
        if(opcao!=0){
            switch(opcao){
                case 1:
                    system("cls");
                    cadastrar();
                    break;
                case 2:
                    system("cls");
                    exibir();
                    break;
                case 3:
                    system("cls");
                    pesquisar();
                    break;
                case 4:
                    system("cls");
                    alterar();
                    break;
                case 5:
                    system("cls");
                    excluir();
                    break;
                default:
                    printf("Please enter a valid choice.");
            }
        }
    }while(opcao!=0);
    free(pessoas);
    pessoas = NULL;
    return 0;
}