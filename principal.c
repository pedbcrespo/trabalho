#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include"funcao_ms_sim.h"

est*vet;
int main(){
    int a=1, b, cont_lixo=0;
    time_t t;
    vet = inicializa();
    srand((unsigned) time(&t));
    while(a<=200){
        system("cls");
        printf("Posicao \t\t Area alocada \t\tNumero de referencias\tEndereco vetor\n");
        if((rand()%20)>13){
            cont_lixo = cont_lixo + apaga(vet, rand()%tam);
        }
        if((rand()%20)>17){
            cont_lixo=cont_lixo+reaponta(vet,rand()%tam,rand()%tam);
        }

        if(cont_lixo>=(tam/2)){
            coletor_lixo(vet);
            vet=reorganiza(vet);
            cont_lixo=0;
        }
        if(cont_lixo != verifica_lixo(vet))
            cont_lixo = verifica_lixo(vet);
        imprime(vet);
        printf("\nlixo de memoria: %d\n", cont_lixo);
        a++;
        system("pause"); //para ver passo a passo do processo
        //usleep(500000); //para ver o processo como um todo
    }
    sair(vet);
    return 0;
}

