#ifndef estructuras_h
#define estructuras_h

#define MAX 5

typedef struct ID{
    int id[MAX];
    int posicion;
} ID;

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

typedef struct Camion{ //Lo puse aqui pooque dependo de pila
    int id;
    int capacidad;
    int carga;
    Pila pila;
}Camion; 

typedef struct Nodo {
    Camion camion;
    struct Nodo *siguiente;
}Nodo; 

typedef struct Historial{
    Paquete paquete;
    struct Historial *siguiente;
}Historial;

//Verificacion de ID
int registrarIdPaquete(int valor);
int buscarIdPaquete(int valor);
int registrarIdCamion(int valor, Nodo *cabeza);

//Cola
int insertarAtras(int id, int peso);
int insertarAdelante(int id, int peso);
Paquete dequeue();
int isFullCola();
int isEmptyCola();
void printQueue();

//Lista circular
void insertarFinal(Nodo **cabeza, Nodo **ultimo, Camion *camion);
void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno);
void mostrarCamiones(Nodo *cabeza, const char *mensaje);
void quitarCamion(Nodo **cabeza, Nodo **ultimo, int valor);
void liberar(Nodo *cabeza, Nodo *ultimo);

//Pila
int push(Pila *pila, Paquete paquete);
Paquete pop(Pila *pila);
int isFullPila(Pila *pila);
int isEmptyPila(Pila *pila);
void mostrar(Pila *pila);

//Asignacion
void asignarPaquete(Nodo *cabeza, Pila *pila, int valor);
void deshacerAsignacion(Nodo *cabeza, Pila *pila);

//Historial
Camion* buscarCamion(Nodo *cabeza, int valor);
void registrarEntrega(Historial **cabeza, Camion *camion);
void mostrarHistorial(Historial *cabeza);
void liberarH(Historial *cabeza);

#endif