/* CREATED BY ZUNIGA */

#include <iostream>
#include <locale.h>

using namespace std;

int hiper_periodo(int processos[3][4], int qnt){
//	Hiper Periodo é o maior periodo dentre todos os processos
	int temp = 0;
	for(int i=0;i<qnt;i++){
		if(processos[i][3]>temp){
			temp=processos[i][3];
		}
	}
	return temp;
}

int escolher_menor_deadline(int processos[3][4], int qnt, int deadlines[]){
	int menor_deadline = 10000;
	int escolhido = -1;
	for(int i=0;i<qnt;i++){
		if(deadlines[i] < menor_deadline){
			menor_deadline = deadlines[i];
			escolhido = i;
		}
	}
	return escolhido;
}

void edf(int processos[3][4], int qnt){
	int relogio = 0;
	int deadlines[qnt] = {0*qnt};
	for(int i=0;i<qnt;i++){
		deadlines[i] = processos[i][2];
	}
	int periodos[qnt] = {0*qnt};
	for(int i=0;i<qnt;i++){
		periodos[i] = processos[i][3];
	}
	
	cout << "Processos: [";
	for(int i=0; i<qnt; i++){
		for(int b=0; b<4; b++){
			if(i<2 && b==0){
				cout << "[" << processos[i][b] << ", ";
			}
			if(i<2 && b<3 && b>0){
				cout << processos[i][b] << ", ";
			}
			if(i<2 && b==3){
				cout << processos[i][b] << "], ";
			}
			if(i==2 && b==0){
				cout << "[" << processos[i][b] << ", ";
			}
			if(i==2 && b<3 && b>0){
				cout << processos[i][b] << ", ";
			}
			if(i==2 && b==3){
				cout << processos[i][b] << "]]";
			}
		}
	}
	
	cout << "\nDeadlines: [";
	for(int i=0; i<qnt; i++){
		if(i<2){
			cout << deadlines[i] << ", ";
		}
		if(i==2){
			cout << deadlines[i] << "]";
		}
	}
	
	cout << "\nPeriodos: [";
	for(int i=0; i<qnt; i++){
		if(i<2){
			cout << periodos[i] << ", ";
		}
		if(i==2){
			cout << periodos[i] << "]";
		}
	}
	
	cout << endl;
	
    int contador[qnt] = {0*qnt};
    
    while(true){
    	int escolhido = escolher_menor_deadline(processos, qnt, deadlines);
    	cout << endl;
    	cout << "Processo Escolhido: " << escolhido << endl;
    	if(periodos[escolhido] >= relogio){
    		relogio += processos[escolhido][1];
    		cout << "Processo: P" << escolhido << " executando..." << endl;
    		cout << "Relogio: "<< relogio << endl;
    		cout << "Burst Time do Processo P" << escolhido << ": " << processos[escolhido][1] << endl;
    		cout << "Deadline ANTERIOR do Processo: " << deadlines[escolhido] << endl;
    		deadlines[escolhido] += processos[escolhido][3];
    		cout << "Deadline do Processo P" << escolhido << " Atualizada: " << deadlines[escolhido] << endl;
    		cout << "Periodo ANTERIOR do Processo: " << periodos[escolhido] << endl;
    		periodos[escolhido] += processos[escolhido][3];
    		cout << "Periodo do Processo P" << escolhido << " Atualizado: " << periodos[escolhido] << endl;
    		contador[escolhido] += 1;
		}
		if(relogio>=20){
			break;
		}
	}
	cout << endl;
	for(int i=0; i<qnt; i++){
		cout << "O Processo P" << i << " Executou " << contador[i] << " vezes" << endl;
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
//				         0  1  2  3
//                       id bt dl p
	int processos[3][4]={0,3,7,20,
					     1,2,4,5,
					     2,2,8,10};
		 
	int qnt=3;
	edf(processos, qnt);
}
