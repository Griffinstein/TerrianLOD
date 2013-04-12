#ifndef _TERRIANLOD_H
#define _TERRIANLOD_H

#include <windows.h>									// Header File For Windows
#include <stdio.h>										// Header file for standard input output (IE, "FILE") (NEW)
#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>										// Header File For The GLu32 Library
#include <gl\glut.h>									// Header File For The Glut Library
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>						     // Header File For Windows Math Library  
#include <stdarg.h>							 // Header File For Variable Argument Routines
#include <time.h>
#include <sstream>

#include "BinTree.h"
#include "sphere.h"
#include "terrianIsh.h"
#include "heightmap.h"

#define HEIGHTMAP_SIZE_HEIGHT 1024
#define HEIGHTMAP_SIZE_WIDTH 1024
#define MAP_SIZE 1024
#define STEP_SIZE 128

struct vector3d
{
public:
    float X, Y, Z;
 
    inline vector3d( void ) {}
    inline vector3d( const float x, const float y, const float z )
    { X = x; Y = y; Z = z; }

    inline vector3d operator + ( const vector3d& A ) const
    { return vector3d( X + A.X, Y + A.Y, Z + A.Z ); }

    inline vector3d operator + ( const float A ) const
    { return vector3d( X + A, Y + A, Z + A ); }

    inline float Dot( const vector3d& A ) const
    { return A.X*X + A.Y*Y + A.Z*Z; }

	inline bool Equals( const vector3d& A ) const
    { 
		if (A.X!=X)
			return false;
		else if (A.Y!=Y)
			return false;
		else if (A.Z!=Z)
			return false;
		else
			return true;
	}

	inline vector3d rotate( const int rot ) const
    { 
		vector3d temp(X,Y,Z);
		if (rot == 1){
			temp.X = X;
			temp.Y = -Y;
			temp.Z = Z;
		}
		else if (rot == 2){
			temp.X = X;
			temp.Y = Y;
			temp.Z = Z;
		}
		else if (rot == 3){
			temp.X = X;
			temp.Y = Z;
			temp.Z = -Y;
		}
		else if (rot == 4){
			temp.X = X;
			temp.Y = Z;
			temp.Z = Y;
		}
		else if (rot == 5){
			temp.X = -Y;
			temp.Y = X;
			temp.Z = Z;
		}
		else if (rot == 6){
			temp.X = Y;
			temp.Y = X;
			temp.Z = Z;
		}
		return temp;
	}
};

#endif