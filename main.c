#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/***********************************************************************************
//HEADER
***********************************************************************************/

typedef struct caixas{
    float peso;
    struct caixas *prox; 
} caixas;

typedef struct vag{
    int chave;
    float kgs;
    /*^Peso total do vagão */
    caixas* topo;
    struct vag* prox;
} vag;
 
typedef struct trem{
    int chave;
    vag* inicioV;
    struct trem *prox;
} trem;


/*   Escaneia valores e armazena em CARGAS
*    Aloca espaço para CARGAS 
*    Ordena CARGAS em ordem crescente
*    Recebe: Endereço de CARGAS
*    Retorna: Tamanho de CARGAS
*    Pré-condição: cargas é o endereço um vetor *float vazio
*    Pós-condição: CARGAS é um vetor *float preenchido e ordenado(crescente)
*/
int recebeCargass(float** cargas);


/*  Aloca e inicializa trem
    Recebe: endereço e chave do trem
    Retorna: *trem
    Pré condição: **t != NULL e count == número do trem
    Pós-condiçao: *t é alocado, possui chave e trem->prox == NULL
 */
void alocaTrem(trem** t, int count);

/*  Aloca e inicializa vagão
    Recebe: endereço e chave do vagão
    Retorna: void
    Pré-condição: Endereço do trem é acessível
    Pós-condição: Um novo trem c é criado com chave (fora da fila)
 */
void alocaVagao(vag** v, int count);

/*  Cria e empilha uma nova caixa
    Recebe: endereço da pilha e peso da carga 
    Retorna: void
    Pré-condição: Pilha aessível 
    Pós-condição: Topo da pilah é a nova caixa
 */
void empilha(caixas** topo, float peso);


/*  Percorre fila recursivamente até o último vagão;
*   Aponta o penúltimo para NULL;
*   Recebe: Início da fila;
*   Retorna: Vagão retirado; 
*   Pré condição: Fila de vagões não nula;
*   Pós condição: Fila diminuída;
*/
vag* retiraUltimo(vag* v);


/*  Recursivamente libera a pilha do vagão;
    Caso base: primeira pilha
    Retorna endereço do topo(não liberado) */

caixas** liberaCaixas(caixas** c);

/*  Recursiva
*   Libera todas as caixas de cada vagão,do primeiro ao último;
*   Libera os vagões do último ao segundo;
*   Retorna  endereço do primeiro vagão(não liberado); 
*/

vag** liberaVagao(vag** v);

/*  Recursiva
*   Libera a memória de todos vagões do primeiro ao último trem;
*   Libera trens do último ao primeiro;
*   Retorna endereço do primeiro trem(não liberado);
*/
trem** liberaTrem(trem** t);


/*  Percorre pilha recursivamente até o fim
    Imprime o peso da próxima caixa
    Recebe: Caixa 
    Retorna: Peso da  caixa
    Pré-condição: Caixa acessível
    Pós-condição: Nehuma
    */
float imprimeBottom(caixas* c );


/*  Acessa vagões de cada trem, chama imprimeBottom e imprime o topo
    Recebe: Fila de trens
    Retorna: Nada
    Pré-condição: Fila preenchida e acessível
    Pós-condição: Nenhuma
 */
void imprimeTrens(trem* head);


/*  Função utilizada no Qsort 
    Define ordem crescente na ordenação
    Recebe: dois valores( void )
    Retorna: -1 se n1 < n2, 0 se n1 == n2, 1 se n2 < n1
 */
static int cmpr(const void *n1, const void *n2 );


//The folllowing two functions are geeksforgeeks' bubble sort from https://www.geeksforgeeks.org/bubble-sort/
//They'll be used to test the cpu and time usage methods, wich should boht be greater than quicksort's
void swap(float *xp, float *yp);

/*  
    Recebe: array desordenado
    Retorna: Array ordenado
    Pré-condição: array and pointer are non-null
    Pós-condição: array is ordered
 */
void bubbleSort(float* arr, int n); //TODO: return void if return is unused

/***********************************************************************************
//HEADER IMPLEMENTATION
***********************************************************************************/

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

/***********************************************************************************
//  MAIN 
***********************************************************************************/

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
    
    

    for (int i = TAM - 1; CARGAS[i] == -1; i--) //Diminui o tamanho do array enquento os pesos maiores forem sabidamente retirados de 
        TAM--;
    
    

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