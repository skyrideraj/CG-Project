/*
IT 441 Computer Graphics Project [Traffic Simulation]
Akash Sharma   	[201001072]

*/



/* includes */
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <GL/glut.h>
#include "imageloader.h"
#define SELECT_BUFFER 32

/* globals */
GLuint signal_list = 0;			/* display list for traffic signal */
GLuint select_buffer[SELECT_BUFFER];	/* selection buffer */
GLint mouse_state = -1;
GLint mouse_button = -1;
GLuint picked = 1;			/* current light that is picked */
GLUquadricObj* quadric;
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId;

/* functions */




 GLfloat x=-48;

/*signal pole*/
void  lists()
{
  quadric = gluNewQuadric();
  gluQuadricDrawStyle(quadric, GLU_FILL);
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricOrientation(quadric, GLU_OUTSIDE);

  if (signal_list)
   
    glDeleteLists(signal_list, 1);

  signal_list = glGenLists(1);
  glNewList(signal_list, GL_COMPILE);
  glBegin(GL_QUADS);
  glColor3f(0.4, 0.4, 0.4);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glNormal3f( 0.0, 1.0, 0.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glNormal3f( 0.0, -1.0, 0.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glEnd();
  glEndList();  
  gluQuadricOrientation(quadric, GLU_INSIDE);

}
/* to create vehicle*/
void  lis()
{

  glBegin(GL_QUADS);
  glColor3f(1,0,0);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glNormal3f( 0.0, 1.0, 0.0);
  glVertex3f( 1.0,  3.0, -1.0);
  glVertex3f(-1.0,  3.0, -1.0);
  glVertex3f(-1.0,  3.0,  1.0);
  glVertex3f( 1.0,  3.0,  1.0);
  glNormal3f( 0.0, -1.0, 0.0);
  glVertex3f( 1.0, -3.0,  1.0);
  glVertex3f(-1.0, -3.0,  1.0);
  glVertex3f(-1.0, -3.0, -1.0);
  glVertex3f( 1.0, -3.0, -1.0);
  glEnd();

}
/*win functio to create side window and win1 to create back window*/
void  win()
{

  glBegin(GL_QUADS);
	glColor3f(0,0,0);
 glNormal3f( 0.0, -1.0, 0.0);
  glVertex3f(-1.0,  .8, -1.0);
  glVertex3f(-1.0, -.8, -1.0);
  glVertex3f(-1.0, -.8,  1.0);
  glVertex3f(-1.0,  .8,  1.0);

  glEnd();

}

void win1()
{
  glBegin(GL_QUADS);
 glColor3f(0,0,0);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-1.0,  1.9,  1.0);
  glVertex3f(-1.0, -1.9,  1.0);
  glVertex3f( 1.0, -1.9,  1.0);
  glVertex3f( 1.0,  1.9,  1.0);

  glEnd();
}




/* function to create the vechile ,its windows and tyres*/
void veh()
{
glTranslatef(0,0,-x);
	glPushMatrix();
glPushMatrix();
	glScalef(0.5,3,3);
glColor3f(0,0,0);
	glTranslated (4, -.8, 2.4);
	glutSolidSphere (0.15, 15, 15); //to create tyre
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5,3,3);
    glColor3f(0,0,0);
	glTranslated (4, -.8, .4);
	glutSolidSphere (0.15, 15, 15);// to create tyre
	glPopMatrix();
glPushMatrix();
	glScalef(.5,3,3);
glColor3f(0,0,0);
	glTranslated (12, -.8, 2.4);
	glutSolidSphere (0.15, 15, 15); // to create the tyre
	glPopMatrix();
	glTranslatef(4, -2.,5);
	glScalef(2,.2,5);
lis();
glPushMatrix();	
	glTranslatef(-.01,1.,.0);
win();              // to create  side window
	glPopMatrix();
	
glPushMatrix();	
glTranslatef(-.05, 1.4,0.05);
win1(); // to create back window
	glPopMatrix();	
   glPopMatrix();

}

/* to initate the program*/
void init(void)
{
  /* lighting */

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
 //glDepthFunc(GL_LEQUAL);
glEnable(GL_CULL_FACE);
 glClearColor(0, 0,0, 1.0);
glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glSelectBuffer(SELECT_BUFFER, select_buffer);
	Image* image = loadBMP("road.bmp");
	_textureId = loadTexture(image);


}



int timeopen=0;

/* to resize the window*/


void  reshape(int w, int h)
{
  GLfloat light_position[4] = { 0.3, 0.3, 0.3, 1 };
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)h / (GLfloat)w ,1.0, 128.0);
 glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glTranslatef(0.0, 0.0, -8.0);
  glRotatef(45.0, 0.0, 1.0, 0.0);
}


int k=0,call=0;
/* function to display text*/
void dispchar(int x,int y,char *s,void *font)
{
	int len,i;

	glRasterPos2f(x,y);
	len=(int)strlen(s);

	for(i=0;i<len;i++)
		glutBitmapCharacter(font,s[i]);
}
/* function to display three different light*/
void ligh()
{
	 glTranslatef(-2.9, -1.1, 1);
  if (picked == 1) {
    glDisable(GL_LIGHTING);
    glColor3f(0.03, 0.0, 0.0);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.75, 32, 32);
    glEnable(GL_LIGHTING);

k=1;

  } else {
    glColor3f(0.4, 0.4, 0.4);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(0.3, 0.0, 0.0);
    glutSolidSphere(0.75, 32, 32);
k=0;
  }
  glTranslatef(0.0, -1.75, 0.0);
  if (picked == 2) {
    glDisable(GL_LIGHTING);
    glColor3f(0.3, 0.3, 0.0);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(0.75, 32, 32);
    glEnable(GL_LIGHTING);
	k=2;

  } else {
    glColor3f(0.4, 0.4, 0.4);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(0.3, 0.3, 0.0);
    glutSolidSphere(0.75, 32, 32);

  }
  glTranslatef(0.0, -1.75, 0.0);
  if (picked == 3) {
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.3, 0.0);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(0.75, 32, 32);
    glEnable(GL_LIGHTING);

  } else {
    glColor3f(0.4, 0.4, 0.4);
    gluCylinder(quadric, 0.74, 0.74, 0.75, 32, 32);
    glColor3f(0.0, 0.3, 0.0);
    glutSolidSphere(0.75, 32, 32);
k=1;
  }

 glutPostRedisplay();
}








/* to display 1st screen*/

void screen()
{		 

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	gluOrtho2D(0,430,0,700);
glColor3f(1,0,0);
dispchar(400,490,"          ",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,1000," DA-IICT ",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-100,950," CG PROJECT ON",GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(0.7,0.7,0.7);
	dispchar(-100,700,"TRAFFIC SIMULATION",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.3,0.7,0.2);
	dispchar(-490,350,"  ",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(700,350,"",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.1,0.9,0.7);
	dispchar(-490,200,"GULSHAN DHINGRA   201001071",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-500,100,"     ",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.1,0.9,0.7);
	dispchar(550,180,"",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-490,400,"AKASH SHARMA	 201001072 ",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.0,0.9,0.0);
	dispchar(-100,-400,"PRESS ENTER TO START ",GLUT_BITMAP_TIMES_ROMAN_24);
	glPopMatrix();
	glutPostRedisplay();
}
/*to display instructions */
void ins()
{
	glPushMatrix();
		gluOrtho2D(0,430,0,700);
glColor3f(1,1,0);
dispchar(400,490,"          ",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,1300," Press r for red light",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,1200," Press o for orange light",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,1100," Press g for green light ",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,1000," Press x to exit,",GLUT_BITMAP_TIMES_ROMAN_24);
	dispchar(-400,900," Press tab to run car",GLUT_BITMAP_TIMES_ROMAN_24);


	glColor3f(0.7,0.7,0.7);
	dispchar(-100,700,"",GLUT_BITMAP_TIMES_ROMAN_24);
	glPopMatrix();
	glutPostRedisplay();
}
void display(void)

{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
if(timeopen==0)
{
screen();
 glutPostRedisplay();
}
else if(timeopen!=0)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
ins();
  glDisable(GL_LIGHT1);
glClearColor(.02,0,.02, 0);
 glDisable(GL_CULL_FACE);
 glPushMatrix();
lists();

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	GLfloat ambientLight[] = {1, 1, 1, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat directedLight[] = {1, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	float height = -4.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_NORMALIZE);
		glTranslatef(0.5f, 1.0f, -6.0f);
glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);	glVertex3f(-10, height, 2);
	glTexCoord2f(1, 1); glVertex3f(-10, height, -20);
	glTexCoord2f(0, 1); glVertex3f(10, height, -20);
	glTexCoord2f(0, 0); glVertex3f(10, height, 2);
	glEnd();

  glEnable(GL_CULL_FACE);
	glTranslatef(-.1, .3, 0);
glScalef(.08,.15,.1);
ligh();
  glTranslatef(0.0, -3.7, -1.0);
glScalef(1,3,1);
  glCallList(signal_list);
if(call==1&&k==0)
x=x+.1;

if(k==2||k==0){
x=x+0.04;
}
if(k==0||k==1)
if(x>-14&&x<=12)
{
x=x+.1;
if(k==2||k==0){
x=x+0.04;
}
}

if(k==0||k==1)
{
	if(x>12)
{
x=x+.5;

}
}
veh();

if(x>=60)
x=-48;
glPopMatrix();
  glPopMatrix();
}


  glutSwapBuffers();
 glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y)
 {


	switch (key) 
	{
	case '\t': // tab key
		call=1;
break;	
	case 'r': // r key
	picked =1;
break;

	case 'o': // o key
	picked =2;

break;
	case 'g': // g key
	picked =3;

break;
	case '\r': // enter key
timeopen++;

break;

case 'x': //x key
exit(0);

break;

	}

}






main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(700, 700);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Traffic Simulator");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
  init();
  glutMainLoop();
  return 0;
}







using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) { }

Image::~Image()
 {
	delete[] pixels;
}

int toInt(const char* bytes)     
{   
	return (int)(((char)bytes[3] << 24) |(( char)bytes[2] << 16) |(( char)bytes[1] << 8) |( char)bytes[0]);
	}	
int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}

template<class T>
	class auto_array
{
private:
			T* array;
		int isReleased;
public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {	}	
~auto_array() 
				{
				if (!isReleased && array != NULL) 
				{
					delete[] array;
				}
			}
			
T* get() const 
		{
			return array;
			}
			
	
T* release() 
			{
			isReleased = true;
				return array;
			}
	
		T* operator+(int i)
		{
				return array + i;
			}
			
			T &operator[](int i) 
			{
				return array[i];
			}
	};


Image* loadBMP(const char* filename) {
	ifstream input;
	input.open(filename, ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);
	
	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readInt(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readInt(input) == 0 || !"Image is compressed");
			break;
		default:
			assert(!"Unknown bitmap format");
	}
	
	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);
	
	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++) 
		{
			for(int c = 0; c < 3; c++)
			{
				pixels2[3 * (width * y + x) + c] =	pixels[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}
	
	input.close();
	return new Image(pixels2.release(), width, height);
}

