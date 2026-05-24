#ifndef estructuras_h
#define estructuras_h

#define MAX 50
//No se que PUTAS estoy haciendo
typedef struct Camion{
    int id;
    int carga;
}Camion; 

typedef struct Paquete{
    int id;
    int peso;
} Paquete;

typedef struct Cola{
    struct Paquete paquete[MAX];
    int frente;
    int final;
    int size;
} Cola;

typedef struct Nodo {
    struct Camion camion;
    struct Nodo *siguiente;
}Nodo; 

Paquete* nuevoPaquete(int id, int peso);
//Cola
int enqueue(int id, int peso);
int dequeue();
int isFull();
int isEmpty();
void peek();
void printQueue();
//Lista
void insertarInicio(Nodo **cabeza, Nodo **ultimo, Camion camion);
void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno);
void recorrer(Nodo *cabeza);
void eliminar(Nodo **cabeza, Nodo **ultimo, int valor);
void liberar(Nodo *cabeza, Nodo *ultimo);

#endif