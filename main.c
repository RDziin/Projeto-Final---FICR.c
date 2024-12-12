// Bibliotecas necessárias para excução do código
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Estruturação do vetor Funcionário
typedef struct
{

    int id;
    char cpf[12];
    char nome[50];
    int nascimento[3];
    char funcao[50];
    float remuneracao;

} Funcionario;

// Função para inicializar as variáveis do vetor Funcionario e garantir que não ocorra erros
void inicializarDados(Funcionario *funcionarios, int maxFunc)
{

    for (int i = 0; i < maxFunc; i++)
    {
        funcionarios[i].id = 0;
        strcpy(funcionarios[i].cpf, "");
        strcpy(funcionarios[i].nome, "");
        funcionarios[i].nascimento[0] = 0;
        funcionarios[i].nascimento[1] = 0;
        funcionarios[i].nascimento[2] = 0;
        strcpy(funcionarios[i].funcao, "");
        funcionarios[i].remuneracao = 0.0;
    }
}

// Usado para puxar os campos da base de dados
int carregarDados(Funcionario *funcionarios, char *bancoDeDados)
{

    FILE *arquivo = fopen(bancoDeDados, "r");
    int quantidade = 0;

    if (arquivo != NULL)
    {

        if (fscanf(arquivo, "%d", &quantidade) == 1)
        {

            for (int i = 0; i < quantidade; i++)
            {

                fscanf(arquivo, "%d\n", &funcionarios[i].id);
                fscanf(arquivo, "%s\n", funcionarios[i].cpf);
                fscanf(arquivo, " %[^\n]", funcionarios[i].nome);
                for (int j = 0; j < 3; j++)
                {
                    fscanf(arquivo, "%d", &funcionarios[i].nascimento[j]);
                }
                fscanf(arquivo, " %[^\n]", funcionarios[i].funcao);
                fscanf(arquivo, "%f", &funcionarios[i].remuneracao);
            }
        }

        fclose(arquivo);
    }

    return quantidade;
}

// Serve para salvar os campos na base de dados
void salvarDados(Funcionario *funcionarios, int quantidade, char *bancoDeDados)
{
    FILE *arquivo = fopen(bancoDeDados, "w");

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%d\n", quantidade);
        for (int i = 0; i < quantidade; i++)
        {
            fprintf(arquivo, "%d\n", funcionarios[i].id);
            fprintf(arquivo, "%s\n", funcionarios[i].cpf);
            fprintf(arquivo, "%s\n", funcionarios[i].nome);
            for (int j = 0; j < 3; j++)
            {
                fprintf(arquivo, "%d\n", funcionarios[i].nascimento[j]);
            }
            fprintf(arquivo, "%s\n", funcionarios[i].funcao);
            fprintf(arquivo, "%.2f\n", funcionarios[i].remuneracao);
        }
        fclose(arquivo);
    }
}

// Utilizado para criar e adicionar um funcionario ao vetor
void criarFuncionario(Funcionario *funcionarios, int *quantidade, int maxFunc)
{
    if (*quantidade >= maxFunc)
    {
        printf("Contigente atingido.\n");
        return;
    }

    Funcionario *newFunc = &funcionarios[*quantidade];
    int idFunc = *quantidade + 1;
    newFunc->id = idFunc;
    printf("ID: %d\n", idFunc);

    printf("CPF (Apenas numeros.):");
    scanf("%11s", newFunc->cpf);

    printf("Nome: ");
    scanf(" %[^\n]", newFunc->nome);

    printf("Data de Nascimento: \n");
    printf("Dia: ");
    scanf("%d", &newFunc->nascimento[0]);

    printf("Mes: ");
    scanf("%d", &newFunc->nascimento[1]);

    printf("Ano: ");
    scanf("%d", &newFunc->nascimento[2]);

    printf("Funcao: ");
    scanf(" %[^\n]", newFunc->funcao);

    printf("Salario: ");
    scanf("%f", &newFunc->remuneracao);

    (*quantidade)++;
    printf("\nFuncionario %d cadastrado com sucesso!!\n", *quantidade);
    salvarDados(funcionarios, *quantidade, "funcionarios.txt");
}

void removerFuncionario(Funcionario *funcionarios, int *quantidade)
{
    int id, idDelete = 0;
    char confirme;

    printf("Insira o ID do funionario que deseja remover: ");
    scanf("%d", &id);

    for (int i = 0; i < *quantidade; i++)
    {
        if (funcionarios[i].id == id)
        {
            system("clear");
            idDelete = 1;
            printf("Funcionario: ");
            printf("ID: %d\n", funcionarios[i].id);
            printf("CPF: %s\n", funcionarios[i].cpf);
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("Data de Nascimento: %d/%d/%d\n", funcionarios[i].nascimento[0], funcionarios[i].nascimento[1], funcionarios[i].nascimento[2]);
            printf("Funaco: %s\n", funcionarios[i].funcao);
            printf("Salario: %.2f\n", funcionarios[i].remuneracao);
            printf("================================================\n");
            printf("Voce deseja remover o usuario acima? (S/N)");
            scanf(" %c", &confirme);

            switch (confirme)
            {
            case 's':
            case 'S':
                for (int j = i; j < *quantidade - 1; j++)
                {
                    funcionarios[j] = funcionarios[j + 1];
                }
                (*quantidade)--;
                printf("Funcionario de ID: %d removido com suecsso!\n", id);
                break;
            case 'n':
            case 'N':
                printf("Voltando a tela Inicial...\n");
                return;
            default:
                printf("Opcao Invalida.\n");
                break;
            }
        }
    }

    salvarDados(funcionarios, *quantidade, "funcionarios.txt");
}

int main()
{
    Funcionario funcionarios[50];
    int quantidade = 0, opt;
    char enter;

    inicializarDados(funcionarios, 50);
    quantidade = carregarDados(funcionarios, "funcionarios.txt");

    do
    {
        system("clear");
        printf("\n====================================\n");
        printf("1 - Adicionar Funcionario\n");
        printf("2 - Remover Funcionario\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opt);

        switch (opt)
        {

        case 1:
            system("clear");
            criarFuncionario(funcionarios, &quantidade, 50);
            printf("Pressione ENTER para continuar...");
            getchar();
            scanf("%c", &enter);
            break;

        case 2:
            system("clear");
            removerFuncionario(funcionarios, &quantidade);
            printf("Pressione ENTER para continuar...");
            getchar();
            scanf("%c", &enter);
            break;
        case 0:
            system("clear");
            printf("Saindo...");
            break;
        default:
            system("clear");
            printf("Opcao não existente");
            printf("Pressione ENTER para continuar...");
            getchar();
            scanf("%c", &enter);
            break;
        }
    } while (opt != 0);

    return 0;
}