#include<stdlib.h>
#include<stdio.h>
#include"TRENS.h"

int MAXKG ;
int MAXVAG;
float *CARGAS; // An array of packages with ascending weight order
int TAM = 0;


void carregaVagao(vag* v);
void preencheTrem(trem* t);
void ordenaVagoes(trem* t);

/*  Recebe ponteiro para trem 
*   Cria nova fila de vagões *ordenada
*   Retira vagões do fim de t->inicioV 
*   Insere vagões em *ordenada (InsertSort) 
*   Aponta a fila do trem para a *ordenada
*   Retorna: nada
*/
void ordenaVagoes(trem* t){
    vag* ordenada, *aux, *novo;

    ordenada = retiraUltimo(t->inicioV);
    
    if(ordenada->chave != 1){
        novo = retiraUltimo(t->inicioV);


        while( novo != NULL){
        
            if ( novo->kgs >= ordenada->kgs){
                novo->prox = ordenada;
                ordenada = novo;
            }

            if ( novo->kgs < ordenada->kgs){

                for( aux = ordenada; aux->prox != NULL && aux->prox->kgs > novo->kgs; aux = aux->prox);

                novo->prox = aux->prox;
                aux->prox = novo;
            }

            if (novo == t->inicioV)
                break;
            novo = retiraUltimo(t->inicioV);
        }
    }

    t->inicioV = ordenada;
    printf("Vagões reordenados.\n");
}

/*  Receives: curent weight in train car and last index checked in CARGAS
*   Searches next package to be loaded in train car (whose weight may be added to car without overloading)
*   Returns: either index of found package or -1 if there's no possible package
*/
int nextCargo(int kgs, int lastChecked){
    int i;

    for ( i = lastChecked - 1; i >= 0; i--){
        if( i >= 0 && CARGAS[i] != -1 && CARGAS[i] + kgs <= MAXKG)
            return i;
    }
    
    return -1;
}

/*  Recebe vagão alocado
*   Retira do pesos do fim de CARGAS 
*   Empilha caixas no vagão
*   Designa peso total do vagão
*   Retorna: nada
 */
void carregaVagao(vag* v){
    int iNext, lastChecked;
    float kgs = 0;

    lastChecked = TAM;
    
    do{
        iNext = nextCargo(kgs, lastChecked);
        lastChecked = iNext;

        if(iNext != -1 && CARGAS[iNext] != -1){
            empilha( &v->topo, CARGAS[iNext]);
            kgs += CARGAS[iNext];
            CARGAS[iNext] = -1;

            if(iNext == TAM - 1)
                TAM--;
                
        printf(">[Vagão %d] %0.fkgs empilhados\n", v->chave, v->topo->peso);
        }
    }while (iNext != -1);    for (int i = TAM - 1; CARGAS[i] == -1 && i >= 0; i--) //Diminui o tamanho do array enquento os pesos maiores forem sabidamente retirados de 
        TAM--; //This is crucial to decide wether sytem stops or not. All packages unloaded means TAM == 0
    
    

    v->kgs = kgs;
    
    if(TAM != 0)
        printf("Carga máxima no vagão %d será excedida...\n", v->chave);

}

/*  Atacha vagões no trem enqunato há espaço e caixas a empilhar
*   Chama carregaVagão enquanto há vagões e cargas a despachar
 */
void preencheTrem(trem* t){
    int count = 1 ;

    vag** aux = &t->inicioV ;
   

    printf("[TREM %d]:\n", t->chave);
    while( TAM >= 1 && count <= MAXVAG) //Isso causava um bug caso ainda haja pacotes a serem despachados mas TAM esteja desatualizado e CARGAS[TAM] já fosse despachado
    {
       alocaVagao(aux, count);
       carregaVagao(*aux);
       aux = &(*aux)->prox;
       count++;
    }

     if( CARGAS[TAM-1] != -1)
         printf("Número máximo de vagões no trem %d será excedido...\n", t->chave);
     
}

static int cmpr(const void *n1, const void *n2 ){
 float a, b;
 a = *(const float*)n1;
 b = *(const float*)n2;
 return (b<a)-(b>a);
}



void main(){
    trem* fila, **aux;
    int count = 1;

    printf("Vagões por trem e peso máximo por vagão: ");   
    scanf("%d%d",&MAXVAG, &MAXKG);

    TAM = recebeCargass(&CARGAS);
    //^Armazena e ordena pesos em *CARGAS 

    printf("Iniciando despache...\n");
    for( aux = &fila; TAM != 0; aux = &(*aux)->prox, count++ )
    {
        
        alocaTrem(aux, count);
        preencheTrem(*aux);
        if( (*aux)->inicioV->prox != NULL) 
        ordenaVagoes(*aux);
        printf("\n");
    }
    
    printf("Despache finalizado.\n");
    
    imprimeTrens(fila);
   
   free( CARGAS);
   free( *liberaTrem( &fila) );
}
    
