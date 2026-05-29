#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"

int confirmacion();
int noLetra(const char *letras, int *numero);

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
        printf("6. Registar entrega\n");
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
                if (registrarIdPaquete(id) == 1)
                {
                    printf("\nID ya registrado\n");
                    printf("Desea continuar con un ID nuevo para el registro de paquete?\n");
                    break;
                }
                while (noLetra("Peso del paquete en kg: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                insertarAtras(id, cantidad);
                printf("\n\n");
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
                while (noLetra("\nID del camion: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                if(registrarIdCamion(id) == 1) //Para no repetir
                {
                    printf("\nID ya registrado\n");
                    printf("Desea continuar con un ID nuevo para el registro de camion?\n");
                    break;
                }
                while (noLetra("Capacidad de carga en kg: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                Camion temp = {.id = id, .capacidad = cantidad, .carga = 0, .pila = {.tope = -1}};
                insertarFinal(&cabeza, &ultimo, &temp);
                mostrarCamiones(cabeza, "en la base");
                mostrarCamiones(cabezaF, "fuera de la base");
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
        if (cabezaF == NULL)
        {
            printf("No hay camiones fuera\n");
            break;
        }
        do //Submenu de confirmacion de opcion
        {
            opcionE = confirmacion(); //Se valida el caracter para el proceso
            switch (opcionE)
            {
            case 0:
                while (noLetra("\nID del camion: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                Nodo *temp = buscarCamion(cabezaF, id);
                if(temp == NULL)
                {
                    printf("\nCamion no encontrado.\n");
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                insertarFinal(&cabeza, &ultimo, &temp->camion);
                quitarCamion(&cabezaF, &ultimoF, id);
                printf("\nSe registro la llegada del Camion con ID: %d\n", ultimo->camion.id);
                mostrarCamiones(cabeza, "en la base");
                mostrarCamiones(cabezaF, "fuera de la base");
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
            break;
        }
        printf("Se quitara el camion con ID: %d de la base\nEsta seguro?\n", cabeza->camion.id);
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                insertarFinal(&cabezaF, &ultimoF, &cabeza->camion); //Copio el camion que esta adelante
                quitarCamion(&cabeza, &ultimo, cabeza->camion.id);
                printf("\nSe registro la salida del camion con ID: %d\n", ultimoF->camion.id);
                mostrarCamiones(cabeza, "en la base");
                mostrarCamiones(cabezaF, "fuera de la base");
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
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n\n",
        cabeza->camion.id, cabeza->camion.capacidad, cabeza->camion.carga, cabeza->camion.capacidad - cabeza->camion.carga);
        printf("Esta seguro de esta accion?\n");
        do
        {   
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                printf("\n");
                asignarPaquete(cabeza);
                printf("\n");
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
                    printf("\nCamion no encontrado.\n");
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                if (isEmptyPila(&temp->camion.pila) == 1)
                {
                    printf("\nNo hay paquetes en el camion con ID: %d\n", temp->camion.id);
                    printf("Desea buscar otro camion?\n");
                    break;
                }
                printf("\nFue exitosa la entrega del paquete con ID: %d?\n", temp->camion.pila.paquete[temp->camion.pila.tope].id);
                do
                {
                    cantidad = confirmacion(); //No quize hacer otra variable
                    switch (cantidad)
                    {
                    case 0:
                        registrarEntrega(&cabezaH, &temp->camion);
                        printf("\nEntrega registrada en el historial.\n");
                        cantidad = 1; //Para no volver al loop
                        break;

                    case 1:
                        deshacerAsignacion(temp); //Es el mismo proceso solo que en un camion especifico
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
        if (isEmptyPila(&cabeza->camion.pila) == 1)
        {
            printf("No hay paquetes en el camion con ID: %d\n", cabeza->camion.id);
            break;
        }
        printf("Camion al que se le quitara el ultimo paquete:\n");
        printf("ID: %d | Capacidad: %dkg | Carga: %dkg | Disponible: %dkg\n",
        cabeza->camion.id, cabeza->camion.capacidad, cabeza->camion.carga, cabeza->camion.capacidad - cabeza->camion.carga);
        printf("Esta seguro de esta accion?\n");
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                printf("\n");
                deshacerAsignacion(cabeza);
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
        if (cabeza == NULL)
        {
            printf("No hay camiones en la base\n");
            break;
        }
        do
        {
            opcionE = confirmacion();
            switch (opcionE)
            {
            case 0:
                printf("\nTurno actual de los camiones:\n");
                mostrarCamiones(cabeza, "en la base");
                while (noLetra("Camion que quiere rotar: ", &id) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                if (buscarCamion(cabeza, id) == NULL)
                {
                    printf("\nCamion no encontrado.\n");
                    printf("Desea ingresar otro ID?\n");
                    break;
                }
                while (noLetra("En que turno lo va a poner: ", &cantidad) == 0)//Verifica que no se pongan letras
                {
                    printf("Entrada invalida. Ingresa un numero entero mayor que 1.\n\n");
                }
                printf("\n");
                rotar(&cabeza, &ultimo, id, cantidad); //Cambia los turnos
                printf("\nTurno actual de los camiones:\n");
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
    char opcionSN[100]; //Para poder guardar mas caracteres en el buffer a limpiar
    printf("Confirmacion [s/n]\n");
    if (fgets(opcionSN, sizeof(opcionSN), stdin) == NULL) //Guarda el input como texto y ve que no este vacio
    {
        return -1;
    }
    int posicion = strcspn(opcionSN, "\n"); //Busca el salto de linea

    if (opcionSN[posicion] != '\n') //Limpio buffer si se pusieron mas caracteres
    {
        int limpiar;
        while ((limpiar = getchar()) != '\n' && limpiar != EOF);
    }

    opcionSN[posicion] = '\0'; //Quito salto de linea

    if (strcmp(opcionSN, "s") == 0 || strcmp(opcionSN, "S") == 0)
    {
        return 0;
    }
    else if (strcmp(opcionSN, "n") == 0 || strcmp(opcionSN, "N") == 0)
    {
         return 1;
    }
    return -1;//Para que al leer otros caracteres no haya errores
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