#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define ESTOQUE_MAX 2
#define ALMOXARIFE 2

typedef struct
{
    char nome[100];
    char cpf[12];
    char cpfLogin[12];
    char matricula[20];
    char dataCadastro[9];
    char senha[8];
    char senhaLogin[8];
} Cadastro;

typedef struct
{
    char nomeItem[50];
    int codigo;
    int quantidade;
    int quantidadeEntrada;
    float preco;
    char data[20];
} Produtos;

typedef struct
{
    char nomeEntrada[50];
    int codigoEntrada;
} Entrada;

typedef struct
{
    char nomeSaida[50];
    int codigoSaida;
    int quantidadeSaida;
} Saida;

void registro(Cadastro *cadastro, char *fazerLogin, int *totalCad)
{

    if (*totalCad >= ALMOXARIFE)
    {
        printf("\n\n\tSEM ESPAÇO PARA NOVOS CADASTROS!.\n\n");
        return;
    }

    printf("\n\n\t\tMENU\n\n\tCadastro de almoxarife\n\n");

    printf("\nNome:\n");
    fgets(cadastro->nome, sizeof(cadastro->nome), stdin);
    cadastro->nome[strcspn(cadastro->nome, "\n")] = '\0';

    do
    {
        printf("\nCpf:\n");
        fgets(cadastro->cpf, sizeof(cadastro->cpf), stdin);
        cadastro->cpf[strcspn(cadastro->cpf, "\n")] = '\0';

        if (strlen(cadastro->cpf) != 11)
        {
            printf("\n\tO cpf deve conter 11 digitos!\n");
        }
    } while (strlen(cadastro->cpf) != 11);

    printf("\nMatrícula:\n");
    fgets(cadastro->matricula, sizeof(cadastro->matricula), stdin);
    cadastro->matricula[strcspn(cadastro->matricula, "\n")] = '\0';

    printf("\nData do cadastro:\n");

    fgets(cadastro->dataCadastro, sizeof(cadastro->dataCadastro), stdin);
    cadastro->dataCadastro[strcspn(cadastro->dataCadastro, "\n")] = '\0';

    do
    {
        printf("\nSenha:\n");
        fgets(cadastro->senha, sizeof(cadastro->senha), stdin);
        cadastro->senha[strcspn(cadastro->senha, "\n")] = '\0';

        if (strlen(cadastro->senha) != 7)
        {
            printf("\n\tA senha deve conter 7 digitos!\n");
        }
    } while (strlen(cadastro->senha) != 7);

    (*totalCad)++;

    printf("Cadastro finalizado com sucesso! Total de cadastros: %d\n\n", *totalCad);

    do
    {
        printf("\n\t\tDeseja fazer o login?\n\t\tSIM - (S) / NÃO - (N)?\n");
        scanf(" %c", fazerLogin);
        printf("\n\n");

        if (*fazerLogin == 's' || *fazerLogin == 'S')
        {
            login(cadastro);
        }
        else
        {
            return;
        }
    } while (*fazerLogin != 's' && *fazerLogin != 'S' && *fazerLogin != 'n' && *fazerLogin != 'N');
}

void login(Cadastro *cadastro)
{
    printf("\n\n\t\tMENU LOGIN\n\n\tInsira seu login para acessar sua conta!.\n\n");

    do
    {
        printf("Cpf:\n");
        fflush(stdin);
        fgets(cadastro->cpfLogin, sizeof(cadastro->cpfLogin), stdin);
        cadastro->cpfLogin[strcspn(cadastro->cpfLogin, "\n")] = '\0';

        if (strcmp(cadastro->cpf, cadastro->cpfLogin) != 0)
        {
            printf("\n\tCpf invalido!\n Por favor, tente novamente!.\n");
        }

        if (strlen(cadastro->cpfLogin) != 11)
        {
            printf("\nO cpf deve conter 11 digitos!\n\n");
        }

    } while (strlen(cadastro->cpfLogin) != 11 || strcmp(cadastro->cpf, cadastro->cpfLogin) != 0);

    do
    {
        printf("\nSenha:\n");
        fflush(stdin);
        fgets(cadastro->senhaLogin, sizeof(cadastro->senhaLogin), stdin);
        cadastro->senhaLogin[strcspn(cadastro->senhaLogin, "\n")] = '\0';

        if (strlen(cadastro->senhaLogin) != 7)
        {
            printf("\nA senha deve conter 7 digitos válidos!\n");
        }

        if (strcmp(cadastro->senha, cadastro->senhaLogin) != 0)
        {
            printf("\n\tSenha incorreta!\n");
        }
        else
        {
            printf("\n\n\tBem vindo %s !\n", cadastro->nome);
        }

    } while (strlen(cadastro->senhaLogin) != 7);
}

void cadastrarProduto(Produtos *novoItem, int *totalProd, int *contadorCodigo, char *resposta)
{

    do
    {
        printf("----- Cadastro de produtos -----\n");

        printf("Informe o nome do produto a ser cadastrado:\n");
        fgets(novoItem[*totalProd].nomeItem, sizeof(novoItem[*totalProd].nomeItem), stdin);
        novoItem[*totalProd].nomeItem[strcspn(novoItem[*totalProd].nomeItem, "\n")] = '\0';

        printf("Informe a data da compra do item a ser cadastrada:\n");
        fgets(novoItem[*totalProd].data, sizeof(novoItem[*totalProd].data), stdin);
        novoItem[*totalProd].data[strcspn(novoItem[*totalProd].data, "\n")] = '\0';

        novoItem[*totalProd].codigo = *contadorCodigo;
        (*contadorCodigo)++;

        printf("Informe a quantidade do produto a ser cadastrada:\n");
        scanf("%d", &novoItem[*totalProd].quantidade);
        getchar();

        printf("Informe o preço do produto a ser cadastrado:\n");
        scanf("%f", &novoItem[*totalProd].preco);
        getchar();

        (*totalProd)++;

        printf("Operação realizada com sucesso! Produto cadastrado.\n");

        printf("Deseja continuar cadastrando outros produtos?\n");
        printf("Digite S - (SIM) / N - (NÃO):\n");
        scanf(" %c", resposta);
        getchar();

    } while (resposta == 's' || resposta == 'S');
}

void entradaProdutos(Produtos *novoItem, Entrada *entrada, char *resposta)
{
    do
    {
        printf("----- Entrada de produtos ------\n");
        do
        {
            printf("Informe o nome do produto:\n ");
            fgets(entrada->nomeEntrada, sizeof(entrada->nomeEntrada), stdin);
            entrada->nomeEntrada[strcspn(entrada->nomeEntrada, "\n")] = '\0';

            if (strcmp(entrada->nomeEntrada, novoItem->nomeItem) != 0)
            {
                printf("Nome incorreto. Tente novamente!\n");
            }
        } while (strcmp(entrada->nomeEntrada, novoItem->nomeItem) != 0);

        do
        {
            printf("\nInforme o codigo:\n ");
            scanf("%d", &entrada->codigoEntrada);

            if (entrada->codigoEntrada != novoItem->codigo)
            {
                printf("codigo incorreto. Tente novamente!\n");
            }
        } while (entrada->codigoEntrada != novoItem->codigo);

        printf("Informe a quantidade:\n");
        scanf("%d", &novoItem->quantidadeEntrada);
        novoItem->quantidade += novoItem->quantidadeEntrada;

        printf("Item adicionado com sucesso!\n");

        printf("Deseja continuar sim(S) ou não(N)?\n");
        scanf("%c", resposta);
        getchar();

    } while (*resposta == 's' || *resposta == 'S');
}

void saidaProdutos(Produtos *novoItem, Saida *saida, char *resposta)
{
    do
    {
        printf("----- Saida de produtos -----\n");
        do
        {
            printf("Informe o nome do produto:\n ");
            fgets(saida->nomeSaida, sizeof(saida->nomeSaida), stdin);
            saida->nomeSaida[strcspn(saida->nomeSaida, "\n")] = '\0';

            if (strcmp(saida->nomeSaida, novoItem->nomeItem) != 0)
            {
                printf("Nome incorreto. Tente novamente!\n");
            }
        } while (strcmp(saida->nomeSaida, novoItem->nomeItem) != 0);

        do
        {
            printf("\nInforme o codigo:\n ");
            scanf("%d", &saida->codigoSaida);

            if (saida->codigoSaida != novoItem->codigo)
            {
                printf("codigo incorreto. Tente novamente!\n");
            }
        } while (saida->codigoSaida != novoItem->codigo);

        printf("Informe a quantidade:\n");
        scanf("%d", &saida->quantidadeSaida);
        novoItem->quantidade -= saida->quantidadeSaida;

        printf("Item adicionado com sucesso!\n");

        printf("Deseja continuar sim(S) ou não(N)?\n");
        scanf("%c", resposta);
        getchar();

    } while (*resposta == 's' || *resposta == 'S');
}

void excluirProdutos(Produtos *novoItem, int *totalProd)
{
    int codigo = 0;
    int find = 0;

    if (*totalProd == 0)
    {
        printf("\nNão há produtos para excluir.\n");
        return;
    }

    printf("\n\n\t\tMENU Excluir\n\n\tInsira seu codigo a ser excluido.\n\n");

    printf("Informe o codigo a ser excluido\n");
    scanf("%d", &codigo);

    for (int i = 0; i < *totalProd; i++)
    {
        if (codigo == novoItem[i].codigo)
        {
            find = 1;
            for (int j = i; j < *totalProd - 1; j++)
            {
                novoItem[j] = novoItem[j + 1];
            }
            (*totalProd)--;

            printf("O produto foi excluido com sucesso!\n\n");
            break;
        }
    }
    if (!find)
    {
        printf("O produto não foi  encontrado!\n\t\tENTRE COM UM PRODUTO VÁLIDO!\n\n");
    }
}

void listarProdutos(Produtos *novoItem, int *totalProd)
{
    if (*totalProd == 0)
    {
        printf("\nNenhum produto cadastrado no estoque.\n");
        return;
    }

    for (int i = 0; i < *totalProd; i++)
    {

        printf("\n\n\t\tMENU LISTAR\n\n");

        printf("\t\tProdutos em estoque\n\n");

        printf("Nome do produto: %s\n", novoItem[i].nomeItem);
        printf("Data do produto: %s\n", novoItem[i].data);
        printf("Codigo do produto: %d\n", novoItem[i].codigo);
        printf("Quantidade do produto: %d\n", novoItem[i].quantidade);
        printf("Preço do produto: %.2f\n\n", novoItem[i].preco);
    }
}

int main()
{
    setlocale(LC_ALL, "");

    Cadastro cadastro[ALMOXARIFE];
    Produtos novoItem[ESTOQUE_MAX];
    Entrada entrada;
    Saida saida;

    char escolha;
    char fazerLogin;
    int contadorCodigo = 0;
    int totalProd = 0;
    char resposta;
    int totalCad = 0;
    int sair = 0;
    int opcao;

    /* printf("\n\n\t\t\t\t\t  MENU PRINCIPAL\n\n\t\t\t\tOlá Administrador, seja bem vindo!\n\n"); // mensagem deverá ser exibida de duas formas, uma para o usuario e outra para o ADM
     printf("\n\tCadastrar um Almoxarife  - (C):\t\t   Fazer login - (L):\t\tSair - (x):\n\n\t\t");
     scanf(" %c", &escolha);
     getchar();
     printf("\n");

     if (escolha == 'C' || escolha == 'c')
     {
         registro(&cadastro[0], &fazerLogin, &totalCad);
     }
     else if (escolha == 'L' || escolha == 'l')
     {
         login(&cadastro[0]);
     }
     else if (escolha == 'x' || escolha == 'X')
     {
         sair = 1;
         printf("\n\t\t\t\tfinalizando Programa!...");
         exit(0);
     }
     else
     {
         printf("Opção inválida! Tente novamente.\n");
     }*/

    while (!sair)
    {

        printf("Escolha a opção desejad 1 cadastrar\n2 entrada de produto\n3 saida de produto\n4 excluir produto\n5 listar produto\n sair");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastrarProduto(novoItem, &totalProd, &contadorCodigo, &resposta);
            break;

        case 2:
            entradaProdutos(novoItem, &entrada, &resposta);
            break;

        case 3:
            saidaProdutos(novoItem, &saida, &resposta);
            break;

        case 4:
            excluirProdutos(novoItem, &totalProd);
            break;

        case 5:
            listarProdutos(novoItem, &totalProd);
            break;

        default:
            printf("opção invalida");
            break;
        }
    };

    return 0;
}
