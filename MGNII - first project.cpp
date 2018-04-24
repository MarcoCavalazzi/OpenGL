#include <windows.h>
#include <stdlib.h>
#include <gl.h>
#include <glut.h>
#include <glu.h>

void myMouse(int button, int state, int x, int y)
{
	const int screenHeight = 480;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glBegin(GL_POINTS);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(x, screenHeight-y);
		glEnd();
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glClearColor(0.0,1.0,1.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glFlush();
}

void myMouse2(int button, int state, int x, int y)
{
	const int screenHeight = 480;
	typedef struct{GLint x,y;} GLintPoint;
	static GLintPoint corner[2];
	static int numCorners=0;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		typedef struct{GLint x,y;} GLintPoint;
		static GLintPoint corner[2];
		static int numCorners=0;
		if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
		{
			corner[numCorners].x=x;
			corner[numCorners].y=screenHeight-y;
			numCorners++;
			if(numCorners==2)
			{
				glRecti(corner[0].x,corner[0].y,corner[1].x,corner[1].y);
				numCorners=0;
			}
		}
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		glClearColor(0.0,1.0,1.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glFlush();
}

void myMouse3(int button, int state, int x, int y)
{
	#define NUM 20
	const int screenHeight=480;
	int i;
	typedef struct{GLint x,y;} GLintPoint;
	static GLintPoint List[NUM];
	static int last=-1;

	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN && last <(NUM-1))
	{
		List[++last].x=x;
		List[last].y=screenHeight-y;
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_STRIP);
		for (i=0;i<=last;i++)
			glVertex2i(List[i].x,List[i].y);
		glEnd();
		glFlush();
	}
	else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		last=-1;
}

void myInit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
	//il corner in basso a sinistra sta a (0,0), quello in alto a destra a (640,480)
}

void display(void)
{
	glClearColor(1.0,0.0,0.0,0.0);		//il quarto valore è la trasparenza
	glClear(GL_COLOR_BUFFER_BIT);		//pulisce lo schermo e lo mette al colore deciso sopra

	glColor3f(0.0,1.0,0.0);		//colore del disegno è verde. il colore è una variabile di stato, resta fisso finchè non lo cambio
	glPointSize(10.0);
	glBegin(GL_TRIANGLES);			//disegno punti
		glVertex2i(100,50);
		glColor3f(1.0,1.0,0.0);
		glVertex2i(100,130);
		glColor3f(0.0,1.0,1.0);
		glVertex2i(150,130);
	glEnd();
	glFlush();		//manda i vertici alla pipeline grafica per essere visualizzati
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//inizializzo display, con rgb
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,150);	//100px da sinistra e 150 dall'alto
	glutCreateWindow("Disegno");		//creo la finestra con nome disegno)
	
	glutDisplayFunc(display);	//crea il disegno
	glutMouseFunc(myMouse3);

	myInit();			//funzione in cui inizializzo il sistema di riferimento
	glutMainLoop();		//loop infinito
}