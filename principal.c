#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include"funcao_ms_sim.h"

est*vet;
int main(){
    int a=0, b=0;
    time_t t;
    vet = inicializa();
    srand((unsigned) time(&t));
    while(a<=200){
        system("cls");
        if(b==tam-1)
            b=0;
        printf("Posicao \t\t Area alocada \t\tNumero de referencias\tEndereco vetor\n");
        if(rand()%20>10){
            if(vet[b].endr==NULL){
                aloca(vet,b);
                b++;
            }
            else
                b++;
        }
        if(b>3 && rand()%2>0){
            reaponta(vet,rand()%b,rand()%b);
        }
        if(b>1 && rand()%20 > 12){
            apaga(vet, rand()%tam-1);
        }
        if(quant_aloc()>tam*6/10 && verifica_lixo()>0){
            coletor_lixo(vet);
        }
        if(verifica_vet(vet)==tam){
            for(int i=0; i<tam/2; i++){
                apaga(vet, rand()%tam);
            }
        }
        imprime(vet);
        printf("\nlixo de memoria: %d\tarea alocada: %d\n", verifica_lixo(), quant_aloc(vet));
        a++;
        system("pause"); //para ver passo a passo do processo
        //usleep(500000); //para ver o processo como um todo
    }
    sair(vet);
    return 0;
}

