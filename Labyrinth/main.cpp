using namespace std;
#include <iostream>
#include <fstream>
#include <time.h>
#include "GL/freeglut.h"
#include "PersonnageBase.h"
#include "Joueur.h"
#include "EnnemiBase.h"
#include "EnnemiVert.h"
#include "EnnemiRouge.h"

enum TYPE_ENNEMI { vert,rouge };

void LabyAffichage();
void LabyRedim(int x,int y);
void DessinerNiveau();
void OuvrirNiveau(string nom_fichier);
void LibererMemoire();
void LabyClavierSpecial(int key,int x,int y);
void TestVictoire();
void LabyTimer(int value);
void AddEnnemi(TYPE_ENNEMI type,int PosC, int PosL);

const int TIMER_MILLIS=500;
int NbColonnes=0;
int NbLignes=0;
int SortieC=0;
int SortieL=0;
char** matrice=NULL;
Joueur MonJoueur;
EnnemiBase* premierEnnemi=NULL;


int main(int argc, char** argv)
{
	srand((int)time(NULL));
	OuvrirNiveau("niveau.txt");

    glutInit(&argc, argv);
	glutInitWindowPosition(400,100);
	glutInitWindowSize(600,600);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Labyrinthe");

	glutDisplayFunc(LabyAffichage);		//principe du gl
    glutReshapeFunc(LabyRedim);
    glutSpecialFunc(LabyClavierSpecial);
	glutTimerFunc(TIMER_MILLIS, LabyTimer, 0);

	glutMainLoop();
	LibererMemoire();
	exit(0);
	return 0;
}


void LabyAffichage()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

	DessinerNiveau();
	MonJoueur.Dessiner();

	EnnemiBase* pointeur=premierEnnemi;
	while(pointeur!= NULL)
	{
		pointeur->Dessiner();
		pointeur=pointeur->GetSuivant();
	}
	//glFlush();
	glutSwapBuffers();		//for GLUT_DOUBLE
}

void LabyRedim(int x, int y)
{
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0.0, (double)NbColonnes, (double)NbLignes, 0.0);
}

void DessinerNiveau()
{
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_QUADS);

	for(int i=0;i<NbLignes;i++)
		for(int j=0;j<NbColonnes;j++)
			if(matrice[i][j] == '0')
			{
				glVertex2d(j, i);				//ici,colonne est l'axe X, ligne est l'axe Y
				glVertex2d(j, i+1);
				glVertex2d(j+1, i+1);
				glVertex2d(j+1, i);
			}

	glEnd();

	glPushMatrix();
	glTranslated(SortieC+0.5, SortieL+0.5, 0.0);
		glColor3d(0.3,1.0,0.3);		//verte
		for(double t=0.1;t<1.0;t+=0.2)
			glutWireCube(t);
	glPopMatrix();
}

void OuvrirNiveau(string nom_fichier)
{
	ifstream f;
	f.open(nom_fichier.c_str());

	if(!f)
	{
		cout<< "Error when open the level file !"<<endl;
		#ifdef _WIN32
            system("pause");
        #else
            cout<<"Press enter to continue > "<<endl;
            getchar();
        #endif
		exit(0);
	}

	f>> NbColonnes;
	f>> NbLignes;

	matrice= new char* [NbLignes];
	for(int i=0;i<NbLignes;i++)
		matrice[i]= new char[NbColonnes];


	for(int i=0;i<NbLignes;i++)
		for(int j=0;j<NbColonnes;j++)
			matrice[i][j]= '0';

	for(int i=0;i<NbLignes;i++)
		for(int j=0;j<NbColonnes;j++)
		{
			f>> matrice[i][j];

			switch(matrice[i][j])
			{
			case 'j':
			case 'J':{
				MonJoueur.SetPosC(j);
				MonJoueur.SetPosL(i);
				break;}
			case 's':
			case 'S':{
				SortieC = j;
				SortieL = i;
				break;}
			case 'v':
			case 'V':{
				AddEnnemi(vert,j,i);
				break;}
			case 'r':
			case 'R':{
				AddEnnemi(rouge,j,i);
				break;}
			}
		}
	f.close();
}

void LibererMemoire()
{
	if(matrice != NULL)
	{
		for(int i=0;i<NbLignes;i++)
			delete [] matrice[i];
		delete [] matrice;
	}

	EnnemiBase* pointeur=premierEnnemi;
	while(pointeur!= NULL)
	{
		premierEnnemi=pointeur->GetSuivant();
		delete pointeur;
		pointeur=premierEnnemi;
	}
}

void LabyClavierSpecial(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:{
		MonJoueur.BougerEnHaut();
					 break;}
	case GLUT_KEY_DOWN:{
		MonJoueur.BougerEnBas();
					  break;}
	case GLUT_KEY_LEFT:{
		MonJoueur.BougerAGauche();
					   break;}
	case GLUT_KEY_RIGHT:{
		MonJoueur.BougerADroite();
						break;}
	}

	EnnemiBase* pointeur=premierEnnemi;
	while(pointeur!= NULL)
	{
		pointeur->TestCollision();
		pointeur=pointeur->GetSuivant();
	}
	TestVictoire();
	glutPostRedisplay();
}

void TestVictoire()
{
	if(MonJoueur.GetPosC()==SortieC && MonJoueur.GetPosL()==SortieL)
	{
		LabyAffichage();			//refraîchir la scène manuellement
		glutExit();
		LibererMemoire();
		cout<<"Congratulations! You win!"<<endl;
		#ifdef _WIN32
            system("pause");
        #else
            cout<<"Press enter to continue > "<<endl;
            getchar();
        #endif
		exit(0);
	}
}

void LabyTimer(int value)
{
	//cout<<"I am in a timer"<<endl;
	EnnemiBase* pointeur=premierEnnemi;
	while( pointeur != NULL)
	{
		pointeur->DeplacementAuto();
		pointeur->TestCollision();
		pointeur=pointeur->GetSuivant();
	}
	glutPostRedisplay();
	glutTimerFunc(TIMER_MILLIS, LabyTimer, 0);
}

void AddEnnemi(TYPE_ENNEMI type,int PosC, int PosL)				//genial
{
	EnnemiBase* pointeur=NULL;
	switch(type)
	{
	case vert:{ pointeur= new EnnemiVert; break; }
	case rouge:{ pointeur= new EnnemiRouge; break; }
	default:exit(0);
	}
	pointeur->SetPosC(PosC);
	pointeur->SetPosL(PosL);
	pointeur->SetSuivant(premierEnnemi);

	premierEnnemi=pointeur;
}
