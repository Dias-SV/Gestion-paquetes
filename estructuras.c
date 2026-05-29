#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

Cola cola = {.frente = 0, .final = -1, .size = 0}; //Asi inicalizo la cola
//Para saber las ids usadas
ID idPaquete = {0};
ID idCamion = {0};

//Registro ids
int registrarIdPaquete(int valor)
{
    for (int i = 0; i < idPaquete.posicion; i++)
    {
        if (idPaquete.id[i] == valor)
        {
            return 1;
        }
    }    
    idPaquete.id[idPaquete.posicion] = valor;
    idPaquete.posicion++;
    return 0;
}


int registrarIdCamion(int valor)
{
    for (int i = 0; i < idCamion.posicion; i++)
    {
        if (idCamion.id[i] == valor)
        {
            return 1;
        }
    }
    idCamion.id[idCamion.posicion] = valor;
    idCamion.posicion++;
    return 0;
}

//Operaciones cola doble
int insertarAtras(int id, int peso)
{
    if (isFullCola() == 1)
    {
        return 1;
    }
    
    if (isEmptyCola() == 1) //Resetea a 0 las posiciones si esta vacia
    {
        cola.frente = 0;
        cola.final = -1; //Al asignar posicion este cambia a 0
    }

    cola.size++;
    cola.final = (cola.final + 1) % MAX;
    cola.paquete[cola.final].id = id;
    cola.paquete[cola.final].peso = peso;
    return 0;
}

int insertarAdelante(int id, int peso)
{
    if (isFullCola() == 1)
    {
        return 1;
    }
    //No pongo verificacion de ID porque solo pondra los paquetes que se quitaron de un camion

    if (isEmptyCola() == 1) //Resetea posiciones y al estar en 0 no se guarda el elemento en 4 si no en 0
    {
        cola.frente = 0;
        cola.final = 0; //Para que no apunte a -1
    }
    else
    {
        cola.frente = (cola.frente - 1 + MAX) % MAX; //Mueve a la izquierda y la hace circular
    }
    cola.size++;
    cola.paquete[cola.frente].id = id;
    cola.paquete[cola.frente].peso = peso;
    return 0;
    
}

Paquete dequeue() //Regreso un paquete para poder guardarlo en otras estructuras
{
    Paquete temp = {-1}; //Para que no haya problema con otros paquetes
    if (isEmptyCola() == 1)
    {
        printf("La cola esta vacia\n");
        return temp;
    }

    temp = cola.paquete[cola.frente];
    cola.frente = (cola.frente + 1) % MAX;
    cola.size--;
    return temp;
}

int isFullCola()
{
    if (cola.size == MAX)
    {
        printf("\nLa cola esta llena\n");
        return 1;
    }
    return 0;
}

int isEmptyCola()
{
    if (cola.size == 0)
    {
        return 1;
    }
    return 0;
}

void printQueue()
{
    int i = cola.frente;
    if (isEmptyCola() == 1)
    {
        printf("La cola esta vacia\n");
        return;
    }

    printf("----- Estado de la cola -----\n");
    for (int j = 0; j < cola.size; j++)
    {
        printf("ID: %d | Peso: %d\n", cola.paquete[i].id, cola.paquete[i].peso);
        i = (i+1) % MAX;
    }
    printf("\n");
}

//Operaciones lista circular
void insertarFinal(Camion **cabeza, Camion **ultimo, Camion *camion)
{
    Camion *nuevo = malloc(sizeof(Camion));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    *nuevo = *camion;
    
    if (*cabeza == NULL) //Para el primer valor todos apuntan a lo mismo
    {
        nuevo->siguiente = nuevo;
        *cabeza = nuevo;
        *ultimo = nuevo;
    }
    else
    {
        nuevo->siguiente = *cabeza;
    }
    (*ultimo)->siguiente = nuevo;
    *ultimo = nuevo;
}

void rotar(Camion **cabeza, Camion **ultimo, int id, int turno)
{
    if (*cabeza == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    int cantidad = 0;
    Camion *temp = *cabeza;
    do //Para saber cuantos camiones hay
    {
        cantidad++;
        temp = temp->siguiente;
    } while (temp != *cabeza);

    if (turno < 1 || turno > cantidad)
    {
        printf("Turno invalido. Debe ser entre 1 y %d\n", cantidad);
        return;
    }
    
    temp = *cabeza; //Reinicio por si las dudas
    Camion *antes = *ultimo; //Pongo en ultimo por si se rompe el oop de una
    int exito = 0;
    int posicion = 1; //Para saber en que turno esta el camion
    do
    {
        if(temp->id == id)
        {
            exito = 1;
            break;
        }
        antes = temp;
        temp = temp->siguiente;
        posicion++;
    } while (temp != *cabeza);
    
    if (exito == 0)
    {
        printf("No se encontro el camion con ID: %d\n", id);
        return;
    }
    if (posicion == turno)
    {
        printf("El camion con ID: %d ya se encuentra en el turno %d\n", id, turno);
        return;
    }
    
    antes->siguiente = temp->siguiente; //Para desligarlo de la lista
    if (temp == *cabeza) //Para camion al inicio
    {
        *cabeza = temp->siguiente;
    }
    if (temp == *ultimo) //Para camion al final
    {
        *ultimo = antes;
    }

    if (turno == 1) //Para inicio
    {
        temp->siguiente = *cabeza;
        *cabeza = temp;
        (*ultimo)->siguiente = *cabeza;
    }
    else if (turno == cantidad)  //Para final
    {
        temp->siguiente = *cabeza;
        (*ultimo)->siguiente = temp;
        *ultimo = temp; 
    }
    else //Para uno en medio
    {
        Camion *temp2 = *cabeza; //Para recorrer la nueva lista
        for (int i = 1; i < turno-1 ; i++)
        {
            temp2 = temp2->siguiente;
        }
        temp->siguiente = temp2->siguiente;
        temp2->siguiente = temp;
    }

    printf("Camion con ID: %d movido al turno %d\n", id, turno);
}

void mostrarCamiones(Camion *cabeza, const char *mensaje)
{
    if (cabeza == NULL) //Sin esto crashea
    {
        printf("No hay camiones %s\n", mensaje);
        return;
    }
    
    Camion *temp = cabeza;
    printf("\n----- Camiones %s -----\n", mensaje);
    do
    {
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n",
        temp->id, temp->capacidad, temp->carga, temp->capacidad - temp->carga);

        temp = temp->siguiente;
    } while (temp != cabeza);
    printf("\n");
}

void quitarCamion(Camion **cabeza, Camion **ultimo, int valor)
{
    if(*cabeza == NULL)
    {
        printf("No hay camiones\n");
        return;
    }
    Camion *temp = *cabeza;
    Camion *antes = *ultimo;
    int exito = 0;
    do
    {
        if(temp->id == valor)
        {
            exito = 1;
            break;
        }
        antes = temp;
        temp = temp->siguiente;
    } while (temp != *cabeza);
    
    if (exito == 0)
    {
        printf("No se encontro el camion\n");
        return;
    }

    if (temp == *cabeza && *cabeza == *ultimo)
    {
        *cabeza = NULL;
        *ultimo = NULL;
        free (temp);
        return;
    }

    if (temp == *cabeza)
    {
        *cabeza = temp->siguiente; //Para cuando esta al inicio
        (*ultimo)->siguiente = *cabeza;
    }
    else if (temp == *ultimo)
    {
        antes->siguiente = *cabeza;//Para cuando esta al final
        *ultimo = antes;
    }
    else
    {
        antes->siguiente = temp->siguiente;//Para cuando esta en medio
    }

    free(temp);
}

void liberar(Camion *cabeza, Camion *ultimo)
{
    Camion *temp;
    if (cabeza == NULL)//Tuve que poner esto para cuando se quitaron todos los datos
    {
        return;
    }

    ultimo->siguiente = NULL; //Ya no se necesita que sea circular, por eso hago que sea NULL
    while (cabeza != NULL)
    {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

//Operaciones pila
int push(Pila *pila, Paquete paquete)
{
    if (isFullPila(pila) == 1)
    {
        return 1;
    }
    if (paquete.id == -1 || paquete.peso == -1) //Para que no se agreguen paquetes vacios
    {
        printf("No se pudo agregar el paquete\n");
        return 1;
    }
    if (isEmptyPila(pila) == 1) //Resetea a -1 el tope si esta vacia
    {
        pila->tope = -1;
    }
    
    pila->tope++;
    pila->paquete[pila->tope] = paquete;
    return 0;
}

Paquete pop(Pila *pila)
{
    if (isEmptyPila(pila) == 1)
    {
        Paquete vacio = {-1, -1};
        return vacio;
    }

    pila->tope--;
    return pila->paquete[pila->tope + 1];
}

int isFullPila(Pila *pila)
{
    if (pila->tope >= MAX-1)
    {
        printf("\nLa pila esta llena\n");
        return 1;
    }
    return 0;
}

int isEmptyPila(Pila *pila)
{
    if (pila->tope <= -1)
    {
        return 1;
    }
    return 0;
}

void mostrar(Pila *pila)
{
    if (isEmptyPila(pila) == 1)
    {
        printf("La pila esta vacia\n");
        return;
    }
    printf("----- Estado de la pila -----\n");
    for (int i = pila->tope; i >= 0; i--)
    {
        printf("ID: %d | Peso: %d\n", pila->paquete[i].id, pila->paquete[i].peso);
    }
    printf("\n");
}

//Asignar paquetes
void asignarPaquete(Camion *cabeza)
{
    if (isEmptyCola() == 1)
    {
        printf("No hay paquetes\n");
        return;
    }

    if(cabeza == NULL)
    {
        printf("No hay camiones\n");
        return;
    }
    
    if (cabeza->capacidad > cabeza->carga && cola.paquete[cola.frente].peso <= (cabeza->capacidad - cabeza->carga))
    {
        Paquete paquete = dequeue(); //Saco el paquete de la cola y lo almaceno en la variable local
        if (push(&cabeza->pila, paquete) == 1)
        {
            insertarAdelante(paquete.id, paquete.peso); //Si no se pudo agregar a la pila lo regreso a la cola
            return;
        }
        cabeza->carga = paquete.peso + cabeza->carga; 
        printf("Paquete con ID: %d se agrego al camion con ID: %d\n", paquete.id, cabeza->camion.id);
        return;
    }
    
    printf("Paquete con ID: %d NO se agrego al camion con ID: %d porque excede el peso.\nPeso paquete: %dkg. Espacio restante en el camion %d.\n"
    , cola.paquete[cola.frente].id, cabeza->id, 
    cola.paquete[cola.frente].peso, cabeza->capacidad - cabeza->carga); //Las puse asi porque no salieron de la cola
}

void deshacerAsignacion(Camion *cabeza)
{    
    if(cabeza == NULL)
    {
        printf("No hay camiones\n");
        return;
    }

    if(isEmptyPila(&cabeza->pila) == 1)
    {
        printf("No hay paquetes en el camion con ID: %d\n", cabeza->id);
        return;
    }

    Paquete paquete = pop(&cabeza->pila);
    if (paquete.id == -1) //otro chequeo por si las dudas
    {
        printf("No se pudo quitar el paquete\n");
        return;
    }
    insertarAdelante(paquete.id, paquete.peso); //Lo regreso a la cola para no perder el paquete
    cabeza->carga = cabeza->carga - paquete.peso;
    printf("Asignacion deshecha\n");
}

Camion* buscarCamion(Camion *cabeza, int valor)
{
    if (cabeza == NULL) //Sin esto crashea
    {
        return NULL;
    }
    
    Camion *temp = cabeza;
    do
    {
        if(temp->id == valor)
        {
            return temp;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    return NULL; //Si no encuentra

}

//Historial
void registrarEntrega(Historial **cabeza, Camion *camion)
{

    if (isEmptyPila(&(camion->pila)) == 1)
    {
        printf("No hay paquetes en el camion con ID: %d\n", camion->id);
        return;
    };

    Historial *nuevo = malloc(sizeof(Historial));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    
    nuevo->paquete = pop(&(camion->pila)); //Saco el paquete del camion
    camion->carga = camion->carga - nuevo->paquete.peso; //Cambio la carga del camion
    nuevo->siguiente = NULL;

    if(*cabeza == NULL)
    {
        *cabeza = nuevo;
    }
    else
    {
        Historial *temp = *cabeza;

        while(temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }

        temp->siguiente = nuevo;
    }
}

void mostrarHistorial(Historial *cabeza)
{
    if(cabeza == NULL)
    {
        printf("Historial vacio\n");
        return;
    }

    printf("\n----- HISTORIAL -----\n");

    while(cabeza != NULL)
    {
        printf("ID: %d | Peso: %dkg\n",
        cabeza->paquete.id,
        cabeza->paquete.peso);

        cabeza = cabeza->siguiente;
    }

    printf("\n");
}

void liberarH(Historial *cabeza)
{
    Historial *temp;

    while (cabeza != NULL)
    {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}
