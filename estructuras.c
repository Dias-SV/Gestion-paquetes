#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

Cola cola;
Camion camion;

//Operaciones para cola
int enqueue (int id, int peso)
{
    if (isFullCola() == 1)
    {
        return 1;
    }
    cola.paquete[cola.final].id = id;
    cola.paquete[cola.final].peso = peso;
    cola.final = (cola.final + 1) % MAX;
    cola.size++;
    return 0;
    
}

Paquete dequeue() //Regreso un paquete para poder guardarlo en otras estructuras
{
    Paquete temp = {-1}; //Para que no haya problema con otros paquetes
    if (isEmptyCola() == 1)
    {
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
        printf("\nLa cola esta vacia\n");
        return 1;
    }
    return 0;
}

void printQueue()
{
    int i = cola.frente;
    if (isEmptyCola() == 1)
    {
        return;
    }

    printf("Estado de la cola:\n");
    for (int j = 0; j < cola.size; j++)
    {
        printf("ID: %d | Peso: %d\n", cola.paquete[i].id, cola.paquete[i].peso);
        i = (i+1) % MAX;
    }
    printf("\n");
}

//Operaciones lista circular
void insertarFinal(Nodo **cabeza, Nodo **ultimo, Camion *camion)
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    nuevo->camion = *camion;
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

void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno)
{
    if (*cabeza == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    int cantidad = 0;
    Nodo *temp = *cabeza;
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
    Nodo *antes = *ultimo; //Pongo en ultimo por si se rompe el oop de una
    int exito = 0;
    int posicion = 1; //Para saber en que turno esta el camion
    do
    {
        if(temp->camion.id == id)
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
        Nodo *temp2 = *cabeza; //Para recorrer la nueva lista
        for (int i = 1; i < turno-1 ; i++)
        {
            temp2 = temp2->siguiente;
        }
        temp->siguiente = temp2->siguiente;
        temp2->siguiente = temp;
    }

    printf("Camion con ID: %d movido al turno %d\n", id, turno);
}

void mostrarCamiones(Nodo *cabeza, const char *mensaje)
{
    if (cabeza == NULL) //Sin esto crashea
    {
        printf("No hay camiones\n");
        return;
    }
    
    Nodo *temp = cabeza;
    printf("\n----- Camiones %s -----\n", mensaje);
    do
    {
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n",
        temp->camion.id, temp->camion.capacidad, temp->camion.carga, temp->camion.capacidad - temp->camion.carga);

        temp = temp->siguiente;
    } while (temp != cabeza);
    printf("\n");
}

void quitarCamion(Nodo **cabeza, Nodo **ultimo, int valor)
{
    if(*cabeza == NULL)
    {
        printf("No hay camiones\n");
        return;
    }
    Nodo *temp = *cabeza;
    Nodo *antes;
    int exito = 0;
    do
    {
        if(temp->camion.id == valor)
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

void liberar(Nodo *cabeza, Nodo *ultimo)
{
    Nodo *temp;
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
    printf("Memoria liberada correctamente");
}

//Operaciones pila
int push(Pila *pila, Paquete paquete)
{
    if (isFullPila(pila) == 1)
    {
        return 1;
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
        printf("\nLa pila esta vacia\n");
        return 1;
    }
    return 0;
}

void mostrar(Pila *pila)
{
    if (isEmptyPila(pila) == 1)
    {
        return;
    }
    printf("Estado de la pila:\n");
    for (int i = pila->tope; i >= 0; i--)
    {
        printf("ID: %d | Peso: %d\n", pila->paquete[i].id, pila->paquete[i].peso);
    }
    printf("\n");
}

//Asignar paquetes
void asignarPaquete(Nodo *cabeza, Nodo *ultimo, Pila *pila, int valor)
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

    //Para recorrer
    Nodo *temp = cabeza;
    Nodo *antes;
    int exito = 0;
    do
    {
        if(temp->camion.id == valor)
        {
            exito = 1;
            break;
        }
        antes = temp;
        temp = temp->siguiente;
    } while (temp != cabeza);
    
    if (exito == 0)
    {
        printf("No se encontro el camion con ID: %d\n", valor);
        return;
    }
    
    if (temp->camion.capacidad > temp->camion.carga && cola.paquete[cola.frente].peso < (temp->camion.capacidad - temp->camion.carga))
    {
        Paquete paquete = dequeue(); //Saco el paquete de la cola y lo almaceno en la variable local
        if (push(&temp->camion.pila, paquete) == 1)
        {
            return;
        }
        temp->camion.carga = paquete.peso + temp->camion.carga; 
        printf("Paquete con ID: %d se agrego al camion con ID: %d\n", paquete.id, temp->camion.id);
        return;
    }
    
    printf("Paquete con ID: %d NO se agrego al camion con ID: %d porque excede el peso.\nPeso paquete: %dkg. Espacio restante en el camion %d.\n"
    , cola.paquete[cola.frente].id, temp->camion.id, 
    cola.paquete[cola.frente].peso, temp->camion.capacidad - temp->camion.carga); //Las puse asi porque no salieron de la cola
}

void deshacerAsignacion(Nodo *cabeza, Nodo *ultimo, Pila *pila, int valor)
{    
    if(cabeza == NULL)
    {
        printf("No hay camiones\n");
        return;
    }
    
    Nodo *temp = cabeza;
    Nodo *antes;
    int exito = 0;
    do
    {
        if(temp->camion.id == valor)
        {
            exito = 1;
            break;
        }
        antes = temp;
        temp = temp->siguiente;
    } while (temp != cabeza);
    
    if (exito == 0)
    {
        printf("No se encontro el camion con ID: %d\n", valor);
        return;
    }

    if(isEmptyPila(&temp->camion.pila) == 1)
    {
        printf("No hay paquetes en el camion con ID: %d\n", temp->camion.id);
        return;
    }

    if(isFullPila(pila) == 1)
    {
        printf("La pila secundaria esta llena\n");
        return;
    }

    push(pila, pop(&temp->camion.pila)); //Lo pongo en una pila secundaria para no perder el paquete
    printf("Asignacion deshecha\n");
}

Camion* buscarCamion(Nodo *cabeza, int valor)
{
    if (cabeza == NULL) //Sin esto crashea
    {
        printf("No hay camiones\n");
        return NULL;
    }
    
    Nodo *temp = cabeza;
    do
    {
        if(temp->camion.id == valor)
        {
            return &temp->camion;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);

    printf("No se encontro el camion con ID: %d\n", valor);
    return NULL;

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

    printf("Entrega registrada\n");
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
    printf("Memoria liberada correctamente");
}