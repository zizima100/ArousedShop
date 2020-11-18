#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char codigo[6];
}Produto;

typedef struct
{
    char codigo[6];
    int quantidadeVendida;
    float valorVenda;
    float valorCompra;
    float lucro;
}Venda;

void AdicionarVenda()
{
    int select;
    Venda v;

    FILE *arquivo;

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

        arquivo = fopen("vendas", "a+b");

        if(arquivo == NULL)
            printf("ERRO NA ABERTURA DO ARQUIVO");
        else
        {
            system("clear");
            printf("DEBUG - ARQUIVO VENDAS ABERTO");
            printf("\n\nDigite o código do produto [6 Dígitos]: ");
            gets(v.codigo);
            v.codigo[strcspn(v.codigo, "\n")] = '\0'; // Encontra a posicao onde está o \n no final da string e troca por \0.
            printf("\n\nDigite a quantidade vendida: ");
            scanf("%d%*c", &v.quantidadeVendida); // %*c Le a info, mas n armazena. Basicamente um getchar();
            printf("\n\nDigite o valor de compra: ");
            scanf("%f%*c", &v.valorCompra);
            printf("\n\nDigite o valor de venda: ");
            scanf("%f%*c", &v.valorVenda);
            v.lucro = (v.valorVenda - v.valorCompra) * v.quantidadeVendida;
            fwrite(&v, sizeof(Venda), 1, arquivo); // 1 = Quantos Structs serão armazenados.
            if(ferror(arquivo))
                printf("\nDeu erro na gravação da vendas. . .");
            else
                printf("\nDeu bom na gravação da venda!");
            if(!fclose(arquivo)) // Fechamento com sucesso retorna 0.
                printf("\nArquivo fechado Com sucesso!");
            else
                printf("\nErro no fechamento do arquivo. . .");
        }
    } while (select != 0);
}

void ListarVendas()
{
    int eof; // Registra o fim do arquivo lido.
    Venda v;

    FILE *arquivo;

    arquivo = fopen("vendas", "a+b");
    if(arquivo == NULL)
        printf("ERRO NA ABERTURA DO ARQUIVO");
    else
    {
        system("clear");
        printf("DEBUG - ARQUIVO VENDAS ABERTO\n");
        
        while (!feof(arquivo)) // Enquanto for diferente da indicação do final do arquivo.
        {
            eof = fread(&v, sizeof(v), 1, arquivo); // 1 = Quantos structs setão lidos.
            if (ferror(arquivo))
                printf("\n\nErro na leitura do arquivo vendas. . .");
            else
            {
                if(eof != 0)
                {
                    printf("========\nCódigo da Venda: %s", v.codigo);
                    printf("\nQuantidade Vendida: %d", v.quantidadeVendida);
                    printf("\nValor Compra: R$%.2f", v.valorCompra);
                    printf("\nValor Venda: R$%.2f", v.valorVenda);
                    printf("\nLucro Total: R$%.2f\n", v.lucro);
                }
            }
        }
        getchar();
        if(!fclose(arquivo)) // Fechamento com sucesso retorna 0.
            printf("\nDEBUG - Arquivo Fechado Com sucesso");
        else
            printf("\nErro no fechamento");
        getchar();
    }
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

void ListarProdutos()
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
            ListarVendas();
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
            ListarProdutos();
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