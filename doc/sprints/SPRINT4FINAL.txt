/********************************************************
* FILENAME : main.c
* DESCRIPTION : A system for a party room enterprise. The
* user can submit partys and write them on a external file.
* This system have register and login system for Clients and Suplliers too, so it can be used for
* many purposes.
*
* PUBLIC FUNCTIONS :
* void cadastro_cliente(FILE *fc);
* void login_cliente(FILE *fc);
* void menu(FILE *f, FILE *fp, FILE *fc, FILE *fct);
* void cadastro_fornecedor(FILE *f);
* void login_fornecedor(FILE *f);
* void cadastros(FILE *f, FILE *fp, FILE *fc, FILE *fct);
* void logins(FILE *f, FILE *fp, FILE *fc, FILE *fct);
* int localiza_fornecedor(FILE *f, int codigo);
* int localiza_cliente(FILE *fc, int codigo);
* void menu_logado(FILE *f, FILE *fp, FILE *fc, FILE *fct);
* void cadastra_festas(FILE *f, FILE *fp, FILE *fc, FILE *fct);
* void pesquisa_cliente_funcionario(FILE *f, FILE *fc);
* int valida_festa(FILE *fp, char data[10], int minutosInicio, int minutosTermino, int sabado);
* void cadastra_contrato(FILE *fp, int codigo, FILE *fct);
* void mostrafestadeumcliente(FILE *fp, FILE *fc, FILE *fct);
* int localizafesta(FILE *fp, int codigo);
* void status_conta(FILE *fct, FILE *fc);
* int localizacontrato(FILE *fct, int codigo);
* void relatoriofestaspelodia(FILE *fp, FILE *fct);
* void mostracontratodafesta(FILE *fct, int codigo);
* void imprime_contrato(FILE *fct);
*
* NOTES :
* . Project made for a interdiciplinar activity from the course of Software Engineering,
* especificaly for the diciplines AEDS and FES. University: PUC MINAS, 1° Semester.
*
* . party.dat -> File for storing partys data (in binary).
* . clientes.dat -> File for storing clients data (in binary).
* . fornecedores.dat -> File for storing suppliers data (in binary).
* . contrato.dat -> File for storing contracts data (in binary).
*
* AUTHOR : Renato Matos & Pedro Araújo
* START DATE : 15 June 2023
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>



#define true 1
#define false 0

// Variável Global para verificar se o usuario está logado
int verifica_usuariolog = 0; // se logado vira 1
int tipo_usuariolog = 0;     // se 1 é cliente, se 2 é fornecedor
int idlogado = 0;

// Funções
/********************************************************
* NAME : void Cadastro_cliente(FILE *fc)
* DESCRIPTION : Função criada para registro de um cliente no arquivo fc
* INPUTS : Dados do Struct cliente
* PARAMETERS :
* FILE fc : Arquivo pelo qual sera registrado os clientes
* RETURN :
* Type :
* Error code :
* Values : Codigo = codigo ja registrado no arquivo
********************************************************/
void cadastro_cliente(FILE *fc);
/********************************************************
* NAME : void login_cliente(FILE *fc)
* DESCRIPTION : Função criada para login de um cliente no sistema,
* conferindo se o codigo inserido pelo usuario existe no arquivo fc.
* INPUTS : int codigo
* PARAMETERS :
*   FILE fc : Arquivo que foi registrado os clientes
* RETURN :
* Type :
* Error code :
* Values : Codigo != todos os codigos inseridos
********************************************************/
void login_cliente(FILE *fc);
/********************************************************
* NAME : void menu(FILE *f, FILE *fp,FILE *fc, FILE *fct);
* DESCRIPTION : Função criada com o recurso switch case para o usuario escolher entre as açoes: Cadastrar, Login e sair.
* INPUTS : int op
* PARAMETERS :
*   FILE fc : Arquivo que foi registrado os clientes
*   FILE fp: Arquivo de registro de festas
*   FILE f: Arquivo de registro de fornecedores
*   FILE fct: Arquivo de registro de contratos
********************************************************/
void menu(FILE *f, FILE *fp,FILE *fc, FILE *fct);
/********************************************************
* NAME : void Cadastro_fornecedor(FILE *f)
* DESCRIPTION : Função criada para registro de um fornecedor no arquivo f
* INPUTS :  Dados do Struct fornecedor
* PARAMETERS :
* FILE f : Arquivo pelo qual sera registrado os fornecedores
* RETURN :
* Type :
* Error code :
* Values : Codigo = codigo ja registrado no arquivo
********************************************************/
void cadastro_fornecedor(FILE *f);
/********************************************************
* NAME : void login_fornecedor(FILE *f)
* DESCRIPTION : Função criada para login de um fornecedor no sistema,
* conferindo se o codigo inserido pelo usuario existe no arquivo fc.
* INPUTS : int codigo
* PARAMETERS :
*   FILE f : Arquivo que foi registrado os fornecedores
* RETURN :
* Type :
* Error code :
* Values : Codigo != todos os codigos inseridos
********************************************************/
void login_fornecedor(FILE *f);
/********************************************************
* NAME : void cadastros(FILE *f, FILE *fp,FILE *fc, FILE *fct);
* DESCRIPTION : Função criada com o recurso switch case para o usuario
* escolher entre as açoes: Cadastro de cliente, cadastro de fornecedor e sair.
* INPUTS : int op
* PARAMETERS :
*   FILE fc : Arquivo que foi registrado os clientes
*   FILE fp: Arquivo de registro de festas
*   FILE f: Arquivo de registro de fornecedores
*   FILE fct: Arquivo de registro de contratos
********************************************************/
void cadastros(FILE *f, FILE *fp,FILE *fc, FILE *fct);
/********************************************************
* NAME : void logins(FILE *f, FILE *fp,FILE *fc, FILE *fct);
* DESCRIPTION : Função criada com o recurso switch case para o usuario
* escolher entre as açoes: login de cliente, login de cliente e sair.
* INPUTS : int op
* PARAMETERS :
*   FILE fc : Arquivo que foi registrado os clientes
*   FILE fp: Arquivo de registro de festas
*   FILE f: Arquivo de registro de fornecedores
*   FILE fct: Arquivo de registro de contratos
********************************************************/
void logins(FILE *f, FILE *fp,FILE *fc, FILE *fct);
/********************************************************
* NAME : int localiza_fornecedor(FILE *f, int codigo);
* DESCRIPTION : Função com o objetivo de percorrer o arquivo f
* e verificar se existe um fornecedor registrado com o mesmo codigo passado por parametro. Retorna true se achou e false se nao encontrou.
* INPUTS :
* PARAMETERS :
*   FILE f: Arquivo de registro de fornecedores
*   int codigo: codigo inserido pelo usuario
* RETURN :
* Type : boolean (true ou false)
* Error code :
* Values :
********************************************************/
int localiza_fornecedor(FILE *f, int codigo);
/********************************************************
* NAME : int localiza_cliente(FILE *fc, int codigo);
* DESCRIPTION : Função com o objetivo de percorrer o arquivo f
* e verificar se existe um cliente registrado com o mesmo codigo passado por parametro. Retorna true se achou e false se nao encontrou.
* INPUTS :
* PARAMETERS :
*   FILE fc: Arquivo de registro de Clientes
*   int codigo: codigo inserido pelo usuario
* RETURN :
* Type : boolean (true ou false)
* Error code :
* Values :
********************************************************/
int localiza_cliente(FILE *fc, int codigo;);
/********************************************************
* NAME : void menu_logado(FILE *f, FILE *fp,FILE *fc, FILE *fct);
* DESCRIPTION : Função executada apos o login com o recurso switch case para o usuario escolher entre as açoes:
* cadastrar festa, atualizar status da conta, pesquisar por funcionarios ou clientes, mostrar festas de determinado cliente, mostrar as festas de uma data especifica, imprime contratos, sair.
* INPUTS : int op
* PARAMETERS :
*   FILE f : Arquivo pelo qual sera registrado os fornecedores
*   FILE fp: Arquivo de registro de festas
*   FILE fc: Arquivo de registro de clientes
*   FILE fct: Arquivo de registro de contratos
********************************************************/
void menu_logado(FILE *f, FILE *fp, FILE *fc, FILE *fct);
/********************************************************
* NAME : void Cadastra_festas(FILE *f, FILE *fp, FILE *fc,FILE *fct)
* DESCRIPTION : Função criada para registro de uma festa no arquivo fp
* INPUTS :  Dados do Struct festa
* PARAMETERS :
*   FILE f : Arquivo pelo qual sera registrado os fornecedores
*   FILE fp: Arquivo de registro de festas
*   FILE fc: Arquivo de registro de clientes
*   FILE fct: Arquivo de registro de contratos
* RETURN :
* Type :
* Error code :
* Values : Codigo = codigo ja registrado no arquivo fp
********************************************************/
void cadastra_festas(FILE *f, FILE *fp, FILE *fc,FILE *fct);
/********************************************************
* NAME : pesquisa_cliente_funcionario(FILE * f, FILE *fc);
* DESCRIPTION : Função criada para pesquisa de um cliente ou funcionario por meio do codigo
* INPUTS : int codigo
* PARAMETERS :
*   FILE f : Arquivo pelo qual sera registrado os fornecedores
*   FILE f: Arquivo de registro de fornecedores
* RETURN :
* Type :
* Error code :
* Values : Codigo = codigo nao registrado no arquivo f ou fc
********************************************************/
void pesquisa_cliente_funcionario(FILE * f, FILE *fc);
/********************************************************
* NAME : int valida_festa(FILE *fp, char data[10], int minutosInicio,int minutosTermino, int sabado);
* DESCRIPTION : Função com o objetivo de percorrer o arquivo fp e checar se o horario escolhido para a festa esta disponivel
* INPUTS :
* PARAMETERS :
*   FILE fp: Arquivo de registro de festas
*   int minutosInicio: horario de inicio da festa em minutos
*   int minutosTermino: horario de termino da festa em minutos
*   int sabado: variavel registrada como true ou false. Determina se a festa foi marcada para um sabado ou nao.
* RETURN :
* Type : boolean (true ou false)
* Error code :
* Values :
********************************************************/
int valida_festa(FILE *fp, char data[10], int minutosInicio,int minutosTermino, int sabado);
/********************************************************
* NAME : void cadastra_contrato(FILE *fp, int codigo, FILE *fct)
* DESCRIPTION : Função gerada para cadastrar o contrato após a criação da festa.
* INPUTS :
* PARAMETERS :
*   FILE fp: ponteiro para o arquivo de registro de festas
*   int codigo: código da festa, usado para conectar o contrato à sua respectiva festa
*   FILE *fct: Ponteiro para o arquivo de registro de contratos.
*
* RETURN : Struct Contrat.
* Type : binário
* Error code : fct = NULL
* Values :
********************************************************/
void cadastra_contrato(FILE *fp, int codigo, FILE *fct);
/********************************************************
* NAME : mostrafestadeumcliente(FILE *fp,FILE *fc,FILE *fct);
* DESCRIPTION : Função de exibiçao das festas de um cliente a partir de seu codigo.
* INPUTS : int cod
* PARAMETERS :
*   FILE fp: Arquivo de registro de festas
*   FILE fc: Arquivo de registro de clientes
*   FILE fct: Arquivo de registro de contratos
* RETURN :
* Type :
* Error code :
* Values : cod = tipo errado da variavel
********************************************************/
void mostrarfestasdeumcliente(FILE *fp,FILE *fc,FILE *fct);
/********************************************************
* NAME : int localizafesta(FILE *fp, int codigo);
* DESCRIPTION : função com o objetivo de percorrer o arquivo fp
* e verificar se existe uma festa registrada com o mesmo codigo passado por parametro. Retorna true se achou e false se nao encontrou.
* INPUTS :
* PARAMETERS :
*   FILE *fp: Arquivo de registro de festas
*   int codigo: codigo inserido pelo usuario
* RETURN :
* Type : boolean (true ou false)
* Error code :
* Values :
********************************************************/
int localizafesta(FILE *fp, int codigo);
/********************************************************
* NAME : void status_conta(FILE *fct, FILE *fc);
* DESCRIPTION : Função para atualizar o status de um contrato. Pode escolher entre pagar ou cancelar a festa. Essas opçoes serao escolhidas a partir do metodo switch.
* INPUTS : op
* PARAMETERS :
*   FILE *fct: arquivo de registro de contratos
*   FILE *fc: arquivo de registro de clientes
*
*
* RETURN :
* Type :
* Error code :
* Values :
********************************************************/
void status_contrato(FILE *fct, FILE *fc);
/********************************************************
* NAME : int localizacontrato(FILE *fct, int codigo);
* DESCRIPTION : função com o objetivo de percorrer o arquivo fct
* e verificar se existe um contrato com o mesmo codigo passado por parametro. Retorna true se achou e false se nao encontrou.
* INPUTS :
* PARAMETERS :
*   FILE *fct: Arquivo de registro de contratos
*   int codigo: codigo inserido pelo usuario
* RETURN :
* Type : boolean (true ou false)
* Error code :
* Values :
********************************************************/
int localizacontrato(FILE *fct, int codigo);
/********************************************************
* NAME : void relatoriofestaspelodia(FILE *fp,FILE *fct)
* DESCRIPTION : Função com objetivo de exibir os detalhes de todas as festas de um dia especifico. Dia será escolhido pelo usuario.
* INPUTS : char[10] data
* PARAMETERS :
*   FILE *fp : arquivo de registro de festas
*   FILE *fct: arquivo de registro de contratos
*
*
* RETURN :
* Type :
* Error code :
* Values :
********************************************************/
void relatoriofestaspelodia(FILE *fp,FILE *fct);
/********************************************************
* NAME : void mostracontratodafesta(FILE *fct,int codigo);
* DESCRIPTION : Apos acionada a Função de exibicao de festas pelo dia, esta Função é chamada. Tem o objetivo de imprimir os detalhes do contratos das festas registradas na data escolhida pelo cliente(Na outra Função).
* INPUTS :
* PARAMETERS :
*   FILE *fct : arquivo de registro de contratos
*   int codigo : codigo do contrato que contem a mesma data inserida pelo usuario na Função "reatoriofestaspelodia"
*
*
* RETURN :
* Type :
* Error code :
* Values :
********************************************************/
void mostracontratodafesta(FILE *fct,int codigo);


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

struct Tdiasemana
{
    int domingo;
    int segunda;
    int terca;
    int quarta;
    int quinta;
    int sexta;
    int sabado;
};
 typedef struct Tdiasemana diasemana;

struct Tstatus
{
    int pago;
    int cancelado;
    int pagar;
};
typedef struct Tstatus status;




struct tcontrato
{
    int codigo_festa;
    int numero_contrato;
    float valor_total;
    float valor_final;
    int desconto;
    status stat;
    char pagamento[17];
};
typedef struct tcontrato contrato;

struct Tfesta
{
    int codigo_festa;
    int codigo_cliente;
    int quantidade_convidados;
    char data[11];
    int minutosInicio,minutosTermino;
    char tema[50];
    int codigo_fornecedor;
    diasemana diasem;

};

typedef struct Tfesta festa;


// Função para verificar se o cliente já existe
int localiza_cliente(FILE *fc,int codigo)
{
    int achou = 0;
    cliente c;
    fseek(fc, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, fc) == 1)
    {
        if (codigo == c.codigo_cliente)
        {
            achou++;
            break;
        }
    }
    if (achou == 1)
    {
        return true; // achou cliente
    }
    else
    {
        return false; // nao achou
    }
}

// Função para verificar se o fornecedor já existe
int localiza_fornecedor(FILE *f, int codigo)
{
    int achou = 0;
    fornecedor f1;
    fseek(f, 0, SEEK_SET);
    while (fread(&f1, sizeof(f1), 1, f) == 1)
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
        return false; // nao achou fornecedor
    }
}
//Função para verificar se a festa já existe
int localizafesta(FILE *fp, int codigo)
{
     int achou = 0;
    festa nova_festa;
    fseek(fp, 0, SEEK_SET);
    while (fread(&nova_festa, sizeof(nova_festa), 1, fp) == 1)
    {
        if (codigo == nova_festa.codigo_festa)
        {
            achou++;
            break;
        }
    }
    if (achou == 1)
    {
        return true; // achou festa
    }
    else
    {
        return false; // nao achou festa
    }
}

//Função para verificar se o contrato já existe
int localizacontrato(FILE *fct, int codigo)
{
     int achou = 0;
    contrato contrat;
    fseek(fct, 0, SEEK_SET);
    while (fread(&contrat, sizeof(contrat), 1, fct) == 1)
    {
        if (codigo == contrat.numero_contrato)
        {
            achou++;
            break;
        }
    }
    if (achou == 1)
    {
        return true; // achou contrato
    }
    else
    {
        return false; // nao achou contrato
    }
}


// MENU INICIAL
void menu(FILE *f, FILE *fp, FILE *fc, FILE *fct)
{
    int escolha;
    printf("\n----MENU----\n");
    printf("Escolha 1 ou 2\n");
    printf("1) Login\n2) Cadastre-se\n3)Sair\n");
    escolha = getch();

    switch (escolha)
    {
    // Login
    case '1':
        logins(f,fp,fc,fct);
        break;

    // Cadastro
    case '2':
        cadastros(f,fp,fc,fct);
        break;

    default:

        exit(0);
        break;
    }
}

void logins(FILE *f, FILE *fp, FILE *fc, FILE *fct)
{
    int escolha_login;

    printf("\nEscolha a opção de Login \n");
    printf("1 - Logar como Cliente \n");
    printf("2 - Logar como Fornecedor \n");
    printf("3 - Voltar \n");
    fflush(stdin);
    escolha_login = getch();

    switch (escolha_login)
    {
    case '1':
        login_cliente(fc);
        break;
    case '2':
        login_fornecedor(f);
        break;
    default:
    system('cls');
        return;
    }
}

void cadastros(FILE *f, FILE *fp, FILE *fc, FILE *fct)
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
        cadastro_cliente(fc);
        break;
    case '2':
        cadastro_fornecedor(f);
        break;
    default:
        system("cls");
       return;
    }
}

void menu_logado(FILE *f, FILE *fp, FILE *fc, FILE *fct)
{
    int escolha;

        do {
            system("cls");
    printf("Você está logado no sistema!\n\nO que deseja fazer?\n");
    printf("1 - Cadastrar uma festa\n");
    printf("2 - Verificar/Atualizar Status do contrato de uma festa\n");
    printf("3 - Pesquisar clientes e funcionarios pelo ID\n");
    printf("4 - Mostrar Festas de um determinado Cliente\n");
    printf("5 - Mostrar todas as festas de uma data específica\n");
    printf("6 - Sair\n");
    escolha = getch();
    switch (escolha) {
        case '1':
            cadastra_festas(f, fp, fc, fct);
            break;
        case '2':
            status_contrato(fct, fc);
            break;
        case '3':
            pesquisa_cliente_funcionario(f, fc);
            break;
        case '4':
            mostrarfestasdeumcliente(fp, fc, fct);
            break;
        case '5':
            // funcionalidade 8 relatorio de festas a partir de uma data
            relatoriofestaspelodia(fp, fct);
            break;
        default:
            printf("Opção inválida! Escolha novamente!");
            system("cls");
            break;
    }
} while (escolha != '6');



        if (escolha == 6)
        {
            fclose(f);
            fclose(fc);
            fclose(fct);
            fclose(fp);
            exit(0);
        }
}

// Cadastro do Cliente
void cadastro_cliente(FILE *fc)
{
    cliente c;
    int posicao, casa_ou_ap;

    printf("\n--CADASTRO DE CLIENTE--");
    printf("\n\nCrie um código para a sua conta (recomendado mínimo 6 números): ");
    scanf("%d", &c.codigo_cliente);
    posicao = localiza_cliente(fc, c.codigo_cliente);
    if (posicao == true)
    {
        printf("\nCódigo já existe\n");
        system("pause");
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
        scanf("%d", &c.ender.num_resid);
        printf("\nBairro:\t");
        fflush(stdin);
        gets(c.ender.bairro);

        // Escrevendo no arquivo
        fseek(fc, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, fc);

        printf("Usuário cadastrado com sucesso!\n");
        system("pause");
    }
}

// Login cliente
void login_cliente(FILE *fc)
{
    int cod, useralive;
    if (verifica_usuariolog == 0)
    {
        printf("\n--LOGIN DE CLIENTE--\n");
        printf("Código do cliente:\n");
        scanf("%d", &cod);
        useralive = localiza_cliente(fc, cod);
        if (useralive == true)
        {
            printf("Cliente logado com sucesso!\n");
            verifica_usuariolog = 1;
            tipo_usuariolog = 1;
            idlogado = cod;
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
    int cod, useralive;

    if (verifica_usuariolog == 0)
    {
        printf("\n--LOGIN FORNECEDOR--\n");
        printf("Código do fornecedor:\n");
        scanf("%d", &cod);
        useralive = localiza_fornecedor(f, cod);
        if (useralive == true)
        {
            printf("Fornecedor logado com sucesso!\n");
            verifica_usuariolog = 1;
            tipo_usuariolog = 2;
            system("pause");
        }
        else
        {
            printf("Erro ao tentar fazer o Login.\nVerifique o código ou cadastre-se antes\n");
        }
    }
}






void cadastra_festas(FILE *f, FILE *fp, FILE *fc, FILE *fct)
{
    festa nova_festa;

  nova_festa.diasem.domingo =false ;nova_festa.diasem.segunda =false; nova_festa.diasem.terca = false; nova_festa.diasem.quarta =false;nova_festa.diasem.quinta = false; nova_festa.diasem.sexta =false; nova_festa.diasem.sabado =false;
    char horario[5];
    int existe, fornecedor_existente,op,codigofesta=0,codcliente=0;

    printf("\n--CADASTRO DE FESTA--\n");

    if (tipo_usuariolog == 1)
    {
        codcliente = idlogado;
    }
    else
    {
        printf("Digite o código do cliente: \t");
        scanf("%d", &codcliente);
    }

    // Verificar se o cliente existe
    existe = localiza_cliente(fc, codcliente);

    if (existe == false)
    {
        printf("\nCliente não encontrado. Cadastre o cliente antes de cadastrar a festa.\n");
        return;
    }

    printf("Digite o código da festa:\t");
    scanf("%d", &codigofesta);
      int validadorcod;
      validadorcod = localizafesta(fp,codigofesta);
      if (validadorcod == true)
      {
        printf("\n Código de festa já existe\n");
        return;
      }



    printf("\nDigite a quantidade de convidados: \t");
    scanf("%d", &nova_festa.quantidade_convidados);

    printf("\nDigite a data da festa (dd/mm/aaaa): \t");
    fflush(stdin);
    gets(nova_festa.data);
    do{
    printf("\nSelecione qual dia da semana cai esse dia (apenas número):  \n");
    printf("(1 - Domingo)\n");
    printf("(2 - Segunda-feira)\n");
    printf("(3 - Terça- feira)\n");
    printf("(4 - Quarta feira)\n");
    printf("(5 - Quinta- feira)\n");
    printf("(6 - Sexta- feira)\n");
    printf("(7 - Sábado)\n");
    scanf("%d",&op);
    switch(op){
        case 1:
        nova_festa.diasem.domingo = true;
        break;
        case 2:
            nova_festa.diasem.segunda = true;
            break;

        case 3:
            nova_festa.diasem.terca = true;
            break;
        case 4:
            nova_festa.diasem.quarta = true;
            break;
        case 5:
            nova_festa.diasem.quinta= true;
            break;

        case 6:
            nova_festa.diasem.sexta = true;
            break;

        case 7:
            nova_festa.diasem.sabado = true;
            break;

            default :
            printf("selecione uma opção válida!");
            break;
    }} while(op>7 || op<1);
    int hora, minuto;
    printf("\nDigite o horário da festa (hh:mm): \t");
    fflush(stdin);
    gets(horario);

    // Extrai as horas e minutos da string
    sscanf(horario, "%d:%d", &hora, &minuto);

    // Realiza as operações desejadas com os valores inteiros
     nova_festa.minutosInicio = hora * 60 + minuto;
    nova_festa.minutosTermino = nova_festa.minutosInicio + 240; // 4 horas em minutos

    printf("\nDigite o tema da festa:\t");
    fflush(stdin);
    gets(nova_festa.tema);

    // Ler o fornecedor
    int codigo_fornecedor;
    printf("\nDigite o código do fornecedor:\t");
    scanf("%d", &nova_festa.codigo_fornecedor);

    // Verificar se o fornecedor existe
    fornecedor_existente = localiza_fornecedor(f, nova_festa.codigo_fornecedor);

    if (fornecedor_existente == false)
    {
        printf("Fornecedor não encontrado. Cadastre o fornecedor antes de cadastrar a festa.\n");
       system("pause");
        return;
    }
 int validador_festa;

  validador_festa  = valida_festa(fp, nova_festa.data, nova_festa.minutosInicio, nova_festa.minutosTermino,nova_festa.diasem.sabado);
  if (validador_festa == false)
  {
    printf("\nJá existe uma festa neste horário!");
  }
  else
  {
    nova_festa.codigo_cliente = codcliente;
nova_festa.codigo_festa = codigofesta;
    fseek(f, 0, SEEK_END);
    fwrite(&nova_festa, sizeof(nova_festa), 1, fp);

    cadastra_contrato(fp,nova_festa.codigo_festa,fct);

    printf("Festa cadastrada com sucesso!\n");

  }
    system("pause");
}

int valida_festa(FILE *fp, char data[10], int minutosInicio, int minutosTermino, int sabado)
{
    festa nova_festa;

    fseek(fp, 0, SEEK_SET);

    while (fread(&nova_festa, sizeof(nova_festa), 1, fp) == 1)
    {
        if (sabado == true && (minutosInicio >= 720 && minutosTermino <= 1320))
        {
            return false;
        }
        else if ((nova_festa.minutosInicio <= minutosInicio && minutosInicio <= nova_festa.minutosTermino) || (nova_festa.minutosInicio <= minutosTermino && minutosTermino <= nova_festa.minutosTermino))
        {
            if (strcmp(nova_festa.data, data) == 0)
            {
                return false;
            }
        }
    }
return true;

}




    void pesquisa_cliente_funcionario(FILE * f, FILE *fc)
    {

        int achou = 0,op,codigo,codigo2;
        do{

        printf("\n\n\nSe quer pesquisar pelo cliente, digite 1 \n Para funcionário, digite 2 \n Para voltar ao menu, digite 3\n");
        scanf("%d",&op);

     if(op==1){
    printf("\n Digite o codigo do cliente que deseja consultar:");
    scanf("%d",&codigo);
    cliente c;
    fseek(fc, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, fc) == 1)
    {
        if (codigo == c.codigo_cliente)
        {
            printf("\nNome do cliente: %s\n",c.nome);
            printf("Telefone: %d\n",c.telefone);
            printf("Endereco: rua %s, num %d\n Bairro %s\n",c.ender.rua,c.ender.num_resid,c.ender.bairro);
            printf("Data de nascimento:%s",c.data_nascimento);

            achou++;
            break;
        }

    }

     if(achou==0)
     {
        printf("Cliente nao encontrado");
     }
    }
    if(op==2){
       printf("\n digite o codigo do fornecedor que deseja consultar:");
    scanf("%d",&codigo2);
    fornecedor f1;
    fseek(f, 0, SEEK_SET);
    while (fread(&f1, sizeof(f1), 1, f) == 1)
    {
        if (codigo2 == f1.cod_fornecedor)
        {
            printf("Buffet: %s\n",f1.buffet);
            printf("Telefone: %d\n",f1.telefone);
            achou++;
            break;
        }
    }
    if(achou==0)
    {
        printf("Funcionario nao encontrado");
    }
    }
    }
    while(op==1 || op==2);
    }

    void mostrarfestasdeumcliente(FILE *fp,FILE *fc,FILE *fct)
    {
        int cod,cexiste,horasinicio,minutosinicio,horasfinal,minutosfinal,achou=0;
        printf("\nDigite o código do cliente: ");
        scanf("%d",&cod);
        cexiste = localiza_cliente(fc, cod);
        if (cexiste == false){
            printf("\nCliente não encontrado!");
            return;}
            contrato contrat;
            festa nova_festa;
            fseek(fp, 0, SEEK_SET);
            while (fread(&nova_festa, sizeof(nova_festa), 1, fp) == 1)
            {
                if (cod == nova_festa.codigo_cliente)
                {
                    printf("\nFesta encontrada!\n");
                    printf("Codigo da festa: %d\n", nova_festa.codigo_festa);
                    printf("Data da festa: %s\n", nova_festa.data);
                    horasinicio = nova_festa.minutosInicio /60;
                    minutosinicio= nova_festa.minutosInicio%60;
                    horasfinal = nova_festa.minutosTermino/60;
                    minutosfinal = nova_festa.minutosTermino%60;
                    printf("Horario de inicio: %d:%d\n",horasinicio,minutosinicio);
                    printf("Horário de término: %d:%d\n",horasfinal,minutosfinal);

                    if (nova_festa.diasem.domingo == true)
                    {
                        printf("Dia da semana: Domingo\n");

                    }
                    if (nova_festa.diasem.segunda == true)
                    {
                        printf("Dia da semana: Segunda-feira\n");

                    }
                    if (nova_festa.diasem.terca == true)
                    {
                        printf("Dia da semana: Terça-feira\n");
                    }
                    if (nova_festa.diasem.quarta == true)
                    {
                        printf("Dia da semana: Quarta-feira\n");
                    }
                    if (nova_festa.diasem.quinta == true)
                    {
                        printf("Dia da semana: Quinta-feira\n");
                    }
                    if (nova_festa.diasem.sexta == true)
                    {
                        printf("Dia da semana: Sexta-feira\n");
                    }
                    if (nova_festa.diasem.sabado == true)
                    {
                        printf("Dia da semana: Sábado\n");
                    }

                    printf("Código do fornecedor: %d\n", nova_festa.codigo_fornecedor);
                    printf("\nINFORMAÇÕES DO CONTRATO: \n");

                    fseek(fct, 0, SEEK_SET);
                         while (fread(&contrat, sizeof(contrat), 1, fct) == 1)
                         {
                            if (contrat.codigo_festa == nova_festa.codigo_festa)
                            {
                                printf("Número do contrato: %d\n",contrat.numero_contrato);
                                printf("Valor total: %2.f\n",contrat.valor_total);
                                printf("Valor FINAL: %2.f\n",contrat.valor_final);
                                printf("Método de pagamento escolhido: %s\n",contrat.pagamento);
                                printf("Desconto aplicado: %d%%\n",contrat.desconto);
                                if (contrat.stat.cancelado == true) printf("Status do contrato: Cancelado\n");
                                else if(contrat.stat.pagar == true) printf("Status do Contrato: A pagar\n");
                                else if(contrat.stat.pago == true) printf("Status do contrato: Pago!\n");
                            }

                         }
                         achou++;
                }
                if(achou==0)
                {
                    printf("\nEste cliente nao cadastrou nenhuma festa!\n");
                }
            }
    system("pause");


    }

   void cadastra_contrato(FILE *fp, int codigo, FILE *fct){

         festa nova_festa;
         contrato contrat;
         int op,criou=0;

            contrat.codigo_festa = codigo;
            contrat.numero_contrato = codigo;
            contrat.stat.cancelado = false;contrat.stat.pagar = false;contrat.stat.pago = false;
            fseek(fp, 0, SEEK_SET);

            while (fread(&nova_festa, sizeof(nova_festa), 1, fp) == 1)
            {
                if (codigo == nova_festa.codigo_festa)
                {
                    //trabalhar aqui

                    contrat.valor_total =0;
                    if (nova_festa.quantidade_convidados <=30  && (nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        /* 1899,00 */
                        contrat.valor_total += 1899;
                    }
                    if (nova_festa.quantidade_convidados <=30  && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        /* 2099,00 */
                        contrat.valor_total += 2099;
                    }
                    if ((nova_festa.quantidade_convidados>30 && nova_festa.quantidade_convidados <=50)  && (nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        /* 2199,00 */
                        contrat.valor_total += 2199;
                    }
                    if ((nova_festa.quantidade_convidados>30 && nova_festa.quantidade_convidados <=50) && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        /* 2299,00 */
                        contrat.valor_total += 2299;
                    }

                    if((nova_festa.quantidade_convidados>50 && nova_festa.quantidade_convidados <=80)&&(nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                     // 3199,00
                     contrat.valor_total += 3199;
                    }
                    if((nova_festa.quantidade_convidados>50 && nova_festa.quantidade_convidados <=80)&&(nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        //3499,00
                        contrat.valor_total += 3499;
                    }

                    if((nova_festa.quantidade_convidados>80 && nova_festa.quantidade_convidados <=100)&&(nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        //3799,00
                        contrat.valor_total += 3799;
                    }

                     if((nova_festa.quantidade_convidados>80 && nova_festa.quantidade_convidados <=100) && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                     {
                           //3999,00
                           contrat.valor_total += 3999;
                     }

                  contrat.stat.pagar = true;
                  printf("\nComo será a forma de pagamento?(Digite o numero correspondente a sua decisão)\n 1-A vista\n 2-Parcelado em 2 vezes\n 3-Parcelado em 3 vezes \n 4-Parcelado em 4 vezes ou mais\n");
                 do{
                  scanf("%d",&op);
                  switch(op){
                    case 1:
                    //contrat.pagamento = "A vista";
                    strcpy(contrat.pagamento,"A vista");
                    break;
                    case 2:
                    //contrat.pagamento ="2 vezes";
                    strcpy(contrat.pagamento,"2 vezes");
                    break;
                    case 3:
                    //contrat.pagamento = "3 vezes";
                    strcpy(contrat.pagamento,"3 vezes");
                    break;
                    case 4:
                    //contrat.pagamento = "4 vezes ou mais";
                    strcpy(contrat.pagamento,"4 vezes ou mais");
                    break;
                    default:
                    printf("\nOpção não disponivel! Digite uma das disponibilizdas acima.\n");
                    break;
                  }
                 }
                 while(op>4 || op<1);

                  if (strcmp(contrat.pagamento,"A vista")==0)
                  {
                  contrat.desconto = 10;
                    contrat.valor_final = contrat.valor_total*0.90;
                  }
                  if (strcmp(contrat.pagamento,"2 vezes")==0)
                  {
                    contrat.desconto = 5;
                    contrat.valor_final = contrat.valor_total*0.95;
                  }
                  if (strcmp(contrat.pagamento,"3 vezes")==0 )
                  {
                   contrat.desconto = 2;
                    contrat.valor_final = contrat.valor_total*0.98;
                  }
                  if (strcmp(contrat.pagamento,"4 vezes ou mais")==0)
                  {
                    contrat.desconto = 0;
                    contrat.valor_final = contrat.valor_total;
                  }


                }
            }
                if (fct != NULL)
                {
               fseek(fct, 0, SEEK_END);
               fwrite(&contrat, sizeof(contrat), 1, fct);
                }



    }

    void status_contrato(FILE *fct, FILE *fc)
    {
        int cod,localizador,op,posicao1=-1,posicao2;
        contrato contrat;
        printf("\nDigite o código da festa: \n");
        fflush(stdin);
        scanf("%d",&cod);
        localizador = localizacontrato(fct,cod);
        if(localizador == false){
            printf("Festa/contrato nao encontrados!\n");
            printf("Voltando ao menu inicial\n");
            system("pause");
        }
        else{
            fseek(fct, 0, SEEK_SET);

            while (fread(&contrat, sizeof(contrat), 1, fct) == 1)
            {
                posicao1++;
                if(cod==contrat.numero_contrato){
                    posicao2 = posicao1;
                    printf("Valor a pagar: %2.f\n",contrat.valor_final);
                    printf("Desconto já aplicado: %d %%\n",contrat.desconto);
                      printf("Forma de pagamento selecionada: %s\n",contrat.pagamento);
                       if (contrat.stat.cancelado == true) printf("Status do contrato: Cancelado\n");
                        else if(contrat.stat.pagar == true) printf("Status do Contrato: A pagar\n");
                        else if(contrat.stat.pago == true) printf("Status do contrato: Pago!\n");

                    if (contrat.stat.pagar == true)
                    {
                    printf("Escolha o que deseja fazer: \n");
                    printf("\t1 - Pagar\n");
                    printf("\t2 - Cancelar\n");
                    printf("\t3 - Voltar ao menu principal\n");


                    scanf("%d",&op);
                    do{
                        switch(op)
                    {
                        case 1:
                        printf("Processando...\n");
                        system("pause");

                        contrat.stat.pagar = false;
                        contrat.stat.pago = true;
                        printf("\nStatus: Pago\n");
                        system("pause");
                        break;

                        case 2:
                        printf("Processando...\n");
                        system("pause");

                        contrat.stat.cancelado = true;
                        contrat.stat.pagar = false;
                        printf("Status: Cancelado\n");
                        system("pause");
                        break;

                        case 3:
                        system("cls");
                        return;
                        default :
                        printf("Opção inválida!\n");
                        system("pause");
                    }
                    }while(op>3 || op<1);
                      fseek(fct,sizeof(contrat)*(posicao2),SEEK_SET);
                fwrite(&contrat, sizeof(contrat), 1, fct);
                return;
                    }
                  else if(contrat.stat.cancelado == true)
                  {
                    printf("\nEste evento está cancelado!\n");
                    system("pause");
                    return;
                  }
                  else if(contrat.stat.pago == true)
                  {
                    printf("\nO pagamento já foi realizado para este evento.\n");
                    system("pause");
                    return;
                  }


                }

            }
        }
    }

    void relatoriofestaspelodia(FILE *fp,FILE *fct)
    {
        char data[10];
        int numfesta =1;
        int horasinicio,minutosinicio,horastermino,minutostermino;
        printf("\n\nDigite a data que deseja buscar as festas (dd/m m/aaaa): ");
        scanf("%s",&data);
        rewind(fp);
        festa nova_festa;
         fseek(fp, 0, SEEK_SET);
         while (fread(&nova_festa, sizeof(nova_festa), 1, fp) == 1)
         {
            if((strcmp(data,nova_festa.data)==0))
            {
                printf("\n\n---FESTA %d---\n",numfesta);
                printf("Código da festa: %d\n",nova_festa.codigo_festa);
                printf("Código do Cliente: %d\n",nova_festa.codigo_cliente);
                printf("Quantidade de convidados: %d\n",nova_festa.quantidade_convidados);
                horasinicio = nova_festa.minutosInicio/60;
                minutosinicio= nova_festa.minutosInicio%60;
                horastermino = nova_festa.minutosTermino/60;
                minutostermino = nova_festa.minutosTermino%60;
                printf("Horário de início: %d:%d\n",horasinicio,minutosinicio);
                printf(" Horário final: %d:%d\n",horastermino,minutostermino);
                if (nova_festa.diasem.domingo == true)
                    {
                        printf("Dia da semana: Domingo\n");

                    }
                    if (nova_festa.diasem.segunda == true)
                    {
                        printf("Dia da semana: Segunda-feira\n");

                    }
                    if (nova_festa.diasem.terca == true)
                    {
                        printf("Dia da semana: Terça-feira\n");
                    }
                    if (nova_festa.diasem.quarta == true)
                    {
                        printf("Dia da semana: Quarta-feira\n");
                    }
                    if (nova_festa.diasem.quinta == true)
                    {
                        printf("Dia da semana: Quinta-feira\n");
                    }
                    if (nova_festa.diasem.sexta == true)
                    {
                        printf("Dia da semana: Sexta-feira\n");
                    }
                    if (nova_festa.diasem.sabado == true)
                    {
                        printf("Dia da semana: Sábado\n");
                    }
                    mostracontratodafesta(fct,nova_festa.codigo_festa);


                numfesta++;
            }
    }
    system("pause");
    }


void mostracontratodafesta(FILE *fct,int codigo)
{
    contrato contrat;
    fseek(fct, 0, SEEK_SET);
    while (fread(&contrat, sizeof(contrat), 1, fct) == 1)
    {
        if (codigo == contrat.numero_contrato)
        {
            printf("Numero do contrato....:%d \n",contrat.numero_contrato);
            printf("Codigo da festa....... %d\n",contrat.codigo_festa);
            printf("Valor total............%2.f \n",contrat.valor_total);
            printf("Desconto...............%d %%\n",contrat.desconto);
            printf("Valor final...........:%.2f\n",contrat.valor_final);
        }
        fread(&contrat, sizeof(contrat), 1, fct);
    }
}


// Main
int main()
{
    setlocale(LC_ALL, "portuguese");
    FILE *f;
    f = fopen("fornecedores.dat", "r+b");
    if (f == NULL)
    {
        perror("Erro ao abrir arquivo!");
        exit(-1);
    }
    FILE *fc;
    fc = fopen("clientes.dat", "r+b");
    if (fc == NULL)
    {
        perror("Erro ao abrir arquivo!");
        exit(-1);
    }
    FILE *fp;
    fp = fopen("party.dat", "r+b");
    if (fp == NULL)
    {
        perror("Erro ao abrir arquivo!");
        exit(-1);
    }
    FILE *fct;
    fct = fopen("contrato.dat", "r+b");
    if (fct == NULL)
    {
        perror("Erro ao abrir arquivo!");
        exit(-1);
    }

    while (verifica_usuariolog == 0)
    {
        menu(f,fp,fc,fct);
        system("cls");
    }
    if (verifica_usuariolog == 1)
    {
        menu_logado(f,fp,fc,fct);
    }


    fclose(f);
    fclose(fp);
    fclose(fc);
    fclose(fct);
    return 0;
}
