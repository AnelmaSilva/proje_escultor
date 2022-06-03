#include "escultor.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

escultor::escultor (int _nx, int _ny, int _nz)
{
    this -> nx = _nx;
    this -> ny = _ny;
    this -> nz = _nz;
    this -> r = 0;
    this -> g = 0;
    this -> b = 0;
    this -> a = 0;

    M_voxel = new Voxel**[_nx];
    for(int i=0; i<_nx; i++)
    {
        M_voxel[i] = new Voxel *[_ny];
        for(int j=0; j <_ny; j++)
        {
            M_voxel[i][j] = new Voxel [_nz];
            for(int k=0; k<_nz; k++)
            {
                this -> M_voxel [i][j][k].r=0;
                this -> M_voxel [i][j][k].g=0;
                this -> M_voxel [i][j][k].b=0;
                this -> M_voxel [i][j][k].a=0;
                this -> M_voxel [i][j][k].esta_incluso=false;
            }
        }
    }
}

escultor::~escultor()
{
    for(int i=0; i<nx; i++)
    {
        for(int j=0;j<ny; j++)
        {
            delete [] M_voxel[i][j];
        }
        delete [] M_voxel[i];
    }
    delete [] M_voxel;
}

void escultor::setCor(float r, float g, float b, float aux)
{
    this -> r = r;
    this -> g = g;
    this -> b = b;
    this -> a = aux;
}

void escultor::putVoxel(int x, int y, int z)
{
    this -> M_voxel[x][y][z].r = this -> r;
    this -> M_voxel[x][y][z].g = this -> g;
    this -> M_voxel[x][y][z].b = this -> b;
    this -> M_voxel[x][y][z].a = this -> a;
    this -> M_voxel[x][y][z].esta_incluso = this -> true;
}
void escultor::cutVoxel(int x, int y, int z)
{
    this -> M_voxel[x][y][z].esta_incluso = false;
}
void escultor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    x0 = (x0 < 0 ) ? 0 : x0;
    x1 = (x1 > this -> nx ) ? this -> nx : x1;
    y0 = (y0 < 0 ) ? 0 : y0;
    y1 = (y1 > this -> ny ) ? this -> ny : y1;
    z0 = (z0 < 0 ) ? 0 : z0;
    z1 = (z1 > this -> nz ) ? this -> nz : z1;

    for(int i=x0; i<x1; i++)
    {
        for(int j=y0; j<y1; j++)
        {
            for(int k=z0; k<z1; k++)
            {
                this -> putVoxel(i,j,k);
            }
        }
    }
}
void escultor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<x1; i++)
    {
        for(int j=y0; j<y1; j++)
        {
            for(int k=z0; k<z1; k++)
            {
                this -> cutVoxel(i,j,k);
            }
        }
    }
}
void escultor::putEsfera(int xc, int yc, int zc, int raio)
{
    putElips(xc, yc, zc, raio, raio, raio);
}
void  escultor::cutEsferaint(int xc, int yc, int zc, int raio)
{
    cutElips(xc, yc, zc, raio, raio, raio);
}
void putElips(int xc, int yc, int zc, int raio)
{
    int x0 = (xc - rx < 0) ? 0 : xc - rx;
    int x1 = (xc + rx > this -> nx) ? this -> nx : xc + rx;
    int y0 = (yc - ry < 0) ? 0 : yc - ry;
    int y1 = (yc + ry > this -> ny) ? this -> ny : yc + ry;
    int z0 = (zc - rz < 0) ? 0 : zc - rz;
    int z1 = (zc + rz > this -> nz) ? this -> nz : zc + rz;

    for(int i=x0; i<x1; i++)
    {
        for(int j=y0; j<y1; j++)
        {
            for(int k=z0; k<z1; k++)
            {
                if(pow(i-xc,2)/pow(rx,2)+pow(j-yc,2)/pow(ry,2)+pow(k-zc,2)/pow(rz,2)<1)
                {
                   this -> putVoxel(i,j,k);
                }
            }
        }
    }
}
void escultor::cutElips(int xc, int yc, int zc, int raio)
{
      int x0 = (xc - rx < 0) ? 0 : xc - rx;
    int x1 = (xc + rx > this -> nx) ? this -> nx : xc + rx;
    int y0 = (yc - ry < 0) ? 0 : yc - ry;
    int y1 = (yc + ry > this -> ny) ? this -> ny : yc + ry;
    int z0 = (zc - rz < 0) ? 0 : zc - rz;
    int z1 = (zc + rz > this -> nz) ? this -> nz : zc + rz;

    for(int i=x0; i<x1; i++)
    {
        for(int j=y0; j<y1; j++)
        {
            for(int k=z0; k<z1; k++)
            {
                if(pow(i-xc,2)/pow(rx,2)+pow(j-yc,2)/pow(ry,2)+pow(k-zc,2)/pow(rz,2)<1)
                {
                   this -> cutVoxel(i,j,k);
                }
            }
        }
    }
}
void escultor::writeOFF(char* filename)
{
    ofstream myfile(fimename);

    if(!myfile.is_open())
    {
        cout<<"Erro ao abrir o arquivo" << filename << endl;
        exit(1);
    }

    int VOn = 0, i, j, k;
    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            for(int k=0; k<nz; k++)
            {
                if(this -> M_voxel[i][j][k].esta_incluso)
                {
                    VOn++;
                }
            }
        }
    }

    myfile << "OFF" <<endl;
    myfile  << 8*VOn << " " << 6*VOn << " 0" << endl;

    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            for(int k=0; k<nz; k++)
            {
                if(this -> M_voxel[i][j][k].esta_incluso)
                {
                    myfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    myfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }

    int ContVon = 0;
     for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            for(int k=0; k<nz; k++)
            {
                if(this -> M_voxel[i][j][k].esta_incluso)
                {
                    myfile << "4 " << ContVon = 8+0 << " " << ContVon = 8+3 << " " << ContVon = 8+2 << " " << ContVon = 8+1 << " "<< endl;
                    myfile << "4 " << ContVon = 8+4 << " " << ContVon = 8+5 << " " << ContVon = 8+6 << " " << ContVon = 8+7 << " "<< endl;
                    myfile << "4 " << ContVon = 8+0 << " " << ContVon = 8+1 << " " << ContVon = 8+5 << " " << ContVon = 8+4 << " "<< endl;
                    myfile << "4 " << ContVon = 8+0 << " " << ContVon = 8+4 << " " << ContVon = 8+7 << " " << ContVon = 8+3 << " "<< endl;
                    myfile << "4 " << ContVon = 8+3 << " " << ContVon = 8+7 << " " << ContVon = 8+6 << " " << ContVon = 8+2 << " "<< endl;
                    myfile << "4 " << ContVon = 8+1 << " " << ContVon = 8+2 << " " << ContVon = 8+6 << " " << ContVon = 8+5 << " "<< endl;
                    ContVon++;
                }
            }
        }
    }
}
