#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//PARTE DO CLIENTE
struct Cliente{
	char nome[100];
	char telefone[100];
	char email[100];
};
typedef struct Cliente Cliente;

void inserir_cliente(Cliente *vetor){

	printf("Digite o nome do cliente: ");
	scanf("%250[^\n]s", vetor->nome);
	setbuf(stdin, NULL);
	printf("Digite o telefone do cliente: ");
	scanf("%250[^\n]s", vetor->telefone);
	setbuf(stdin, NULL);
	printf("Digite o email do cliente: ");
	scanf("%250[^\n]s", vetor->email);
	setbuf(stdin, NULL);
}


//PARTE DA CONTA
struct Conta{
	int numero;
	float saldo;
	Cliente cliente;
};
typedef struct Conta Conta;


int pesquisar(Conta *vetor, int tamanho_vetor, int pes){

	int i;	
	for (i = 0; i < tamanho_vetor; i++)
	{
		if (pes == vetor[i].numero){
			return i;
		}
	}
	return -1;
}

// FUNÇÃO PARA DIGITAR O NUMERO DA CONTA
int numero_da_conta(int *x){
	printf("\n\nDigite o número da conta: ");
	scanf("%d", &(*x));
	return *x;
}
void inserir_conta(Conta *vetor, int *tamanho){

	int p, n;

	numero_da_conta(&n);
	p = pesquisar(vetor, *tamanho, n);

	while (p >= 0)
	{
		printf("JA EXISTE UMA CONTA COM ESSE NUMERO!!!!");
		printf("\n\nDigite o número da conta: ");
		scanf("%d", &n);
		p = pesquisar(vetor, *tamanho, n);
	}
	vetor[*tamanho].numero = n;
	setbuf(stdin, NULL);
	
	//printf("Digite o saldo da conta: ");
	//scanf("%f", &vetor[*tamanho].saldo);
	//setbuf(stdin, NULL);
	inserir_cliente(&vetor[*tamanho].cliente);
	setbuf(stdin, NULL);

	(*tamanho)++;
}

// FUNÇÕES PRINCIPAIS


int menu() {
	int op;
	system("@cls||clear");  // LIMPA A TELA
	printf("\n\nSISTEMA BANCÁRIO\n\n");
	printf("1 - Inserir cliente\n");
	printf("2 - Pesquisar por número da conta\n");
	printf("3 - Pesquisar por nome do cliente\n");
	printf("4 - Atualizar saldo\n");
	printf("5 - Cliente com Maior \n");
	printf("6 - Excluir conta\n");
	printf("7 - Listar todas as contas\n");
	printf("0 - Sair do sistema\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
		setbuf(stdin, NULL);
	} while(op < 0 || op > 7);
	return op;
}

// FUNÇÃO LISTAR
void listar(Conta *vetor, int i){
	
	printf("\nNÚMERO DA CONTA: %d\n", vetor[i].numero);
	printf("SALDO DA CONTA: R$%.2f\n", vetor[i].saldo);
	printf("NOME DO CLIENTE: %s\n", vetor[i].cliente.nome);
	printf("NÚMERO DO CLIENTE: %s\n", vetor[i].cliente.telefone);
	printf("EMAIL DO CLIENTE: %s\n", vetor[i].cliente.email);
	printf("\n");
	
}

//FUNÇÃO PARA TRANFORMAR TODOS OS CARACTERES EM MINUSCULOS

void caractere_minusculo(char *vetor){

	int i, tamanho;
	tamanho = strlen(vetor);

	for ( i = 0; i < tamanho; i++)
	{
		vetor[i] = tolower(vetor[i]);
	}
}

// FUNÇÃO PESQUISAR POR NOME
int pesquisar_nome(Conta *vetor, int tamanho){

	char pes[100];
	char str1[100];	// STRING PARA RECEBER O NOME A PESQUISAR
	char str2[100]; //STRING PARA RECEBER O NOME DO CLIENTE

	printf("\nDigite o nome a pesquisar: ");
	scanf("%30[^\n]s", pes);

	strcpy(str1, pes);
	caractere_minusculo(str1); // TRANSFORMANDO TODA A STRING EM MINUSCULA PARA PESQUISAR

	int i;	
	for (i = 0; i < tamanho; i++)
	{
		strcpy(str2, ""); // REINICIANDO A STR2 PARA QUE AO FAZER O LOOP ELA INICIE SEM ERRO
		strcpy(str2, vetor[i].cliente.nome);
		caractere_minusculo(str2); // TRANSFORMANDO TODA A STRING EM MINUSCULA PARA PESQUISAR
		if ((strcmp(str1, str2) == 0)){
			return i;
		}
	}
	return -1;

}

void pesquisar_por_matricula(Conta *vetor, int tamanho){

	int p, pes;

	numero_da_conta(&pes);
	p = pesquisar(vetor, tamanho, pes);
	if (p >= 0){
		printf("\nConta encontrada!!!\n\n");
		listar(vetor,p);
	}
	else{
		printf("\nEssa conta não existe\n\n");
		}
}

// FUNÇÃO PARA ATUALIZAR SALDO
void atualizar_saldo(Conta *vetor, int tamanho){

	int numero, op, pes;
	float valor;
	
	do {
		numero_da_conta(&numero);
		pes = pesquisar(vetor, tamanho, numero);
	} while (pes < 0);
	
	do{
		printf("\nO que você deseja:\n\n[0] - SACAR\n[1] - DEPOSITAR\n\nOPCAO: ");
		scanf("%d", &op);
	} while((op != 0) && (op != 1));

	printf("Informe o valor: ");
	scanf("%f", &valor);

	if (op == 0){
		vetor[pes].saldo = vetor[pes].saldo - valor;
	}
	else{
		vetor[pes].saldo = vetor[pes].saldo + valor;
	}

}

// FUNÇÃO PARA SABER QUAL CLIENTE TEM O MAIOR SALDO
void maior(Conta *vetor, int tamanho){

	int i, cliente, maior;
	maior = 0;

	for ( i = 0; i < tamanho; i++)
	{
		if (vetor[i].saldo > maior){
			cliente = i;
			maior = vetor[i].saldo;
		}		
	}

	printf("\n\nDados do cliente com maior saldo:\n");
	listar(vetor, cliente);
}

// FUNÇÃO PARA EXCLUIR CLIENTE

void excluir(Conta *vetor, int *tamanho){

	int i, n, pes;

	numero_da_conta(&n);
	pes = pesquisar(vetor, *tamanho, n);

	for ( i = pes; i < *tamanho; i++)
	{
		vetor[i] = vetor[i + 1];
	}
	(*tamanho)--;

	printf("\n\nCONTA EXCLUÍDA!!!!\n\n");
	
}

int main() {

	//PARA TRATAR OS CARACTERES ESPECIAIS
	setlocale(LC_ALL, "");

	//VETOR PARA AS CONTAS;
	Conta conta[100];
	int tamanho_vetor, p, i;
	tamanho_vetor = 0;

	int op;
	do {
		op = menu();
		switch ( op ) {
			case 0:
				// SAIR. NÃO PRECISA FAZER NADA
				return 0;
			case 1:
				// INSERIR
				inserir_conta(conta, &tamanho_vetor);
				break;
			case 2:
				// PESQUISAR POR CODIGO/MATRICULA
				pesquisar_por_matricula(conta, tamanho_vetor);
				break;
			case 3:
				//PESQUISAR POR NOME
				p = pesquisar_nome(conta, tamanho_vetor);
				if (p >= 0){
					printf("\nConta encontrada!!!\n\n");
					listar(conta,p);
				}
				else{
					printf("\nEssa conta não existe\n\n");
				}
				break;
			case 4:
				// ATUALIZAR
				atualizar_saldo(conta, tamanho_vetor);
				break;
			case 5:
				// MAIOR
				maior(conta, tamanho_vetor);
				break;
			case 6:
				// EXCLUIR
				excluir(conta, &tamanho_vetor);
				break;
			case 7:
				// LISTAR
				for (i = 0; i < tamanho_vetor; i++)
				{
					listar(conta, i);
				}
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}
