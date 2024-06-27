#include <iostream>
using namespace std;

#define MAX 5

struct Fila {
	int ini;
	int fim;
	float nos[MAX];
};

Fila* init() {
	Fila *f = new Fila;
	f->ini = 0;
	f->fim = 0;
	return f;
}

int isEmpty(Fila *f) {
	return(f->ini == f->fim);
}

int incrementa(int i) {
	/*
	int ret;
	if (i == MAX) {
		ret = 0;
	}
	else {
		ret = i +1;
	}
	return ret;
	*/
	return (i==MAX?0:++i);
}

int enqueue(Fila *f, float v) {
	int podeEnfileirar = (incrementa(f->fim) != f->ini);
	if (podeEnfileirar) {
		f->nos[f->fim] = v;
		f->fim = incrementa(f->fim);
	}
	return podeEnfileirar;
}

float dequeue(Fila *f) {
	float ret;
	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		ret = f->nos[f->ini];
		f->ini = incrementa(f->ini);
	}
	return ret;
}

int count(Fila *f) {
	int qtde = 0;
	int i = f->ini;
	while (i != f->fim) {
		qtde++;
		i = incrementa(i);
	}
	return qtde;
}

void print(Fila *f) {
	int i = f->ini;
	cout << "-------------------------------" << endl;
	cout << "Qtde de senhas não atendidas: " << count(f) << endl;
	//while (i != f->fim) {
	//	cout << f->nos[i] << endl;
	//	i = incrementa(i);
	//}
	cout << "-------------------------------" << endl;
}

void freeFila(Fila * f) {
	free(f);
}


int main(int argc, char** argv)
{
	Fila *senhasGeradas = new Fila; // fila das senhas geradas pelo 1. Gerar Senha
	senhasGeradas = init(); 
	
	float senha_base = 0; // valor inicial das senhas, por ser incrementando pelo 1. Gerar Senha, sempre irá começar como 1
	
    Fila *senhasAtendidas = new Fila; // fila atendida pelo 2. Realizar atendimento
    senhasAtendidas = init();

	bool continuar = true;
    int input;
    
    while (continuar) { // mantém o loop até todas senhas serem atendidas
        print(senhasGeradas); // mostra a qtde de senhas que precisam ser atendidas
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;
        cout << "Digite o número da opção que deseja: ";
        cin >> input;

        switch (input) {
            case 0:
                if (isEmpty(senhasGeradas)) { // se a fila das senhas não atendidas estiver vazia
                    continuar = false;
                    freeFila(senhasGeradas); // limpa a memória
                    cout << "\nPrograma encerrado.\n" << endl;
                    break;
                } else { // se a lista tiver elementos
                    cout << "\nAinda restam senhas a serem atendidas.\n" << endl;
                    break;
                }
            case 1:
                cout << "\nGerando e incrementando senha.\n" << endl;
                senha_base++; // incrementa a senha
                enqueue(senhasGeradas, senha_base); // coloca ela na fila das senhasGeradas (senhas não atendidas)
                break;
            case 2:
                cout << "\nConsumindo senha da vez.\n" << endl;
                dequeue(senhasGeradas); // tira o valor recente da fila das senhasGeradas
                enqueue(senhasAtendidas, senha_base); // coloca esse mesmo valor na fila das senhas atendidas
                cout << "Senha atendida: " << senha_base << endl; // mostra o valor na tela
                break;
            default:
                cout << "\nOpção inválida.\n" << endl;
                break;
        }
    }
	
	return 0;
}