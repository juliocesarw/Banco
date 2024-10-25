#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
}

//PARTE DA CONTA
struct Conta{
	int numero;
	float saldo;
	Cliente cliente;
};
typedef struct Conta Conta;

int pesquisar(Conta *vetor, int tamanho_vetor, int pes){

	// "%250[^\n]s"
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

	printf("\n\nDigite o número da conta: ");
	scanf("%d", &n);
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
	printf("Digite o saldo da conta: ");
	scanf("%f", &vetor[*tamanho].saldo);
	setbuf(stdin, NULL);
	inserir_cliente(&vetor[*tamanho].cliente);
	setbuf(stdin, NULL);
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
		setbuf(stdin, NULL);
	} while(op < 0 || op > 7);
	return op;
}

// FUNÇÃO LISTAR
void listar(Conta *vetor, int tamanho){
	
	int i;
	for ( i = 0; i < tamanho; i++)
	{
		printf("NUMERO DA CONTA: %d\n", vetor[i].numero);
		printf("SALDO DA CONTA: R$%.2f\n", vetor[i].saldo);
		printf("NOME DO CLIENTE: %s\n", vetor[i].cliente.nome);
		printf("NUMERO DO CLIENTE: %s\n", vetor[i].cliente.telefone);
		printf("EMAIL DO CLIENTE: %s\n", vetor[i].cliente.email);
		printf("\n");
	}
}

// FUNÇÃO PESQUISAR POR NOME
int pesquisar_nome(Conta *vetor, int tamanho){

	int i, pes;	
	char nome[30];

	printf("Nome do Cliente: ");
	scanf("%30[^\n]s", nome);

	for (i = 0; i < tamanho; i++)
	{
		pes = strcmp(vetor->cliente.nome, nome);
		if (pes == 0){
			return 1;
		}
	}
	return -1;

}


int main() {

	//VETOR PARA AS CONTAS;
	Conta conta[100];
	int tamanho_vetor, pes, p;
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
				printf("número da conta: ");
				scanf("%d", &pes);
				p = pesquisar(conta, tamanho_vetor, pes);
				if (p > 0){
					printf("Conta encontrada!!!");
				}
				else{
					printf("Essa conta não existe");
					}
				break;
			case 3:
				// PESQUISAR POR NOME
				p = pesquisar_nome(conta, tamanho_vetor);
				if (p == 0){
					printf("Conta encontrada!!!");
				}
				else{
					printf("Essa conta não existe");
					}
				break;
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
				listar(conta, tamanho_vetor);
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}
