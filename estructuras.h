#ifndef estructuras_h
#define estructuras_h

#define MAX 5
//No se que PUTAS estoy haciendo
typedef struct Camion{
    int id;
    int capacidad;
    int carga;
}Camion; 

typedef struct Paquete{
    int id;
    int peso;
} Paquete;

typedef struct Cola{
    Paquete paquete[MAX];
    int frente;
    int final;
    int size;
} Cola;

typedef struct Pila{
    Paquete paquete[MAX];
    int tope;
} Pila;

typedef struct Nodo {
    Camion camion;
    struct Nodo *siguiente;
}Nodo; 

//Cola
int enqueue(int id, int peso);
Paquete dequeue();
int isFullCola();
int isEmptyCola();
void peek();
void printQueue();
//Lista
void insertarInicio(Nodo **cabeza, Nodo **ultimo, Camion camion);
void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno);
void recorrer(Nodo *cabeza);
void eliminar(Nodo **cabeza, Nodo **ultimo, int valor);
void liberar(Nodo *cabeza, Nodo *ultimo);
//Pila
int push(Paquete paquete);
int pop();
int isFullPila();
int isEmptyPila();
void mostrar();
//Asignacion
void asignarPaquete(Nodo *cabeza, Nodo *ultimo, int valor);
#endif