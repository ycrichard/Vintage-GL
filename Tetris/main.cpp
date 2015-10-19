using namespace std;
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "GL/freeglut.h"
#include "color.h"
#include "BrickBase.h"
#include "BrickT.h"
#include "BrickZ1.h"
#include "BrickZ2.h"
#include "BrickL1.h"
#include "BrickL2.h"
#include "BrickE.h"
#include "BrickI.h"
#include "box.h"

void NewSession();
void LibererMemoire();
void BrickAffichage();
void BrickRedim(int x,int y);
void BrickClavierSpecial(int key,int x,int y);
void BrickNormalKey(unsigned char key,int x,int y);
void BrickTimer(int value);
void FuncOisivte();
void NewBrick();
void ChangerABox();
bool TouchBas();
bool TouchGauche();
bool TouchDroite();
void CheckFullLigne();
bool CheckEnd();
void EndOut();
void Save();
void Load();
//int height();
void createGLUTMenus();
void processMenuEvents(int option);
void initSubmenu();
void replayCheck();

int NbColonnes;
int NbLignes;
double TIMER_MILLIS=650;
double TIMER_MILLIS2=650;
int Score=0;
int Level=1;
BrickBase* B;
box** matrice;
int ii;   //for ending Animation
int jj;
bool Exit=false;
bool Pause=false;
int winID;
//int menu,submenu;

int main()
{
	srand((int)time(NULL));

	#ifdef _WIN32
	    system("cls");
	#else
	    // Assume POSIX
	    system("clear");
	#endif

	cout<<"Welcome to Tetris !"<<endl<<endl;
	cout<<"F1 : Save"<<endl;
	cout<<"F2 : Load"<<endl;
	cout<<"P : Pause"<<endl;
	cout<<"Space : Fast drop down"<<endl;
	cout<<"Esc : Quit"<<endl;
	cout<<"Or, right click on your mouse to check menu."<<endl<<endl;

	cout<<"Press enter to start the game > "<<endl;
	getchar();

	NewSession();

	LibererMemoire();
	exit(0);
	return 0;
}


void NewSession()
{
    Exit=false;
    Pause=false;
    B=NULL;
    NbColonnes=15;
    NbLignes=22;
    ii=NbLignes+3;
    jj=1;

    matrice= new box*[NbLignes+5];
    for(int i=0;i<NbLignes+5;i++)
      matrice[i]=new box[NbColonnes+2];
    for(int i=0;i<NbLignes+5;i++)
      for(int j=0;j<NbColonnes+2;j++)
        matrice[i][j].SetXY(j-1,i-4);
    for(int i=1;i<NbColonnes+1;i++)
    {
      matrice[NbLignes+4][i].SetAppear(true);
    }
    for(int i=3;i<NbLignes+5;i++)
    {
      matrice[i][0].SetAppear(true);
      matrice[i][NbColonnes+1].SetAppear(true);
    }

	#ifdef _WIN32
	    system("cls");
	#else
	    // Assume POSIX
	    system("clear");
	#endif
	cout<<"Score : "<<Score<<endl;
	cout<<"Level : "<<Level<<endl;

    NewBrick();

    int argc = 1;
    char *argv[1] = {(char*)""};
    glutInit(&argc, argv);
    glutInitWindowPosition(500,30);
    glutInitWindowSize(480,690);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    winID=glutCreateWindow("Tetris");
    glutSpecialFunc(BrickClavierSpecial);
    glutKeyboardFunc(BrickNormalKey);
    createGLUTMenus();

    glutDisplayFunc(BrickAffichage);		//principe du gl!!
    glutReshapeFunc(BrickRedim);			//
    glutTimerFunc(TIMER_MILLIS, BrickTimer, 0);

    glutMainLoop();
}


void BrickAffichage()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);


	B->Dessiner();
	for(int i=4;i<=NbLignes+4;i++)
		for(int j=0;j<NbColonnes+2;j++)
			matrice[i][j].Dessiner();

	glutSwapBuffers();
}
void BrickRedim(int x,int y)
{
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(-0.7, (double)NbColonnes+0.7, (double)NbLignes+0.7, 0.0);
}


void BrickClavierSpecial(int key,int x,int y)
{

	if(Exit || CheckEnd()) return;
	switch(key)
	{
	case GLUT_KEY_UP:if(Pause) return; B->Rotation();break;
	case GLUT_KEY_DOWN:if(Pause) return; if(TouchBas()){ChangerABox();CheckFullLigne();CheckEnd();}if(!Exit) B->Tomber();break;
	case GLUT_KEY_LEFT:if(Pause) return; if(!TouchGauche()) B->BougerAGauche();break;
	case GLUT_KEY_RIGHT:if(Pause) return; if(!TouchDroite()) B->BougerADroite();break;
	case GLUT_KEY_F1:Save();break;
	case GLUT_KEY_F2:Load();break;
	}
	glutPostRedisplay();
}


void BrickNormalKey(unsigned char key,int x,int y)
{
	if(Exit || CheckEnd()) return;
	switch(key)
	{
	//case 49:B->Translate(0,height());ChangerABox();CheckFullLigne();break;
	case 32:{
		if(Pause) return;
		while(!TouchBas())
			B->Tomber();

		ChangerABox();CheckFullLigne();break;}
	case 27:Exit=true;glutIdleFunc(FuncOisivte); break;		//esc
	case 80:													//P et p
	case 112:{Pause=!Pause;
		if(Pause)
		cout<<"Pause..."<<endl;
		else cout<<"Playing..."<<endl;break;}
	}
	glutPostRedisplay();
}


void BrickTimer(int value)
{
	if(Pause) goto Skip;
	if(Exit || CheckEnd() ){
    glutIdleFunc(FuncOisivte);
	}
	else
	{
		if(TouchBas())
		{
			ChangerABox();
			CheckFullLigne();
			CheckEnd();
		}
		if(!Exit) B->Tomber();
		if(TouchBas())TIMER_MILLIS2=650;			//将changerABox独立出来，使时间间隔不变
		else TIMER_MILLIS2=TIMER_MILLIS;
	}

	Skip:
	glutPostRedisplay();
	glutTimerFunc(TIMER_MILLIS2, BrickTimer, 0);

}


void LibererMemoire()
{
	if(B!=NULL)
		delete B;
	if(matrice!=NULL)
		for(int i=0;i<NbLignes+5;i++)
			delete [] matrice[i];
	delete [] matrice;

}


void NewBrick()
{
	//if(CheckEnd() || Exit) return;
	if(B!=NULL)
	delete B;

	switch(rand()%7)
	{
	case 0:B=new BrickT;break;
	case 1:B=new BrickZ1;break;
	case 2:B=new BrickZ2;break;
	case 3:B=new BrickL1;break;
	case 4:B=new BrickL2;break;
	case 5:B=new BrickE;break;
	case 6:B=new BrickI;break;
	}
}


void ChangerABox()
{
	//if(TouchBas())
	//{
		matrice[B->GetY1()+4][B->GetX1()+1].SetAppear(true);
		matrice[B->GetY1()+4][B->GetX1()+1].SetCouleur(B->GetCouleur());
		matrice[B->GetY2()+4][B->GetX2()+1].SetAppear(true);
		matrice[B->GetY2()+4][B->GetX2()+1].SetCouleur(B->GetCouleur());
		matrice[B->GetY3()+4][B->GetX3()+1].SetAppear(true);
		matrice[B->GetY3()+4][B->GetX3()+1].SetCouleur(B->GetCouleur());
		matrice[B->GetCentreY()+4][B->GetCentreX()+1].SetAppear(true);
		matrice[B->GetCentreY()+4][B->GetCentreX()+1].SetCouleur(B->GetCouleur());
		NewBrick();
	//}
}


bool TouchBas()
{
	bool t=false;
	if(matrice[B->GetY1()+5][B->GetX1()+1].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY2()+5][B->GetX2()+1].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY3()+5][B->GetX3()+1].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetCentreY()+5][B->GetCentreX()+1].GetAppear())
	{
		t=true;
		return t;
	}
	return t;
}


bool TouchGauche()
{
	//if(B->GetY1()<0 || B->GetY2()<0 || B->GetY3()<0 || B->GetCentreY()<0 ) return false;
	bool t=false;
	if(matrice[B->GetY1()+4][B->GetX1()].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY2()+4][B->GetX2()].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY3()+4][B->GetX3()].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetCentreY()+4][B->GetCentreX()].GetAppear())
	{
		t=true;
		return t;
	}
	return t;
}


bool TouchDroite()
{
	//if(B->GetY1()<0 || B->GetY2()<0 || B->GetY3()<0 || B->GetCentreY()<0 ) return false;
	bool t=false;
	if(matrice[B->GetY1()+4][B->GetX1()+2].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY2()+4][B->GetX2()+2].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetY3()+4][B->GetX3()+2].GetAppear())
	{
		t=true;
		return t;
	}
	if(matrice[B->GetCentreY()+4][B->GetCentreX()+2].GetAppear())
	{
		t=true;
		return t;
	}
	return t;
}


void CheckFullLigne()
{
	int f;
	int bonus=0;
	for(int i=5;i<NbLignes+4;i++)
	{
		f=0;
		for(int j=1;j<NbColonnes+1;j++)
			if(matrice[i][j].GetAppear())
				f++;
		if(f==15)
		{
			bonus++;
			for(int k=i;k>3;k--)
				for(int j=1;j<NbColonnes+1;j++)
				{
					matrice[k][j].SetAppear(matrice[k-1][j].GetAppear());
					matrice[k][j].SetCouleur(matrice[k-1][j].GetCouleur());
				}
		}
	}
	if(bonus!=0)
	{
		switch(bonus)
		{
		case 1: Score+=1;break;
		case 2: Score+=3;break;
		case 3: Score+=7;break;
		case 4: Score+=15;break;
		}
		if(Level<10)
		if(Score>=Level*50)				//算法需要修改
		{Level++;TIMER_MILLIS-=60;}

		#ifdef _WIN32
		    system("cls");
		#else
		    // Assume POSIX
		    system("clear");
		#endif
		cout<<"Score : "<<Score<<endl;
		cout<<"Level: "<<Level<<endl;
	}
}


bool CheckEnd()
{
	for(int i=1+5;i<NbColonnes+1-5;i++)
		if(matrice[4][i].GetAppear()==true)
		{
			Exit=true;
			return true;
		}
	return false;
}


void EndOut()
{
      //glutLeaveMainLoop();
			glutExit();
			LibererMemoire();
			int high=0;
			string nom="god";
			ifstream f;
			f.open("HighScore.sav");
			f>>high;
			f>>nom;
			f.close();

			cout<<"Game over !!"<<endl;
			cout<<"Your Final Score : "<<Score<<endl;

			if(Score>high)
			{
				high=Score;
				cout<<"New HighScore~~~~ "<<endl;
				cout<<"Your name : ";
				cin>>nom;
				ofstream f;
				f.open("HighScore.sav");
				f<<high<<endl;
				f<<nom<<endl;
				f.close();
			}
			cout<<"*********************************"<<endl;
			cout<<"  High Score : "<<high<<endl;
			cout<<"  By : "<<nom<<endl;
			cout<<"*********************************"<<endl<<endl;

      replayCheck();

			exit(0);
}


void replayCheck(){
      string yesorno;
      cout<<"Replay? [Y/n]"<<endl;
      cin >> yesorno;
      if(yesorno == "y" | yesorno == "Y") NewSession();
      else if (yesorno == "n" | yesorno == "N")exit(0);
      else {
      cout<<"Wrong input..."<<endl;
      replayCheck();
      }
}

/*
int height()
{
		int height;
		for(int i=0;i<22;i++)
		if(matrice[B->GetY1()+5+i][B->GetX1()+1].GetAppear())
		{
			height=i;
			break;
		}
		for(int i=0;i<22;i++)
		if(matrice[B->GetY2()+5+i][B->GetX2()+1].GetAppear())
		{
		    if(i<height) height=i;
			break;
		}
		for(int i=0;i<22;i++)
		if(matrice[B->GetY3()+5+i][B->GetX3()+1].GetAppear())
		{
			if(i<height) height=i;
			break;
		}
		for(int i=0;i<22;i++)
		if(matrice[B->GetCentreY()+5+i][B->GetCentreX()+1].GetAppear())
		{
			if(i<height) height=i;
			break;
		}
		return height;
}*/


void FuncOisivte()
{
	matrice[ii][jj].SetAppear(true);
	matrice[ii][jj].SetCouleur(gris);

	//switch(ii%2)
	//{
	//case 1:
	if(ii%2==1)
		{
			jj++;
				if(jj==NbColonnes+1)
				{
					jj=NbColonnes;
					if(ii>3)
					ii--;
					else EndOut();
				}
				//break;
		}
	//case 0:
	else
		{
				jj--;
				if(jj==0)
				{
					jj=1;
					if(ii>3)
					ii--;
					else EndOut();
				}
				//break;
		}
	//}
	glutPostRedisplay();
}


void Save()
{
	ofstream f;
	f.open("SaveDate.sav");
	f<<Score<<endl;
	f<<TIMER_MILLIS<<endl;
	f<<Level<<endl;
	for(int i=4;i<NbLignes+4;i++)
		for(int j=1;j<NbColonnes+1;j++)
		{
			f<<matrice[i][j].GetAppear()<<endl;
			f<<matrice[i][j].GetCouleur()<<endl;
		}
	f.close();
}


void Load()
{
	bool bb;
	int cc;
	ifstream f;
	f.open("SaveDate.sav");
	f>>Score;
	f>>TIMER_MILLIS;
	f>>Level;
	for(int i=4;i<NbLignes+4;i++)
		for(int j=1;j<NbColonnes+1;j++)
		{
			f>>bb;		matrice[i][j].SetAppear(bb);
			f>>cc;
			switch(cc)
			{
			case 0:matrice[i][j].SetCouleur(rouge);break;
			case 1:matrice[i][j].SetCouleur(vert);break;
			case 2:matrice[i][j].SetCouleur(bleu);break;
			case 3:matrice[i][j].SetCouleur(jaune);break;
			case 4:matrice[i][j].SetCouleur(rose);break;
			case 5:matrice[i][j].SetCouleur(orange);break;
			case 6:matrice[i][j].SetCouleur(aqua);break;
			case 7:matrice[i][j].SetCouleur(gris);break;
			}
		}
	f.close();
	#ifdef _WIN32
	    system("cls");
	#else
	    // Assume POSIX
	    system("clear");
	#endif
	cout<<"Score : "<<Score<<endl;
	cout<<"Level: "<<Level<<endl;
}


void createGLUTMenus()
{
	int menu,submenu;

	submenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Level 1",11);
	glutAddMenuEntry("Level 2",12);
	glutAddMenuEntry("Level 3",13);
	glutAddMenuEntry("Level 4",14);
	glutAddMenuEntry("Level 5",15);
	glutAddMenuEntry("Level 6",16);
	glutAddMenuEntry("Level 7",17);
	glutAddMenuEntry("Level 8",18);
	glutAddMenuEntry("Level 9",19);
	glutAddMenuEntry("Level 10",20);

	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Save (F1)",1);
	glutAddMenuEntry("Load (F2)",2);
	glutAddMenuEntry("Pause (P)",3);
	glutAddSubMenu("Speeds",submenu);			//nouvelle function
	glutAddMenuEntry("Quit (Esc)",4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void processMenuEvents(int option)
{
	switch (option) {
		case 1 : Save(); break;
		case 2 : Load(); break;
		case 3 : {
			Pause=!Pause;
			if(Pause)
			{cout<<"Pause..."<<endl;glutChangeToMenuEntry(3,"Resume (P)",3);}
			else
			{cout<<"Playing..."<<endl;glutChangeToMenuEntry(3,"Pause (P)",3);}
			break;}
		case 4 : Exit=true;glutIdleFunc(FuncOisivte); 	break;
		case 11: Level=1;TIMER_MILLIS=650;initSubmenu();glutChangeToMenuEntry(1,"Level 1 ←",11); break;
		case 12: Level=2;TIMER_MILLIS=590;initSubmenu();glutChangeToMenuEntry(2,"Level 2 ←",12); break;
		case 13: Level=3;TIMER_MILLIS=530;initSubmenu();glutChangeToMenuEntry(3,"Level 3 ←",13); break;
		case 14: Level=4;TIMER_MILLIS=470;initSubmenu();glutChangeToMenuEntry(4,"Level 4 ←",14); break;
		case 15: Level=5;TIMER_MILLIS=410;initSubmenu();glutChangeToMenuEntry(5,"Level 5 ←",15); break;
		case 16: Level=6;TIMER_MILLIS=350;initSubmenu();glutChangeToMenuEntry(6,"Level 6 ←",16); break;
		case 17: Level=7;TIMER_MILLIS=290;initSubmenu();glutChangeToMenuEntry(7,"Level 7 ←",17); break;
		case 18: Level=8;TIMER_MILLIS=230;initSubmenu();glutChangeToMenuEntry(8,"Level 8 ←",18); break;
		case 19: Level=9;TIMER_MILLIS=170;initSubmenu();glutChangeToMenuEntry(9,"Level 9 ←",19); break;
		case 20: Level=10;TIMER_MILLIS=110;initSubmenu();glutChangeToMenuEntry(10,"Level 10 ←",20);break;
			/*glutChangeToSubMenu(10,"Level 10 ←",20);*/
			//This function appears to have some problems in Microsoft Windows.When one changes a sub menu twice.
	}
}


void initSubmenu()
{
	glutChangeToMenuEntry(1,"Level 1",11);
	glutChangeToMenuEntry(2,"Level 2",12);
	glutChangeToMenuEntry(3,"Level 3",13);
	glutChangeToMenuEntry(4,"Level 4",14);
	glutChangeToMenuEntry(5,"Level 5",15);
	glutChangeToMenuEntry(6,"Level 6",16);
	glutChangeToMenuEntry(7,"Level 7",17);
	glutChangeToMenuEntry(8,"Level 8",18);
	glutChangeToMenuEntry(9,"Level 9",19);
	glutChangeToMenuEntry(10,"Level 10",20);
}
