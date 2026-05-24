#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

Cola cola;
Camion camion;
Pila pila = {.tope = -1};

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

void peek()
{
    if (isEmptyCola() == 0)
    {
        printf("%d", cola.paquete[cola.final].id);
    }
}

void printQueue()
{
    int i = cola.frente;
    if (isEmptyCola() == 1)
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

void recorrer(Nodo *cabeza) //Solo para checar
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

//Operaciones pila
int push(Paquete paquete)
{
    if (isFullPila() == 1)
    {
        return 1;
    }
    
    pila.tope++;
    pila.paquete[pila.tope] = paquete;
    return 0;
}

int pop()
{
    if (isEmptyPila() == 1)
    {
        return 1;
    }

    pila.tope--;
    return 0;
}

int isFullPila()
{
    if (pila.tope >= MAX-1)
    {
        printf("\nLa pila esta llena\n");
        return 1;
    }
    return 0;
}

int isEmptyPila()
{
    if (pila.tope <= -1)
    {
        printf("\nLa pila esta vacia\n");
        return 1;
    }
    return 0;
}

void mostrar()
{
    printf("Estado de la pila:\n");
    for (int i = pila.tope; i >= 0; i--)
    {
        printf("ID: %d Peso: %d\n", pila.paquete[i].id, pila.paquete[i].peso);
    }
    printf("\n");
}

//Asignar paquetes
void asignarPaquete(Nodo *cabeza, Nodo *ultimo, int valor)
{
    if (isEmptyCola() == 1)
    {
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
    if (cabeza == NULL) //Sin esto crashea
    {
        printf("La lista esta vacia\n");
        return;
    }
    
    if (temp->camion.capacidad > temp->camion.carga && cola.paquete[cola.frente].peso < (temp->camion.capacidad - temp->camion.carga))
    {
        if (push(dequeue()) == 1)
        {
            return;
        }
        temp->camion.carga = pila.paquete[pila.tope].peso + temp->camion.carga;
        printf("Paquete con ID: %d se agrego al camion con ID: %d\n", pila.paquete[pila.tope].id, temp->camion.id);
        return;
    }
    
    printf("Paquete con ID: %d NO se agrego al camion con ID: %d porque excede el peso.\nPeso paquete: %dkg. Espacio restante en el camion %d.\n"
    , cola.paquete[cola.frente].id, temp->camion.id, pila.paquete[pila.tope].peso, temp->camion.capacidad - temp->camion.carga);
}