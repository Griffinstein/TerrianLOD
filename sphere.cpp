#define _USE_MATH_DEFINES

#include "TerrianLOD.h"

using namespace std;

#pragma comment(lib, "opengl32.lib")					// Link OpenGL32.lib
#pragma comment(lib, "glut32.lib")						// Link Glut32.lib
#pragma comment(lib, "glu32.lib")						// Link Glu32.lib


vector3d centreSphere = vector3d(0, 0, 0);
int depthderp = 12;

struct triangleSph
{
	triangleSph *childA, *childB;
	triangleSph *ABNeighbour, *BCNeighbour, *ACNeighbour;
	vector3d A, B, C, centre, splitPoint;
	bool split;
	int depth;
	float distanceFC;
	float AngA, AngB, AngC;
	char rightAng;

	inline triangleSph( void ) {}
    inline triangleSph( const vector3d a, const vector3d b, const vector3d c, const int oldDepth, const float distance){
		A = a; B = b; C = c;

		distanceFC = distance;

		//A.Y = A.Y + 2;

		centre.X = (A.X + b.X + c.X) / 3;
		centre.Y = (A.Y + b.Y + c.Y) / 3;
		centre.Z = (A.Z + b.Z + c.Z) / 3;	

		split = false; 	
		depth = oldDepth + 1;

		this->rightAngle();
		//distanceFromCam();

		struct triangleSph* triangleSph = new(struct triangleSph);
		triangleSph->childA = NULL;
		triangleSph->childB = NULL;
		triangleSph->ABNeighbour = NULL;
		triangleSph->BCNeighbour = NULL;
		triangleSph->ACNeighbour = NULL;

		if (depth != depthderp){
			this->splitTri();
		}
	}
	
	inline vector3d getUnit(const vector3d a, const vector3d b){
		vector3d vector, unit;
		float mag;

			vector.X = a.X - b.X;
			vector.Y = a.Y - b.Y;
			vector.Z = a.Z - b.Z;
			
			mag = sqrt(pow(vector.X, 2) + pow(vector.Y, 2) + pow(vector.Z, 2));
			
			unit.X = vector.X/mag;
			unit.Y = vector.Y/mag;
			unit.Z = vector.Z/mag;

			return unit;
		}
		
		inline float getAngle(const vector3d a, const vector3d b){
			vector3d vector;
			float angle, Atemp, Btemp;
			float x;

			x = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
			Atemp = sqrt(pow(a.X, 2) + pow(a.Y, 2) + pow(a.Z, 2)); 
			Btemp = sqrt(pow(b.X, 2) + pow(b.Y, 2) + pow(b.Z, 2));
			angle = acos(fabs(x/(Atemp*Btemp)));

			return angle;
		}
		
		inline void rightAngle(){
		vector3d ABUnit, BCUnit, CAUnit;

		ABUnit = getUnit(A,B);
		BCUnit = getUnit(B,C);
		CAUnit = getUnit(C,A);

		AngA = getAngle(ABUnit, CAUnit);
		AngB = getAngle(ABUnit, BCUnit);
		AngC = getAngle(BCUnit, CAUnit);
		//int temp = AngA * 100;
		//AngA = (float)((int)(AngA * 100))/100;
		//AngA = AngA;
		//if (AngA == 1.57f){
			splitPoint.X = (B.X + C.X)/2;
			splitPoint.Y = (B.Y + C.Y)/2;
			splitPoint.Z = (B.Z + C.Z)/2;
			rightAng = 'A';
		//}
		//if (AngB == 1.57f){
		//	splitPoint.X = (A.X + C.X)/2;
		//	splitPoint.Y = (A.Y + C.Y)/2;
		//	splitPoint.Z = (A.Z + C.Z)/2;
		//	rightAng = 'B';
		//}
		//if (AngC == 1.57f){
		//	splitPoint.X = (B.X + A.X)/2;
		//	splitPoint.Y = (B.Y + A.Y)/2;
		//	splitPoint.Z = (B.Z + A.Z)/2;
		//	rightAng = 'C';
		//}

		vector3d vector, vectorrr;
		float mag;
		centreSphere;
		
		vector.X = splitPoint.X - centreSphere.X;
		vector.Y = splitPoint.Y - centreSphere.Y;
		vector.Z = splitPoint.Z - centreSphere.Z;
		
		mag = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
	
		distanceFC = distanceFC - depth;

		vectorrr.X = (vector.X/mag)*distanceFC;
		vectorrr.Y = (vector.Y/mag)*distanceFC;
		vectorrr.Z = (vector.Z/mag)*distanceFC;

		splitPoint.X = vectorrr.X + centreSphere.X;
		splitPoint.Y = vectorrr.Y + centreSphere.Y;
		splitPoint.Z = vectorrr.Z + centreSphere.Z;

		int i = 1;
	}

	inline int longestEdge(){
		float AB, BC, CA;

		AB = fabs(sqrt(pow(A.X - B.X, 2) + pow(A.Y - B.Y, 2) + pow(A.Z - B.Z, 2)));
		BC = fabs(sqrt(pow(B.X - C.X, 2) + pow(B.Y - C.Y, 2) + pow(B.Z - C.Z, 2)));
		CA = fabs(sqrt(pow(C.X - A.X, 2) + pow(C.Y - A.Y, 2) + pow(C.Z - A.Z, 2)));

		if (AB > BC){
			if (AB > CA)
				return 1;//AB
			else
				return 3;//CB
		}
		else{
			if (BC > CA)
				return 2;//BC
			else
				return 3;//CB
		}
	}

	inline void splitTri(){
		split = true;

		triangleSph *leftChild;
		triangleSph *rightChild;

		leftChild = new triangleSph(this->splitPoint, this->A, this->B, this->depth, this->distanceFC);
		rightChild = new triangleSph(this->splitPoint, this->A, this->C, this->depth, this->distanceFC);

		leftChild->ABNeighbour = rightChild;
		rightChild->ABNeighbour = leftChild;

		childA = leftChild;
		childB = rightChild;
	}

	inline void drawTri(){
		if (this->childA->depth != depthderp){
			this->childA->drawTri();
			this->childB->drawTri();
		}
		else{
			glColor3f(0,1.0f,0);
			glVertex3f(this->A.X,this->A.Y,this->A.Z);
			glColor3f(1.0f,0,0);
			glVertex3f(this->B.X,this->B.Y,this->B.Z);
			glColor3f(0,0,1.0f);
			glVertex3f(this->C.X,this->C.Y,this->C.Z);
		}
	}
	/*
	inline void distanceFromCam(){
		vector3d vector;

		vector.X = camera.X - centre.X;
		vector.Y = camera.Y - centre.Y;
		vector.Z = camera.Z - centre.Z;

		distanceFC = fabs(sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z)));
		distanceFC = distanceFC;
	}*/

	inline void mergeTri(){
		split = false;
	}
};

struct quad
{
	vector3d A, B, C, D;
	triangleSph left, right;

	inline quad( void ) {}
    inline quad( const vector3d a, const vector3d b, const vector3d c, const vector3d d, const float radius)
    { A = a; B = b; C = c; D = d;
	left = triangleSph(A,B,D,0, radius);
	right = triangleSph(C,B,D,0, radius);}

	inline void draw(){
		left.drawTri();
		right.drawTri();
	}

	inline void split(){



		/*
		left.splitTri();
		left.childA->drawTri();
		left.childB->drawTri();
		right.splitTri();
		right.childA->drawTri();
		right.childB->drawTri();
		*/
		/*	
		left.splitTri();
		left.childA->splitTri();
		left.childB->splitTri();
		left.childA->childA->drawTri();
		left.childA->childB->drawTri();
		left.childB->childA->drawTri();
		left.childB->childB->drawTri();
		right.splitTri();
		right.childA->splitTri();
		right.childB->splitTri();
		right.childA->childA->drawTri();
		right.childA->childB->drawTri();
		right.childB->childA->drawTri();
		right.childB->childB->drawTri();
		*/
		//left.childA->drawTri();
		//left.childB->drawTri();
		//right.childA->drawTri();
		//right.childB->drawTri();
		
		//float i = left.childA->childA->splitPoint.X;	
	}
};


struct cube
{
	vector3d centre;
	vector3d topBackLeft, topBackRight, topFrontLeft, topFrontRight, bottomBackLeft, bottomBackRight, bottomFrontLeft, bottomFrontRight;
	float size, radius;
	quad top, bottom, front, back, left, right;

	inline cube( void ) {}
    inline cube( const vector3d a)
    { centre = a;
	size = 200;

	//struct vector3d* vector3d = new(struct vector3d);

	topBackLeft = vector3d(a.X+size, a.Y+size, a.Z-size);
	topBackRight = vector3d(a.X-size, a.Y+size, a.Z-size);
	topFrontLeft = vector3d(a.X+size, a.Y+size, a.Z+size);
	topFrontRight = vector3d(a.X-size, a.Y+size, a.Z+size);
	bottomBackLeft = vector3d(a.X+size, a.Y-size, a.Z-size);
	bottomBackRight = vector3d(a.X-size, a.Y-size, a.Z-size);
	bottomFrontLeft = vector3d(a.X+size, a.Y-size, a.Z+size);
	bottomFrontRight = vector3d(a.X-size, a.Y-size, a.Z+size);

	vector3d vector;

	vector.X = topBackLeft.X - centre.X;
	vector.Y = topBackLeft.Y - centre.Y;
	vector.Z = topBackLeft.Z - centre.Z;

	radius = fabs(sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z)));

	top = quad(topBackLeft, topBackRight, topFrontRight, topFrontLeft, radius);
	bottom = quad(bottomBackLeft, bottomBackRight, bottomFrontRight, bottomFrontLeft, radius);
	front = quad(bottomFrontRight, bottomFrontLeft, topFrontLeft, topFrontRight,radius);
	back = quad(bottomBackRight, bottomBackLeft, topBackLeft, topBackRight, radius);
	left = quad(topBackLeft, topFrontLeft, bottomFrontLeft, bottomBackLeft, radius);
	right = quad(topBackRight, topFrontRight, bottomFrontRight, bottomBackRight, radius);
	}

	inline void draw(){
		top.draw();
		bottom.draw();
		front.draw();
		back.draw();
		left.draw();
		right.draw();
		/*top.split();
		bottom.split();
		front.split();
		back.split();
		left.split();
		right.split();*/
	}
};

cube testtttyy = cube(centreSphere);

void sphereTest(){
	//cube test = cube(centreSphere);
	
	glDisable(GL_LIGHTING);									//Enable lighting
	glDisable(GL_LIGHT0);									//Enable light0

	glBegin (GL_TRIANGLES);

	testtttyy.draw();

	glEnd();

	glColor4f(1.0f,1.0f,1.0f,1.0f);
}

//MAKE CAMERA GLOBAL