#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

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

    int vida, misiles, distancia, velocidad, contdecisiones, objeto, planeta, nivel = 0;
    char op, obstaculo[25];
    const int MAXVIDAS[4] = {2000, 1900, 1500, 1000}, MAXMISILES[4] = {8000, 7800, 7400, 6900};
    const int DESTMISILES[3] = {50, 60, 80}, DESTVIDAS[3] = {25, 30, 35}, CAPSULAS[3] = {5, 10, 15};
    const int NODESTMISILES[3] = {30, 40, 50}, NODESTVIDAS[3] = {15, 20, 30}, NOCAPSULAS[3] = {3, 7, 35};
    const int MAXDIST[3] = {10000, 8000, 6000}, MAXVEL[3] = {12000, 20000, 28000};

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
        vida = MAXVIDAS[nivel];
        misiles = MAXMISILES[nivel];
        contdecisiones = 1;

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
        printf("Si la distancia entre la nave y un obstaculo esta entre %d y %d km se DEBE evadir el obstaculo\n", MAXDIST[nivel] - 2000, MAXDIST[nivel]);
        printf("Si la distancia entre un obstaculo y la nave es menor a %d km la nave choca y pierde el juego\n", MAXDIST[nivel] - 2000);
        printf("Si la distancia entre la nave y el obstaculo es mayor a %d km la nave sigue su camino\n", MAXDIST[nivel]);
        printf("Si la distancia entre nave y objeto de interes es menor o igual a %d km se ganan %d caps. de vida (No importa la velocidad)\n", MAXDIST[nivel] - 4000, CAPSULAS[nivel]);
        printf("    - Si no se cumplen las condiciones se pierden %d capsulas de vida\n", CAPSULAS[nivel]);
        printf("La nave puede destruir obstaculos si la distancia es igual o menor a %d km\n", MAXDIST[nivel] - 2000);
        printf("    - Por cada obstaculo destruido se pierden %d caps. de vida y %d misiles\n", DESTVIDAS[nivel], DESTMISILES[nivel]);
        printf("    - Al intentar destruir un obstaculo sin respetar las condiciones se pierden %d caps. y %d misiles\n", NODESTVIDAS[nivel], NODESTMISILES[nivel]);
        printf("Pierdes si tienes menos de %d misiles o menos de %d caps. de vida\n", MAXMISILES[nivel + 1], MAXVIDAS[nivel + 1]);
        printf(WHITE "Presiona enter para continuar...");
        getch();
        printf("\e[1;1H\e[2J");

        while(misiles >= MAXMISILES[nivel + 1] && vida >= MAXVIDAS[nivel + 1] && contdecisiones <= 7)
        {
            //Generar una distancia y velocidad aleatoria
            distancia = (rand() % 15 + 1) * 1000;
            velocidad = (rand() % 30 + 1) * 1000;

            //Display
            printf(MAGENTA "CAPS. VIDA: %d  ",vida);
            printf(WHITE "|" CYAN "  VELOCIDAD: %d km/h  ", velocidad);
            printf(WHITE "|" YELLOW "  MISILES: %d\n", misiles);

            printf(RESET);	

            //Generar objeto al azar
            objeto = rand() % 2;

            //Si se generó un obstáculo
            if(objeto == 0)
            {

                //Mostrar el obstáculo de acuerdo al nivel
                switch(nivel)
                {
                    case 0:
                        //Como hay dos tipos de planeta, generar uno aleatoriamente
                        planeta = rand() % 2;
                        if(planeta == 0)
                            strcpy(obstaculo, BRIGHT_BLUE "PLANETA SIN VIDA");
                        else
                            strcpy(obstaculo, BRIGHT_GREEN "PLANETA CON VIDA");
                        break;
                    case 1:
                        strcpy(obstaculo, BLUE "ASTEROIDE");
                        break;
                    case 2:
                        strcpy(obstaculo, PURPLE "HOYO NEGRO");
                        break;
                }

                printf("Un %s" WHITE " se encuentra a %d km de distancia\n", obstaculo, distancia);

                //Obtener input del usuario    
                do
                {
                    printf("Que desea hacer?\n");
                    printf("Presione[E] para esquivar o [D] para destruir\n");
                    op = getch();

                    switch (op)
                    {
                        //Evitar un obstáculo
                        case 'E': case 'e':
                            if (distancia > MAXDIST[nivel] - 2000)
                                printf("Se esquivo el %s\n", obstaculo);
                            else
                            {
                                printf("Se ha estrellado con el %s\n", obstaculo);
                                vida = 0;
                            }
                            break;
                        //Destruir un obstáculo
                        case 'D': case 'd': 
                            if(nivel == 0 && planeta == 1) //Un planeta con vida, no se puede destruir
                            {
                                printf("Se ha estrellado con el %s\n", obstaculo);
                                vida = 0;
                            }
                            else if (distancia <= (MAXDIST[nivel] - 2000) && velocidad >= MAXVEL[nivel])
                            {
                                printf("Se destruyo el %s\n", obstaculo);
                                vida -= DESTVIDAS[nivel];
                                misiles -= DESTMISILES[nivel];
                            }
                            else
                            {
                                if(distancia > (MAXDIST[nivel] - 2000) && distancia <= MAXDIST[nivel] && velocidad >= MAXVEL[nivel])
                                {
                                    printf("Debiste haber esquivado\n");
                                    vida = 0;
                                }
                                else
                                {
                                    printf("No has podido destruir el %s\n", obstaculo);
                                    vida -= NODESTVIDAS[nivel];
                                    misiles -= NODESTMISILES[nivel];
                                }
                            }
                            break;
                        default:
                            printf("No presiono una opcion correcta.\n");
                            break;
                        }
                    }
                    while (op != 'e' && op != 'E' && op != 'D' && op != 'd');
            }
            //Si se generó un objeto de interés
            else
            {
                printf("Un " BRIGHT_RED "OBJETO DE INTERES " WHITE "se encuentra a %d km de distancia\n", distancia);
                //Obtener input del usuario
                do
                {
                    printf("Que desea hacer.\n");
                    printf("Presione [C] para capturar y [E] para esquivar\n");
                    op = getch();

                    switch (op)
                    {
                        //Decisiones para capturar o esquivar
                        case 'c': case 'C':
                            if(distancia <= MAXDIST[nivel] - 4000)
                            {
                                printf("Objeto capturado\n");
                                vida += CAPSULAS[nivel];
                            }
                            else
                            {
                                printf("Objeto no capturado\n");
                                vida -= NOCAPSULAS[nivel];
                            }
                            break;
                        case 'e': case 'E':
                            printf("Esquivaste la capsula\n");
                            break;
                        default:
                            printf("No presiono una opcion correcta.\n");
                            break;
                        }
                    } while (op != 'e' && op != 'E' && op != 'C' && op != 'c');
            }

            contdecisiones++;
            printf(WHITE "Presiona enter para continuar...");
            getch();
            printf("\e[1;1H\e[2J");
        } 

        //Compara la cantidad de misiles y de capsulas restantes y define si pierdes o ganas
        if (misiles >= MAXMISILES[nivel + 1] && vida >= MAXVIDAS[nivel + 1])
        {
            nivel++;
            op = 's';
            printf("Ganaste el nivel %d\n", nivel);
            printf(WHITE "Presiona enter para continuar...");
            getch();
            printf("\e[1;1H\e[2J");
        }
        else 
        {
            printf("Perdiste\n");  
            printf(MAGENTA "CAPS. VIDA: %d  ",vida);
            printf(WHITE "|" YELLOW "    MISILES: %d\n", misiles);  

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