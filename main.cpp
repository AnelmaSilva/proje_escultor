#include <iostream>
#include "escultor.h"

using namespace std;

int main()
{
    int c;

    escultor t1(150,150, 150);

    t1.setCor(0.502, 0.502, 0.502, 1.0);
    t1.putVoxel(0,0,0);
    t1.putBox(0,50,0,30,0,24);

    for(c=0; c<=5;  c++)
    {
        t1.cutBox((44+c), 50, (29-c), 30-c, 0, 24);
        t1.cutBox(0, 6-c, (29-c), 30-c, 0, 24);
        t1.cutBox(0, (6-c), (0+c), 1+c, 0, 24);
        t1.cutBox((44+c), 50, (0+c), 1+c, 0, 24);

    }

    for(c=0; c<=4;  c++)
    {
        t1.cutBox((6-c), (45+c), (29-c), 30-c, 19+c, 24);
        t1.cutBox((6-c), (45+c), (0+c), 1+c, 19+c, 24);
        t1.cutBox((6-c), (45+c), (29-c), 30-c, 0, 5-c);
        t1.cutBox((6-c), (45+c), (0+c), 1+c, 0, 5-c);

    }

    t1.setCor(0.5882, 0.2941, 0.0,1.0);
    t1.putBox(22,28,30,80,9,14);

    for(c = 30; c<80; c+=3)
    {
        t1.cutBox(22,28,c, c+1,9,10);
        t1.cutBox(22,28,c, c+1,13,14);
        t1.cutBox(22,23,c, c+1,9,14);
        t1.cutBox(27,28,c, c+1,9,14);
    }

    t1.writeOFF("C:/Users/HP/Desktop/ARQUIVOS_NELMA/2022.1/PA/Projeto_P1/Escultor/t1.OFF");

    return 0;
}
