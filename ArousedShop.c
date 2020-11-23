#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char codigoProduto[6];
    float valorVenda;
    float valorCompra;
    int produtoAtivo;
} Produto;

typedef struct
{
    char codigoPrdVendido[6];
    int quantidadeVendida;
    int codigoVenda;
    float lucro;
    int vendaAtiva;
} Venda;

int VerificarAtvPrd() // Retorna a posicao do primeiro item desativado.
{
    FILE *procura;
    Produto p;

    int posicaoEncontrada = 0;

    procura = fopen("produtos", "rb");

    while (1)
    {
        fread(&p, sizeof(Produto), 1, procura);
        if (feof(procura))
            break;
        if (p.produtoAtivo == 0)
        {
            printf("\n\nEncontrei um meliante desativado na posição: %d.", posicaoEncontrada);
            fclose(procura);
            return posicaoEncontrada;
        }
        else
        {
            printf("\n\nNenhum meliante encontrado.");
            fclose(procura);
            return -1;
        }
        posicaoEncontrada++;
    }
}

int ProcurarProduto(char codigoProduto[6])
{
    FILE *procura;
    Produto p;

    int eof, posicaoEncontrado = 0;

    procura = fopen("produtos", "rb");

    if (procura == NULL)
    {
        return -1;
    }
    else
    {
        while (1)
        {
            fread(&p, sizeof(p), 1, procura);
            if (feof(procura))
                break;
            if (strcmp(codigoProduto, p.codigoProduto) == 0)
            {
                // printf("\n\nENCONTROU O MALDITO");
                fclose(procura);
                return posicaoEncontrado;
            }
            posicaoEncontrado++;
        }
        fclose(procura);
        return -1;
    }
}

void AdicionarVenda()
{
    FILE *arquivo, *codigo;
    Venda v;

    int select, size, n = 1;

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

        codigo = fopen("codigo", "a+b");

        if (NULL != codigo)
        {
            fseek(codigo, 0, SEEK_END);
            size = ftell(codigo);

            if (0 == size)
            {
                printf("Arquivo Criado\n");
                fwrite(&n, sizeof(n), 1, codigo);
            }
        }

        rewind(codigo);
        fread(&n, sizeof(n), 1, codigo);

        fclose(codigo);

        arquivo = fopen("vendas", "a+b");

        if (arquivo == NULL)
            printf("ERRO NA ABERTURA DO ARQUIVO");
        else
        {
            system("clear");
            printf("DEBUG - ARQUIVO VENDAS ABERTO");
            printf("\n\nDigite o código do produto vendido [6 Dígitos]: ");
            gets(v.codigoPrdVendido);
            v.codigoPrdVendido[strcspn(v.codigoPrdVendido, "\n")] = '\0'; // Encontra a posicao onde está o \n no final da string e troca por \0.
            v.codigoVenda = n;
            printf("\n\nDigite a quantidade vendida: ");
            scanf("%d%*c", &v.quantidadeVendida); // %*c Le a info, mas n armazena. Basicamente um getchar();
            v.vendaAtiva = 1;
            fwrite(&v, sizeof(Venda), 1, arquivo); // 1 = Quantos Structs serão armazenados.
            if (ferror(arquivo))
                printf("\nDeu erro na gravação da vendas. . .");
            else
                printf("\nDeu bom na gravação da venda!");
            if (!fclose(arquivo)) // Fechamento com sucesso retorna 0.
            {
                printf("\nArquivo fechado Com sucesso!");
                getchar();
            }
            else
                printf("\nErro no fechamento do arquivo. . .");

            n++;

            fopen("codigo", "w");
            fwrite(&n, sizeof(n), 1, codigo);
            fclose(codigo);

            getchar();
            return 0;
        }
    } while (select != 0);
}

void ListarVendas()
{
    FILE *arquivo;
    Venda v;

    int eof; // Registra o fim do arquivo lido.

    arquivo = fopen("vendas", "a+b");
    if (arquivo == NULL)
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
                if (eof != 0)
                {
                    printf("========\nCódigo do Produto: %s.", v.codigoPrdVendido);
                    printf("\nCódigo da Venda: %d.", v.codigoVenda);
                    printf("\nQuantidade Vendida: %d\n", v.quantidadeVendida);
                    //printf("\nLucro Total: R$%.2f\n", v.lucro); - Implementar no futuro quando juntar com produto.
                }
            }
        }
        getchar();
        if (!fclose(arquivo)) // Fechamento com sucesso retorna 0.
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
        printf("+=======================+\n");
        printf("|     Remover Venda     |\n");
        printf("+=======================+\n");
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
    FILE *arquivo;
    Produto p;

    int select;

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

        arquivo = fopen("produtos", "a+b");
        fclose(arquivo);

        system("clear");
        printf("DEBUG - ARQUIVO PRODUTOS ABERTO");
        printf("\n\nDigite o código do produto [6 Dígitos]: ");
        gets(p.codigoProduto);
        p.codigoProduto[strcspn(p.codigoProduto, "\n")] = '\0'; // Encontra a posicao onde está o \n no final da string e troca por \0.
        printf("\n\nDigite o nome do produto: ");
        gets(p.nome);
        p.nome[strcspn(p.nome, "\n")] = '\0';
        printf("\n\nDigite o valor de compra: ");
        scanf("%f%*c", &p.valorCompra);
        printf("\n\nDigite o valor de venda: ");
        scanf("%f%*c", &p.valorVenda);
        p.produtoAtivo = 1;

        arquivo = fopen("produtos", "r+b");

        if (VerificarAtvPrd() < 0)
        {
            fseek(arquivo, 0, SEEK_END);
            fwrite(&p, sizeof(Produto), 1, arquivo);
        }
        else
        {
            fseek(arquivo, VerificarAtvPrd() * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arquivo);
        }

        fclose(arquivo);

        getchar();
    } while (select != 0);
}

void ListarProdutos()
{
    FILE *arquivo;
    Produto p;

    int eof; // Registra o fim do arquivo lido.

    arquivo = fopen("produtos", "a+b");
    if (arquivo == NULL)
        printf("ERRO NA ABERTURA DO ARQUIVO");
    else
    {
        system("clear");
        printf("DEBUG - ARQUIVO PRODUTO ABERTO\n");

        while (!feof(arquivo)) // Enquanto for diferente da indicação do final do arquivo.
        {
            eof = fread(&p, sizeof(p), 1, arquivo); // 1 = Quantos structs setão lidos.
            if (ferror(arquivo))
                printf("\n\nErro na leitura do arquivo vendas. . .");
            else
            {
                if (eof != 0 && p.produtoAtivo != 0)
                {
                    printf("========\nNome do Produto: %s", p.nome);
                    printf("\nCódigo do Produto: %s", p.codigoProduto);
                    printf("\nValor Compra: R$%.2f", p.valorCompra);
                    printf("\nValor Venda: R$%.2f\n", p.valorVenda);
                }
            }
        }
        if (!fclose(arquivo)) // Fechamento com sucesso retorna 0.
        {
            printf("\nDEBUG - Arquivo Fechado Com sucesso");
        }
        else
            printf("\nErro no fechamento");
        getchar();
    }
}

void RemoverProduto()
{
    FILE *fp;
    Produto p;

    int select;
    char codPesquisado[6];
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
            printf("Digite uma opção válida. . .");
            getchar();
            continue;
        }

        printf("\nDigite o código do produto que deseja remover: ");
        gets(codPesquisado);

        posicaoCodigo = ProcurarProduto(codPesquisado);

        if (posicaoCodigo >= 0)
        {
            system("clear");

            printf("\nO código existe e sua posição é: %d.", posicaoCodigo);

            fp = fopen("produtos", "r+b");

            fseek(fp, posicaoCodigo * sizeof(Produto), SEEK_SET);

            fread(&p, sizeof(Produto), 1, fp);

            printf("\n\nNome do produto: %s.", p.nome);

            printf("\n\nEstado do produto: ");
            if (p.produtoAtivo == 1)
                printf("Ativado.");
            else
                printf("Desativado.");

            printf("\n\nDigite o estado atual do produto: ");
            scanf("%d%*c", &p.produtoAtivo);

            fseek(fp, posicaoCodigo * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, fp);

            fclose(fp);
        }
        else
        {
            printf("\n\nCódigo %s não encontrado. . .", codPesquisado);
        }
        getchar();
    } while (select != 0);
}

void MenuVenda()
{
    int select;

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
        printf("+======================+\n");
        printf("|     Menu Produto     |\n");
        printf("+======================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Voltar para o menu principal\n");
        printf("[ 1 ] - Adicionar Produtos\n");
        printf("[ 2 ] - Listar Produtos\n");
        printf("[ 3 ] - Remover Produtos\n");

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
        printf("+=======================================+\n");
        printf("|     Menu Principal - Aroused Shop     |\n");
        printf("+=======================================+\n");
        printf("\n\nSelecione uma opção:\n");
        printf("[ 0 ] - Sair do Programa\n");
        printf("[ 1 ] - Acessar Menu Vendas\n");
        printf("[ 2 ] - Acessar Menu Produtos\n");

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