#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"

int confirmacion();
int noLetra(const char *letras, int *numero);

Pila pila = {.tope = -1}; //Pila de paquetes para meter en camion
//Camiones en la base
Nodo *cabeza = NULL;
Nodo *ultimo = NULL;
//Camiones fuera
Nodo *cabezaF = NULL;
Nodo *ultimoF = NULL;

Historial *cabezaH = NULL;

int main()
{
    int opcionM=0, id=0, cantidad=0, opcionE=0;//Opciones del menu

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
        while (noLetra("Opcion: ", &opcionM) == 0)//Verifica que no se pongan letras
        {
            printf("Entrada invalida. Ingresa un numero entre 1 y 10.\n\n");
        }
        printf("\n");
    
    switch (opcionM)
    {
    case 1: //Registrar paquete
        do //Submenu de confirmacion de opcion
        {
            opcionE = confirmacion(); //Se valida el caracter para el proceso
            switch (opcionE)
            {
            case 0:
                while (noLetra("\nID del paquete: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                if (buscarIdPaquete(id) == 1)
                {
                    printf("ID ya registrado\n\n");
                    printf("Desea continuar con el registro de paquete?\n");
                    break;
                }
                while (noLetra("Peso del paquete: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                insertarAtras(id, cantidad);
                printQueue();
                opcionE = 1; //Para no volver al loop
                break;
        
            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
        } while(opcionE != 1);
        break;
        
    case 2: //Registrar nuevo camion
        do //Submenu de confirmacion de opcion
        {
            opcionE = confirmacion(); //Se valida el caracter para el proceso
            switch (opcionE)
            {
            case 0:
                while (noLetra("ID del camion: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                if(registrarIdCamion(id, cabeza) == 1) //Para no repetir
                {
                    printf("ID ya registrado\n\n");
                    printf("Desea continuar con el registro de camion?\n");
                    break;
                }
                while (noLetra("Capacidad de carga en kg: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                Camion temp = {.id = id, .capacidad = cantidad, .carga = 0, .pila = {.tope = -1}};
                insertarFinal(&cabeza, &ultimo, &temp);
                printf("Camion con ID: %d registrado correctamente.\n", id);
                opcionE = 1; //Para no volver al loop
                break;

            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }        
        } while(opcionE != 1);
        break;

    case 3: //Registro llegada camion
        do //Submenu de confirmacion de opcion
        {
            if (cabezaF == NULL)
            {
            printf("No hay camiones fuera\n");
            opcionE = 1; //Para no volver al loop
            break;
            }
            opcionE = confirmacion(); //Se valida el caracter para el proceso
            switch (opcionE)
            {
            case 0:
                while (noLetra("ID del camion: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                Nodo *temp = buscarCamion(cabezaF, id);
                if(temp == NULL)
                {
                    printf("Camion no encontrado.\n\n");
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                insertarFinal(&cabeza, &ultimo, &temp->camion);
                quitarCamion(&cabezaF, &ultimoF, id);
                opcionE = 1; //Para no volver al loop
                break;

        case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }        
        } while(opcionE != 1);
        break;

    case 4: //Registro salida camion
        if (cabeza == NULL)
        {
            printf("No hay camiones en la base\n");
            opcionE = 1; //Para no volver al loop
            break;
        }
        printf("Se quitara el camion con ID: %d de la base\nEsta seguro? [s/n]: ", cabeza->camion.id);
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                insertarFinal(&cabezaF, &ultimoF, &cabeza->camion); //Copio el camion que esta adelante
                quitarCamion(&cabeza, &ultimo, cabeza->camion.id);
                opcionE = 1; //Para no volver al loop
                break;

            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
        } while(opcionE != 1);
        break;
    
    case 5: //Asignar paquete
        if (cabeza == NULL)
        {
            printf("No hay camiones en la base\n\n");
            break;
        }
        printf("Camion al que se le asignara el paquete del frente de la cola:\n");
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n",
        cabeza->camion.id, cabeza->camion.capacidad, cabeza->camion.carga, cabeza->camion.capacidad - cabeza->camion.carga);
        printf("Esta seguro de esta accion?\n");
        do
        {   
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                asignarPaquete(cabeza, &pila);
                mostrar(&cabeza->camion.pila);
                printQueue();
                opcionE = 1; //Para no volver al loop
                break;
            
            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
        } while(opcionE != 1);
        break;
        
    case 6: //Registrar entrega
        if (cabeza == NULL)
        {
            printf("No hay camiones en la base\n\n");
            break;
        }
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                while (noLetra("\nCamion que entrego el paquete: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                Nodo *temp = buscarCamion(cabeza, id);
                if (temp == NULL)
                {
                    printf("Camion no encontrado.\n\n");
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                if (isEmptyPila(&temp->camion.pila) == 1)
                {
                    printf("No hay paquetes en el camion con ID: %d\n", temp->camion.id);
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                printf("Fue exitosa la entrega del paquete con ID: %d?\n", temp->camion.pila.paquete[temp->camion.pila.tope].id);
                do
                {
                    cantidad = confirmacion(); //No quize hacer otra variable
                    switch (cantidad)
                    {
                    case 0:
                        registrarEntrega(&cabezaH, &temp->camion);
                        printf("Entrega registrada en el historial.\n");
                        cantidad = 1; //Para no volver al loop
                        break;

                    case 1:
                        deshacerAsignacion(temp, &pila); //Es el mismo proceso solo que en un camion especifico
                        printf("\nRegistro de entrega cancelado.\nEl paquete se regreso al frente de la cola.\n\n");
                        break;

                    default:
                        printf("Opcion invalida.\n\n");
                        break;
                    }
                } while (cantidad != 1);
                opcionE = 1; //Para no volver al loop
                break;

            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
            } while(opcionE != 1);
        break;
    
    case 7: //Deshacer ultima asignacion
        if (cabeza == NULL)
        {
            printf("No hay camiones en la base\n");
            break;
        }
        printf("Camion al que se le quitara el paquete en el tope de la pila:\n");
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n",
        cabeza->camion.id, cabeza->camion.capacidad, cabeza->camion.carga, cabeza->camion.capacidad - cabeza->camion.carga);
        printf("Esta seguro de esta accion?\n");
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                deshacerAsignacion(cabeza, &pila);
                opcionE = 1; //Para no volver al loop
                break;
                
            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
            } while(opcionE != 1);
        break;

    case 8:
        printf("\n===== REPORTES =====\n");
        printQueue();
        mostrarCamiones(cabeza, "en la base");
        mostrarCamiones(cabezaF, "fuera de la base");
        mostrarHistorial(cabezaH);
        break;
    
    case 9: //Rotar turno
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                printf("Turno actual de los camiones:\n");
                mostrarCamiones(cabeza, "en la base");
                while (noLetra("Camion que quiere rotar: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                if (buscarCamion(cabeza, id) == NULL)
                {
                    break;
                }
                while (noLetra("En que turno lo va a poner: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                rotar(&cabeza, &ultimo, id, cantidad); //Cambia los turnos
                printf("Turno actual de los camiones:\n");
                mostrarCamiones(cabeza, "en la base"); //Enseña el nuevo orden
                opcionE = 1; //Para no volver al loop
                break;
                
            case 1:
                printf("\nCerrando submenu.\n\n");
                break;

            default:
                printf("Opcion invalida.\n\n");
                break;
            }
            } while(opcionE != 1);
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
    liberar(cabezaF, ultimoF);
    liberarH(cabezaH);
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
    long valor = strtol(buffer, &fin, 10); //Convierte el texto en un numero

    if (fin == buffer || (*fin != '\n' && *fin != '\0')) //Fin debe apuntar al final si no habia letras
    {
        return 0;
    }
    if (valor < 1) //Evita numeros negativos
    {
        return 0;
    }
    *numero = (int)valor; //Regresa el valor que se obtuvo en la conversion
    return 1;
}