#include <stdio.h>
#include <string.h>
#include "cola_pila.h"

int confirmacion();

int main()
{
    int opcionM=0, opcionE=0, cantidad=0; //Opciones del menu
    char texto[100];//Nombre de paquete
    
    Camion camionChico, camionMedio, camionGrande;
    camionChico.carga = 100;
    camionMedio.carga = 500;
    camionGrande.carga = 1000;

    Cola cola;
    cola.size = 0, cola.frente = 0, cola.final = 0;

    printf("\n-----Gestor de paqueteria-----\n\n");
    do
    {
        printf("\n---------Menu---------\n");
        printf("1. Nuevo paquete\n");
        printf("2. Asignar paquetes\n");
        printf("3. Registar entregas\n");
        printf("4. Deshacer ultima asignacion\n");
        printf("5. Reporte de estado\n");
        printf("6. Rotar turno de camiones\n");
        printf("7. Salir\n");
        printf("Opcion: ");

        scanf("%d", &opcionM);
        getchar();

    switch (opcionM)
    {
    case 1:
        printf("ID del paquete: ");
        scanf("%d", &opcionE);
        printf("Peso del paquete: ");
        scanf("%d", &cantidad);
        enqueue(opcionE, cantidad);
        printQueue();
        break;

    case 2:
        break;
    
    case 3:
        break;
        
    case 4:
        break;
    
    case 5:
        break;

    case 6:
        break;
    
    case 7:
        printf("Saliendo del programa.\n");
        break;

    default:
        printf("Opcion invalida.\n");
        break;
    }
    } while (opcionM != 7); //Termina el programa

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
