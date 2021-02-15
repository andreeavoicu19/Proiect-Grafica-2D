#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>


using namespace std;

static GLint windowSizeX = 800, windowSizeY = 1200;
static GLint orthoSizeX = 600, orthoSizeY = 400;


static char scor_1[20], scor_2[20];
static GLint jucator1_scor = 0, jucator2_scor = 0;
static GLint marginePaleta = 350, inaltimePaleta = 150, vitezaPaleta = 8.0;
static GLint jucator1_paleta_y = 0, jucator2_paleta_y = 0, paleta_x = 595;
static GLfloat viteza_minge_x = 0, viteza_minge_y = 0, crestereViteza = 0.5;
static GLint pozitie_minge_x = 0, pozitie_minge_y = 0, raza_minge = 20;

double x = 0.0;
double i = 0.0;
double j = 0.0;
double alpha = 1.0;
const int poligon = 1;
const double PI = 3.1415926; 

class scrPt {

public:
	GLint x, y;

};


// initializarea ecranului negru
void init(void) {
  
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	srand(time(NULL));

}


// desenarea cifrelor pe ecran
void desenareScor(char *string, int x, int y, int z) {

	char *c;
	glPushMatrix();

	glTranslatef(x, y + 7, z);
	glScalef(0.4, 0.4, z);
	for (c = string; *c != '\0'; c++) {

		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
		glutStrokeWidth(GLUT_STROKE_ROMAN, *c);
		glLineWidth(3);
	}

	glPopMatrix();

}


// desenarea textului de la finalul jocului
void desenareText(char *string, int x, int y, int z) {
	
	char *c;

	glRasterPos3f(x, y, z);
	glColor3f(1.0, 1.0, 1.0);

	for (c = string; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	
}


// desenarea liniilor centrale cu spatiu de 30 px intre ele si latime de 4 px
void desenareLiniiCentrale() {

	for (int i = -410; i < 400 + 10; i += 40) {

		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-2, i);
		glVertex2f(2, i);
		glVertex2f(2, i + 30);
		glVertex2f(-2, i + 30);
		glEnd();
	}

}


// x, y este coordonata din stanga sus a paletei
void desenarePaleta(int x, int y) {

	glPushMatrix();

	glTranslatef(x, y, 0);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	int inaltime = inaltimePaleta / 2;
	glVertex2f(-15, inaltime); // latime paleta 15
	glVertex2f(15, inaltime);
	glVertex2f(15, -inaltime);
	glVertex2f(-15, -inaltime);
	glEnd();

	glPopMatrix();

}


void desenareMinge(int x, int y) {

	double randomR, randomG, randomB;

	glPushMatrix();

	glTranslatef(x, y, 0);
	
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			randomR = (double)rand() / (RAND_MAX);
			randomG = (double)rand() / (RAND_MAX);
			randomB = (double)rand() / (RAND_MAX);
			glColor3f(randomR, randomG, randomB);
		}
	}
	glutSolidSphere(raza_minge, 20, 16);

	glPopMatrix();

}


void miscaPoligon(void) {

	x += alpha;
	i = i + alpha;
	if (i < -600.0)
		alpha = 1.0;
	else if (i > 600.0)
		alpha = -1.0;
	j = j + 15.0;
	Sleep(1);
	glutPostRedisplay();

}


void gameOver1(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	char text1[40] = "GAME OVER";
	char text2[40] = "Jucatorul 1 castiga.";

	snprintf(scor_1, sizeof(scor_1), "%s", text1);
	glColor3f(1.0, 1.0, 1.0);
	desenareText(scor_1, -80, 80, 0);
	
	snprintf(scor_1, sizeof(scor_1), "%s", text2);
	glColor3f(1.0, 1.0, 1.0);
	desenareText(scor_1, -100, 30, 0);

	glLineWidth(3);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4, 0x00FF);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(-600, -295);
	glVertex2i(600, -295);
	glEnd();


	// poligonul de pe axa de la finalul jocului
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
	int n;
	n = 10;

	glNewList(poligon, GL_COMPILE);
	glPushMatrix();
	glTranslated(i, -300.0, 0.0);
	glRotated(j, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glTranslated(-i, -100, 0);
	glBegin(GL_POLYGON);
	for (k = 0; k < n; k++) {

		glColor3f(0.5, 0.5, 0.5);
		hexTheta = PI * k / n;
		hexVertex.x = i + 50 * cos(hexTheta);
		hexVertex.y = 80 + 50 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glPopMatrix();
	glEndList();

	glLoadIdentity();
	glCallList(poligon);
	glutIdleFunc(miscaPoligon);


	// rama din jurul textului
	const int ry = 10;

	glColor3f(1.0, 0.0, 0.0);
	const GLdouble width = 7;
	glLoadIdentity();
	glPushMatrix();
	for (int i = 0; i < 13; i = i + 2) {

		glPointSize(6.0);
		glScalef(1, 1, 0);
		glBegin(GL_POINTS);
		glVertex2i(163, (i + 1)*width + ry);
		glVertex2i(163, i*width + ry);
		glEnd();
	}
	glPopMatrix();
	glTranslated(-350, 0.0, 0.0);
	for (int i = 0; i < 13; i = i + 2) {

		glPointSize(6.0);
		glBegin(GL_POINTS);
		glVertex2i(170, (i + 1)*width + ry);
		glVertex2i(170, i*width + ry);
		glEnd();
	}
	glPopMatrix();
	

	// desenarea luminilor
	glColor3d(1.0, 0.75, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex2i(65, 140);
	glVertex2i(110, 140);
	glVertex2i(-690, 670);
	glEnd();

	glColor3d(1.0, 0.95, 0.60);
	glBegin(GL_TRIANGLES);
	glVertex2i(130, 140);
	glVertex2i(165, 140);
	glVertex2i(-690, 670);
	glEnd();

	glColor3d(1.0, 0.95, 0.60);
	glBegin(GL_TRIANGLES);
	glVertex2i(520, 140);
	glVertex2i(560, 140);
	glVertex2i(1070, 480);
	glEnd();

	glColor3d(1.0, 0.75, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex2i(580, 140);
	glVertex2i(630, 140);
	glVertex2i(1070, 480);
	glEnd();
	

	glutSwapBuffers();
	glFlush();

}


void gameOver2(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	char text1[40] = "GAME OVER";
	char text2[40] = "Jucatorul 2 castiga.";

	snprintf(scor_2, sizeof(scor_2), "%s", text1);
	glColor3f(1.0, 1.0, 1.0);
	desenareText(scor_2, -80, 80, 0);
	
	snprintf(scor_2, sizeof(scor_1), "%s", text2);
	glColor3f(1.0, 1.0, 1.0);
	desenareText(scor_2, -100, 30, 0);

	glLineWidth(3);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4, 0x00FF);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(-600, -295);
	glVertex2i(600, -295);
	glEnd();


	// poligonul de pe axa de la finalul jocului
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
	int n;
	n = 10;

	glNewList(poligon, GL_COMPILE);
	glPushMatrix();
	glTranslated(i, -300.0, 0.0);
	glRotated(j, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(-i, -100, 0);
	glBegin(GL_POLYGON);
	for (k = 0; k < n; k++) {

		glColor3f(0.5, 0.5, 0.5);
		hexTheta = PI * k / n;
		hexVertex.x = i + 50 * cos(hexTheta);
		hexVertex.y = 80 + 50 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glPopMatrix();
	glEndList();

	glLoadIdentity();
	glCallList(poligon);
	glutIdleFunc(miscaPoligon);


	// rama din jurul textului
	const int ry = 10;

	glColor3f(1.0, 0.0, 0.0);
	const GLdouble width = 7;
	glLoadIdentity();
	glPushMatrix();
	for (int i = 0; i < 13; i = i + 2) {

		glPointSize(6.0);
		glScalef(1, 1, 0);
		glBegin(GL_POINTS);
		glVertex2i(170, (i + 1)*width + ry);
		glVertex2i(170, i*width + ry);
		glEnd();
	}
	glPopMatrix();
	glTranslated(-350, 0.0, 0.0);
	for (int i = 0; i < 13; i = i + 2) {

		glPointSize(6.0);
		glBegin(GL_POINTS);
		glVertex2i(170, (i + 1)*width + ry);
		glVertex2i(170, i*width + ry);
		glEnd();
	}
	glPopMatrix();


	// desenarea luminilor 
	glColor3d(1.0, 0.75, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex2i(65, 140);
	glVertex2i(110, 140);
	glVertex2i(-690, 670);
	glEnd();

	glColor3d(1.0, 0.95, 0.60);
	glBegin(GL_TRIANGLES);
	glVertex2i(130, 140);
	glVertex2i(165, 140);
	glVertex2i(-690, 670);
	glEnd();

	glColor3d(1.0, 0.95, 0.60);
	glBegin(GL_TRIANGLES);
	glVertex2i(520, 140);
	glVertex2i(560, 140);
	glVertex2i(1070, 480);
	glEnd();

	glColor3d(1.0, 0.75, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex2i(580, 140);
	glVertex2i(630, 140);
	glVertex2i(1070, 480);
	glEnd();

	glutSwapBuffers();
	glFlush();

}


// functii principale de afisare
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	// creeaza linii centrale
	desenareLiniiCentrale();

	// deseneaza paleta stanga la coordonata (-paleta_x, jucator1_paleta_y)
	desenarePaleta(-paleta_x, jucator1_paleta_y);
	// deseneaza paleta dreapta la coordonata (paleta_x, jucator2_paleta_y)
	desenarePaleta(paleta_x, jucator2_paleta_y);

	// deseneaza mingea la coordonata (pozitie_minge_x, pozitie_minge_y) - variaza in fiecare cadru
	desenareMinge(pozitie_minge_x, pozitie_minge_y);

	// deseneaza scorul in partea stanga pentru primul jucator
	snprintf(scor_1, sizeof(scor_1), "%d", jucator1_scor);
	desenareScor(scor_1, -300, 200, 0);

	// deseneaza scorul in partea stanga pentru al doilea jucator
	snprintf(scor_2, sizeof(scor_2), "%d", jucator2_scor);
	desenareScor(scor_2, 200, 200, 0);


	glutSwapBuffers();
	glFlush();

}


void startJoc(void) {

	// misca mingea
	pozitie_minge_x += viteza_minge_x;
	pozitie_minge_y += viteza_minge_y;

	// caz - mingea loveste partea de sus sau cea de jos 
	if (pozitie_minge_y + raza_minge > orthoSizeY || pozitie_minge_y - raza_minge < -orthoSizeY)
		viteza_minge_y = -viteza_minge_y;

	// mingea loveste paleta stanga
	if (pozitie_minge_x - raza_minge - 5 < -paleta_x && pozitie_minge_x - raza_minge < -paleta_x)
		if (pozitie_minge_y < jucator1_paleta_y + inaltimePaleta && pozitie_minge_y > jucator1_paleta_y - inaltimePaleta) {

			viteza_minge_x = -viteza_minge_x;
			viteza_minge_x += crestereViteza;
			vitezaPaleta += crestereViteza;
		}

	// mingea loveste paleta dreapta
	if (pozitie_minge_x + raza_minge + 5 > paleta_x && pozitie_minge_x + raza_minge < paleta_x)
		if (pozitie_minge_y < jucator2_paleta_y + inaltimePaleta && pozitie_minge_y > jucator2_paleta_y - inaltimePaleta)
			viteza_minge_x = -viteza_minge_x;


	// primul jucator inscrie
	if (pozitie_minge_x + raza_minge > orthoSizeX) {

		jucator1_scor++;
		cout << "Jucator 1 : " << jucator1_scor << " pct." << endl;
		viteza_minge_x = -viteza_minge_x;
	}

	if (jucator1_scor >= 5) {

		glutIdleFunc(NULL);
		glutDisplayFunc(gameOver1);

	}

	// al doilea jucator inscrie
	if (pozitie_minge_x - raza_minge < -orthoSizeX) {

		jucator2_scor++;
		cout << "Jucator 2 : " << jucator2_scor << " pct." << endl;
		viteza_minge_x = -viteza_minge_x;
	}

	if (jucator2_scor >= 5) {

		glutIdleFunc(NULL);
		glutDisplayFunc(gameOver2);
	}

	glutPostRedisplay();

}


void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-orthoSizeX, orthoSizeX, -orthoSizeY, orthoSizeY, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void mouse(int button, int state, int x, int y) {

	switch (button) {
		// click stanga mouse - initializeaza viteza la intamplare intre (rand(5) - rand(3)) 
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

			viteza_minge_x = (rand() % 4) - (rand() % 3);
			viteza_minge_y = (rand() % 4) - (rand() % 3);
		}
		// continua sa apeleze functia pentru a misca mingea si a verifica conditiile de delimitare 
		glutIdleFunc(startJoc);
		
		glutSwapBuffers();
		break;


		// butonul din mijloc pentru a reseta pozitia mingii, cea a paletei si scorul
	case GLUT_MIDDLE_BUTTON:
		// reseteaza pozitia mingii, cea a paletei si scorul
		pozitie_minge_x = pozitie_minge_y = 0;
		jucator1_paleta_y = jucator2_paleta_y = 0;
		jucator1_scor = jucator2_scor = 0;
		if (state == GLUT_DOWN)
			// elimina apelul astfel incat jocul sa se opreasca
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}

}


void tastatura(unsigned char key, int x, int y) {

	switch (key) {
		// muta mai sus paleta jucatorului 1
	case 'w':
		if (jucator1_paleta_y < marginePaleta)
			jucator1_paleta_y += (20 * vitezaPaleta);
		glutPostRedisplay();
		break;
		// muta mai jos paleta jucatorului 1
	case 's':
		if (jucator1_paleta_y > -marginePaleta)
			jucator1_paleta_y -= (20 * vitezaPaleta);
		glutPostRedisplay();
		break;
		// muta mai sus paleta jucatorului 2
	case 'i':
		if (jucator2_paleta_y < marginePaleta)
			jucator2_paleta_y += (20 * vitezaPaleta);
		glutPostRedisplay();
		break;
		// muta mai jos paleta jucatorului 2
	case 'k':
		if (jucator2_paleta_y > -marginePaleta)
			jucator2_paleta_y -= (20 * vitezaPaleta);
		glutPostRedisplay();
		break;
		// iesire pe esc 
	case 27:
		exit(0);
		break;
	default:
		break;
	}

}


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Ping Pong");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(tastatura);
	glutReshapeFunc(reshape);

	glutMainLoop();

}
