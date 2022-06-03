#ifndef ESCULTOR_H_INCLUDED
#define ESCULTOR_H_INCLUDED
#include "Voxel.h"

class escultor
{
protected:
    Voxel ***M_voxel;
    int nx, ny, nz;
    float r, g , b;

public:
    escultor (int _nx, int _ny, int _nz);
    ~escultor();
    void setCor(float r, float g, float b, float aux);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putEsfera(int xc, int yc, int zc, int raio);
    void cutEsferaint(int xc, int yc, int zc, int raio);
    void putElips(int xc, int yc, int zc, int raio);
    void cutElips(int xc, int yc, int zc, int raio);
    void writeOFF (char* filename);

};
#endif // ESCULTOR_H_INCLUDED
