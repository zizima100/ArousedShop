#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int codigoProduto;
    float valorVenda;
    float valorCompra;
    int produtoAtivo;
} Produto;

typedef struct
{
    int codigoPrdVendido;
    int quantidadeVendida;
    int codigoVenda;
    float lucro;
    int vendaAtiva;
} Venda;

int VerificarAtvVnd()
{
    FILE *arqVendas;
    Venda v;

    int posProcura = 0;

    arqVendas = fopen("vendas", "rb");

    while(1)
    {
        fread(&v, sizeof(Venda), 1, arqVendas);
        if (feof(arqVendas))
            break;
        if (v.vendaAtiva == 0)
        {
            // printf("\n\nEncontrei uma venda inativa na posição %d.", posProcura);
            fclose(arqVendas);
            return posProcura;
        }
        posProcura++;
    }
    // printf("\n\nNão achei venda inativa.");
    fclose(arqVendas);
    return -1;
}

int ProcurarVenda(int codigoVenda)
{
    FILE *arqVendas;
    Venda v;

    int posPesquisa = 0;

    arqVendas = fopen("vendas", "rb");

    while(1)
    {
        fread(&v, sizeof(Venda), 1, arqVendas);
        if(feof(arqVendas))
            break;
        if(v.codigoVenda == codigoVenda)
        {
            fclose(arqVendas);
            return posPesquisa;
        }
        posPesquisa++;
    }
    fclose(arqVendas);
    return -1;
}

int VerificarAtvPrd() // Retorna a posicao do primeiro item desativado.
{
    FILE *arqProdutos;
    Produto p;

    int posicaoEncontrada = 0;

    arqProdutos = fopen("produtos", "rb");

    while(1)
    {
        fread(&p, sizeof(Produto), 1, arqProdutos);
        if (feof(arqProdutos))
            break;
        if (p.produtoAtivo == 0)
        {
            // printf("\n\nEncontrei um meliante desativado na posição: %d.", posicaoEncontrada);
            fclose(arqProdutos);
            return posicaoEncontrada;
        }
        posicaoEncontrada++;
    }
    // printf("\n\nNenhum meliante encontrado.");
    fclose(arqProdutos);
    return -1;
}

int ProcurarProduto(int codigoProduto) // Retorna a posicao do produto a partir de seu código.
{
    FILE *arqProduto;
    Produto p;

    int eof, posicaoEncontrado = 0;

    arqProduto = fopen("produtos", "rb");

    if (arqProduto == NULL)
    {
        return -1;
    }
    else
    {
        while(1)
        {
            fread(&p, sizeof(p), 1, arqProduto);
            if (feof(arqProduto))
                break;
            if (codigoProduto == p.codigoProduto)
            {
                // printf("\n\nENCONTROU O MALDITO");
                fclose(arqProduto);
                return posicaoEncontrado;
            }
            posicaoEncontrado++;
        }
        fclose(arqProduto);
        return -1;
    }
}

int ExisteProduto()
{
    FILE *arqProduto;

    arqProduto = fopen("produtos", "rb");

    if (arqProduto == NULL)
    {
        return 0;
    }
    fclose(arqProduto);
    return 1;
}

void AdicionarVenda()
{
    FILE *arqVendas, *arqCodigoVnd;
    Venda v;

    int select, size, codigoVenda = 1;

    do
    {
        system("clear");
        printf("+=========================+\n");
        printf("|     Adicionar Venda     |\n");
        printf("+=========================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu venda\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("\nDigite uma opção válida. . .");
            getchar();
            continue;
        }

        arqCodigoVnd = fopen("codigoVnd", "r+b");
        if (arqCodigoVnd == NULL)
        {
            arqCodigoVnd = fopen("codigoVnd", "wb");
            fwrite(&codigoVenda, sizeof(codigoVenda), 1, arqCodigoVnd);
            rewind(arqCodigoVnd);
        }
        fread(&codigoVenda, sizeof(codigoVenda), 1, arqCodigoVnd);

        arqVendas = fopen("vendas", "a+b");
        fclose(arqVendas);

        system("clear");
        printf("======== Adicionando Um Novo Produto ========");
        printf("\n\nDigite o código do produto vendido: ");
        scanf("%d%*c", &v.codigoPrdVendido);
        v.codigoVenda = codigoVenda;
        printf("\nDigite a quantidade vendida: ");
        scanf("%d%*c", &v.quantidadeVendida);
        v.vendaAtiva = 1;

        arqVendas = fopen("vendas", "r+b");

        if(VerificarAtvVnd() < 0)
        {
            fseek(arqVendas, 0, SEEK_END);
            fwrite(&v, sizeof(Venda), 1, arqVendas);
        }
        else
        {
            fseek(arqVendas, VerificarAtvPrd() * sizeof(Venda), SEEK_SET);
            fwrite(&v, sizeof(Venda), 1, arqVendas);
        }

        codigoVenda++;
        rewind(arqCodigoVnd);
        fwrite(&codigoVenda, sizeof(codigoVenda), 1, arqCodigoVnd);

        fclose(arqCodigoVnd);
        fclose(arqVendas);
        return 0;
    } while (select != 0);
}

void ListarVendas()
{
    FILE *arqVendas, *arqProdutos;
    Venda v;
    Produto p;

    arqVendas = fopen("vendas", "a+b");
    arqProdutos = fopen("produtos", "rb");

    if (arqVendas == NULL)
        printf("ERRO NA ABERTURA DO ARQUIVO");
    else
    {
        system("clear");
        printf("======== Lista de Vendas ========\n");
        while(1)
        {
            fread(&v, sizeof(v), 1, arqVendas); // 1 = Quantos structs setão lidos.
            if (feof(arqVendas))
                break;
            if (v.vendaAtiva != 0)
            {
                fseek(arqProdutos, ProcurarProduto(v.codigoPrdVendido) * sizeof(Produto), SEEK_SET);
                fread(&p, sizeof(Produto), 1, arqProdutos);

                printf("\nCódigo da Venda: %d.", v.codigoVenda);
                printf("\nProduto Vendido: %s.", p.nome);
                printf("\nCódigo do Produto Inserido: %d.", v.codigoPrdVendido);
                printf("\nQuantidade Vendida: %d\n", v.quantidadeVendida);
                printf("\nLucro: R$%.2f.", (p.valorVenda - p.valorCompra) * v.quantidadeVendida);
                printf("\n\n========\n");
            }
        }
        fclose(arqVendas);
        fclose(arqProdutos);

        printf("\n\nPressione Enter para continuar. . .");
        getchar();
    }
}

void RemoverVenda()
{
    FILE *arqVendas, *arqProdutos;
    Venda v;
    Produto p;

    int select, codigoVenda, posVenda, posProduto, select2;

    do
    {
        system("clear");
        printf("+=======================+\n");
        printf("|     Remover Venda     |\n");
        printf("+=======================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu venda\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            printf("\nDigite uma opção válida. . .");
            getchar();
            continue;
        }

        printf("Digite o código da venda: ");
        scanf("%d%*c", &codigoVenda);

        if(ProcurarVenda(codigoVenda) < 0)
        {
            system("clear");
            printf("Código não encontrado.\n\nVerifique o código da venda na lista de vendas.");
            printf("\n\nPressione enter para continuar. . .");
            getchar();
            return;
        }
        else
        {
            arqVendas = fopen("vendas", "r+b");
            arqProdutos = fopen("produtos", "rb");

            fseek(arqVendas, ProcurarVenda(codigoVenda) * sizeof(Venda), SEEK_SET);
            fread(&v, sizeof(Venda), 1, arqVendas);

            fseek(arqProdutos, ProcurarProduto(v.codigoPrdVendido) * sizeof(Produto), SEEK_SET);
            fread(&p, sizeof(Produto), 1, arqProdutos);

            do
            {
                system("clear");
                printf("======== Removendo Venda ========");
                printf("\n\nA venda selecionada está na posição: %d.", ProcurarVenda(codigoVenda));
                printf("\nO produto vendido é: %s.", p.nome);
                printf("\nO código do produto é: %s.", v.codigoPrdVendido);
                printf("\nA quantidade vendida é: %d.", v.quantidadeVendida);
                printf("\nO valor de compra é: R$%.2f.", p.valorCompra);
                printf("\nO valor de venda é: R$%.2f.", p.valorVenda);
                printf("\nO lucro é: R$%.2f.", (p.valorVenda - p.valorCompra) * v.quantidadeVendida);

                if(v.vendaAtiva == 1)
                    printf("\n\nA venda está: ATIVA");
                else
                    printf("\n\nA venda está: INATIVA");

                printf("\n\n========\nO que você quer fazer?\n[ 0 ] - Desativar Venda\n[ 1 ] - Ativar Venda");
                printf("\nResposta: ");
                scanf("%d%*c", &select2);

                switch (select2)
                {
                case 0:
                    v.vendaAtiva = 0;
                    break;
                case 1:
                    v.vendaAtiva = 1;
                    break;

                default:
                    printf("\nDigite uma opção válida. . .");
                    continue;
                }
            } while (select2 < 0 && select2 > 1);

            fseek(arqVendas, ProcurarVenda(codigoVenda) * sizeof(Venda), SEEK_SET);
            fwrite(&v, sizeof(Venda), 1, arqVendas);

            fclose(arqVendas);
            fclose(arqProdutos);
        }
    } while (select != 0);
}

void AdicionarProduto()
{
    FILE *arqProdutos, *arqCodigoPrd;
    Produto p;

    int select, codigoDoPrd = 1;

    do
    {
        system("clear");
        printf("+===========================+\n");
        printf("|     Adicionar Produto     |\n");
        printf("+===========================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu produto\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("\nDigite uma opção válida. . .");
            getchar();
            continue;
        }

        arqProdutos = fopen("produtos", "a+b");
        fclose(arqProdutos);

        arqCodigoPrd = fopen("codigoPrd", "r+b");
        if(arqCodigoPrd == NULL)
        {
            arqCodigoPrd = fopen("codigoPrd", "wb");
            fwrite(&codigoDoPrd, sizeof(codigoDoPrd), 1, arqCodigoPrd);
            rewind(arqCodigoPrd);
        }
        fread(&codigoDoPrd, sizeof(codigoDoPrd), 1, arqCodigoPrd);

        system("clear");
        printf("======== Adicionando Novo Produto ========");
        printf("\n\nDigite o nome do produto: ");
        gets(p.nome);
        p.nome[strcspn(p.nome, "\n")] = '\0';
        printf("\n\nDigite o valor de compra: ");
        scanf("%f%*c", &p.valorCompra);
        printf("\n\nDigite o valor de venda: ");
        scanf("%f%*c", &p.valorVenda);
        p.produtoAtivo = 1;
        p.codigoProduto = codigoDoPrd;

        codigoDoPrd++;
        rewind(arqCodigoPrd);
        fwrite(&codigoDoPrd, sizeof(codigoDoPrd), 1, arqCodigoPrd);

        arqProdutos = fopen("produtos", "r+b");

        if (VerificarAtvPrd() < 0)
        {
            fseek(arqProdutos, 0, SEEK_END);
            fwrite(&p, sizeof(Produto), 1, arqProdutos);
        }
        else
        {
            fseek(arqProdutos, VerificarAtvPrd() * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arqProdutos);
        }
        fclose(arqProdutos);
        fclose(arqCodigoPrd);
    } while (select != 0);
}

void ListarProdutos()
{
    if(!ExisteProduto())
    {
        printf("========\n\nNenhum produto cadastrado.");
        printf("\n\nAdicione um produto para acessar essa opção.");
        printf("\n\nPressione Enter para continuar. . . ");
        getchar();
        return;
    }

    FILE *arqProdutos;
    Produto p;

    arqProdutos = fopen("produtos", "a+b");
    if (arqProdutos == NULL)
        printf("ERRO NA ABERTURA DO ARQUIVO");
    else
    {
        system("clear");
        printf("+=========================+\n");
        printf("|     Lista de Produtos   |\n");
        printf("+=========================+\n");
        while(1)
        {
            fread(&p, sizeof(p), 1, arqProdutos); // 1 = Quantos structs setão lidos.
            if (feof(arqProdutos))
                break;
            if (p.produtoAtivo != 0)
            {
                printf("\nNome do Produto: %s.", p.nome);
                printf("\nCódigo do Produto: %d.", p.codigoProduto);
                printf("\nValor Compra: R$%.2f.", p.valorCompra);
                printf("\nValor Venda: R$%.2f.\n", p.valorVenda);
                printf("\n========\n");
            }
        }
        fclose(arqProdutos);
        printf("\n\nPressione Enter para continuar. . .");
        getchar();
    }
}

void RemoverProduto()
{
    if(!ExisteProduto())
    {
        printf("========\n\nNenhum produto cadastrado.");
        printf("\n\nAdicione um produto para acessar essa opção.");
        printf("\n\nPressione Enter para continuar. . .");
        getchar();
        return;
    }

    FILE *arqProdutos;
    Produto p;

    int select;
    int codPesquisado;
    int posicaoCodigo;

    do
    {
        system("clear");
        printf("+=========================+\n");
        printf("|     Remover Produto     |\n");
        printf("+=========================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu produtos\n");
        printf("[ 1 ] - Continuar\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

        switch (select)
        {
        case 0:
            continue;
        case 1:
            break;
        default:
            select = -1;
            printf("\nDigite uma opção válida. . .");
            getchar();
            continue;
        }

        printf("\nDigite o código do produto que deseja remover: ");
        scanf("%d%*c", &codPesquisado);

        posicaoCodigo = ProcurarProduto(codPesquisado);

        if (posicaoCodigo >= 0)
        {
            system("clear");

            printf("\nO código existe e sua posição é: %d.", posicaoCodigo);

            arqProdutos = fopen("produtos", "r+b");

            fseek(arqProdutos, posicaoCodigo * sizeof(Produto), SEEK_SET);

            fread(&p, sizeof(Produto), 1, arqProdutos);

            printf("\n\nNome do produto: %s.", p.nome);

            printf("\n\nEstado do produto: ");
            if (p.produtoAtivo == 1)
                printf("Ativado.");
            else
                printf("Desativado.");

            printf("\n\n========\nO que você quer fazer?\n[ 0 ] - Desativar Produto\n[ 1 ] - Ativar Produto");
            printf("\nResposta: ");
            scanf("%d%*c", &p.produtoAtivo);

            fseek(arqProdutos, posicaoCodigo * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arqProdutos);

            fclose(arqProdutos);
        }
        else
        {
            printf("\n\nCódigo %d não encontrado.", codPesquisado);
        }
        printf("\n\nPressione Enter para continuar. . .");
        getchar();
    } while (select != 0);
}

void MenuVenda()
{
    int select;

    if (!ExisteProduto())
    {
        printf("\n========\n\nNenhum produto cadastrado.\n\nCadastre um produto para poder acessar o menu de vendas.");
        printf("\n\nPressione Enter para continuar. . .");
        getchar();
        return;
    }

    do
    {
        system("clear");
        printf("+====================+\n");
        printf("|     Menu Venda     |\n");
        printf("+====================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu principal\n");
        printf("[ 1 ] - Adicionar Vendas\n");
        printf("[ 2 ] - Listar Vendas\n");
        printf("[ 3 ] - Remover Vendas\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

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
            printf("\nDigite uma opção válida. . .");
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
        printf("+======================+\n");
        printf("|     Menu Produto     |\n");
        printf("+======================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu principal\n");
        printf("[ 1 ] - Adicionar Produtos\n");
        printf("[ 2 ] - Listar Produtos\n");
        printf("[ 3 ] - Remover Produtos\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

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
            printf("\nDigite uma opção válida. . .");
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
        printf("+=======================================+\n");
        printf("|     Menu Principal - Aroused Shop     |\n");
        printf("+=======================================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Sair do Programa\n");
        printf("[ 1 ] - Acessar Menu Vendas\n");
        printf("[ 2 ] - Acessar Menu Produtos\n");

        printf("\nResposta: ");
        scanf("%d%*c", &select);

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
            printf("\nDigite uma opção válida. . .");
            getchar();
            break;
        }
    } while (select != 0);
    return 0;
}
