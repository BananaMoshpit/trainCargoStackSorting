#ifndef TRENS_H_
#define TRENS_H_


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


//The folllowing two functions are geeksforgeeks' bubble sort from https://www.geeksforgeeks.org/bubble-sort/, only return was changed (previously void)
//They'll be used to test the cpu and time usage methods, wich should boht be greater than quicksort's
void swap(int *xp, int *yp);

/*  
    Recebe: array desordenado
    Retorna: Array ordenado
    Pré-condição: array and pointer are non-null
    Pós-condição: array is ordered
 */
int* bubbleSort(int* arr, int n);

#endif /*TRENS_H_*/
/*  
    Recebe:
    Retorna:
    Pré-condição:
    Pós-condição:
 */