#ifndef FUNCAO_MS_SIM_H_INCLUDED
#define FUNCAO_MS_SIM_H_INCLUDED
#define tam 40

//estrutura para guardar os endereços e contador de referências
typedef struct estrutura{
    void* endr;
    int cont_ref;
}est;

est*aux;

//inicializa o vetor e faz o auxiliar apontar para as mesmas áreas de memória alocadas
est*inicializa(){
    est*vetor=(est*)malloc(tam*sizeof(est));
    aux=(est*)malloc(tam*sizeof(est));
    for(int i=0; i<tam; i++){
        vetor[i].endr=(est*)malloc(sizeof(est));
        vetor[i].cont_ref=1;
        aux[i].endr = vetor[i].endr;
        aux[i].cont_ref=1;
    }
    return vetor;
}

//imprimir posição do vetor, quantidade de referências e endereço alocado
void imprime(est*vetor_est){
    for(int i=0; i<tam; i++){
        printf("%2d \t\t\t %p \t\t\t %d \t\t %p\n",i, aux[i].endr, vetor_est[i].cont_ref, vetor_est[i].endr );
    }
}

//atribui NULL a área alocada, gerando lixo
int apaga(est*vetor_est, int pos){
    if(vetor_est[pos].endr!=NULL && vetor_est[pos].cont_ref>0){
        vetor_est[pos].endr=NULL;
        vetor_est[pos].cont_ref--;
        if(vetor_est[pos].cont_ref==0)
            return 1;
    }
    else
        return 0;
}

//percorre o vetor verificando a quantidade de lixo gerado
int verifica_lixo(est*vetor_est){
    int quantidade_lixo=0;
    for(int i=0; i<tam; i++){
        if(vetor_est[i].cont_ref==0){
            quantidade_lixo++;
        }
    }
    return quantidade_lixo;
}
//faz um elemento do vetor apontar para outra área ja referenciada,
int reaponta(est*vetor_est, int pos, int pos2){
    if(vetor_est[pos].endr!=NULL && vetor_est[pos2].endr!=NULL && pos!=pos2 && vetor_est[pos].cont_ref>0 && vetor_est[pos2].cont_ref>0){
        vetor_est[pos].endr=vetor_est[pos2].endr;
        vetor_est[pos2].cont_ref++;
        vetor_est[pos].cont_ref--;
        if(vetor_est[pos].cont_ref==0)
            return 1;
    }
    else
        return 0;
}
//libera área de memória que não está sendo usada mais a partir do vetor auxiliar
void coletor_lixo(est*vetor){
    for(int i=0; i<tam; i++){
        if((vetor[i].cont_ref + aux[i].cont_ref)==1){
            free(aux[i].endr);
        }
    }
}

//reorganiza o vetor removendo as partes sem referencia e realocando novas areas
est* reorganiza(est*vetor_est){
    int cont=0;
    est* novo = (est*)malloc(tam*sizeof(est));
    //percorre vetor antigo e passa as alocações não nulas para novo vetor
    for(int i=0; i<tam; i++){
        if(vetor_est[i].endr != NULL){
            novo[cont].endr=vetor_est[i].endr;
            novo[cont].cont_ref=1;
            aux[cont].endr=novo[cont].endr;
            cont++;
        }
    }
    //percorre o novo vetor procurando as áreas nulas alocando nova área para eles
    for(int i=0; i<tam; i++){
        if(novo[i].endr==NULL){
            novo[i].endr = (est*)malloc(sizeof(est));
            novo[i].cont_ref = 1;
            aux[i].endr = novo[i].endr;
            aux[i].cont_ref = 1;
        }
    }
    free(vetor_est);
    return novo;
}

void sair(est*vetor_est){
    for(int i; i<tam; i++){
        free(vetor_est[i].endr);
        free(aux[i].endr);
    }
    free(vetor_est);
    free(aux);
}
#endif // FUNCAO_MS_SIM_H_INCLUDED
