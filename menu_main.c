#include <stdio.h>
#include <string.h>
#include "estructuras.h"

int confirmacion();

int main()
{
    int opcionM=0, opcionE=0, cantidad=0; //Opciones del menu
    char texto[100];//Nombre de paquete
    
    Camion camionChico, camionMedio, camionGrande;
    camionChico.capacidad = 100, camionMedio.capacidad = 500, camionGrande.capacidad = 1000;
    camionChico.carga = 0, camionMedio.carga = 0, camionGrande.carga = 0;
    camionChico.id = 1, camionMedio.id = 2, camionGrande.id = 3;

    Nodo *cabeza = NULL;
    Nodo *ultimo = NULL;
    insertarFinal(&cabeza, &ultimo, camionChico);
    insertarFinal(&cabeza, &ultimo, camionMedio);
    insertarFinal(&cabeza, &ultimo, camionGrande);

    printf("\n-----Gestor de paqueteria-----\n\n");
    do
    {
        printf("\n---------Menu---------\n");
        printf("1. Nuevo paquete\n");
        printf("2. Cargar paquetes desde un archivo\n");
        printf("3. Registrar llegada de camion\n");
        printf("4. Asignar paquetes\n");
        printf("5. Registar entregas\n");
        printf("6. Deshacer ultima asignacion\n");
        printf("7. Reporte de estado\n");
        printf("8. Rotar turno de camiones\n");
        printf("9. Salir\n");
        printf("Opcion: ");

        scanf("%d", &opcionM);
        getchar();
        printf("\n");

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
        Camion camion;
        printf("\nID del camion: ");
        scanf("%d", &opcionE);
        printf("\nCapacidad de carga en kg: ");
        scanf("%d", &cantidad);
        camion.id = opcionE, camion.capacidad = cantidad;
        insertarFinal(&cabeza, &ultimo, camion);
        break;
    
    case 4:
        printf("A que camion quieres asignar el paquete al frente de la cola: ");
        scanf("%d", &opcionE);
        asignarPaquete(cabeza, ultimo, opcionE);
        mostrar();
        printQueue();
        break;
        
    case 5:
        break;
    
    case 6:
        pop();
        break;

    case 7:
        printQueue();
        mostrar();
        break;
    
    case 8:
        printf("Turno actual de los camiones:\n");
        recorrer(cabeza);
        printf("Que camion quiere rotar? ");
        scanf("%d", &cantidad);
        getchar();
        printf("\nEn que turno lo va a pone: ");
        scanf("%d", &opcionE);
        getchar();
        rotar(&cabeza, &ultimo, cantidad, opcionE);
        printf("Turno actual de los camiones:\n");
        recorrer(cabeza);
        break;
        
    case 9:
        printf("Saliendo del programa.\n");
        break;

    default:
        printf("Opcion invalida.\n");
        break;
    }
    } while (opcionM != 9); //Termina el programa

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
