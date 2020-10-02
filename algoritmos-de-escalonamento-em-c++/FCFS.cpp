/* CREATED BY ZUNIGA */

#include <iostream>
#include <locale.h>

using namespace std;

//  Calcular media do waiting time
double average_wt(int wt[], int qnt_processos){
    double wt_all = 0;
    for(int i = 0; i < qnt_processos; i++){
    	wt_all += wt[i];
	}
    return wt_all / qnt_processos;
}

//  Calcular media do Turnaround time
double average_tat(int tat[], int qnt_processos){
    double tat_all = 0;
    for(int i = 0; i < qnt_processos; i++){
    	tat_all += tat[i];
	}
    return tat_all / qnt_processos;
}


int main(){
	setlocale(LC_ALL, "Portuguese");
	
//Lista de todos os processos
	int qnt_processos;
	cout << "Qnt de Processos: ";
	cin >> qnt_processos;
	int processos[qnt_processos][2];
	for(int x = 0; x < qnt_processos; x++){
		int at,bt;
		cout << "Arrival Time: ";
		cin >> at;
		cout << "Burst Time: ";
		cin >> bt;
		processos[x][0] = at;
		processos[x][1] = bt;
	}

/*
Estrutura do Processo
    [ [arrival_time, burst_time] ]
*/

	printf("Process\t\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n\n");
	
//  Calcular Waiting Time
//	Definindo a quantidade tempos de servico de cada baseado na qnt. de processos
	int tempo_servico[qnt_processos] = {0 * qnt_processos};
//	O tempo de servico é a soma de todos os BurstTime dos Processos anteriores
	tempo_servico[0] = 0;
//	Definindo tamanho da waiting list
	int wt[qnt_processos] = {0 * qnt_processos};	
	
	for(int x = 1; x < qnt_processos; x++){
		tempo_servico[x] = (tempo_servico[x-1] + processos[x-1][1]);
		wt[x] = tempo_servico[x] - processos[x][0];
		if(wt[x] < 0){
			wt[x] = 0;
		}
	}

//  Calcular Turn around Time
//  TurnAround Time = BurstTime + WaitingTime
    int tat[qnt_processos] = {0 * qnt_processos};// Turn around time
    for(int c=0; c < qnt_processos; c++){
        tat[c] = processos[c][1] + wt[c];
    }

	double avg_wt,avg_tat; 
	avg_wt = average_wt(wt, qnt_processos);
	avg_tat = average_tat(tat, qnt_processos);
	
//	Completion Time = Turn Around Time + Arrival Time
	for(int proc = 0; proc < qnt_processos; proc++){
		cout << proc << "\t\t" << processos[proc][1]<< "\t\t" << processos[proc][0] << "\t\t" << wt[proc] << "\t\t" << tat[proc] << "\t\t\t" << tat[proc] + processos[proc][0] << endl << endl;
	}
	cout << "\nAverage Waiting Time : " << avg_wt << endl;
	cout << "Average Turn-Around Time: " << avg_tat << endl;
}
