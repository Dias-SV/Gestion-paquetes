#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

Cola cola;
Camion camion;

Paquete* nuevoPaquete(int id, int peso) //En apuntadores para no necesitar un arreglo
{
    Paquete *nuevo = malloc(sizeof(Paquete));
    if (nuevo == NULL)
    {
        return NULL;
    }
    nuevo->id = 
    nuevo->peso = peso;
    return nuevo;
}

//Operaciones para cola
int enqueue (int id, int peso)
{
    if (isFull() == 1)
    {
        return 1;
    }

    Paquete *nuevo = nuevoPaquete(id, peso);
    if(nuevo == NULL) //Verficacion
    {
        printf("Error de memoria\n");
        return 1;
    }

    cola.paquete[cola.final] = *nuevo;
    cola.final = (cola.final + 1) % MAX;
    cola.size++;
    return 0;
    
}

int dequeue()
{
    if (isEmpty() == 1)
    {
        return 1;
    }

    cola.frente = (cola.frente + 1) % MAX;
    cola.size--;
    return 0;
}

int isFull()
{
    if (cola.size == MAX)
    {
        printf("\nLa cola esta llena\n");
        return 1;
    }
    return 0;
}

int isEmpty()
{
    if (cola.size == 0)
    {
        printf("\nLa cola esta vacia\n");
        return 1;
    }
    return 0;
}

void peek()
{
    if (isEmpty() == 0)
    {
        printf("%d", cola.paquete[cola.final]);
    }
}

void printQueue()
{
    int i = cola.frente;
    if (isEmpty() == 1)
    {
        return;
    }

    printf("\nEstado de la cola:\n");
    for (int j = 0; j < cola.size; j++)
    {
        printf("ID: %d  ", cola.paquete[i].id);
        printf("Peso: %d\n", cola.paquete[i].peso);
        i = (i+1) % MAX;
    }
    printf("\n");
}

//Operaciones lista circular
void insertarInicio(Nodo **cabeza, Nodo **ultimo, Camion camion) //Creo que esto no lo necesito
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->camion = camion;
    if (*cabeza == NULL) //Para el primer valor todos apuntan a lo mismo
    {
        nuevo->siguiente = nuevo;
        *ultimo = nuevo;
    }
    else
    {
        nuevo->siguiente = *cabeza;
    }
    *cabeza = nuevo;
    (*ultimo)->siguiente = *cabeza;

    
}

void rotar(Nodo **cabeza, Nodo **ultimo, int id, int turno)
{
    Nodo *temp = *cabeza;
    Nodo *antes;
    int exito = 0;
    do
    {
        if(temp->camion.id == id)
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

    switch (turno) //Todo esto depende de que solo sean 3 turnos y 3 camiones, agrega mas y se va a la mierda
    {
    case 1: //Matutino, turno 1
        if (temp == *cabeza)
        {
            printf("El camion ya se encuentra en el turno matutino\n");
        }
        else
        {
            *cabeza = temp; //Solo hago que sea el primero
            *ultimo = antes; //Para manterner la circularidad correctamente
            printf("El camion con ID: %d ahora esta en el turno matutino\n", temp->camion.id);
        }
        break;

    case 2: //Vespertino, turno 2
        if (temp != *cabeza && temp != *ultimo )
        {
            printf("El camion ya se encuentra en el turno vespertino\n");
        }
        else
        {
            *cabeza = antes; //Creo que esto no lo necesito explicar
            *ultimo = temp->siguiente;
            printf("El camion con ID: %d ahora esta en el turno vespertinoo\n", temp->camion.id);
        }
        break;

    case 3: //Nocturno, turno 3
        if (temp == *ultimo)
        {
            printf("El camion ya se encuentra en el turno nocturno\n");
        }
        else
        {
            *ultimo = temp;
            *cabeza = temp->siguiente;
            printf("El camion con ID: %d ahora esta en el turno nocturno\n", temp->camion.id);
        }
        break;
    
    default:
        break;
    }
    
}

void recorrer(Nodo *cabeza)
{
    if (cabeza == NULL) //Sin esto crashea
    {
        printf("La lista se vacio\n");
        return;
    }
    
    Nodo *temp = cabeza;
    printf("ID: ");
    do
    {
        printf("%d -> ", temp->camion.id);
        temp = temp->siguiente;
    } while (temp != cabeza);
    printf("\n");
}

//Puse ultimo porque si se elimina la cabeza se pierde la circularidad

void eliminar(Nodo **cabeza, Nodo **ultimo, int valor)
{
    Nodo *temp = *cabeza;
    Nodo *antes;
    int exito = 0;
    do
    {
        if(temp->camion.carga == valor)
        {
            exito = 1;
            break;
        }
        antes = temp;
        temp = temp->siguiente;
    } while (temp != *cabeza);
    
    if (exito == 0)
    {
        printf("No se encontro el valor\n");
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

    free (temp);
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