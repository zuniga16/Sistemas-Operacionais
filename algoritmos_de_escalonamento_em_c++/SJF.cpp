/* CREATED BY ZUNIGA */

#include <iostream>
#include <locale.h>

using namespace std;

double average_wt(int wt[], int qnt_processos){
    double wt_all = 0;
    for(int i = 0; i < qnt_processos; i++){
    	wt_all += wt[i];
	}
    return wt_all / qnt_processos;
}


double average_tat(int tat[], int qnt_processos){
    double tat_all = 0;
    for(int i = 0; i < qnt_processos; i++){
    	tat_all += tat[i];
	}
	// Retornando o tempo medio 
   	// Soma_dos_tat / qnt.Processos
    return tat_all / qnt_processos;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	cout << ":::::::::::::::::::::::::::::::::::SJF:::::::::::::::::::::::::::::::::::" << endl;

	int qnt_processos;
	cout << "Qnt de Processos: ";
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
	
/*	#############################################
	# Estrutura da Lista de Processos           #
	#  Lista_processos = [                      #
	#                    [id, at, bt],          #
	#                    [id2, at2, bt2],       #
	#                   ]                       #
	#                                           #
	#   id = id do processo                     #
	#   at = Arrival Time                       #
	#   bt = Burst Time                         #
	#                                           #
	############################################# */
	
//Waiting_time
//  definindo a qnt. tempo de servico baseado na qnt de processos
	int tempo_servico[qnt_processos] = {0 * qnt_processos};
	int wt[qnt_processos] = {0 * qnt_processos};	
	
	for(int x = 1; x < qnt_processos; x++){
		tempo_servico[x] = (tempo_servico[x-1] + processos[x-1][2]);
		wt[x] = tempo_servico[x] - processos[x][1];
		if(wt[x] < 0){
			wt[x] = 0;
		}
	}
	
//Turn around Time
//  TurnAround Time = BurstTime + WaitingTime
    int tat[qnt_processos] = {0 * qnt_processos};// Turn around time
    for(int c=0; c < qnt_processos; c++){
        tat[c] = processos[c][2] + wt[c];
    }

	double avg_wt,avg_tat; 
	avg_wt = average_wt(wt, qnt_processos);
	avg_tat = average_tat(tat, qnt_processos);	
	
	int d,f;
	cout << "\n[";
	for(d = 0; d < qnt_processos; d++){
		for(f = 0; f < 3; f++){
			if(f==0){
				cout << "[P" << processos[d][f] << ", ";
			}
			else if(d<qnt_processos-1 && f==2){
				cout << processos[d][f] << "], ";
			}
			else if(d==qnt_processos-1 && f==2){
				cout << processos[d][f] << "]";
			}
			else{
				cout << processos[d][f] << ", ";
			}
		}
	}
	cout << "]" << endl << endl;
	
	cout << "| Process |\t| Burst Time |\t\t| Arrival Time |\t| Waiting Time |\t| Turn-Around Time |\t| Completion Time |\n\n";
	for(int proc = 0; proc < qnt_processos; proc++){
   		cout << "P" << processos[proc][0] << "\t\t\t" << processos[proc][2] << "\t\t\t" << processos[proc][1] << "\t\t\t" << wt[proc] << "\t\t\t  " << tat[proc] << "\t\t\t  " << tat[proc] + processos[proc][1] << "\t\t\t\n" << endl;
	}
	cout << "Average Waiting Time: " << avg_wt << endl;
	cout << "Average Turn-Around Time: " << avg_tat << endl;
	
	cout << "\n:::::::::::::::::::::::DEPOIS::::::::::::::::::::::\n";
	
//SJF
//  Ordenando por Job(Burst time) mais curto
    for(int a=0; a<qnt_processos; a++){
        for(int b=0; b<qnt_processos-1; b++){
            if(processos[b][2] > processos[b+1][2]){
            	int op[1][3];
            	op[0][0] = processos[b][0];
            	op[0][1] = processos[b][1];
            	op[0][2] = processos[b][2];
                processos[b][0] = processos[b+1][0];
                processos[b][1] = processos[b+1][1];
                processos[b][2] = processos[b+1][2];
                processos[b+1][0] = op[0][0];
                processos[b+1][1] = op[0][1];
                processos[b+1][2] = op[0][2];
            }
        }
	}

	tempo_servico[qnt_processos] = {0 * qnt_processos};
	wt[qnt_processos] = {0 * qnt_processos};	
	
	for(int x = 1; x < qnt_processos; x++){
		tempo_servico[x] = (tempo_servico[x-1] + processos[x-1][2]);
		wt[x] = tempo_servico[x] - processos[x][1];
		if(wt[x] < 0){
			wt[x] = 0;
		}
	}
	
	tat[qnt_processos] = {0 * qnt_processos};// Turn around time
    for(int c=0; c < qnt_processos; c++){
        tat[c] = processos[c][2] + wt[c];
    }

	avg_wt = average_wt(wt, qnt_processos);
	avg_tat = average_tat(tat, qnt_processos);	
	
	cout << "\n[";
	for(d = 0; d < qnt_processos; d++){
		for(f = 0; f < 3; f++){
			if(f==0){
				cout << "[P" << processos[d][f] << ", ";
			}
			else if(d<qnt_processos-1 && f==2){
				cout << processos[d][f] << "], ";
			}
			else if(d==qnt_processos-1 && f==2){
				cout << processos[d][f] << "]";
			}
			else{
				cout << processos[d][f] << ", ";
			}
		}
	}
	cout << "]" << endl << endl;
	
	cout << "| Process |\t| Burst Time |\t\t| Arrival Time |\t| Waiting Time |\t| Turn-Around Time |\t| Completion Time |\n\n";
	for(int proc = 0; proc < qnt_processos; proc++){
   		cout << "P" << processos[proc][0] << "\t\t\t" << processos[proc][2] << "\t\t\t" << processos[proc][1] << "\t\t\t" << wt[proc] << "\t\t\t  " << tat[proc] << "\t\t\t  " << tat[proc] + processos[proc][1] << "\t\t\t\n" << endl;
	}
	cout << "Average Waiting Time: " << avg_wt << endl;
	cout << "Average Turn-Around Time: " << avg_tat << endl;
}

