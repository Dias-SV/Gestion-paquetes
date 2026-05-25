#ifndef estructuras_h
#define estructuras_h

#define MAX 5
//No se que PUTAS estoy haciendo
typedef struct Camion{
    int id;
    int capacidad;
    int carga;
    Pila pila;
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

typedef struct Historial{
    Paquete paquete;
    struct Historial *siguiente;
}Historial;

//Cola
int enqueue(int id, int peso);
Paquete dequeue();
int isFullCola();
int isEmptyCola();
void peek();
void printQueue();

//Lista circular
void insertarFinal(Nodo **cabeza, Nodo **ultimo, Camion *camion);
void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno);
void recorrer(Nodo *cabeza);
int buscar(Nodo *cabeza, int id);
void eliminar(Nodo **cabeza, Nodo **ultimo, int valor);
void liberar(Nodo *cabeza, Nodo *ultimo);

//Pila
int push(Pila *pila, Paquete paquete);
Paquete pop(Pila *pila);
int isFullPila(Pila *pila);
int isEmptyPila(Pila *pila);
void mostrar(Pila *pila);

//Asignacion
void asignarPaquete(Nodo *cabeza, Nodo *ultimo, Pila *pila, int valor);
int deshacerAsignacion(Nodo *cabeza, Nodo *ultimo, Pila *pila, int valor);

//Historial
Camion* buscarCamion(Nodo *cabeza, int valor);
void registrarEntrega(Historial **cabeza, Camion *camion);
void mostrarHistorial(Historial *cabeza);

#endif