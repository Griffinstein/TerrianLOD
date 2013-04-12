#ifndef _BINTREE_H
#define _BINTREE_H

//#define STEP_DISTANCE_SIZE 100;

void split(struct triangle* triangle);

void createHeightMap(BYTE pHeightMap[], BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[]);

int Height(BYTE *pHeightMap, int X, int Y);

//Just holding the test method
void test(float CamA, float CamB, float CamC, float CamDirA, float CamDirB, float CamDirC, BYTE pHeightMap[], BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[], bool stop);
void test(float CamA, float CamB, float CamC, float CamDirA, float CamDirB, float CamDirC, BYTE pHeightMap[], bool stop, bool pauseCull);
#endif