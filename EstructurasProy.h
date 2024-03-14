#ifndef ESTRUCTURASPROY_H
#define ESTRUCTURASPROY_H
struct nave
{
    int capsvid;
    int misiles;
    int velocidad;
    int dist;
};

struct objeto
{
    short int esObstaculo;
    char* nombre;
    int maxDist;
    int misilesCorrecto;
    int misilesIncorrecto;
    int vidasCorrecto;
    int vidasIncorrecto;
};
#endif