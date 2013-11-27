How to Install:

Because this application uses older OpenGL files, I have provided the files in the GLUT folder.
Follow the instructions, then rebuild and run the solution in Visual Studios
	
	- In the Solution Explorer in Visual Studios, right click on TerrianLOD, Properties, Configuration Properties, Linker, General, Additional Library Directories, Add the GLUT folder. 
	- Copy glut.h file to Program Files (x86)/Windows Kits/8.0/Include/um/gl
	- Copy glut32.dll to your Windows/SysWOW64 folder


How to Run:

Copy paste the 6 HMP Files in the TerrianLOD into the Release Folder then run the TerrianLOD application.


Controls:

Click and Drag with the mouse to turn
Arrow keys move forward back and side to side
F1 - Pause LOD algorithms (Useful to see what is and is not being drawn at the point in time
F2 - Disable/Enable Lighting
F3 - Select smooth model
F4 - Select plains model
F5 - Select hills model
F6 - Select mountain model
F7 - Select spiked model
F8 - Select tiered model