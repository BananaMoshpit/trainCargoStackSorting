#include<stdlib.h>
#include<stdio.h>
#include "TRENS.h"





int recebeCargass(float** cargas){
    int tam = 0;
    float carga;
    
    *cargas = (float*)malloc(sizeof(float));
 
    if (*cargas == NULL)
        printf("Erro na alocação de memória!\n");
    
    else{

        printf("Digite pesos (-1 para paraar): \n");

        while(carga != -1)
        {
            scanf("%f",&carga);
            tam++;
            if( (*cargas = (float*)realloc(*cargas, sizeof(float)*tam)) == NULL ){
                printf("Erro na alocação de memória!\n");
                break;
            }
            cargas[0][tam - 1] = carga;  
        }

        qsort(*cargas, tam, sizeof(float), cmpr);

        printf("\nCargas ordenadas:\n");
    }
 return tam;
}



void alocaTrem(trem** t, int count){

    if( (*t = (trem*)malloc(sizeof(trem))) != NULL ){
       (*t)->chave = count;
       (*t)->prox =NULL;
        printf("\n(Trem %d alocado)\n", (*t)->chave );
    }
    else 
     printf("[Trem %d] Memória insuficiente para alocação do Trem\n", count);
}

void alocaVagao(vag** v, int count){
    if( (*v=(vag*)malloc(sizeof(vag))) != NULL ){
        (*v)->chave = count;
        (*v)->topo = NULL;  
        (*v)->prox = NULL;
        printf(" (Vagão %d alocado)\n", (*v)->chave );
    }
    else 
      printf(" Erro ao alocar vagão %d.\n", count);
}
 
void empilha(caixas** topo, float peso){
    caixas* nova = (caixas*)malloc(sizeof(caixas)) ;
    if( nova != NULL ){
        nova->peso = peso;
        nova->prox = NULL;
        if( *topo != NULL )        
            nova->prox = *topo;
        *topo = nova;
    }
    else
    printf("Memória insuficiente!\n");
}


vag* retiraUltimo(vag* v){
    vag* ultimo;
   
    if (v->prox == NULL )
    return v;

    if( v->prox->prox != NULL)   
        ultimo = retiraUltimo( v->prox);
    else 
    {
        ultimo = v->prox;
        v->prox = NULL;
    }

 return ultimo;
}


caixas** liberaCaixas(caixas** c){

    if ( (*c)->prox != NULL )
        free( *liberaCaixas(&(*c)->prox) );

 return c;
}

vag** liberaVagao(vag** v){
    free( *liberaCaixas( &(*v)->topo ));

    if( (*v)->prox != NULL )
        free( *liberaVagao( &(*v)->prox) );

 return v;
}

trem** liberaTrem(trem** t){
    free( *liberaVagao( &(*t)->inicioV ) );

    if ( (*t)->prox != NULL)
        free( *liberaTrem( &(*t)->prox) );
 
 return t;
}


void imprimeTrens(trem* head){
    trem *aux;
    vag* printa;

    for ( aux = head; aux != NULL ; aux = aux->prox){

        printf("Trem %d: ", aux->chave);

        for (printa = aux->inicioV; printa != NULL; printa = printa->prox)
        {
            printf("—[%d|", printa->chave);
            printf("%g ",imprimeBottom(printa->topo));
            printf("|%g].", printa->kgs);
        }

        printf("\n");
    }
    
}

float imprimeBottom(caixas* c ){

    if (c->prox == NULL)
        return c->peso;
    else
        printf("%g ",imprimeBottom( c->prox));
 return c->peso;
}

static int cmpr(const void *n1, const void *n2 ){
 float a, b;
 a = *(const float*)n1;
 b = *(const float*)n2;
 return (b<a)-(b>a);
}
