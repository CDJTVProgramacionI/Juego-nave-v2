#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "EstructurasProy.h"

#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define AQUA "\e[36m"
#define BRIGHT_GRAY "\e[37m"
#define GRAY "\e[90m"
#define BRIGHT_RED "\e[91m"
#define BRIGHT_GREEN "\e[92m"
#define BRIGHT_YELLOW "\e[93m"
#define BRIGHT_BLUE "\e[94m"
#define MAGENTA "\e[95m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"
#define RESET "\e[0m"


static HANDLE stdoutHandle;
static DWORD outModeInit;

void main()
{
    //La consola de windows acepte colores
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;
    
    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }
    
    //Establecer la semilla para números aleatorios
    //La función time() nos permite que sea más aleatorio el número
    srand(time(0));

    //Datos del jugador
    nave jugador = {0,0,0,0};

    //Obstáculos por nivel
    objeto* objetosPorNivel[3] = 
    {
        (objeto*)calloc(3, sizeof(objeto)),
        (objeto*)calloc(2, sizeof(objeto)),
        (objeto*)calloc(2, sizeof(objeto))
    };

    //Crear objetos nivel 1
    objetosPorNivel[0][0].esObstaculo = 0;
    objetosPorNivel[0][0].nombre = BRIGHT_RED "OBJETO DE INTERES";
    objetosPorNivel[0][0].maxDist = 6000;
    objetosPorNivel[0][0].vidasCorrecto = 5;
    objetosPorNivel[0][0].vidasIncorrecto = 3;

    objetosPorNivel[0][1].esObstaculo = 1;
    objetosPorNivel[0][1].nombre = BRIGHT_BLUE "PLANETA SIN VIDA";
    objetosPorNivel[0][1].maxDist = 10000;
    objetosPorNivel[0][1].misilesCorrecto = 50;
    objetosPorNivel[0][1].misilesIncorrecto = 25;
    objetosPorNivel[0][1].vidasCorrecto = 25;
    objetosPorNivel[0][1].vidasIncorrecto = 15;

    objetosPorNivel[0][2].esObstaculo = 1;
    objetosPorNivel[0][2].nombre = BRIGHT_GREEN "PLANETA CON VIDA";
    objetosPorNivel[0][2].maxDist = 10000;
    
    //Crear objetos nivel 2
    objetosPorNivel[1][0].esObstaculo = 0;
    objetosPorNivel[1][0].nombre = BRIGHT_RED "OBJETO DE INTERES";
    objetosPorNivel[1][0].maxDist = 4000;
    objetosPorNivel[1][0].vidasCorrecto = 10;
    objetosPorNivel[1][0].vidasIncorrecto = 7;

    objetosPorNivel[1][1].esObstaculo = 1;
    objetosPorNivel[1][1].nombre = BLUE "ASTEROIDE";
    objetosPorNivel[1][1].maxDist = 8000;
    objetosPorNivel[1][1].misilesCorrecto = 60;
    objetosPorNivel[1][1].misilesIncorrecto = 40;
    objetosPorNivel[1][1].vidasCorrecto = 30;
    objetosPorNivel[1][1].vidasIncorrecto = 20;

    //Crear objetos nivel 3
    objetosPorNivel[2][0].esObstaculo = 0;
    objetosPorNivel[2][0].nombre = BRIGHT_RED "OBJETO DE INTERES";
    objetosPorNivel[2][0].maxDist = 2000;
    objetosPorNivel[2][0].vidasCorrecto = 15;
    objetosPorNivel[2][0].vidasIncorrecto = 35;

    objetosPorNivel[2][1].esObstaculo = 1;
    objetosPorNivel[2][1].nombre = PURPLE "HOYO NEGRO";
    objetosPorNivel[2][1].maxDist = 6000;
    objetosPorNivel[2][1].misilesCorrecto = 80;
    objetosPorNivel[2][1].misilesIncorrecto = 50;
    objetosPorNivel[2][1].vidasCorrecto = 35;
    objetosPorNivel[2][1].vidasIncorrecto = 30;

    short int max_objetos = 3, nivel = 0, contdecisiones = 0;
    int distancia,supera=0;
    objeto *objeto_actual;
    char op;
    const int MAXVIDAS[4] = {2000, 1900, 1500, 1000}, MAXMISILES[4] = {8000, 7800, 7400, 6900};
    const int MAXVEL[3][2]={{9,12},{9,20},{13,28}};
    int dist_obstaculos[7];

    //Pantalla principal
    printf(" ______     ______     __   __   ______           __    __     ______     ______     ______\n");    
    printf("/\\  ___\\   /\\  __ \\   /\\ \\ / /  /\\  ___\\         /\\ \"-./  \\   /\\  __ \\   /\\  == \\   /\\  ___\\\n");   
    printf("\\ \\___  \\  \\ \\  __ \\  \\ \\ \\'/   \\ \\  __\\         \\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\  __<   \\ \\___  \\\n");  
    printf(" \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\__|    \\ \\_____\\        \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\/\\_____\\\n"); 
    printf("  \\/_____/   \\/_/\\/_/   \\/_/      \\/_____/         \\/_/  \\/_/   \\/_/\\/_/   \\/_/ /_/   \\/_____/\n\n"); 
                                                                                               

    printf("                                            @@@@\n");
    printf("                                          @@@@@@@@\n");
    printf("                                          @@....@@\n");
    printf("                                         @@@.....@@\n");
    printf("                                         @@.@@@@.@@\n");
    printf("                                       @@@@......@@@@\n");
    printf("                                     @@@@@@@@@@@@@@@@@@              PROGRAMACION I\n");
    printf("                                     @@@@.@......@.@@@@       Segundo examen departamental\n");
    printf("                                     @@@@.@......@.@@@@             Huerta Johana\n");
    printf("                                     @@@@.@@@@@@@@.@@@@             Garcia Viridiana\n");
    printf("                                   @@@@@..@......@..@@@@@           Garcia Tania\n");
    printf("                                  @@@@@...@.@..@.@....@@@@@         Gomez Camila\n");
    printf("                                 @@@@@....@.@..@.@.....@@@@         Rosas Daniel\n");
    printf("                               @@@@@......@.@..@.@......@@@@@\n");
    printf("                             @@@@@........@......@........@@@@@\n");
    printf("                             @@@@.........@@@@@@@@.........@@@@\n");
    printf("                             @@@@....@@..@@@@@@@@@@..@@....@@@@\n");
    printf("                              @@.@@@@@@.@....@@....@.@@@@@@.@@\n");
    printf("                              @@@@@@@@@@@....@@....@.@@@@@@@@@\n");
    printf("                                       @@@@@@@@@@@@@@\n");

    printf(WHITE "Presiona enter para continuar...");
    getch();
    printf("\e[1;1H\e[2J");

    //Instrucciones
    printf("Instrucciones\n");
    printf("En este juego podras realizar diferentes jugadas, esquivar, atacar o capturar\n");
    printf(WHITE "Presiona enter para continuar...");
    getch();
    printf("\e[1;1H\e[2J");

    do
    {
        //Valores iniciales de vidas, velocidad y misiles
        jugador.capsvid = MAXVIDAS[nivel];
        jugador.misiles = MAXMISILES[nivel];
        jugador.velocidad = MAXVEL[nivel][1] * 1000;
        jugador.dist = 0;
        max_objetos = nivel == 0 ? 3 : 2;
        contdecisiones = 1;
        op = 'c';
        supera=0;

        //Generar 7 distancias
        for(int i = 0; i < 7; i++)
        {
            if(i == 0)
            {
                dist_obstaculos[0] = (rand()%8) + 5;
            }
            else
            {
                dist_obstaculos[i] = (rand()%8) + (dist_obstaculos[i-1]) + 1;
            }
        }

        //Instrucciones de nivel
        printf("NIVEL %d\n", nivel + 1);
        printf("En este nivel, te enfrentaras a:\n");
        switch(nivel)
        {
            case 0: 
                printf("Los " BRIGHT_GREEN "PLANETAS CON VIDA " WHITE "que no pueden ser destruidos\n");
                printf("y los " BRIGHT_BLUE "PLANETAS SIN VIDA " WHITE "que pueden ser destruidos.\n");
                break;
            case 1:
                printf("Los " BLUE "ASTEROIDES\n");
                break;
            case 2:
                printf("Los " PURPLE "HOYOS NEGROS\n");
                break;
        }

        printf(WHITE "Iniciaras con %d caps. de vida y %d misiles\n", MAXVIDAS[nivel], MAXMISILES[nivel]);
        printf("Si la distancia entre la nave y un obstaculo esta entre %d y %d km se DEBE evadir el obstaculo\n", objetosPorNivel[nivel][1].maxDist - 2000, objetosPorNivel[nivel][1].maxDist);
        printf("Si la distancia entre un obstaculo y la nave es menor a %d km la nave choca y pierde el juego\n", objetosPorNivel[nivel][1].maxDist - 2000);
        printf("Si la distancia entre la nave y el obstaculo es mayor a %d km la nave sigue su camino\n", objetosPorNivel[nivel][1].maxDist);
        printf("Si la distancia entre nave y objeto de interes es menor o igual a %d km se ganan %d caps. de vida (No importa la velocidad)\n", objetosPorNivel[nivel][0].maxDist, objetosPorNivel[nivel][0].vidasCorrecto);
        printf("    - Si no se cumplen las condiciones se pierden %d capsulas de vida\n", objetosPorNivel[nivel][0].vidasIncorrecto);
        printf("La nave puede destruir obstaculos si la distancia es igual o menor a %d km\n", objetosPorNivel[nivel][1].maxDist - 2000);
        printf("    - Por cada obstaculo destruido se pierden %d caps. de vida y %d misiles\n", objetosPorNivel[nivel][1].vidasCorrecto, objetosPorNivel[nivel][1].misilesCorrecto);
        printf("    - Al intentar destruir un obstaculo sin respetar las condiciones se pierden %d caps. y %d misiles\n", objetosPorNivel[nivel][1].vidasIncorrecto, objetosPorNivel[nivel][1].misilesIncorrecto);
        printf("Pierdes si tienes menos de %d misiles o menos de %d caps. de vida\n", MAXMISILES[nivel + 1], MAXVIDAS[nivel + 1]);
        printf(WHITE "Presiona enter para continuar...");
        getch();
        printf("\e[1;1H\e[2J");

        while(jugador.misiles >= MAXMISILES[nivel + 1] && jugador.capsvid >= MAXVIDAS[nivel + 1] && contdecisiones <= 7)
        {
            //Si ya avanzó 100 km, variar la velocidad aleatoriamente
            if (jugador.dist - supera >= 100)
            {
                supera=jugador.dist; //Aqui va guardando la distancia 
                jugador.velocidad=(rand() % MAXVEL[nivel][0] + MAXVEL[nivel][1]) * 1000;
            }
            
            //Calcular distancia
            distancia = (dist_obstaculos[contdecisiones - 1])*1000 - jugador.dist;

            //Display
            printf(MAGENTA "CAPS. VIDA: %d  ", jugador.capsvid);
            printf(WHITE "|" CYAN "  VELOCIDAD: %d km/h  ",jugador.velocidad);
            printf(WHITE "|" YELLOW "  MISILES: %d\n", jugador.misiles);

            printf(RESET);	

            //Generar objeto al azar
            if(op == 'E' || op == 'e' || op == 'c' || op == 'C' || op == 'D' || op == 'd')
                objeto_actual = &objetosPorNivel[nivel][rand()%max_objetos];

            //Mostrar objeto generado
            printf("Un %s" WHITE " se encuentra a %d km de distancia\n", objeto_actual->nombre, distancia);

            //Si se generó un obstáculo
            if(objeto_actual->esObstaculo)
            {
                //Obtener input del usuario    
                do
                {
                    printf("Que desea hacer?\n");
                    printf("Presione [S] para seguir adelante, [E] para esquivar o [D] para destruir\n");
                    op = getch();

                    switch (op)
                    {
                        case 's': case 'S':
                            if(distancia <= objeto_actual->maxDist - 2000 || (distancia < objeto_actual->maxDist && jugador.velocidad >= (MAXVEL[nivel][1]*1000)))
                            {
                                jugador.capsvid = 0;
                                printf("Se ha estrellado con el %s\n", objeto_actual->nombre);
                            }
                            else
                                jugador.dist += 25;
                            break;
                        //Evitar un obstáculo
                        case 'E': case 'e':
                            if (distancia > objeto_actual->maxDist - 2000)
                                printf("Se esquivo el %s\n", objeto_actual->nombre);
                            else
                            {
                                printf("Se ha estrellado con el %s\n", objeto_actual->nombre);
                                jugador.capsvid = 0;
                            }
                            jugador.dist += distancia;
                            contdecisiones++;
                            break;
                        //Destruir un obstáculo
                        case 'D': case 'd': 
                            //Un planeta con vida, no se puede destruir
                            if(strcmp(BRIGHT_GREEN "PLANETA CON VIDA", objeto_actual->nombre) == 0)
                            {
                                printf("Se ha estrellado con el %s\n", objeto_actual->nombre);
                                jugador.capsvid = 0;
                            }
                            else if (distancia <= (objeto_actual->maxDist - 2000) && jugador.velocidad >= (MAXVEL[nivel][1] * 1000))
                            {
                                printf("Se destruyo el %s\n", objeto_actual->nombre);
                                jugador.capsvid -= objeto_actual->vidasCorrecto;
                                jugador.misiles -= objeto_actual->misilesCorrecto;
                            }
                            else
                            {
                                if(distancia > (objeto_actual->maxDist - 2000) && distancia < objeto_actual->maxDist && jugador.velocidad >= (MAXVEL[nivel][1] * 1000))
                                {
                                    printf("Debiste haber esquivado\n");
                                    jugador.capsvid = 0;
                                }
                                else
                                {
                                    printf("No has podido destruir el %s\n", objeto_actual->nombre);
                                    jugador.capsvid -= objeto_actual->vidasIncorrecto;
                                    jugador.misiles -= objeto_actual->misilesIncorrecto;
                                }
                            }
                            contdecisiones++;
                            jugador.dist += distancia;
                            break;
                        default:
                            printf("No presiono una opcion correcta.\n");
                            break;
                        }
                    }
                    while (op != 'e' && op != 'E' && op != 'D' && op != 'd' && op != 's' && op != 'S');
            }
            //Si se generó un objeto de interés
            else
            {
                //Obtener input del usuario
                do
                {
                    printf("Que desea hacer.\n");
                    printf("Presione [C] para capturar y [S] para seguir adelante\n");
                    op = getch();

                    switch (op)
                    {
                        //Decisiones para capturar o esquivar
                        case 'c': case 'C':
                            if(distancia <= objeto_actual->maxDist)
                            {
                                printf("Objeto capturado\n");
                                jugador.capsvid += objeto_actual->vidasCorrecto;
                            }
                            else
                            {
                                printf("Objeto no capturado\n");
                                jugador.capsvid -= objeto_actual->vidasIncorrecto;
                            }
                            contdecisiones++;
                            jugador.dist += distancia;
                            break;
                        case 's': case 'S':
                            //Se saltó la capsula por completo
                            if(distancia <= 25)
                            {
                                //Ir al siguiente obstáculo
                                op = 'c';
                                contdecisiones++;
                            }
                            jugador.dist += 25;
                            break;
                        default:
                            printf("No presiono una opcion correcta.\n");
                            break;
                        }
                    } while (op != 's' && op != 'S' && op != 'C' && op != 'c' && op != 's' && op != 'S');
            }

            printf(WHITE "Presiona enter para continuar...");
            getch();
            printf("\e[1;1H\e[2J");
        } 

        //Compara la cantidad de misiles y de capsulas restantes y define si pierdes o ganas
        if (jugador.misiles >= MAXMISILES[nivel + 1] && jugador.capsvid >= MAXVIDAS[nivel + 1])
        {
            nivel++;
            op = 's';
            printf("Ganaste el nivel %d\n", nivel);
            printf(WHITE "Presiona enter para continuar...");
            getch();
            printf("\e[1;1H\e[2J");
            free(objetosPorNivel[nivel]);
        }
        else 
        {
            printf("Perdiste\n");  
            printf(MAGENTA "CAPS. VIDA: %d  ", jugador.capsvid);
            printf(WHITE "|" YELLOW "    MISILES: %d\n", jugador.misiles);  

            //obtener input del usuario
            do
            {
                printf(WHITE "Deseas continuar? [s/n]\n");
                op = getch();
                printf("\e[1;1H\e[2J"); //Borrar pantalla

                if(op != 's' && op != 'S' && op != 'N' && op != 'n')
                    printf("No presiono una opcion correcta\n");
            } while (op != 's' && op != 'S' && op != 'N' && op != 'n');
        } 
    }
    while((op == 's' || op == 'S') && nivel < 3);

    printf("FIN DEL JUEGO\n");  
    printf(WHITE "Presiona enter para continuar...");
    getch();
    printf("\e[1;1H\e[2J");
}