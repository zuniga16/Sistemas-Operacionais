#include <iostream>
#include <locale.h>

using namespace std;

double average_tat(int tat[], int qnt_processos){
    double turnaround_time = 0;
    for(int i = 0; i < qnt_processos; i++){
    	turnaround_time += tat[i];
	}
    return turnaround_time / qnt_processos;
}

double average_wt(int wt[], int qnt_processos){
    double waiting_time = 0;
    for(int i = 0; i < qnt_processos; i++){
    	waiting_time += wt[i];
	}
    return waiting_time / qnt_processos;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	cout << "Algoritmo Round Robin" << endl;
	int qnt_processos;
	cout << "Quantidade de processos: ";
	cin >> qnt_processos;
	int processos[qnt_processos][3];

	for(int x = 0; x < qnt_processos; x++){
	    int pid,at,bt;
		pid = x;
	    cout << "Arrival Time: ";
	    cin >> at;
	    cout << "Burst Time: ";
	    cin >> bt;
	    processos[x][0] = pid;
	    processos[x][1] = at;
	    processos[x][2] = bt;
	}
	int quantum;
	cout << "Informe o Quantum: ";
	cin >> quantum;

/*	###########################################
	# Estrutura da Lista de Processos
	# 
	#   processos = [
	#               [id, at, bt],
	#               [id2, at2, bt2]
	#               ]
	#
	#   id = id do processo
	#   at = Arrival Time
	#   bt = Burst Time
	############################################
*/

//  Waiting Time
//  Criando uma lista de Burst Time restante dos processos
	int bt_restante[qnt_processos] = {0 * qnt_processos};  // ROUND-ROBIN
//  Criando uma lista de Waiting Time
	int wt[qnt_processos] = {0 * qnt_processos};
//  Copiando BurstTime dos processos para o bt_restante
	for(int x = 0; x < qnt_processos; x++){
		bt_restante[x] = processos[x][2];
	}
	
	int tempo = 0; // Tempo total que será adicionado ao WaitingTime
    int overhead = 1; // Valor hipotetico para o tempo gasto na troca de contexto entre processos

    while(true){
//  Variavel de Controle, verifica se os processos foram
//  finalizados ou não
	    bool finalizados = true;
	    for(int i = 0; i < qnt_processos; i++){
	        tempo += overhead; // Para cada troca de contexto entre os processos, Adicionar ao Tempo Total
	
	        // Se for maior que 0, ainda há processos a serem
	        // Finalizados
	        if(bt_restante[i] > 0){
	            finalizados = false;
	            // Se o tempo restante for maior que Quantum 
	            if(bt_restante[i] > quantum){
	                // Somar quantum ao tempo de processamento
	                tempo += quantum;
	                // Retirar do BurstTime restante o Tempo(quantum)
	                // que ja foi processado
	                bt_restante[i] -= quantum;
	            }
	            else{// Caso o tempo restante seja menor que quantum
	                // Somar ao tempo, o tempo restante de bt
	                tempo += bt_restante[i];
	                // WaitingTime = tempo_total - burst_time do processo
	                wt[i] = tempo - processos[i][2];
	                // Zerando burst time
	                bt_restante[i] = 0;
	            }
	        }
	    }
	    // Se todos os Processos foram concluídos
	    if(finalizados == true){
    	break;
		}
    }

	// TurnAround Time
	int tat[qnt_processos] = {0 * qnt_processos};
    for(int c=0; c < qnt_processos; c++){
        tat[c] = processos[c][2] + wt[c];
    }
    
	// Média de todos os TurnAround Time
	double avg_tat;
	avg_tat = average_tat(tat, qnt_processos);
	
	// Média de todos os Waiting Time
	double avg_wt;
	avg_wt = average_wt(wt, qnt_processos);
	
	
	cout << "WT = [";
	for(int a = 0; a < qnt_processos; a++){
		if(a < qnt_processos-1){
			cout << wt[a] << ", ";
		}
		if(a == qnt_processos-1){
			cout << wt[a] << "]" << endl;
		}
	}
	cout << "TAT = [";
	for(int a = 0; a < qnt_processos; a++){
		if(a < qnt_processos-1){
			cout << tat[a] << ", ";
		}
		if(a == qnt_processos-1){
			cout << tat[a] << "]" << endl;
		}
	}
	
	cout << "AVG_TAT = " << avg_tat << endl;
	cout << "AVG_WT = " << avg_wt << endl;

	cout << "| Process |\t| Burst Time |\t\t| Arrival Time |\t| Waiting Time |\t| Turn-Around Time |\t\n\n";
	for(int proc = 0; proc < qnt_processos; proc++){
   		cout << "P" << processos[proc][0] << "\t\t\t" << processos[proc][2] << "\t\t\t" << processos[proc][1] << "\t\t\t" << wt[proc] << "\t\t\t  " << tat[proc] << "\t\t\t\n";
	}
	cout << "Average Waiting Time: " << avg_wt << endl;
	cout << "Average Turn-Around Time: " << avg_tat << endl;

}
