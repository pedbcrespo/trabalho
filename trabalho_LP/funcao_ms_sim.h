#ifndef FUNCAO_MS_SIM_H_INCLUDED
#define FUNCAO_MS_SIM_H_INCLUDED
#define tam 20

//estrutura para guardar os endere�os e contador de refer�ncias
typedef struct estrutura{
    void* endr;
    int cont_ref;
}est;

est*aux;
int pos_aloc[tam];

//inicializa os vetores atribuindo endere�os null e 0 nos contadores
est*inicializa(){
    est*vet=(est*)malloc(tam*sizeof(est));
    aux=(est*)malloc(tam*sizeof(est));
    for(int i=0; i<tam; i++){
        vet[i].endr=NULL;
        aux[i].endr=NULL;
        vet[i].cont_ref=0;
        aux[i].cont_ref=0;
    }
    return vet;
}

//busca a posi��o do endere�o referenciado no vetor aux. A busca � a partir do vet para o aux
int busca_pos_aux(est*vetor, int pos){
    int pos_encontrada=-1;
    for(int i=0; i<tam; i++){
        if(aux[i].endr==vetor[pos].endr){
            pos_encontrada = i;
            break;
        }
    }
    return pos_encontrada;
}

//percorre o vetor aux e conta quantos endere�os de vet sao iguais ao do aux em determinada posi��o
int quant_aloc_aux(est* vetor, int pos){
    int cont=0;

    if(aux[pos].endr!=NULL){
        for(int i=0; i<tam; i++){
            if(vetor[i].endr == aux[pos].endr)
                cont++;
        }
    }
    return cont;
}

//aloca uma area a uma determinada posi��o do vetor
void aloca(est*vetor,int pos){
    int cont=0;
    vetor[pos].endr = (est*)malloc(sizeof(est));

        if(aux[pos].endr==NULL){
            aux[pos].endr = vetor[pos].endr;
            vetor[pos].cont_ref++;
            aux[pos].cont_ref++;
        }
        else if(aux[pos].endr!=NULL){

            for(int i=0; i<tam; i++){

                if(aux[i].endr==NULL){
                    aux[i].endr = vetor[pos].endr;
                    vetor[pos].cont_ref++;
                    aux[i].cont_ref++;
                    break;
                }
            }
        }
}

//atribui null no endere�o de determinado vetor
void apaga(est*vetor, int pos){
    if(vetor[pos].endr!=NULL){
        if(aux[busca_pos_aux(vetor,pos)].cont_ref>0)
            aux[busca_pos_aux(vetor,pos)].cont_ref--;
        vetor[pos].endr = NULL;
        vetor[pos].cont_ref--;
    }
}

//o endere�o do vetor de posi��o 1 passa a apontar para o endere�� armazenado no vetor de posi��o 2
void reaponta(est*vetor, int pos_apontar, int pos_apontada){

    int pos_aux1 = busca_pos_aux(vetor, pos_apontar), pos_aux2 = busca_pos_aux(vetor, pos_apontada);

    if(aux[pos_aux2].endr!=NULL && vetor[pos_aux2].endr!=NULL){
        vetor[pos_apontar].endr = vetor[pos_apontada].endr;
        if(aux[pos_aux1].cont_ref>0){
            aux[pos_aux1].cont_ref--;
            aux[pos_aux2].cont_ref++;
        }
    }
}

int verifica_vet(est*vetor){
    int cont=0;
    for(int i=0; i<tam; i++){
        if(vetor[i].endr!=NULL)
            cont++;
    }
    return cont;
}
//verifica a quantidade de lixo
int verifica_lixo(){
    int cont=0;
    for(int i=0; i<tam; i++){
        if(aux[i].endr!=NULL && aux[i].cont_ref==0)
            cont++;
    }
    return cont;
}
//verifica a quantidade de areas alocadas
int quant_aloc(){
    int cont=0;
    for(int i=0; i<tam; i++){
        if(aux[i].endr!=NULL)
            cont++;
    }
    return cont;
}
//reorganiza o vetor descartando as areas consideradas lixo
est*reorganiza(est*vetor){
    int cont = 0, cont2 = 0;
    est*novo = (est*)malloc(tam*sizeof(est));
    for(int i=0; i<tam; i++){
        novo[i].cont_ref=0;
        novo[i].endr=NULL;
    }

    for(int i=0; i<tam; i++){
        if(aux[i].endr!=NULL && vetor[i].endr!=NULL){
            novo[cont].endr = vetor[i].endr;
            novo[cont].cont_ref = vetor[cont].cont_ref;
            cont++;
        }
    }

    return novo;
}
//percorre o vetor aux em busca de lixos de memoria, quando encontra, o coleta e libera
void coletor_lixo(est*vetor){
    for(int i=0; i<tam; i++){
        if(aux[i].cont_ref==0){
            free(aux[i].endr);
            aux[i].endr = NULL;
        }
    }
    vetor=reorganiza(vetor);
}
//imprime as informa��es do simulador como a area alocada, a quantidade de referencias e o comportamento do vetor que a referencia
void imprime(est*vetor_est){
    for(int i=0; i<tam; i++){
        //printf("%2d \t\t\t %p \t\t\t %d \t\t",i, aux[i].endr, aux[i].cont_ref);
        printf("%2d \t\t\t ",i);

        if(aux[i].endr!=NULL)
            printf(" %p \t\t\t ", aux[i].endr);
        else
            printf("         \t\t\t ");
        printf("%d \t\t", aux[i].cont_ref);
        //printf("%d \t\t", quant_aloc_aux(vetor_est, i));
        if(vetor_est[i].endr!=NULL)
            printf(" %p\n", vetor_est[i].endr);
        else
            printf("\n");
    }
}
//libera tudo antes de fechar o programa
void sair(est*vetor_est){
    for(int i; i<tam; i++){
        free(vetor_est[i].endr);
        free(aux[i].endr);
    }
    free(vetor_est);
    free(aux);
}
#endif // FUNCAO_MS_SIM_H_INCLUDED
