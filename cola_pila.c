#include <stdio.h>
#include <stdlib.h>
#include "cola_pila.h"

Cola cola;

Paquete* nuevoPaquete(int id, int peso)
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

int enqueue (int id, int peso)
{
    if (isFull(MAX) == 1)
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
    cola.peso = cola.peso + peso;
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
