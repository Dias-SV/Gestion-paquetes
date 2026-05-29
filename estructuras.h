#ifndef estructuras_h
#define estructuras_h

#define MAX 50

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
    struct Camion *siguiente;
}Camion; 

typedef struct Historial{
    Paquete paquete;
    struct Historial *siguiente;
}Historial;

//Verificacion de ID
int registrarIdPaquete(int valor);
int registrarIdCamion(int valor);

//Cola doble
int insertarAtras(int id, int peso);
int insertarAdelante(int id, int peso);
Paquete dequeue();
int isFullCola();
int isEmptyCola();
void printQueue();

//Lista circular
void insertarFinal(Camion **cabeza, Camion **ultimo, Camion *camion);
void rotar(Camion **cabeza, Camion **ultimo, int id, int turno);
void mostrarCamiones(Camion *cabeza, const char *mensaje);
void quitarCamion(Camion **cabeza, Camion **ultimo, int valor);
void liberar(Camion *cabeza, Camion *ultimo);

//Pila
int push(Pila *pila, Paquete paquete);
Paquete pop(Pila *pila);
int isFullPila(Pila *pila);
int isEmptyPila(Pila *pila);
void mostrar(Pila *pila);

//Asignacion
void asignarPaquete(Camion *cabeza);
void deshacerAsignacion(Camion *cabeza);

//Historial
Camion* buscarCamion(Camion *cabeza, int valor);
void registrarEntrega(Historial **cabeza, Camion *camion);
void mostrarHistorial(Historial *cabeza);
void liberarH(Historial *cabeza);

#endif
