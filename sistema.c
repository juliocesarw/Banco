#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//PARTE DO CLIENTE
struct Cliente{
	char nome[100];
	char telefone[100];
	char email[100];
};
typedef struct Cliente Cliente;

void inserir_cliente(Cliente *vetor){

	printf("Digite o nome do cliente: ");
	scanf("%s", vetor->nome);
	setbuf(stdin, NULL);
	printf("Digite o telefone do cliente: ");
	scanf("%s", vetor->telefone);
	setbuf(stdin, NULL);
	printf("Digite o email do cliente: ");
	scanf("%s", vetor->email);
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
			return 1;
		}
	}
	return -1;
}
void inserir_conta(Conta *vetor, int *tamanho){

	int p, n;

	//// LEMBRAR QUE VOCÊ DEVE RETIRAR O VETOR-> NUMERO E SUBSTITUIR POR UMA VARIAVEL ANTES DE CONFERIR

	printf("\n\nDigite o número da conta: ");
	scanf("%d", &vetor->numero);
	p = pesquisar(vetor, *tamanho, vetor->numero);

	while (p >= 0)
	{
		printf("JA EXISTE UMA CONTA COM ESSE NUMERO!!!!");
		printf("\n\nDigite o número da conta: ");
		scanf("%d", &vetor->numero);
		p = pesquisar(vetor, *tamanho, vetor->numero);
		printf("%d\n\n", p);
	}
	
	setbuf(stdin, NULL);
	printf("Digite o saldo da conta: ");
	scanf("%f", &vetor->saldo);
	setbuf(stdin, NULL);
	inserir_cliente(&vetor->cliente);
	(*tamanho)++;
}

// FUNÇÕES PRINCIPAIS


int menu() {
	int op;
	system("@cls||clear");  // LIMPA A TELA
	printf("\n\nSISTEMA XXYYZZ\n\n");
	printf("1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n");
	printf("6 - Excluir\n");
	printf("7 - Listar\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}

int main() {

	//VETOR PARA AS CONTAS;
	Conta conta[100];
	int tamanho_vetor = 0;

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
				//pesquisar(conta, tamanho_vetor);
				break;
			case 3:
				// PESQUISAR POR NOME
				break;
			case 4:
				// ATUALIZAR
				break;
			case 5:
				// MAIOR
				break;
			case 6:
				// EXCLUIR
				break;
			case 7:
				// LISTAR
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}
