#ifndef cola_pila_h
#define cola_pila_h

#define MAX 100
//No se que PUTAS estoy haciendo
typedef struct Camion{
    int carga;
}Camion; 

typedef struct Paquete{
    int id;
    int peso;
} Paquete;

typedef struct Cola{
    int peso;
    struct Paquete paquete[MAX];
    int frente;
    int final;
    int size;
} Cola;

Paquete* nuevoPaquete(int id, int peso);
int enqueue(int id, int peso);
int dequeue();
int isFull();
int isEmpty();
void peek();
void printQueue();

#endif