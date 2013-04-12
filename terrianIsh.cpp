#define _USE_MATH_DEFINES

#include "TerrianLOD.h"

using namespace std;

#pragma comment(lib, "opengl32.lib")					// Link OpenGL32.lib
#pragma comment(lib, "glut32.lib")						// Link Glut32.lib
#pragma comment(lib, "glu32.lib")						// Link Glu32.lib]

BYTE heightMap[MAP_SIZE*MAP_SIZE];

void flatTest(){
	FILE *pFile = NULL;

	pFile = fopen("Terrian.raw","rb");
}