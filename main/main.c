/*
- Creators: Renato Matos Alves Penna, Pedro Araújo Franco
-
- Functions:
-
- Date: 19/06
-
- Language: Portuguese
*/



#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>


#define true 1
#define false 0




// Funções
void cadastro_cliente(FILE *f);
void login_cliente(FILE *f);
void menu(FILE *f);
void cadastro_fornecedor(FILE *f);
void login_fornecedor(FILE *f);
void cadastros(FILE *f);
void logins(FILE *f);
int localiza_fornecedor(FILE *f, int codigo);
int localiza_cliente(FILE *f, int codigo);
void menu_logado(FILE *f);



// Structs
struct Tendereco
{
    char rua[50];
    char bairro[50];
    int apartamento; // true or false
    int casa;        // true or false
    int num_resid;
};

typedef struct Tendereco endereco;

struct Tcliente
{
    int codigo_cliente;
    char nome[70], data_nascimento[10];
    endereco ender;
    int telefone; // sem hifen
};

typedef struct Tcliente cliente;

struct Tfornecedor
{
    int cod_fornecedor;
    int telefone;
    char buffet[40];
};

typedef struct Tfornecedor fornecedor;





// Função para verificar se o cliente já existe
int localiza_cliente(FILE *f, int codigo)
{
    int achou = 0;
    cliente c;
    fseek(f, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, f);
    while (!feof(f))
    {
        if (codigo == c.codigo_cliente)
        {
            achou++;
            break;
        }
        
    }
    if (achou == 1)
    {
        return true; //achou cliente
    }
    else
    {
        return false; //nao achou
    }
}

// Função para verificar se o fornecedor já existe
int localiza_fornecedor(FILE *f, int codigo)
{
    int achou = 0;
    fornecedor f1;
    fseek(f, 0, SEEK_SET);
    fread(&f1, sizeof(f1), 1, f);
    while (!feof(f))
    {
        if (codigo == f1.cod_fornecedor)
        {
            achou++;
            break;
        }
        
    }
    if (achou == 1)
    {
        return true; // achou fornecedor
    }
    else
    {
        return false; //nao achou fornecedor
    }
}





// MENU INICIAL
void menu(FILE *f)
{
    int escolha;
    printf("\n----MENU----\n");
    printf("Escolha 1 ou 2\n");
    printf("1) Login\n2) Cadastre-se\n");
    escolha = getch();

    switch (escolha)
    {
    // Login
    case '1':
        logins(f);
        break;

    // Cadastro
    case '2':
        cadastros(f);
        break;
    }
}

void logins(FILE *f)
{
    int escolha_login;

    printf("\nEscolha a opção de Login \n");
    printf("1 - Logar como Cliente \n");
    printf("2 - Logar como Fornecedor \n");
    printf("3 - Voltar \n");
    escolha_login = getch();

    switch (escolha_login)
    {
    case '1':
        login_cliente(f);
        break;
    case '2':
        login_fornecedor(f);
        break;
    default:
        menu(f);
    }
}

void cadastros(FILE *f)
{
    int escolha_cadastro;
    printf("\nEscolha a opção de cadastro \n");
    printf("1 - Cadastro de cliente\n");
    printf("2 - Cadastro de fornecedor \n");
    printf("3 - Voltar \n");
    escolha_cadastro = getch();
    switch (escolha_cadastro)
    {
    case '1':
        cadastro_cliente(f);
        break;
    case '2':
        cadastro_fornecedor(f);
        break;
    default:
        system("cls");
        menu(f);
    }
}

void menu_logado(FILE *f)
{
    int escolha;
    if (tipo_usuariolog =1)//cliente
    {
        /* menu do cliente*/
        printf("Você está logado no sistema!\n\nO que deseja fazer?");
        printf("1 - Cadastrar uma festa\n"); //FAZER UMA FUNÇÃO QUE PASSE O ID DO CLIENTE LOGADO
        printf("2 - Calcular valor\n")
        printf("3 - Status da conta\n");
        printf("4 - Informações da conta\n");
        printf("5- Pesquisar clientes e funcionarios pelo ID");
    }
    else if (tipo_usuariolog=2)//fornecedor
    {
        /*menu do forneceodor */
        printf("Você está logado no sistema!\n\nO que deseja fazer?");
    }
    
}



// Variável Global para verificar se o usuario está logado
int verifica_usuariolog = 0; // se logado vira 1
int tipo_usuariolog = 0 // se 1 é cliente, se 2 é fornecedor
int idlogado = 0
// Main
int main()
{
    setlocale(LC_ALL, "portuguese");

    FILE *f;
    f = fopen("documentos.dat", "r+b");
    if (f == NULL)
    {
        perror("Erro ao abrir arquivo!");
        exit(-1);
    }


 while (verifica_usuariolog==0)
 {
    menu(f);
    system("cls");
 }
//Fazer menu pós login
    menu_logado(f);

    fclose(f);
    return 0;
}





// Cadastro do Cliente
void cadastro_cliente(FILE *f)
{
    cliente c;
    int posicao, casa_ou_ap;

    printf("\n--CADASTRO DE CLIENTE--");
    printf("\n\nCrie um código para a sua conta (recomendado mínimo 6 números): ");
    scanf("%d", &c.codigo_cliente);
    posicao = localiza_cliente(f, c.codigo_cliente);
    if (posicao == true)
    {
        printf("\nCódigo já existe\n");
    }
    else
    {
        printf("Digite seu nome completo: ");
        fflush(stdin);
        gets(c.nome);
        printf("Digite seu telefone (apenas números): ");
        scanf("%d", &c.telefone);
        printf("Digite sua data de nascimento (dia/mês/ano): ");
        fflush(stdin);
        scanf("%s", &c.data_nascimento);
        printf("\nMora em apartamento ou casa?\n");
        printf("1 - Apartamento\n");
        printf("2 - Casa\n");
        scanf("%d", &casa_ou_ap);
        if (casa_ou_ap == 1 || casa_ou_ap == 2)
        {
            if (casa_ou_ap == 1)
            {
                c.ender.apartamento = true;
                c.ender.casa = false;
            }
            else
            {
                c.ender.apartamento = false;
                c.ender.casa = true;
            }

        }
        else
        {
            printf("\n\tOpção inválida! Tente novamente.\n\n");
            return;

        }



        printf("Digite o endereço da casa ou apartamento onde você reside atualmente \n");
        printf("Rua:\t");
        fflush(stdin);
        gets(c.ender.rua);
        printf("\nNúmero(apenas o número):\t");
        scanf("%d",&c.ender.num_resid);
        printf("\nBairro:\t");
        fflush(stdin);
        gets(c.ender.bairro);

        // Escrevendo no arquivo
        fseek(f, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, f);

        printf("Usuário cadastrado com sucesso!\n");
        system("pause");
    }
}

// Login cliente
void login_cliente(FILE *f)
{
    int cod, useralive;
     if (verifica_usuariolog==0)
    {
        printf("\n--LOGIN DE CLIENTE--\n");
        printf("Código do cliente:\n");
        scanf("%d",&cod);
       useralive = localiza_cliente(f,cod);
       if (useralive == true)
       {
        printf("Cliente logado com sucesso!\n");
        verifica_usuariolog =1;
        tipo_usuariolog = 1;
        system("pause");
       }
       else
       {
        printf("Erro ao tentar fazer o Login.\nVerifique o código ou cadastre-se antes\n");
        system("pause");
        }

    }
}

// Cadastro Fornecedor
void cadastro_fornecedor(FILE *f)
{
    fornecedor f1;
    int posicao;

    printf("\n--CADASTRO DE FORNECEDOR--");
    printf("\n\nCrie um código para sua conta (recomendado mínimo 6 números): ");
    scanf("%d", &f1.cod_fornecedor);
    posicao = localiza_fornecedor(f, f1.cod_fornecedor);
    if (posicao == true)
    {
        printf("\nCódigo já existe\n");
    }
    else
    {
        printf("Digite seu telefone (apenas números): ");
        scanf("%d", &f1.telefone);
        printf("Digite o nome do buffet: ");
        fflush(stdin);
        scanf("%s", &f1.buffet);

        // Escrevendo no arquivo
        fseek(f, 0, SEEK_END);
        fwrite(&f1, sizeof(f1), 1, f);

        printf("Usuário cadastrado com sucesso!\n");
        system("pause");
    }
}

void login_fornecedor(FILE *f)
{
    int cod,useralive;

    if (verifica_usuariolog==0)
    {
        printf("\n--LOGIN FORNECEDOR--\n");
        printf("Código do fornecedor:\n");
        scanf("%d",&cod);
       useralive = localiza_fornecedor(f,cod);
       if (useralive == true)
       {
        printf("Fornecedor logado com sucesso!\n");
        verifica_usuariolog =1;
        tipo_usuariolog = 2;
        system("pause");
       }
        else
        {
            printf("Erro ao tentar fazer o Login.\nVerifique o código ou cadastre-se antes\n");
        }
    }

}






/*int cria_codigo(FILE *f)
{

    int lastCodigo, novocodigo;
    f = open("clientes.txt", "r+b");
    fseek(f,0,SEEK_END -1);
    lastCodigo = m.codigo
    novocodigo = lastCodigo +1
}
*/
