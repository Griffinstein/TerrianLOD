#define _USE_MATH_DEFINES

#include "TerrianLOD.h"

using namespace std;

#pragma comment(lib, "opengl32.lib")					// Link OpenGL32.lib
#pragma comment(lib, "glut32.lib")						// Link Glut32.lib
#pragma comment(lib, "glu32.lib")						// Link Glu32.lib

float xAngle = 0.0, yAngle = 0.0, deltaSide = 0.0, deltaMove = 0.0,xDeltaAngle = 0.0, yDeltaAngle = 0.0, ratio;		//Used to change the camera position and orientation
float x = 1500.0f, y = 1500.0f, z = 3000.0f;		//Holds the position of the camera				
float lx = 0, ly = 0, lz = -1.f;		//Holds the orientation of the camera, what the camera is looking at
float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};    //The colour where the light directly hits the object's surface
float lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};    //The colour applied everywhere
float lightPosition[] = {2.0f, 2.0f, -100.0f, 1.0f};	//The position of the light
float emission[] = {0.0, 0.0, 0.0, 0.0};			//Will hold the emission for certain objects
float yPrevious, yCurrent, yDifference, xPrevious, xCurrent, xDifference;	//Used to hold the mouse co-ordinates that will turn the camera
bool pause = false, light = true;			//Holds the bool for if the lights are on or off, and if the animation is paused or not

float newx = x, newy = y, newz = z, newlx = lx, newly = ly, newlz = lz;

LPSTR fileName;

BYTE g_HeightMap[MAP_SIZE*MAP_SIZE];

bool done = false;
bool oncer = true;
bool reload = false;

void changeSize(int w, int h)
	{

	//Prevent a divide by zero, when window is too short
	if(h == 0)
		h = 1;

	//Gets the ratio of the viewport
	ratio = 1.0f * w / h;
	//Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	//Set the clipping volume
	gluPerspective(45,ratio,1,5000);
	//Sets up the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
	}


//Orients the camera
void orientMe(float xAng, float yAng) {
	lx = sin(xAng);
	ly = tan(yAng);
	lz = -cos(xAng);

	//Prevents the camera going upside down
	if (ly > 2)
		ly = 2;
	else if (ly < -2)
		ly = -2;

	//Updates the camera accordingly
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

//Moves the camera in the direction the camera is facing back or forth
void moveMeFlat(int i) {
	x = x + i*(lx)*2;
	y = y + i*(ly)*2;
	z = z + i*(lz)*2;

	//Updates the camera accordingly
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void moveMeSide(int i) {

	vector3d camera, origin, vector, unitVector, crossVector, upVec;

	upVec.X = 0;
	upVec.Y = 1;
	upVec.Z = 0;

	float mag;

	camera.X = x + lx;	camera.Y = y + ly;	camera.Z = z + lz;
	origin.X = x;	origin.Y = y;	origin.Z = z;

	vector.X = origin.X - camera.X;
	vector.Y = origin.Y - camera.Y;
	vector.Z = origin.Z - camera.Z;

	mag = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
	
	unitVector.X = vector.X/mag;
	unitVector.Y = vector.Y/mag;
	unitVector.Z = vector.Z/mag;

	crossVector.X = (upVec.Y*unitVector.Z) - (upVec.Z*unitVector.Y);
	crossVector.Y = (upVec.Z*unitVector.X) - (upVec.X*unitVector.Z);
	crossVector.Z = (upVec.X*unitVector.Y) - (upVec.Y*unitVector.X);

	mag = sqrt((crossVector.X * crossVector.X) + (crossVector.Y * crossVector.Y) + (crossVector.Z * crossVector.Z));

	//Updates the camera accordingly

	x = x - i*(crossVector.X * mag)*2;
	y = y - i*(crossVector.Y * mag)*2;
	z = z - i*(crossVector.Z * mag)*2;

	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx,y + ly,z + lz,
		0.0f,1.0f,0.0f);
}

//A function to remove emission quickly
void clearEmission(){
	//Clears the emission to zero
	emission[0] = 0.0;	
	emission[1] = 0.0;
	emission[2] = 0.0;
	emission[3] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}

//A function to add emission quickly
void setEmission(float r, float g, float b, float a){
	emission[0] = r;	
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}

void init()
{
	fileName = "HMMountain.hmp";
	LoadRawFile(fileName, MAP_SIZE * MAP_SIZE, g_HeightMap);
	createHeightMap(g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap);
	glEnable(GL_DEPTH_TEST);								//Enable depth
	glEnable(GL_BLEND);										//Enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		//Set the blend function
}

const float start = static_cast <float> (clock ()) / static_cast <float> (CLOCKS_PER_SEC);
float newTime = (static_cast <float> (clock ()) / static_cast <float> (CLOCKS_PER_SEC)) - start;
static const int NUM_FPS_SAMPLES = 64;
float fpsSamples[NUM_FPS_SAMPLES];
int currentSample = 0;
float fps = 0;
	
void display(){
	float dt, oldTime;
	oldTime = newTime;//(static_cast <float> (clock ()) / static_cast <float> (CLOCKS_PER_SEC)) - start;
	newTime = (static_cast <float> (clock ()) / static_cast <float> (CLOCKS_PER_SEC)) - start;
	dt = newTime - oldTime;
	fps = fps * 0.9 + dt * 0.1;
    cout << fps << " FPS    \r";

	currentSample++;

	//Required to draw the gluSpheres
	GLUquadric *myQuad;
	myQuad = gluNewQuadric();
	gluQuadricTexture(myQuad, true);

	//Onlys calls the funcations when it is moving
	if (deltaMove) //Updates the camera's position
		moveMeFlat(deltaMove);
	if (deltaSide) //Updates the camera's position
		moveMeSide(deltaSide);
	if (xDeltaAngle || yDeltaAngle) { //Updates the camera's orientation
		xAngle += xDeltaAngle;
		yAngle += yDeltaAngle;
		orientMe(xAngle, yAngle);}

		//Clears the buffers
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);			//Ambient light component
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);			//Diffuse light component
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);		//Light position
    
    glEnable(GL_TEXTURE_2D);								//Enable 2D texturing

	glDisable(GL_LIGHTING);									//Enable lighting
	glDisable(GL_LIGHT0);									//Enable light0

		//If the light bool is true, then enable the light
	if (light)
	{
		//Light is enabled after the sun and stars so that there are no shadows
		//on the sun and stars which would be unrealistic
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

	}

	glDisable(GL_CULL_FACE);

	if (!pause){
		glEnable(GL_CULL_FACE);
		newx = x;
		newy = y;
		newz = z;
		newlx = lx;
		newly = ly;
		newlz = lz;
	}

	test(newx,newy,newz,newlx,newly,newlz, g_HeightMap, oncer, pause);

	glDisable(GL_TEXTURE_2D);//Disable 2D texturing

	glutSwapBuffers();
	glFlush();
    glutPostRedisplay();

	//Resets the Delta angles for orientating the camera
	xDeltaAngle = 0;
	yDeltaAngle = 0;

	if (reload){
		reload = false;
		LoadRawFile(fileName, MAP_SIZE * MAP_SIZE, g_HeightMap);
		createHeightMap(g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap, g_HeightMap);
	}
}

//Controls for the application
void pressKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT : deltaSide = 2;break;
		case GLUT_KEY_RIGHT : deltaSide = -2;break;
		case GLUT_KEY_UP : deltaMove = 2;break;											//Moves the camera forward
		case GLUT_KEY_DOWN : deltaMove = -2;break;										//Moves the camera backward
		case GLUT_KEY_F1 : if(pause){pause = false; break;}else{pause = true; break;}	//Pauses or unpauses the game
		case GLUT_KEY_F2 : if(light){light = false; break;}else{light = true; break;}	//Turns the lights on and off
	}
}

//Resets the deltaMove when the key is no longer pressed
void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : 
		case GLUT_KEY_RIGHT : deltaSide = 0;break;
		case GLUT_KEY_UP : 
		case GLUT_KEY_DOWN : deltaMove = 0;break;
		case GLUT_KEY_F3 : reload = true; fileName = "HMFlat.hmp";break;
		case GLUT_KEY_F4 : reload = true; fileName = "HMPlains.hmp";break;
		case GLUT_KEY_F5 : reload = true; fileName = "HMHills.hmp";break;
		case GLUT_KEY_F6 : reload = true; fileName = "HMMountain.hmp";break;
		case GLUT_KEY_F7 : reload = true; fileName = "HMSpikes.hmp";break;
		case GLUT_KEY_F8 : reload = true; fileName = "HMTeir.hmp";break;
		case GLUT_KEY_F10 : if (oncer)oncer = false; else oncer = true;
	}
}

//Allows the application to exit when the escape key is pressed
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) 
		exit(0);
}

//Gets the difference between the last and current update for the mouse
//Position, and then scales it down and stores it.
void processMouseActiveMotion(int x, int y) {
	//Gets the difference for the X axis
	xPrevious = x;
	xDifference = (xCurrent - xPrevious)/200;
	xCurrent = x;

	//Gets the difference for the Y axis
	yPrevious = y;
	yDifference = (yCurrent - yPrevious)/200;
	yCurrent = y;

	//Sets the difference to the delta angle, inverting the Y axis for control sake
	xDeltaAngle = -xDifference;
	yDeltaAngle = yDifference;
}

//Resets the mouse position to the current position when the mouse button is pressed
void processMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN){
		xCurrent = x;
		yCurrent = y;}
}


void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    glutCreateWindow ("Sphere Renderer");
    init();

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

    glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(changeSize);

	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);

	glutMainLoop();
}