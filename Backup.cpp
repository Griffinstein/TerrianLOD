//#define _USE_MATH_DEFINES
//
//#include "TerrianLOD.h"
//
//using namespace std;
//
//#pragma comment(lib, "opengl32.lib")					// Link OpenGL32.lib
//#pragma comment(lib, "glut32.lib")						// Link Glut32.lib
//#pragma comment(lib, "glu32.lib")						// Link Glu32.lib
//
//int depthherp = 5;
//int numOfVer = 0;
//bool once = true;
//int derpherpepre = 0;
//
//struct node {
//	int data;
//	struct node* right;
//	struct node* left;
//
//	struct node* NewNode(int data){
//	struct node* node = new(struct node);
//	node->data = data;
//	node->left = NULL;
//	node->right = NULL;
//
//	return(node);
//	}
//};
//
///*
//struct triangle
//{
//	triangle *childA, *childB;
//	triangle *ABNeighbour, *BCNeighbour, *ACNeighbour;
//	vector3d A, B, C, centre, splitPoint, camera;
//	bool split;
//	int depth;
//	float distanceFC;
//	float AngA, AngB, AngC;
//	char rightAng;
//
//	inline triangle( void ) {}
//    inline triangle( const vector3d a, const vector3d b, const vector3d c, const int oldDepth, vector3d Camera){
//		A = a; B = b; C = c;
//
//		//A.Y = A.Y + 2;
//
//		centre.X = (A.X + b.X + c.X) / 3;
//		centre.Y = (A.Y + b.Y + c.Y) / 3;
//		centre.Z = (A.Z + b.Z + c.Z) / 3;	
//
//		split = false; 	
//		depth = oldDepth + 1;
//		camera = Camera;
//
//		rightAngle();
//		distanceFromCam();
//
//		struct triangle* triangle = new(struct triangle);
//		triangle->childA = NULL;
//		triangle->childB = NULL;
//		triangle->ABNeighbour = NULL;
//		triangle->BCNeighbour = NULL;
//		triangle->ACNeighbour = NULL;
//	}
//
//		inline vector3d getUnit(const vector3d a, const vector3d b){
//			vector3d vector, unit;
//			float mag;
//
//			vector.X = a.X - b.X;
//			vector.Y = a.Y - b.Y;
//			vector.Z = a.Z - b.Z;
//			
//			mag = sqrt(pow(vector.X, 2) + pow(vector.Y, 2) + pow(vector.Z, 2));
//			
//			unit.X = vector.X/mag;
//			unit.Y = vector.Y/mag;
//			unit.Z = vector.Z/mag;
//
//			return unit;
//		}
//		
//		inline float getAngle(const vector3d a, const vector3d b){
//			vector3d vector;
//			float angle, Atemp, Btemp;
//			float x;
//
//			x = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
//			Atemp = sqrt(pow(a.X, 2) + pow(a.Y, 2) + pow(a.Z, 2)); 
//			Btemp = sqrt(pow(b.X, 2) + pow(b.Y, 2) + pow(b.Z, 2));
//			angle = acos(fabs(x/(Atemp*Btemp)));
//
//			return angle;
//		}
//		
//		/*
//		inline void rightAngle(){
//		vector3d ABUnit, BCUnit, CAUnit;
//
//		ABUnit = getUnit(A,B);
//		BCUnit = getUnit(B,C);
//		CAUnit = getUnit(C,A);
//
//		AngA = getAngle(ABUnit, CAUnit);
//		AngB = getAngle(ABUnit, BCUnit);
//		AngC = getAngle(BCUnit, CAUnit);
//		//int temp = AngA * 100;
//		AngA = (float)((int)(AngA * 100))/100;
//		//AngA = AngA;
//		if (AngA == 1.57f){
//			splitPoint.X = (B.X + C.X)/2;
//			splitPoint.Y = (B.Y + C.Y)/2;
//			splitPoint.Z = (B.Z + C.Z)/2;
//			rightAng = 'A';
//		}
//		if (AngB == 1.57f){
//			splitPoint.X = (A.X + C.X)/2;
//			splitPoint.Y = (A.Y + C.Y)/2;
//			splitPoint.Z = (A.Z + C.Z)/2;
//			rightAng = 'B';
//		}
//		if (AngC == 1.57f){
//			splitPoint.X = (B.X + A.X)/2;
//			splitPoint.Y = (B.Y + A.Y)/2;
//			splitPoint.Z = (B.Z + A.Z)/2;
//			rightAng = 'C';
//		}
//		int i = 0;
//	}
//
//	inline int longestEdge(){
//		float AB, BC, CA;
//
//		AB = fabs(sqrt(pow(A.X - B.X, 2) + pow(A.Y - B.Y, 2) + pow(A.Z - B.Z, 2)));
//		BC = fabs(sqrt(pow(B.X - C.X, 2) + pow(B.Y - C.Y, 2) + pow(B.Z - C.Z, 2)));
//		CA = fabs(sqrt(pow(C.X - A.X, 2) + pow(C.Y - A.Y, 2) + pow(C.Z - A.Z, 2)));
//
//		if (AB > BC){
//			if (AB > CA)
//				return 1;//AB
//			else
//				return 3;//CB
//		}
//		else{
//			if (BC > CA)
//				return 2;//BC
//			else
//				return 3;//CB
//		}
//	}
//
//	inline void splitTri(){
//		split = true;
//
//		triangle *leftChild;
//		triangle *rightChild;
//
//		leftChild = new triangle(this->splitPoint, this->A, this->B, this->depth, this->camera);
//		rightChild = new triangle(this->splitPoint, this->A, this->C, this->depth, this->camera);
//
//		leftChild->ABNeighbour = rightChild;
//		rightChild->ABNeighbour = leftChild;
//
//		childA = leftChild;
//		childB = rightChild;
//	}
//
//	inline void drawTri(){
//		glColor3f(0,1.0f,0);
//		glVertex3f(this->A.X,this->A.Y,this->A.Z);
//		glColor3f(1.0f,0,0);
//		glVertex3f(this->B.X,this->B.Y,this->B.Z);
//		glColor3f(0,0,1.0f);
//		glVertex3f(this->C.X,this->C.Y,this->C.Z);
//	}
//
//	inline void distanceFromCam(){
//		vector3d vector;
//
//		vector.X = camera.X - centre.X;
//		vector.Y = camera.Y - centre.Y;
//		vector.Z = camera.Z - centre.Z;
//
//		distanceFC = fabs(sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z)));
//		distanceFC = distanceFC;
//	}
//
//	inline void mergeTri(){
//		split = false;
//	}
//};*/
//
///*struct quad
//{
//	vector3d A, B, C, D;
//
//	inline quad( void ) {}
//    inline quad( const vector3d a, const vector3d b, const vector3d c, const vector3d d)
//    { A = a; B = b; C = c; D = d;}
//};*/
//
//struct triangler
//{
//	triangler *childA, *childB;
//	vector3d A, B, C, ACur, BCur, CCur, centre, splitPoint, xHeight, yHeight;
//	bool split, drawChild;
//	int depth, maxDepth;
//	float AngA, AngB, AngC, radius, heightA, heightB, heightC;
//
//	inline triangler( void ) {}
//    inline triangler( const vector3d a, const vector3d b, const vector3d c, const int oldDepth, BYTE pHeightMap[], int g_depth, float radius, const vector3d XHeightCords, const vector3d YHeightCords, bool dChild){
//		A = a; B = b; C = c;
//		ACur = a; BCur = b; CCur = c;
//		maxDepth = g_depth;
//		this->radius = radius;
//		depth = oldDepth + 1;
//
//		drawChild = dChild;
//
//		xHeight = XHeightCords;
//		yHeight = YHeightCords;
//
//		heightA = Height(pHeightMap,xHeight.X,yHeight.X);
//		heightB = Height(pHeightMap,xHeight.Y,yHeight.Y);
//		heightC = Height(pHeightMap,xHeight.Z,yHeight.Z);
//
//		if (radius == 0){
//			A.Y = heightA;
//			B.Y = heightB;
//			C.Y = heightC;
//		}
//
//		centre.X = (A.X + b.X + c.X) / 3;
//		centre.Y = (A.Y + b.Y + c.Y) / 3;
//		centre.Z = (A.Z + b.Z + c.Z) / 3;	
//
//		split = false; 	
//
//		this->rightAngle();
//		if (radius != 0){
//			this->sphereEdge();
//		}
//		//distanceFromCam();
//
//		struct triangler* triangler = new(struct triangler);
//		triangler->childA = NULL;
//		triangler->childB = NULL;
//
//		if (depth != maxDepth){
//			this->splitTri(pHeightMap);
//		}
//		else{
//			if (radius != 0){
//				this->sphereEdge();
//			}
//		}
//	}
//	
//	inline vector3d getUnit(const vector3d a, const vector3d b){
//		vector3d vector, unit;
//		float mag;
//
//			vector.X = a.X - b.X;
//			vector.Y = a.Y - b.Y;
//			vector.Z = a.Z - b.Z;
//			
//			mag = sqrt(pow(vector.X, 2) + pow(vector.Y, 2) + pow(vector.Z, 2));
//			
//			unit.X = vector.X/mag;
//			unit.Y = vector.Y/mag;
//			unit.Z = vector.Z/mag;
//
//			return unit;
//		}
//		
//		inline float getAngle(const vector3d a, const vector3d b){
//			vector3d vector;
//			float angle, Atemp, Btemp;
//			float x;
//
//			x = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
//			Atemp = sqrt(pow(a.X, 2) + pow(a.Y, 2) + pow(a.Z, 2)); 
//			Btemp = sqrt(pow(b.X, 2) + pow(b.Y, 2) + pow(b.Z, 2));
//			angle = acos(fabs(x/(Atemp*Btemp)));
//
//			return angle;
//		}
//		
//		inline void rightAngle(){
//			vector3d ABUnit, BCUnit, CAUnit;
//
//			ABUnit = getUnit(A,B);
//			BCUnit = getUnit(B,C);
//			CAUnit = getUnit(C,A);
//	
//			AngA = getAngle(ABUnit, CAUnit);
//			AngB = getAngle(ABUnit, BCUnit);
//			AngC = getAngle(BCUnit, CAUnit);
//
//			splitPoint.X = (B.X + C.X)/2;
//			splitPoint.Y = (B.Y + C.Y)/2;
//			splitPoint.Z = (B.Z + C.Z)/2;
//
//			//if (radius != 0){
//			//	applyRadius(&splitPoint, heightA);
//			//}
//		}
//
//		inline void sphereEdge(){
//			applyRadius(&ACur, heightA);
//			applyRadius(&BCur, heightB);
//			applyRadius(&CCur, heightC);
//		}
//		
//		inline void updatePointA(){
//			applyRadius(&ACur, heightA);
//		}
//		
//		inline void updatePointB(){
//			applyRadius(&BCur, heightB);
//		}
//		
//		inline void updatePointC(){
//			applyRadius(&CCur, heightC);
//		}
//
//		inline void applyRadius(vector3d *point, float height){
//			vector3d vector;
//			float mag;
//
//			vector.X = point->X - (MAP_SIZE/2);
//			vector.Y = point->Y - (MAP_SIZE/2);
//			vector.Z = point->Z - (MAP_SIZE/2);
//			
//			mag = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
//
//			vector.X = floorf(((vector.X/mag)*(radius+height))* 10000 + 0.5) / 10000;
//			vector.Y = floorf(((vector.Y/mag)*(radius+height))* 10000 + 0.5) / 10000;
//			vector.Z = floorf(((vector.Z/mag)*(radius+height))* 10000 + 0.5) / 10000;
//
//
//			//vector.X = (vector.X/mag)*(radius+height);
//			//vector.Y = (vector.Y/mag)*(radius+height);
//			//vector.Z = (vector.Z/mag)*(radius+height);
//			
//			point->X = vector.X + (MAP_SIZE/2);
//			point->Y = vector.Y + (MAP_SIZE/2);
//			point->Z = vector.Z + (MAP_SIZE/2);
//		}
//
//		inline int longestEdge(){
//		float AB, BC, CA;
//
//		AB = fabs(sqrt(pow(A.X - B.X, 2) + pow(A.Y - B.Y, 2) + pow(A.Z - B.Z, 2)));
//		BC = fabs(sqrt(pow(B.X - C.X, 2) + pow(B.Y - C.Y, 2) + pow(B.Z - C.Z, 2)));
//		CA = fabs(sqrt(pow(C.X - A.X, 2) + pow(C.Y - A.Y, 2) + pow(C.Z - A.Z, 2)));
//
//		if (AB > BC){
//			if (AB > CA)
//				return 1;//AB
//			else
//				return 3;//CB
//		}
//		else{
//			if (BC > CA)
//				return 2;//BC
//			else
//				return 3;//CB
//		}
//	}
//
//	inline void splitTri(BYTE pHeightMap[]){
//		bool child = this->drawChild;
//		split = true;
//
//		triangler *leftChild;
//		triangler *rightChild;
//
//		leftChild = new triangler(this->splitPoint, this->A, this->B, this->depth, pHeightMap, this->maxDepth, this->radius, vector3d((this->xHeight.Y+this->xHeight.Z)/2,this->xHeight.X,this->xHeight.Y), vector3d((this->yHeight.Y+this->yHeight.Z)/2,this->yHeight.X,this->yHeight.Y),child);
//		rightChild = new triangler(this->splitPoint, this->A, this->C, this->depth, pHeightMap, this->maxDepth, this->radius, vector3d((this->xHeight.Y+this->xHeight.Z)/2,this->xHeight.X,this->xHeight.Z), vector3d((this->yHeight.Y+this->yHeight.Z)/2,this->yHeight.X,this->yHeight.Z),!child);
//
//		childA = leftChild;
//		childB = rightChild;
//	}
//
//	inline void drawTri(vector3d position, int rot){
//		if (this->depth != maxDepth){
//			this->childA->drawTri(position, rot);
//			this->childB->drawTri(position, rot);
//		}
//		else{
//			float Red, Blue, Green;
//			if (maxDepth == 2){
//				Red = (float)0;
//				Blue = (float)0;
//				Green = (float)1;
//			}
//			else if (maxDepth == 3){
//				Red = (float)0;
//				Blue = (float)0.25;
//				Green = (float)0.75;
//			}
//			else if (maxDepth == 4){
//				Red = (float)0;
//				Blue = (float)0.5;
//				Green = (float)0.5;
//			}
//			else if (maxDepth == 5){
//				Red = (float)0.25;
//				Blue = (float)0.75;
//				Green = (float)0;
//			}
//			else if (maxDepth == 6){
//				Red = (float)0;
//				Blue = (float)0.75;
//				Green = (float)0.25;
//			}
//			else if (maxDepth == 7){
//				Red = (float)0.5;
//				Blue = (float)0.5;
//				Green = (float)0;
//			}
//			else if (maxDepth == 8){
//				Red = (float)0.75;
//				Blue = (float)0.25;
//				Green = (float)0;
//			}
//			else if (maxDepth == 9){
//				Red = (float)1;
//				Blue = (float)0;
//				Green = (float)0;
//			}
//
//			vector3d NewA(this->ACur.X, this->ACur.Y, this->ACur.Z);
//			vector3d NewB(this->BCur.X, this->BCur.Y, this->BCur.Z);
//			vector3d NewC(this->CCur.X, this->CCur.Y, this->CCur.Z);
//
//			NewA = NewA.rotate(rot);
//			NewB = NewB.rotate(rot);
//			NewC = NewC.rotate(rot);
//
//			if (this->drawChild){
//				glColor3f(Red/3,Green,0);
//				glVertex3f(NewA.X + position.X,NewA.Y + position.Y,NewA.Z + position.Z);
//				numOfVer++;
//				glColor3f(Red/2,0,0);
//				glVertex3f(NewB.X + position.X,NewB.Y + position.Y,NewB.Z + position.Z);
//				numOfVer++;
//				glColor3f(Red,0,Blue);
//				glVertex3f(NewC.X + position.X,NewC.Y + position.Y,NewC.Z + position.Z);
//				numOfVer++;
//			}
//			else{
//				glColor3f(Red/3,Green,0);
//				glVertex3f(NewC.X + position.X,NewC.Y + position.Y,NewC.Z + position.Z);
//				numOfVer++;
//				glColor3f(Red/2,0,0);
//				glVertex3f(NewB.X + position.X,NewB.Y + position.Y,NewB.Z + position.Z);
//				numOfVer++;
//				glColor3f(Red,0,Blue);
//				glVertex3f(NewA.X + position.X,NewA.Y + position.Y,NewA.Z + position.Z);
//				numOfVer++;
//			}
//
//
//			/*glColor3f(Red/3,Green,0);
//			glVertex3f(NewA.X,NewA.Y,NewA.Z);
//			numOfVer++;
//			glColor3f(Red/2,0,0);
//			glVertex3f(NewB.X,NewB.Y,NewB.Z);
//			numOfVer++;
//			glColor3f(Red,0,Blue);
//			glVertex3f(NewC.X,NewC.Y,NewC.Z);
//			numOfVer++;*/
//		}
//	}
//
//	inline void mergeTri(){
//		split = false;
//	}
//};
//
//
//struct quad
//{
//	vector3d A, B, C, D, centre, curveCentre;
//	triangler top, bottom, left, right;
//	int depth, maxDepth;
//	bool wasEdge, isEdge, fixed, drawChild;
//	float radius;
//
//	inline quad( void ) {}
//    inline quad( const vector3d a, const vector3d b, const vector3d c, const vector3d d, BYTE pHeightMap[], float radius, bool dChild){
//		depth = 2;
//		drawChild = dChild;
//		A = a; B = b; C = c; D = d;
//		centre.X = ((B.X+D.X)/2);
//		centre.Y = ((B.Y+D.Y)/2);
//		centre.Z = ((B.Z+D.Z)/2);
//		wasEdge = false;
//		isEdge = false;
//		fixed = false;
//		this->radius = radius;
//
//		determineMaxDepth(pHeightMap);
//
//		top = triangler(centre,A,B,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),A.X,B.X), vector3d(((B.Z+D.Z)/2),A.Z,B.Z), drawChild);
//		bottom = triangler(centre,C,D,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),C.X,D.X), vector3d(((B.Z+D.Z)/2),C.Z,D.Z), drawChild);
//		left = triangler(centre,D,A,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),D.X,A.X), vector3d(((B.Z+D.Z)/2),D.Z,A.Z), drawChild);
//		right = triangler(centre,B,C,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),B.X,C.X), vector3d(((B.Z+D.Z)/2),B.Z,C.Z), drawChild);
//
//		curveCentre = centre;
//
//		if (radius != 0){
//			vector3d vector;
//			float mag;
//			
//			vector.X = curveCentre.X - (MAP_SIZE/2);
//			vector.Y = curveCentre.Y - (MAP_SIZE/2);
//			vector.Z = curveCentre.Z - (MAP_SIZE/2);
//			
//			mag = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
//			
//			vector.X = (vector.X/mag)*radius;
//			vector.Y = (vector.Y/mag)*radius;
//			vector.Z = (vector.Z/mag)*radius;
//			
//			curveCentre.X = vector.X + (MAP_SIZE/2);
//			curveCentre.Y = vector.Y + (MAP_SIZE/2);
//			curveCentre.Z = vector.Z + (MAP_SIZE/2);
//		}
//
//		//left = triangler(A,B,D,0,pHeightMap,depth);
//		//right = triangler(C,B,D,0,pHeightMap,depth);
//	}
//
//	inline void determineMaxDepth(BYTE pHeightMap[]){
//
//		int maxHeight = 0;
//		int minHeight = 256;
//		int i = 0;
//
//
//
//		for ( int X = A.X; X <= D.X; X++){
//			for ( int Y = A.Z; Y <= D.Z; Y++){
//				i = Height(pHeightMap,X,Y);
//				if (i < minHeight)
//					minHeight = i;				
//				if (i > maxHeight)
//					maxHeight = i;	
//			}
//		}
//
//		i = maxHeight - minHeight;
//
//		if (i == 0)
//			maxDepth = 2;
//		//else if (i == 1)
//		//	maxDepth = 3; \
//		//else if (i == 2)
//		//	maxDepth = 4;
//		//else if (i <= 4)
//		//	maxDepth = 5;
//		//else if (i <= 8)
//		//	maxDepth = 6;
//		//else if (i <= 16)
//		//	maxDepth = 7;
//		//else if (i <= 32)
//		//	maxDepth = 8;
//		else
//			maxDepth = 9;
//
//		//maxDepth = 2;
//	}
//
//	inline void draw(vector3d position, int rot){
//		top.drawTri(position, rot);
//		bottom.drawTri(position, rot);
//		left.drawTri(position, rot);
//		right.drawTri(position, rot);
//	}
//
//	inline void compareDistance(const vector3d cam, BYTE pHeightMap[], int rot, const vector3d position){
//
//		vector3d NewCen(curveCentre.X, curveCentre.Y, curveCentre.Z);
//
//		NewCen = NewCen.rotate(rot);
//
//		float Distance = fabs(sqrt(pow(cam.X - NewCen.X - position.X, 2) + pow(cam.Y - NewCen.Y - position.Y, 2) + pow(cam.Z - NewCen.Z - position.Z, 2)));
//
//		//float Distance = 500;
//
//		int newDepth;
//
//		if (Distance < 250)
//			newDepth = 9;
//		else if (Distance < 375)
//			newDepth = 8;
//		else if (Distance < 500)
//			newDepth = 7;
//		else if (Distance < 750)
//			newDepth = 6;
//		else if (Distance < 100)
//			newDepth = 5;
//		else if (Distance < 1250)
//			newDepth = 4;
//		else if (Distance < 1500)
//			newDepth = 3;
//		else
//			newDepth = 2;
//
//		if (newDepth > maxDepth)
//			newDepth = maxDepth;
//
//		if (newDepth != depth || (!isEdge && wasEdge)){
//			depth = newDepth;
//			wasEdge = false;
//			fixed = false;
//			updateQuad(pHeightMap);
//		//	left = triangler(A,B,D,0,pHeightMap,depth);
//		//	right = triangler(C,B,D,0,pHeightMap,depth);
//		}
//	}
//
//	inline void updateQuad(BYTE pHeightMap[]){
//		top = triangler(centre,A,B,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),A.X,B.X), vector3d(((B.Z+D.Z)/2),A.Z,B.Z), drawChild);
//		bottom = triangler(centre,C,D,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),C.X,D.X), vector3d(((B.Z+D.Z)/2),C.Z,D.Z), drawChild);
//		left = triangler(centre,D,A,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),D.X,A.X), vector3d(((B.Z+D.Z)/2),D.Z,A.Z), drawChild);
//		right = triangler(centre,B,C,0,pHeightMap,depth, radius, vector3d(((B.X+D.X)/2),B.X,C.X), vector3d(((B.Z+D.Z)/2),B.Z,C.Z), drawChild);
//	}
//};
//
///*
//void split(struct triangle* orgTriangle){
//
//	if (orgTriangle->depth == 1){
//		orgTriangle->drawTri();
//	}
//	else{
//		orgTriangle->splitTri();
//		split(orgTriangle->childA);
//		split(orgTriangle->childB);
//	}
//
//	//cout<<ceil(orgTriangle->distanceFC/200);
//	/*
//	if((orgTriangle->depth != 5) && orgTriangle->depth == (ceil(orgTriangle->distanceFC/50))){
//		orgTriangle->split = true;
//		triangle *leftChild;
//		triangle *rightChild;
//		if ( orgTriangle->rightAng == 'A'){
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->A, orgTriangle->B, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->A, orgTriangle->C, orgTriangle->depth, orgTriangle->camera);
//		}
//		else if ( orgTriangle->rightAng == 'B'){
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->B, orgTriangle->A, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->B, orgTriangle->C, orgTriangle->depth, orgTriangle->camera);
//		}
//		else {
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->C, orgTriangle->A, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->C, orgTriangle->B, orgTriangle->depth, orgTriangle->camera);
//		}
//		split(leftChild);
//		split(rightChild);
//	}
//	else {
//		glColor3f(0,1.0f,0);
//		glVertex3f(orgTriangle->A.X,orgTriangle->A.Y,orgTriangle->A.Z);
//		glColor3f(1.0f,0,0);
//		glVertex3f(orgTriangle->B.X,orgTriangle->B.Y,orgTriangle->B.Z);
//		glColor3f(0,0,1.0f);
//		glVertex3f(orgTriangle->C.X,orgTriangle->C.Y,orgTriangle->C.Z);
//	}
//	
//	if (orgTriangle->depth == (ceil(orgTriangle->distanceFC/200)) || orgTriangle->depth == 7){
//		glColor3f(0,1.0f,0);
//		glVertex3f(orgTriangle->A.X,orgTriangle->A.Y,orgTriangle->A.Z);
//		glColor3f(1.0f,0,0);
//		glVertex3f(orgTriangle->B.X,orgTriangle->B.Y,orgTriangle->B.Z);
//		glColor3f(0,0,1.0f);
//		glVertex3f(orgTriangle->C.X,orgTriangle->C.Y,orgTriangle->C.Z);
//	}
//	else {
//		orgTriangle->split = true;
//		triangle *leftChild;
//		triangle *rightChild;
//		if ( orgTriangle->rightAng == 'A'){
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->A, orgTriangle->B, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->A, orgTriangle->C, orgTriangle->depth, orgTriangle->camera);
//		}
//		else if ( orgTriangle->rightAng == 'B'){
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->B, orgTriangle->A, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->B, orgTriangle->C, orgTriangle->depth, orgTriangle->camera);
//		}
//		else {
//			leftChild = new triangle(orgTriangle->splitPoint, orgTriangle->C, orgTriangle->A, orgTriangle->depth, orgTriangle->camera);
//			rightChild = new triangle(orgTriangle->splitPoint, orgTriangle->C, orgTriangle->B, orgTriangle->depth, orgTriangle->camera);
//		}
//
//		//		leftChild->ABNeighbour = rightChild;   //develop this code
//		//		rightChild->ACNeighbour = leftChild;
//		split(leftChild);
//		split(rightChild);
//	}
//	*/
////}
//
//struct platform{
//	quad top[(MAP_SIZE/STEP_SIZE)*(MAP_SIZE/STEP_SIZE)];
//	vector<bool> changed;
//	vector3d position;
//	int rotate;
//	bool drawChild;
//
//	inline platform( void ) {}
//	inline platform( const vector3d pos, BYTE pHeightMap[], const int rot, float radius, bool dChild){
//		drawChild = dChild;
//		position = pos;
//		rotate = rot;
//		int i = 0;
//
//		for ( int X = 0; X < MAP_SIZE; X += STEP_SIZE){
//			for ( int Y = 0; Y < MAP_SIZE; Y += STEP_SIZE)
//			{
//				vector3d TestA, TestB, TestC, TestD;
//
//				TestA = vector3d(X+STEP_SIZE,0,Y);
//				TestB = vector3d(X,0,Y);
//				TestC = vector3d(X+STEP_SIZE,0,Y+STEP_SIZE);
//				TestD = vector3d(X,0,Y+STEP_SIZE);
//
//				changed.push_back(false);
//				top[i] = quad(TestB, TestD, TestC, TestA, pHeightMap, radius, drawChild);
//				i++;
//			}
//		}
//	}
//
//	inline void bubbleSortArray(vector<vector3d> *unPo, int *count, bool vert){
//		int i, j, flag = 1;    // set flag to 1 to start first pass
//		vector3d temp;             // holding variable
//		for(i = 0; (i <= *count) && flag; i++){
//			flag = 0;
//			for (j=0; j < (*count -1); j++){
//				if (vert){
//					if ((*unPo)[j+1].X < (*unPo)[j].X){
//						temp = (*unPo)[j];             
//						(*unPo)[j] = (*unPo)[j+1];
//						(*unPo)[j+1] = temp;
//						flag = 1;           
//					}
//				}
//				else{
//					if ((*unPo)[j+1].Z < (*unPo)[j].Z){
//						temp = (*unPo)[j];             
//						(*unPo)[j] = (*unPo)[j+1];
//						(*unPo)[j+1] = temp;
//						flag = 1;           
//					}
//				}
//			}
//		}
//	}
//
//	inline float findHeight(triangler *tri, vector3d point, float temp){
//		if (temp != 0)
//			return temp;
//		if(tri->depth == tri->maxDepth){
//			if (tri->A.Equals(point))
//				return temp = tri->heightA;
//			else if (tri->B.Equals(point))
//				return temp = tri->heightB;
//			else if (tri->C.Equals(point))
//				return temp = tri->heightC;
//		}
//		else{
//			temp = findHeight(tri->childA, point, temp);
//			temp = findHeight(tri->childB, point, temp);
//		}
//		return temp;
//	}
//
//	inline vector3d applyRadius(vector3d point, float radius, float height){
//			vector3d vector;
//			float mag;
//
//			vector.X = point.X - (MAP_SIZE/2);
//			vector.Y = point.Y - (MAP_SIZE/2);
//			vector.Z = point.Z - (MAP_SIZE/2);
//			
//			mag = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
//
//			vector.X = (vector.X/mag)*(radius + height);
//			vector.Y = (vector.Y/mag)*(radius + height);
//			vector.Z = (vector.Z/mag)*(radius + height);
//			
//			return vector3d(vector.X + (MAP_SIZE/2), vector.Y + (MAP_SIZE/2), vector.Z + (MAP_SIZE/2));
//	}
//
//	inline vector3d determineInsert(vector3d newPoint, vector<vector3d> *unPo, int *count, bool vert, triangler *neighbour){
//		int position = 0;
//		float differenceAB, differenceANew, ratio, posAHeight = 0, posBHeight = 0;
//		float heightChange = 0;
//		vector3d changedVector, posAReal, posBReal, orgReal;
//		for(int i = 0; i < *count; i++){
//			if (vert){
//
//				if (newPoint.X >= (*unPo)[i].X){
//					position++;
//				}
//				else
//					break;
//			}
//			else{
//				if (newPoint.Z >= (*unPo)[i].Z){
//					position++;
//				}
//				else
//					break;
//			}
//		}
//		//if (position != 0){
//			if (vert){
//				differenceAB = (*unPo)[position].X-(*unPo)[position-1].X;
//				differenceANew = newPoint.X-(*unPo)[position-1].X;
//			}
//			else{
//				differenceAB = (*unPo)[position].Z-(*unPo)[position-1].Z;
//				differenceANew = newPoint.Z-(*unPo)[position-1].Z;
//			}
//		
//			ratio = differenceANew/differenceAB;
//
//			if (neighbour->radius == 0){
//				changedVector.X = newPoint.X;
//				changedVector.Y = ((*unPo)[position].Y+(*unPo)[position-1].Y)/2;
//				changedVector.Z = newPoint.Z;
//			}
//			else{
//				posAHeight = findHeight(neighbour,(*unPo)[position], posAHeight);
//				posBHeight = findHeight(neighbour,(*unPo)[position-1], posBHeight);
//
//			//orgReal = applyRadius(newPoint,neighbour->radius, posAHeight);
//				posAReal = applyRadius((*unPo)[position],neighbour->radius, posAHeight);
//				posBReal = applyRadius((*unPo)[position-1],neighbour->radius, posBHeight);
//
//			
//			//ratio = (posAReal.X - posBReal.X)/(orgReal.X - posBReal.X);
//				changedVector.X = ((posAReal.X-posBReal.X)*ratio)+posBReal.X;
//
//			//ratio = (posAReal.Y - posBReal.Y)/(orgReal.Y - posBReal.Y);
//				changedVector.Y = ((posAReal.Y-posBReal.Y)*ratio)+posBReal.Y;
//
//			//ratio = (posAReal.Z - posBReal.Z)/(orgReal.Z - posBReal.Z);
//				changedVector.Z = ((posAReal.Z-posBReal.Z)*ratio)+posBReal.Z;
//			}
//			
//			//heightChange = ((posAHeight-posBHeight)*ratio)+posBHeight;
//			//if (posAReal.X > posBReal.X)			
//			//changedVector.X = ((posAReal.X-posBReal.X)*ratio)+posBReal.X;
//			//else
//			//	changedVector.X = ((posBReal.X-posAReal.X)*ratio)+posBReal.X;
//				
//			//ratio = (posAReal.Y - posBReal.Y)/(newPoint.Y - posBReal.Y);
//			
//			//if (posAReal.Y > posBReal.Y)			
//			//changedVector.Y = ((posAReal.Y-posBReal.Y)*ratio)+posBReal.Y;
//			//else
//			//	changedVector.Y = ((posBReal.Y-posAReal.Y)*ratio)+posBReal.Y;
//			//ratio = (posAReal.Z - posBReal.Z)/(newPoint.Z - posBReal.Z);
//			//if (posAReal.Z > posBReal.Z)			
//			//changedVector.Z = ((posAReal.Z-posBReal.Z)*ratio)+posBReal.Z;
//			//else
//			//	changedVector.Z = ((posBReal.Z-posAReal.Z)*ratio)+posBReal.Z;
//			//changedVector.X = ((posBReal.X-posAReal.X)*ratio)+posBReal.X
//			//changedVector.Y = ((posAReal.Y-posBReal.Y)*ratio)+posAReal.Y;
//			//changedVector.Z = ((posAReal.Z-posBReal.Z)*ratio)+posAReal.Z;
//
//			//changedVector.X = (posAReal.X+posBReal.X)*0.5;
//			//changedVector.Y = (posAReal.Y+posBReal.Y)*0.5;
//			//changedVector.Z = (posAReal.Z+posBReal.Z)*0.5;
//
//			//changedVector.X = posBReal.X;
//			//changedVector.Y = posBReal.Y;
//			//changedVector.Z = posBReal.Z;
//
//		//}
//		//else
//		//	heightChange = findHeight(neighbour,(*unPo)[position]);
//
//		//return 0;
//		return changedVector;
//	}
//
//	inline bool vectorInArray(vector3d point, vector<vector3d> *unPo, int *count){
//		for (int i = 0; i<*count; i++){
//			if (point.X == (*unPo)[i].X && point.Y == (*unPo)[i].Y && point.Z == (*unPo)[i].Z)
//				return true;
//		}
//		return false;
//	}
//
//	inline void search(triangler *tri, triangler *neighbour, int edge, vector<vector3d> *unPo, int *count, bool updating, bool vert){
//		bool fixed = false;
//		if(tri->depth == tri->maxDepth){
//			if ((tri->A.Z == edge && vert) || (tri->A.X == edge && !vert))
//				if (!vectorInArray(tri->A,unPo,count)){
//					if (!updating){
//						unPo->push_back(tri->A);
//						*count = *count + 1;
//					}
//					else{
//						tri->ACur = determineInsert(tri->A,unPo,count,vert, neighbour);
//						int sdfsdf = 1;
//						//tri->updatePointA();
//					}
//				}
//			if ((tri->B.Z == edge && vert) || (tri->B.X == edge && !vert))
//				if (!vectorInArray(tri->B,unPo,count)){
//					if (!updating){
//						unPo->push_back(tri->B);
//						*count = *count + 1;
//					}
//					else{
//						tri->BCur = determineInsert(tri->B,unPo,count,vert, neighbour);
//						int sdfsdf = 1;
//						//tri->updatePointB();
//					}
//				}
//			if ((tri->C.Z == edge && vert) || (tri->C.X == edge && !vert))
//				if (!vectorInArray(tri->C,unPo,count)){
//					if (!updating){
//						unPo->push_back(tri->C);
//						*count = *count + 1;
//					}
//					else{
//						tri->CCur = determineInsert(tri->C,unPo,count,vert, neighbour);
//						int sdfsdf = 1;
//						//tri->updatePointC();
//					}
//				}
//		}
//		else{
//			search(tri->childA, neighbour, edge, unPo, count, updating, vert);
//			search(tri->childB, neighbour, edge, unPo, count, updating, vert);
//		}
//	}
//
//	inline void edgeCrackSearch(triangler *currentTri, triangler *neighbourTri, bool vert){
//		int count=0;
//		vector<vector3d> uniquePoints;
//		
//		if (currentTri->maxDepth > neighbourTri->maxDepth){
//			if (vert)
//				search(neighbourTri, currentTri, currentTri->B.Z,&uniquePoints,&count, false, vert);
//			else
//				search(neighbourTri, currentTri, currentTri->B.X,&uniquePoints,&count, false, vert);
//			bubbleSortArray(&uniquePoints,&count,vert);
//			if (vert)
//				search(currentTri, neighbourTri, currentTri->B.Z,&uniquePoints,&count, true, vert);
//			else
//				search(currentTri, neighbourTri, currentTri->B.X,&uniquePoints,&count, true, vert);
//		}
//
//		count = count;
//	}
//
//	/*inline void depthCrackSearch(quad *currentQuad, quad *topQuad, quad *bottomQuad, quad *rightQuad, quad *leftQuad){
//		bool isEdge, wasEdge;
//		
//		wasEdge = currentQuad->wasEdge;
//		isEdge = false;
//
//
//			if ((topQuad->A.X + STEP_SIZE) == currentQuad->A.X && topQuad->depth != currentQuad->depth){
//				edgeCrackSearch(&currentQuad->top, &topQuad->bottom, false);
//				isEdge = true;
//				wasEdge = true;
//			}
//			if ((bottomQuad->A.X - STEP_SIZE) == currentQuad->A.X && bottomQuad->depth != currentQuad->depth){
//				edgeCrackSearch(&currentQuad->bottom, &bottomQuad->top, false);
//				isEdge = true;
//				wasEdge = true;
//			}
//			if ((rightQuad->A.Z - STEP_SIZE) == currentQuad->A.Z && rightQuad->depth != currentQuad->depth){
//				edgeCrackSearch(&currentQuad->right, &rightQuad->left, true);
//				isEdge = true;
//				wasEdge = true;
//			}
//			if ((leftQuad->A.Z + STEP_SIZE) == currentQuad->A.Z && leftQuad->depth != currentQuad->depth){
//				edgeCrackSearch(&currentQuad->left, &leftQuad->right, true);
//				isEdge = true;
//				wasEdge = true;
//			}
//
//			currentQuad->isEdge = isEdge;
//			currentQuad->wasEdge = wasEdge;
//	}*/
//
//	inline void depthCrackSearch(quad *currentQuad, quad *neighbourQuad, int side, bool vert){
//		if (side == 0){edgeCrackSearch(&currentQuad->top, &neighbourQuad->bottom, vert);}
//		else if (side == 1){edgeCrackSearch(&currentQuad->right, &neighbourQuad->left, vert);}
//		else if (side == 2){edgeCrackSearch(&currentQuad->bottom, &neighbourQuad->top, vert);}
//		else if (side == 3){edgeCrackSearch(&currentQuad->left, &neighbourQuad->right, vert);}
//	}
//
//	inline bool compareDirections(const vector3d cameraDir, vector3d a, vector3d b, vector3d c, vector3d d, int rot, float radius){
//		vector3d centreA;
//		vector3d vector, A, B;
//		float mag, dot, Atotal, Btotal, angle;
//
//		a = applyRadius(a,radius,0);
//		b = applyRadius(b,radius,0);
//		c = applyRadius(c,radius,0);
//		d = applyRadius(d,radius,0);
//
//		A = vector3d(a.X-c.X,a.Y-c.Y,a.Z-c.Z);
//		B = vector3d(b.X-d.X,b.Y-d.Y,b.Z-d.Z);
//
//		A = A.rotate(rot);
//		B = B.rotate(rot);
//
//		vector = vector3d(A.Y*B.Z - A.Z*B.Y, A.Z*B.X - A.X*B.Z, A.X*B.Y - A.Y*B.X);
//		
//		if (rot == 2 || rot == 3 || rot == 5)
//			vector = vector3d(-vector.X, -vector.Y, -vector.Z);
//
//		dot = (vector.X * cameraDir.X) + (vector.Y * cameraDir.Y) + (vector.Z * cameraDir.Z);
//		Atotal = sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
//		Btotal = sqrt((cameraDir.X * cameraDir.X) + (cameraDir.Y * cameraDir.Y) + (cameraDir.Z * cameraDir.Z));
//
//		angle = acos(dot/(Atotal*Btotal));
//
//		if (angle < (M_PI*0.375f))
//			return false;
//		else
//			return true;
//	}
//
//	/*inline void findPoints(triangler *tri, vector3d *unPo, int *count){
//		if(tri->depth == tri->maxDepth){
//			if (!vectorInArray(tri->A,unPo,count)){
//				unPo[*count] = tri->A;
//				*count = *count + 1;
//			}
//			if (!vectorInArray(tri->B,unPo,count)){
//				unPo[*count] = tri->B;
//				*count = *count + 1;
//			}
//			if (!vectorInArray(tri->C,unPo,count)){
//				unPo[*count] = tri->C;
//				*count = *count + 1;
//			}
//		}
//		else{
//			findPoints(tri->childA, unPo, count);
//			findPoints(tri->childB, unPo, count);
//		}
//	}
//
//	inline void drawTriFan(quad *currentQuad){
//		vector3d uniquePoints[100];
//		int count=0;
//		findPoints(&currentQuad->top, uniquePoints, &count);
//		findPoints(&currentQuad->right, uniquePoints, &count);
//		findPoints(&currentQuad->bottom, uniquePoints, &count);
//		findPoints(&currentQuad->left, uniquePoints, &count);
//		
//		glEnd();
//		glBegin (GL_TRIANGLE_STRIP);
//
//		for (int i = 0; i<count; i++){
//			glColor3f(0,1,0);
//			glVertex3f(uniquePoints[i].X,uniquePoints[i].Y,uniquePoints[i].Z);
//			numOfVer++;
//		}
//
//		glEnd();
//		glBegin (GL_TRIANGLES);
//	}*/
//
//	inline void draw(const vector3d camera, const vector3d cameraDir, BYTE pHeightMap[]){
//		int i = 0, oldDepth, newDepth, topNum, botNum, leftNum, rightNum;
//		bool temp;
//
//		if (once){
//		for ( int X = 0; X < MAP_SIZE; X += STEP_SIZE){
//			for ( int Y = 0; Y < MAP_SIZE; Y += STEP_SIZE)
//			{	
//				//if (compareDirections(cameraDir, top[i].A, top[i].B, top[i].C, top[i].D, rotate, top[i].radius)){
//					changed[i] = false;
//					oldDepth = top[i].depth;
//					top[i].compareDistance(camera, pHeightMap, rotate, position);
//					newDepth = top[i].depth;
//			
//					if (oldDepth != newDepth)
//						changed[i] = true;
//				//}
//				i++;
//			}
//		}
//		}
//		//once = false;
//
//		i = 0;
//		bool update;
//		for ( int X = 0; X < MAP_SIZE; X += STEP_SIZE){
//			for ( int Y = 0; Y < MAP_SIZE; Y += STEP_SIZE)
//			{
//				//////if (compareDirections(cameraDir, top[i].A, top[i].B, top[i].C, top[i].D, rotate, top[i].radius)){
//					//top[i].isEdge = false;
//					update = false;
//
//					topNum = i-(MAP_SIZE/STEP_SIZE);
//					botNum = i+(MAP_SIZE/STEP_SIZE);
//					leftNum = i-1;
//					rightNum = i+1;
//
//					if (!update && topNum >= 0) {if(changed[topNum]) update = true;}
//					if (!update &&  botNum <= changed.size()-1) {if(changed[botNum]) update = true;}
//					if (!update && leftNum >= 0)	{if(changed[leftNum]) update = true;}
//					if (!update && rightNum <= changed.size()-1) {if(changed[rightNum]) update = true;}
//
//					if (update)
//						top[i].updateQuad(pHeightMap);
//
//				//if (!top[i].fixed){
//						top[i].isEdge = false;
//					if (topNum < 0) 
//						topNum = 0;
//					else {
//						if(top[i].depth != top[topNum].depth &&
//							top[i].right.B.Equals(top[topNum].bottom.B) &&
//							top[i].top.B.Equals(top[topNum].left.B)) {
//							//	cout << "TOP  \r";
//							//depthCrackSearch(&top[i],&top[topNum], 0, false);
//						}
//					}
//
//					if (botNum > changed.size()-1) 
//						botNum = 0;
//					else {
//						if(top[i].depth != top[botNum].depth &&
//							top[i].bottom.B.Equals(top[botNum].right.B) &&
//							top[i].left.B.Equals(top[botNum].top.B)) {
//							//	cout << "BOTTOM  \r";
//							//depthCrackSearch(&top[i],&top[botNum], 2, false);
//						}
//					}
//	
//					if (leftNum < 0) 
//						leftNum = 0;
//					else {
//						if(top[i].depth != top[leftNum].depth &&
//							top[i].top.B.Equals(top[leftNum].right.B) &&
//							top[i].left.B.Equals(top[leftNum].bottom.B)) {
//							//cout << "LEFT  \r";
//							//depthCrackSearch(&top[i],&top[leftNum], 3, true);
//						}
//					}
//
//					if (rightNum > changed.size()-1) 
//						rightNum = 0;
//					else {
//						if(top[i].depth != top[rightNum].depth &&
//							top[i].right.B.Equals(top[rightNum].top.B) &&
//							top[i].bottom.B.Equals(top[rightNum].left.B)){
//							//cout << "RIGHT  \r";
//							derpherpepre++;
//							//cout << derpherpepre << "    RIGHT       \r";
//		
//							//if (derpherpepre == 10992){
//							//	cout << "OH SHIT!!!  \r";
//							//}
//	
//							//depthCrackSearch(&top[i],&top[rightNum], 1, true);
//						}
//					}//*/
//				//}
//				//top[i].fixed = true;
//
//
//		//		if ((changed[topNum] || changed[botNum] || changed[leftNum] || changed[rightNum]) && top[i].isEdge)
//		//			top[i].updateQuad(pHeightMap);
//
//				//depthCrackSearch(&top[i],&top[topNum],&top[botNum],&top[rightNum],&top[leftNum]);
//				//drawTriFan(&top[i]);
//				top[i].draw(position, rotate);
//				//////}
//				i++;
//			}
//		}
//	}
//};
//
//struct sphereal{
//	platform top, bottom, front, back, left, right;
//	vector3d position;
//	float radius;
//	int size;
//	
//	inline sphereal( void ) {}
//	inline sphereal( const vector3d pos, BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[]){
//		position = pos;
//		size = MAP_SIZE/2;
//
//		vector3d vector;
//		
//		vector.X = pos.X-size - pos.X;
//		vector.Y = pos.Y+size - pos.Y;
//		vector.Z = pos.Z-size - pos.Z;
//
//		radius = fabs(sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z)));
//		//radius = 0;
//
//		top = platform(vector3d(pos.X-size, pos.Y+size, pos.Z-size), topHM, 1, radius, true);
//		bottom = platform(vector3d(pos.X-size, pos.Y-size, pos.Z-size), bottomHM, 2, radius, false);
//		front = platform(vector3d(pos.X-size, pos.Y-size, pos.Z+size), frontHM, 3, radius, false);
//		back = platform(vector3d(pos.X-size, pos.Y-size, pos.Z-size), backHM, 4, radius, true);
//		left = platform(vector3d(pos.X+size, pos.Y-size, pos.Z-size), leftHM, 5, radius, false);
//		right = platform(vector3d(pos.X-size, pos.Y-size, pos.Z-size), rightHM, 6, radius, true);
//	}
//
//	inline void draw(const vector3d camera, const vector3d cameraDir, BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[]){
//		top.draw(camera, cameraDir, topHM);
//		bottom.draw(camera, cameraDir, bottomHM);
//		front.draw(camera, cameraDir, frontHM);
//		back.draw(camera, cameraDir, backHM);
//		left.draw(camera, cameraDir, leftHM);
//		right.draw(camera, cameraDir, rightHM);
//	}
//};
//
////sphereal worldwide;
//platform testtttrr;
//
//void createHeightMap(BYTE pHeightMap[], BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[]){
//	testtttrr = platform(vector3d(0,0,0), pHeightMap, 2, 0, true);
//	//worldwide = sphereal(vector3d(0,0,0), topHM, bottomHM, frontHM, backHM, leftHM, rightHM);
//}
//
//int Height(BYTE *pHeightMap, int X, int Y)
//{
//	int x = X % MAP_SIZE;					// Error check our x value
//	int y = Y % MAP_SIZE;					// Error check our y value
//
//	if(!pHeightMap) return 0;				// Make sure our data is valid
//
//	//return 0;
//	return pHeightMap[x + (y * MAP_SIZE)];	// Index into our height array and return the height
//}
//
////void test(float CamA, float CamB, float CamC, float CamDirA, float CamDirB, float CamDirC, BYTE pHeightMap[], BYTE topHM[], BYTE bottomHM[], BYTE frontHM[], BYTE backHM[], BYTE leftHM[], BYTE rightHM[], bool stop){
//void test(float CamA, float CamB, float CamC, float CamDirA, float CamDirB, float CamDirC, BYTE pHeightMap[], bool stop){
//	vector3d TestA(0,0,0), TestB(1000,0,0), TestC(0,0,1000), TestD(1000,0,1000), Camera(CamA,CamB,CamC), Direction(CamDirA,CamDirB,CamDirC);
//
//	numOfVer = 0;
//
//	once = stop;
//
//	//float colour;
//	//triangle *root;
//	//root = new triangle(TestA, TestB, TestC, 0, Camera);
////	triangle *temp;
//
//	//temp = root;
//
//	//glDisable(GL_LIGHTING);									//Enable lighting
//	//glDisable(GL_LIGHT0);									//Enable light0
//	glEnable(GL_CULL_FACE);
//
//	glBegin (GL_TRIANGLES);
//
//	//glFrontFace(GL_CW);
//	//glBegin (GL_TRIANGLE_STRIP);
//
//	testtttrr.draw(Camera, Direction, pHeightMap);
//	//worldwide.draw(Camera, Direction, pHeightMap, pHeightMap, pHeightMap, pHeightMap, pHeightMap, pHeightMap);
//
//	glEnd();
//	glColor4f(1.0f,1.0f,1.0f,1.0f);
//
//	//split(root);
//
////	while(temp->depth != 5){
////		temp->splitTri();
////		temp = temp->childA;
////	}
////	testtttrr.draw();
////	temp->drawTri();
//
//	//temp->childA->drawTri();
//	//temp->childB->drawTri();
//	//split(root);
//int derp = sizeof(numOfVer);
//	glEnd();
//
//	glColor4f(1.0f,1.0f,1.0f,1.0f);
//}
//
///*
//		vector3d empty(0,0,0);
//		A = empty; B = empty; C = empty; D = empty; centre = empty;
//		//top = NULL; bottom = NULL; left = NULL; right = NULL;
//
//		depth = 2;
//		wasEdge = false;
//		isEdge = false;	*/