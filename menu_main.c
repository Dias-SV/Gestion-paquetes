#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"

int confirmacion();
int noLetra(const char *letras, int *numero);

Pila pila = {.tope = -1}; //Pila de paquetes para meter en camion
Pila pilaD = {.tope = -1}; //Pila de paquetes desasignados para poder volver a asignar
//Camiones en la base
Nodo *cabeza = NULL;
Nodo *ultimo = NULL;
//Camiones fuera
Nodo *cabezaF = NULL;
Nodo *ultimoF = NULL;

int main()
{
    int opcionM=0, id=0, cantidad=0, opcionE=0;//opciones del menu
    char texto[100];//Nombre de paquete
    
    Camion camion, camionChico, camionMedio, camionGrande;
    camionChico.capacidad = 100, camionMedio.capacidad = 500, camionGrande.capacidad = 1000;
    camionChico.carga = 0, camionMedio.carga = 0, camionGrande.carga = 0;
    camionChico.id = 1, camionMedio.id = 2, camionGrande.id = 3;

    Historial *cabezaH = NULL;
    insertarFinal(&cabeza, &ultimo, &camionChico);
    insertarFinal(&cabeza, &ultimo, &camionMedio);
    insertarFinal(&cabeza, &ultimo, &camionGrande);

    printf("\n-----Gestor de paqueteria-----\n\n");
    do
    {
        printf("\n---------Menu---------\n");
        printf("1. Nuevo paquete\n");
        printf("2. Registrar nuevo camion\n");
        printf("3. Registrar llegada de camion\n");
        printf("4. Registrar salida de camion\n");
        printf("5. Asignar paquetes\n");
        printf("6. Registar entregas\n");
        printf("7. Deshacer ultima asignacion\n");
        printf("8. Reporte de estado\n");
        printf("9. Rotar turno de camiones\n");
        printf("10. Salir\n");
        printf("Opcion: ");

        scanf("%d", &opcionM);
        getchar();
        printf("\n");
    


    switch (opcionM)
    {
    case 1:
        do //Submenu de confirmacion de opcion
        {
            opcionE = confirmacion(); //Se valida el caracter para el proceso
            switch (opcionE)
            {
            case 0:
                while (noLetra("ID del paquete: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                while (noLetra("Peso del paquete: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                enqueue(id, cantidad);
                printQueue();
                opcionE = 1; //Para no volver al loop
                break;
        
            case 1:
                printf("\nCerrando submenu.\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
        } while (opcionE != 1);
        break;
        
    case 2:
        while (noLetra("ID del camion: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        while (noLetra("Capacidad de carga en kg: ", &cantidad) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        camion.id = id, camion.capacidad = cantidad;
        insertarFinal(&cabeza, &ultimo, &camion);
        break;

    case 3:
        while (noLetra("ID del camion: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        if (buscarCamion(cabeza, id) == NULL)
        {
            break;
        }
        insertarFinal(&cabeza, &ultimo, buscarCamion(cabezaF, id));
        break;

    case 4:
        while (noLetra("ID del camion: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        if (buscarCamion(cabeza, id) == NULL)
        {
            break;
        }
        insertarFinal(&cabezaF, &ultimoF, buscarCamion(cabeza, id));
        break;
    
    case 5:
        while (noLetra("A que camion quieres asignar el paquete al frente de la cola: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        if (buscarCamion(cabeza, id) == NULL)
        {
            break;
        }
        asignarPaquete(cabeza, ultimo, &pila, id);
        mostrar(&pila);
        printQueue();
        break;
        
    case 6:
        while (noLetra("Camion que entrego el paquete: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        if (buscarCamion(cabeza, id) == NULL)
        {
            break;
        }
        registrarEntrega(&cabezaH, buscarCamion(cabeza, id));
        break;
    
    case 7:
        while (noLetra("A que camion quieres quitarle el ultimo paquete: ", &id) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
        }
        if (buscarCamion(cabeza, id) == NULL)
        {
            break;
        }
        deshacerAsignacion(cabeza, ultimo, &pila, id);
        break;

    case 8:
        printQueue();
        mostrar(&pila);
        break;
    
    case 9:
        printf("Turno actual de los camiones:\n");
        recorrer(cabeza);
        printf("Que camion quiere rotar? ");
        scanf("%d", &cantidad);
        getchar();
        printf("\nEn que turno lo va a pone: ");
        scanf("%d", &id);
        getchar();
        rotar(&cabeza, &ultimo, cantidad, id);
        printf("Turno actual de los camiones:\n");
        recorrer(cabeza);
        break;
        
    case 10:
        printf("Saliendo del programa.\n");
        break;

    default:
        printf("Opcion invalida.\n");
        break;
    }
    } while (opcionM != 10); //Termina el programa

    liberar(cabeza, ultimo);
    return 0;
}


//Para no equivocarse de opcion
int confirmacion()
{
    char opcionSN[3];
    printf("Confirmacion [s/n]\n");
    fgets(opcionSN, sizeof(opcionSN), stdin);
    opcionSN[strcspn(opcionSN, "\n")] = '\0'; //Quita salto de lines
    if (strcmp(opcionSN, "s") == 0 || strcmp(opcionSN, "S") == 0)
    {
        return 0;
    }
    else if (strcmp(opcionSN, "n") == 0 || strcmp(opcionSN, "N") == 0)
    {
         return 1;
    }
    else
    {
        return -1;//Para que al leer otros caracteres no haya errores
    }
}

int noLetra(const char *letras, int *numero)
{
    char buffer[20];
    printf("%s", letras);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) //Guarda el input como texto
        return 0;

    char *fin;
    long valor = strtol(buffer, &fin, 10); //Trata de convertir el texto en un numero, el puntero para donde para la conversion

    if (fin == buffer || (*fin != '\n' && *fin != '\0')) //Fin debe apuntar al final si no habia letras
    {
        return 0;
    }
    if (valor < 1 || valor > 1000000) //Limite para evitar numeros muy grandes o negativos
    {
        return 0;
    }
    *numero = (int)valor; //Regresa el valor que se obtuvo en la conversion
    return 1;
}