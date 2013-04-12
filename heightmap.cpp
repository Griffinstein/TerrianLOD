#define _USE_MATH_DEFINES

#include "TerrianLOD.h"

using namespace std;

#pragma comment(lib, "opengl32.lib")					// Link OpenGL32.lib
#pragma comment(lib, "glut32.lib")						// Link Glut32.lib
#pragma comment(lib, "glu32.lib")						// Link Glu32.lib

BYTE tempHeight[MAP_SIZE*MAP_SIZE+100];

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)
{
	FILE *pFile = NULL;
	int i;

	// Let's open the file in Read/Binary mode.
	pFile = fopen( strName, "rb" );

	// Check to see if we found the file and could open it
	if ( pFile == NULL )	
	{
		// Display our error message and stop the function
		MessageBox(NULL, "Can't find the height map!", "Error", MB_OK);
		return;
	}

	// Here we load the .raw file into our pHeightMap data array.
	// We are only reading in '1', and the size is the (width * height)
	fread(tempHeight, 1, (nSize+100), pFile );

	for (i = 0; i<nSize; i++){
		pHeightMap[i] = tempHeight[i+100];
	}

	//fread(pHeightMap, 1, (nSize), pFile );

	// After we read the data, it's a good idea to check if everything read fine.
	int result = ferror( pFile );

	// Check if we received an error.
	if (result)
	{
		MessageBox(NULL, "Can't get data!", "Error", MB_OK);
	}

	// Close the file.
	fclose(pFile);
}