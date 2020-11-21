#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "TRENS.h"


//Adding new sorting algorithm(to later test cpu, memory and mainly time consumption)
int recebeCargass(float** cargas){
    double quick_time, bubble_time;

    float carga;
    int tam = 0;
    float* quick, *bubble; //Declared further down
    
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

        
        quick = *cargas;
        bubble = *cargas;

//The clock usage here was borrowed from https://github.com/aastharawat/Comparative-Analysis/blob/master/main.c
        clock_t quick_begin = clock();
        qsort(quick, tam, sizeof(float), cmpr);
        clock_t quick_end = clock();

        quick_time = (double) (quick_end - quick_begin)/CLOCKS_PER_SEC; //TODO: research this: how is time measured? wich unity? Could this inform real time cost of rearranging packagees in a storage facility?
        printf("\nTime taken by quicksort: %f", quick_time);


        clock_t bubble_begin = clock();
        bubbleSort(bubble, tam);
        clock_t bubble_end = clock();

        bubble_time = (double) (bubble_end - bubble_begin)/CLOCKS_PER_SEC; //TODO: research this: how is time measured? wich unity? Could this inform real time cost of rearranging packagees in a storage facility?
        printf("\nTime taken by bubblesort: %f", bubble_time);


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

//The folllowing two functions are geeksforgeeks' bubble sort from https://www.geeksforgeeks.org/bubble-sort/
//They'll be used to test the cpu and time usage methods, wich should boht be greater than quicksort's
void swap(float *xp, float *yp){ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubbleSort(float* arr, int n){  //TODO: return void if return is unused
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
}
