#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char cpf[11];
    char telefone[9];
    char email[50];
}Venda;

typedef struct
{
    int quantidade;
    float valorCompra;
    float valorVenda;
}Produto;

void AdicionarVenda()
{
    int select;

    do
    {
        system("clear");
        printf("+===============+\n");
        printf("|Adicionar Venda|\n");
        printf("+===============+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu venda\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            continue;
        }
    } while (select != 0);
}

void ListarVenda()
{

}

void RemoverVenda()
{
    int select;

    do
    {
        system("clear");
        printf("+=============+\n");
        printf("|Remover Venda|\n");
        printf("+=============+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu venda\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            continue;
        }
    } while (select != 0);
}

void AdicionarProduto()
{
    int select;

    do
    {
        system("clear");
        printf("+=================+\n");
        printf("|Adicionar Produto|\n");
        printf("+=================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu produto\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            continue;
        }
    } while (select != 0);
}

void ListarProduto()
{

}

void RemoverProduto()
{
    int select;

    do
    {
        system("clear");
        printf("+===============+\n");
        printf("|Remover Produto|\n");
        printf("+===============+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu produto\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            continue;
        }
    } while (select != 0);
}


void MenuVenda()
{
    int select;

    do
    {
        system("clear");
        printf("+==========+\n");
        printf("|Menu Venda|\n");
        printf("+==========+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu principal\n");
        printf("[ 1 ] - Adicionar Venda\n");
        printf("[ 2 ] - Listar Venda\n");
        printf("[ 3 ] - Remover Venda\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            break;
        case 1:
            AdicionarVenda();
            break;
        case 2:
            ListarVenda();
            break;
        case 3:
            RemoverVenda();
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            break;
        }
    } while (select != 0);
}

void MenuProduto()
{
    int select;

    do
    {
        system("clear");
        printf("+============+\n");
        printf("|Menu Produto|\n");
        printf("+============+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu principal\n");
        printf("[ 1 ] - Adicionar Produto\n");
        printf("[ 2 ] - Listar Produto\n");
        printf("[ 3 ] - Remover Produto\n");
        
        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            break;
        case 1:
            AdicionarProduto();
            break;
        case 2:
            ListarProduto();
            break;
        case 3:
            RemoverProduto();
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            break;
        }
    } while (select != 0);
}

int main()
{
    int select;

    do
    {
        system("clear");
        printf("+=============================+\n");
        printf("|Menu Principal - Aroused Shop|\n");
        printf("+=============================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Sair do Programa\n");
        printf("[ 1 ] - Acessar Venda\n");
        printf("[ 2 ] - Acessar Produtos\n");

        printf("\nResposta: ");
        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 0:
            exit(0);
            break;
        case 1:
            MenuVenda();
            break;
        case 2:
            MenuProduto();
            break;
        default:
            select = -1;
            printf("Digite uma opção válida. . .");
            getchar();
            break;
        }
    } while (select != 0);

    getchar();
    return 0;
}