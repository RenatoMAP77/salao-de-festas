/********************************************************
* FILENAME : main.c
* DESCRIPTION : A system for a party room enterprise. The
* user can submit partys and write them on a external file.
*
* PUBLIC FUNCTIONS :
* int FM_CompressFile( FileHandle )
* int FM_DecompressFile( FileHandle )
* NOTES :
* These functions are a part of the FM suite;
* See IMS FM0121 for detailed description.
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
void cadastro_cliente(FILE *fc);
void login_cliente(FILE *fc);
void menu(FILE *f, FILE *fp,FILE *fc, FILE *fct);
void cadastro_fornecedor(FILE *f);
void login_fornecedor(FILE *f);
void cadastros(FILE *f, FILE *fp,FILE *fc, FILE *fct);
void logins(FILE *f, FILE *fp,FILE *fc, FILE *fct);
int localiza_fornecedor(FILE *f, int codigo);
int localiza_cliente(FILE *fc, int codigo;);
void menu_logado(FILE *f, FILE *fp, FILE *fc, FILE *fct);
void cadastra_festas(FILE *f, FILE *fp, FILE *fc);
void pesquisa_cliente_funcionario(FILE * f, FILE *fc);
int valida_festa(FILE *fp, char data[10], int minutosInicio,int minutosTermino, int sabado);
void cadastra_contrato(FILE *fp, int codigo, FILE *fct);
void mostrarfestasdeumcliente(FILE *fp,FILE *fc,FILE *fct);
int localizafesta(FILE *fp, int codigo);
void status_conta(FILE *fct, FILE *fc);
int localizacontrato(FILE *fct, int codigo);

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

struct tcontrato
{
    int codigo_festa;
    int numero_contrato;
    float valor_total;
    float valor_final;
    char desconto[4];
    char status[10];
    char pagamento[10];
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
    fread(&c, sizeof(c), 1, fc);
    while (!feof(fc))
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
        return false; // nao achou fornecedor
    }
}
//Função para verificar se a festa já existe
int localizafesta(FILE *fp, int codigo)
{
     int achou = 0;
    festa nova_festa;
    fseek(fp, 0, SEEK_SET);
    fread(&nova_festa, sizeof(nova_festa), 1, fp);
    while (!feof(fp))
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
    fread(&contrat, sizeof(contrat), 1, fct);
    while (!feof(fct))
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
        logins(f,fp,fc);
        break;

    // Cadastro
    case '2':
        cadastros(f,fp,fc);
        break;

    default:

        exit(0);
    }
}

void logins(FILE *f, FILE *fp, FILE *fc, FILE *fct)
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
        login_cliente(fc);
        break;
    case '2':
        login_fornecedor(f);
        break;
    default:
    system('cls');
        menu(f,fp,fp);
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
        menu(f,fp,fc);
    }
}

void menu_logado(FILE *f, FILE *fp, FILE *fc, FILE *fct)
{
    int escolha;
    if (tipo_usuariolog == 1) // cliente
    {
        /* menu do cliente*/
        printf("Você está logado no sistema!\n\nO que deseja fazer?\n");
        printf("1 - Cadastrar uma festa\n"); 
        printf("2 - Calcular valor\n");
        printf("3 - Status da conta\n");
        printf("4 - Informações da conta\n");
        printf("5- Pesquisar clientes e funcionarios pelo ID ou nome\n");
        printf("6 - Mostrar Festas de um determinado Cliente\n");
        printf("7 - Sair");
        escolha = getch();
        switch (escolha)
        {

        case '1':
            cadastra_festas(f,fp,fc,fct);
            break;
        case '2':
           // calcula_valor(f,fp,fc);
            break;
        case '3':
           status_conta(fct,fc);
            break;
        case '4':
           // informacoes_conta(f,fp,fc);
            break;
        case '5':
            pesquisa_cliente_funcionario(f,fc);
            break;
            case '6':
             mostrarfestasdeumcliente(fp,fc,fct);
            break;

        default:
            printf("Opção inválida! Escolha novamente!");
            system('cls');
            menu_logado(f,fp,fc);
            break;
        }
        if (escolha == 7)
        {
            fclose(f);
            exit(0);
        }

    }
    else if (tipo_usuariolog = 2) // fornecedor
    {
        /*menu do forneceodor */
        printf("Você está logado no sistema!\n\nO que deseja fazer?");
    }
}

// Main
int main()
{
    setlocale(LC_ALL, "Portuguese");

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
    fct = = fopen("contrato.dat", "r+b");
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
    int existe, fornecedor_existente,op;

    printf("\n--CADASTRO DE FESTA--\n");

    if (tipo_usuariolog == 1)
    {
        nova_festa.codigo_cliente = idlogado;
    }
    else
    {
        printf("Digite o código do cliente: ");
        scanf("%d", &nova_festa.codigo_cliente);
    }

    // Verificar se o cliente existe
    existe = localiza_cliente(fc, nova_festa.codigo_cliente);

    if (existe == false)
    {
        printf("Cliente não encontrado. Cadastre o cliente antes de cadastrar a festa.\n");
        return;
    }

    printf("Digite o código da festa");
    scanf("%s", nova_festa.codigo_festa);
      int validadorcod;
      validadorcod = validacodigofesta(fp,nova_festa.codigo_festa);
      if (validadorcod == false)
      {
        printf("\n Código de festa já existe\n");
        return;
      }



    printf("Digite a quantidade de convidados: ");
    scanf("%d", &nova_festa.quantidade_convidados);

    printf("Digite a data da festa (dd/mm/aaaa): ");
    fflush(stdin);
    gets(nova_festa.data);

    printf("Selecione qual dia da semana cai esse dia (apenas número):  \n");
    printf("(1 - Domingo)\n");
    printf("(2 - Segunda-feira)\n");
    printf("(3 - Terça- feira)\n");
    printf("(4 - Quarta feira)\n");
    printf("(5 - Quinta- feira)\n");
    printf("(6 - Sexta- feira)\n");
    printf("(7 - Sábado)\n");
    scanf("%d",&op);
    switch(op){
        case '1':
        nova_festa.diasem.domingo =true;
        break;
        case'2':
            nova_festa.diasem.segunda =true;
            break;

        case'3':
            nova_festa.diasem.terca =true;
            break;
        case'4':
            nova_festa.diasem.quarta = true;
            break;
        case'5':
            nova_festa.diasem.quinta=true;
            break;

        case'6':
            nova_festa.diasem.sexta = true;
            break;

        case'7':
            nova_festa.diasem.sabado = true;
            break;

    }
    int hora, minuto;
    printf("Digite o horário da festa (hh:mm): ");
    fflush(stdin);
    gets(horario);

    // Extrai as horas e minutos da string
    sscanf(horario, "%d:%d", &hora, &minuto);

    // Realiza as operações desejadas com os valores inteiros
     nova_festa.minutosInicio = hora * 60 + minuto;
    nova_festa.minutosTermino = nova_festa.minutosInicio + 240; // 4 horas em minutos

    printf("Digite o tema da festa: ");
    fflush(stdin);
    gets(nova_festa.tema);

    // Ler o fornecedor
    int codigo_fornecedor;
    printf("Digite o código do fornecedor: ");
    scanf("%d", &nova_festa.codigo_fornecedor);

    // Verificar se o fornecedor existe
    fornecedor_existente = localiza_fornecedor(f, nova_festa.codigo_fornecedor);

    if (fornecedor_existente == false)
    {
        printf("Fornecedor não encontrado. Cadastre o fornecedor antes de cadastrar a festa.\n");
        return;
    }
 int validador_festa;

  validador_festa  = valida_festa(fp, nova_festa.data, nova_festa.minutosInicio, nova_festa.minutosTermino,nova_festa.diasem.sabado);
  if (validador_festa == true)
  {
    printf("Já existe uma festa neste horário!");
  }
  else
  {
     // Realizar o cadastro da festa
        fseek(f, 0, SEEK_END);
    fwrite(&nova_festa, sizeof(nova_festa), 1, fp);

    cadastra_contrato(fp,nova_festa.codigo_festa,fct);

    printf("Festa cadastrada com sucesso!\n");

  }

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

        printf("\n\n\nSe quer pesquisar pelo cliente, digite 1 \n Para funcionário, digite 2 \n Para voltar ao menu, digite 3");
        scanf("%d",&op);

     if(op==1){
    printf("\n Digite o codigo do cliente que deseja consultar:");
    scanf("%d",&codigo);
    cliente c;
    fseek(fc, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, fc);
    while (!feof(fc))
    {
        if (codigo == c.codigo_cliente)
        {
            printf("\nNome do cliente: %s\n",c.nome);
            printf("Telefone: %d\n",c.telefone);
            printf("Endereco: rua %s, num %d\n Bairro %s\n",c.ender.rua,c.ender.num_resid,c.ender.bairro);
            printf("Data de nascimento:%s",c.data_nascimento);


            break;
        }
        else{
            printf("Nao existe nenhum cliente cadastrado com esse codigo!");
        }
    }

    }
    if(op==2){
       printf("\n digite o codigo do fornecedor que deseja consultar:");
    scanf("%d",&codigo2);
    fornecedor f1;
    fseek(f, 0, SEEK_SET);
    fread(&f1, sizeof(f1), 1, f);
    while (!feof(f))
    {
        if (codigo2 == f1.cod_fornecedor)
        {
            printf("Buffet: %s\n",f1.buffet);
            printf("Telefone: %d\n",f1.telefone);



            break;
        }
        else{
            printf("Nao existe nenhum fornecedor cadastrado com este codigo!\n");
        }
    }
    }

    }
    while(op==1 || op==2);

    }


    void mostrarfestasdeumcliente(FILE *fp,FILE *fc,FILE *fct)
    {
        int cod,cexiste,horasinicio,minutosinicio,horasfinal,minutosfinal;
        printf("Digite o código do cliente");
        scanf("%d",&cod);
        cexiste = localiza_cliente(fc, cod);
        if (cexiste == false){
            printf("\nCliente não encontrado!");
            return;}
            contrato contrat;
            festa nova_festa;
            fseek(fp, 0, SEEK_SET);
            fread(&nova_festa, sizeof(nova_festa), 1, fp);
            while (!feof(fp))
            {
                if (cod == nova_festa.codigo_cliente)
                {
                    printf("Festa encontrada!\n");
                    printf("Codigo da festa: %s\n", nova_festa.nome);
                    printf("Data da festa: %s\n", nova_festa.data);
                    horasinicio = nova_festa.minutosInicio /60;
                    minutosinicio= nova_festa.minutosInicio%60;
                    horasfinal = nova_festa.minutosTermino/60;
                    minutosfinal = nova_festa.minutosTermino%60;
                    printf("Horario de inicio: %d:%d",horasinicio,minutosinicio);
                    printf("Horário de término: %d:%d",horasfinal,minutosfinal);

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
                    printf("INFORMAÇÕES DO CONTRATO: \n");
                    
                    fseek(fct, 0, SEEK_SET);
                         fread(&contrat, sizeof(contrat), 1, fct);
                         while (!feof(fct))
                         {
                            if (contrat.codigo_festa == nova_festa.codigo_festa)
                            {
                                printf("Número do contrato: %d\n",contrat.numero_contrato);
                                printf("Valor total: %2.f\n",contrat.valor_total);
                                printf("Valor FINAL: %2.f",contrat.valor_final);
                                printf("Método de pagamento escolhido: %s",contrat.pagamento);
                                printf("Desconto aplicado: %s",contrat.desconto);
                                printf("Status da festa: %s",contrat.status);
                            }

                         }
                }
            }



    }

    cadastra_contrato(FILE *fp, int codigo, FILE *fct){

         festa nova_festa;
         contrato contrat;
         int op;
            fseek(fp, 0, SEEK_SET);
            fread(&nova_festa, sizeof(nova_festa), 1, fp);
            while (!feof(fp))
            {
                if (codigo == nova_festa.codigo_festa)
                {
                    //trabalhar aqui
                    contrat.codigo_festa = nova_festa.codigo_festa;
                    contrat.numero_contrato = nova_festa.codigo_festa;

                    if (nova_festa.quantidade_convidados <=30  && (nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        /* 1899,00 */
                        contrat.valor_total = 1899.00;
                    }
                    if (nova_festa.quantidade_convidados <=30  && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        /* 2099,00 */
                        contrat.valor_total = 2099.00;
                    }
                    if ((nova_festa.quantidade_convidados>30 && nova_festa.quantidade_convidados <=50)  && (nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        /* 2199,00 */
                        contrat.valor_total = 2199.00;
                    }
                    if ((nova_festa.quantidade_convidados>30 && nova_festa.quantidade_convidados <=50) && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        /* 2299,00 */
                        contrat.valor_total = 2299.00;
                    }

                    if((nova_festa.quantidade_convidados>50 && nova_festa.quantidade_convidados <=80)&&(nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                     // 3199,00
                     contrat.valor_total = 3199.00;
                    }
                    if((nova_festa.quantidade_convidados>50 && nova_festa.quantidade_convidados <=80)&&(nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                    {
                        //3499,00
                        contrat.valor_total = 3499.00;
                    }

                    if((nova_festa.quantidade_convidados>80 && nova_festa.quantidade_convidados <=100)&&(nova_festa.diasem.segunda == true || nova_festa.diasem.terca == true ||nova_festa.diasem.quarta == true || nova_festa.diasem.quinta == true))
                    {
                        //3799,00
                        contrat.valor_total = 3799.00;
                    }

                     if((nova_festa.quantidade_convidados>80 && nova_festa.quantidade_convidados <=100) && (nova_festa.diasem.sexta == true || nova_festa.diasem.sabado == true ||nova_festa.diasem.domingo == true))
                     {
                           //3999,00
                           contrat.valor_total = 3999.00;
                     }
                  contrat.status = "A pagar";
                  printf("Como será a forma de pagamento?(Digite o numero correspondente a sua decisao)\n 1-A vista\n 2-Parcelado em 2 vezes\n3-Parcelado em 3 vezes \n 4-Parcelado em 4 vezes ou mais\n");
                 do{
                  scanf("%d",&op);
                  switch(op){
                    case '1':
                    contrat.pagamento = "A vista";
                    break;
                    case '2':
                    contrat.pagamento ="2 vezes";
                    break;
                    case '3':
                    contrat.pagamento = "3 vezes";
                    break;
                    case '4':
                    contrat.pagamento = "4 vezes ou mais";
                    break;
                    default:
                    printf("\nOpçao nao disponivel! Digite uma das disponibilizdas acima.\n");
                    break;
                  }
                 }
                 while(op>4 || op<1);

                  if (contrat.pagamento == "A vista")
                  {
                    contrat.desconto =="10%%";
                    contrat.valor_final = contrat.valor_total*0.90;
                  }
                  if (contrat.pagamento == "2 vezes" )
                  {
                    contrat.desconto =="5%%";
                    contrat.valor_final = contrat.valor_total*0.95;
                  }
                  if (contrat.pagamento == "3 vezes" )
                  {
                    contrat.desconto =="2%%";
                    contrat.valor_final = contrat.valor_total*0.98;
                  }
                  if (contrat.pagamento == "4 vezes ou mais" )
                  {
                    contrat.desconto =="0%%";
                    contrat.valor_final = contrat.valor_total;
                  }

                   fseek(fct, 0, SEEK_END);
                 fwrite(&contrat, sizeof(contrat), 1, fct);
                }
            }

    }

    void status_conta(FILE fct, FILE *fc)
    {
        int cod,localizador,op;
        contrato contrat;
        printf("Digite o código da festa: \n");
        scanf("%d",&cod);
        localizador = localizacontrato(fct,cod);
        if(localizador = false){
            printf("Festa/contrato nao encontrados!");
        }
        else{
            fseek(fct, 0, SEEK_SET);
            fread(&contrat, sizeof(contrat), 1, fct);
            while (!feof(fct))
            {
                if(cod==contrat.numero_contrato){
                    printf("Valor a pagar: %2.f\n",contrat.valor_final);
                    printf("Desconto já aplicado: %s\n",contrat.desconto);
                      printf("Forma de pagamento selecionada: %s\n",contrat.pagamento);
                       printf("Status do pagamento: %s \n\n\n",contrat.status);

                    if (strcmp (contrat.status,"A pagar")==0)
                    {
                    printf("Escolha o que deseja fazer: \n");
                    printf("\t1 - Pagar\n");
                    printf("\t2 - Cancelar\n");
                    printf("\t3 - Voltar ao menu principal\n");


                    scanf("%d",&op);
                    do{
                        switch(op)
                    {
                        case '1':
                        printf("Processando...\n");
                        system("pause");
                        contrat.status = "Pago";
                        printf("Status: Pago");
                        break;

                        case'2':
                        printf("Processando...");
                        system("pause");
                        contrat.status="Cancelado";
                        printf("Status: Cancelado");
                        break;

                        case '3':
                        system("cls"); 
                        exit(0);
                        default :
                        printf("Opção inválida!\n");
                    }
                    }while(op>3 || op<1);
                    
                    }
                  else if(strcmp(contrat.status,"Cancelado"))
                  {
                    printf("\nEste evento está cancelado!\n");
                  }
                  else if(contrat.status=="Pago")
                  {
                    printf("\nO pagamento já foi realizado para este evento.\n");
                  }
                }
            }
        }
    }



/*

    void status_conta(FILE * f)
    {
        // printf("Status da conta: \n");
        // system("pause");
    }

    void informacoes_conta(FILE * f)
    {
    }


    */


