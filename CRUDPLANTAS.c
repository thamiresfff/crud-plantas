#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char nomePlanta[100];
    int luzPlanta;
    float valorPlanta;
}Planta;


void menu() {
    printf("\n\t*** CRUD DE PLANTAS ***\n");
    printf("\n\t1 - CADASTRAR PLANTA");
    printf("\n\t2 - LISTAR PLANTAS");
    printf("\n\t3 - ATUALIZAR PLANTA");
    printf("\n\t4 - DELETAR PLANTA");
    printf("\n\t5 - SALVAR LISTA DE PLANTAS CADASTRADAS");
    printf("\n\t6 - LER LISTA DE PLANTAS CADASTRADAS");
    printf("\n\t7 - SAIR DO SISTEMA");
} 


int cadastrarPlanta(Planta p[], int tamanhoVetor, int qtd){
    Planta plantaCadastrada;

  
    printf("\nDigite o nome da planta: ");
    scanf("%99[^\n]", plantaCadastrada.nomePlanta);
    
   
   do{
       
        printf("\nQuanto a preferência de luz. Digite 1- sol, 2- meia sombra ou 3- sombra: ");
        scanf("%d", &plantaCadastrada.luzPlanta);
        
        if(plantaCadastrada.luzPlanta<1|| plantaCadastrada.luzPlanta>3){
            
            printf("Opcao invalida, tente novamente");
        }
   }while(plantaCadastrada.luzPlanta<1 || plantaCadastrada.luzPlanta>3);

    do{
        printf("\nDigite o valor da planta:");
        scanf("%f", &plantaCadastrada.valorPlanta);
        
        if(plantaCadastrada.valorPlanta<0){
            printf("Valor inválido, tente novamente");
        }
    }while(plantaCadastrada.valorPlanta<0);
    p[qtd] = plantaCadastrada;
   
   return 1;
}


void listarPlanta(Planta p[], int qtd){
    printf("\n\t\t\tLista de Plantas:\n");
    printf("\t----------------------------------------------------\n");
    for(int i = 0; i < qtd; i++){
        printf("\t****************\n");
        printf("\n\tPlanta %d\n\tNome:%s\n\tPreferência luminosa %d\n\tValor: %.2f\n",(i+1), p[i].nomePlanta, p[i].luzPlanta,p[i].valorPlanta);
        printf("\t****************\n");
    }
    printf("\t----------------------------------------------------\n");
}

void alterarPlantaCadastrada(Planta p[], int qtd){
    if (qtd == 0){
        printf("\nVoce ainda não possui plantas cadastradas!\n");
    } else {
        listarPlanta(p, qtd);

        int id;

        printf("\n\tDigite o numero (identificador) da planta que deseja atualizar: ");
        scanf("%d", &id);
        getchar();
            
        id--;

        if (id >= 0 && id < qtd) {
            Planta plantaAtualizada;

            printf("\nDigite o novo nome da planta: ");
            scanf("%99[^\n]", plantaAtualizada.nomePlanta);

           do{
       
                printf("\nQuanto a nova preferência de luz. Digite 1- sol, 2- meia sombra ou 3- sombra: ");
                scanf("%d", &plantaAtualizada.luzPlanta);
                
                if(plantaAtualizada.luzPlanta<1|| plantaAtualizada.luzPlanta>3){
                    
                    printf("Opcao invalida, tente novamente");
                }
           }while(plantaAtualizada.luzPlanta<1 || plantaAtualizada.luzPlanta>3);
           do{
                printf("\nDigite o novo valor da planta:");
                scanf("%f", &plantaAtualizada.valorPlanta);
                
                if(plantaAtualizada.valorPlanta<0){
                    printf("Valor inválido, tente novamente");
                }
            }while(plantaAtualizada.valorPlanta<0);
            p[id]=plantaAtualizada;
        }

     printf("\nPlanta atualizada\n");
    }   
}
int deletarPlanta(Planta p[], int qtd){
    if (qtd == 0){
        printf("\nVoce ainda nao possui plantas cadastradas!\n");
        return 0;
    }

    int opcao;

    listarPlanta(p, qtd);

    printf("\n\tDigite o numero (identificador) para deletar a planta: ");
    scanf("%d", &opcao);
    getchar();
    opcao--;

    if (opcao >= 0 && opcao < qtd){
        if (opcao == qtd - 1){
            printf("\nPlanta deletada\n");
            return -1;
        }
        int i, j;
        for (i = opcao; i < qtd; i++){
            if (i == qtd - 1){
                j = i;
            } else {
                j = i + 1;
            }
            Planta temporaria = p[i];
            p[i] = p[j];
            p[j] = temporaria;
        }
    } else {
        printf("\nOpcao Invalida!\n");
        return 0;
    }
    printf("\n\tPlanta deletada com sucesso\n");
    return -1;
}
    
void salvarPlantaArquivo(Planta p[], int qtd, char arq[]){
    FILE *arquivo = fopen(arq, "w");

    if(arquivo){
        fprintf(arquivo, "%d\n", qtd);
        for(int i = 0; i < qtd; i++){
            fprintf(arquivo, "%s\n", p[i].nomePlanta);
            fprintf(arquivo, "%d\n", p[i].luzPlanta);
            fprintf(arquivo, "%.2f\n", p[i].valorPlanta);
            
        }
        fclose(arquivo);
    }

    printf("\n\tSua Lista Foi Salva Com Sucesso\n");
}
int lerArquivoTexto(Planta p[], char nomeArquivo[]){
    FILE *arquivo = fopen(nomeArquivo, "r");
    int quantidadePlanta = 0;
    Planta novaPlanta;

    if (arquivo){
        fscanf(arquivo, "%d\n", &quantidadePlanta);
        for(int i = 0; i < quantidadePlanta; i++){
            fscanf(arquivo, "%99[^\n]", novaPlanta.nomePlanta);
            fscanf(arquivo, "%d\n", &novaPlanta.luzPlanta);
            fscanf(arquivo, "%f\n", &novaPlanta.valorPlanta);
            p[i] = novaPlanta;
        }
        fclose(arquivo);
        printf("\n\tSua lista foi carregada no sistema\n");
    } else {
        printf("\n\tNao foi possivel abrir o arquivo\n");
    }

    return quantidadePlanta;
}
int main() {
  
    Planta listadePlanta [100];
    int tamanhoVetorPlanta= sizeof(listadePlanta)/sizeof(Planta);
    int qtdPlanta = 0;
    char Plantaslist[]={"ListaDePlantas.txt"};
  
    int opcao;

    do {
        menu();
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
               qtdPlanta += cadastrarPlanta(listadePlanta, tamanhoVetorPlanta, qtdPlanta);
               printf("\n\tPlantas Cadastradas = %d\n", qtdPlanta);
                break;
            case 2:
               listarPlanta(listadePlanta,qtdPlanta);
                break;
            case 3:
                alterarPlantaCadastrada(listadePlanta, qtdPlanta);
                break;
            case 4:
            
                qtdPlanta += deletarPlanta(listadePlanta,qtdPlanta);
                break;
            case 5:
                salvarPlantaArquivo(listadePlanta, qtdPlanta, Plantaslist);
                break;
            case 6:
                qtdPlanta=lerArquivoTexto(listadePlanta, Plantaslist);
                break;
            case 7:
               printf("Obrigado por usar nosso sistema!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}