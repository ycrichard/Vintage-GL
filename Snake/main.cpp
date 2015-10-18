using namespace std;
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "GL/freeglut.h"
#include "corps.h"

void NewSession();
void LibererMemoire();
void OuvrirNiveau(string nom_fichier);
void SnakeAffichage();
void SnakeRedim(int x,int y);
void DessinerNiveau();
void SnakeClavierSpecial(int key,int x,int y);
void SnakeTimer(int value);
void AddCorps();
void SuiviHead();
void Collision();
void EndOut();
void replayCheck();

double TIMER_MILLIS=500;
int Score=0;
int NbColonnes;
int NbLignes;
char** matrice=NULL;
list<corps*> snake(1);
list<corps*>::iterator head= snake.begin();
int map;


class foods
{
private:
        int PosC;
        int PosL;
public:
        foods() { PosC=0; PosL=0; }
        int GetPosC() { return PosC;}
        int GetPosL() { return PosL;}
        void SetPosC(int C) { PosC=C; }
        void SetPosL(int L) { PosL=L; }
        void Dessiner();
        void ChangePosition();
};

foods* food=new foods;


int main()
{
        cout<<"Welcome to Snake game."<<endl;
        srand((int)time(NULL));

        NewSession();

        LibererMemoire();
        system("pause");
        exit(0);
        return 0;
}


void NewSession()
{

        matrice=NULL;
        TIMER_MILLIS=500;
        Score=0;
        NbColonnes=48;
        NbLignes=36;
        string maps="map/niveau1.txt";
        do{
        cout<<"Chose a map (1 - 4) : ";
        cin>>map;}while(map<1||map>4);
        maps[10]=map+48;

        OuvrirNiveau(maps);
        food->ChangePosition();
        cout << "good so far"<< endl;
        system("cls");
        cout<<"Score : "<<Score<<endl;
        cout<<"Speed : "<<1000/TIMER_MILLIS<<endl;

        int argc = 1;
        char *argv[1] = {(char*)"xx"};
        glutInit(&argc, argv);
        glutInitWindowPosition(400,150);
        glutInitWindowSize(800,600);

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutCreateWindow("Snake");

        glutDisplayFunc(SnakeAffichage);                //principe du gl!!
        glutReshapeFunc(SnakeRedim);                    //
        glutSpecialFunc(SnakeClavierSpecial);   //
        glutTimerFunc(TIMER_MILLIS, SnakeTimer, 0);

        glutMainLoop();
}


void OuvrirNiveau(string nom_fichier)
{
        ifstream f;
        f.open(nom_fichier.c_str());

        if(!f)
        {
                cout<< "Error when open the file !"<<endl;
                system("pause");
                exit(0);
        }

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
                        if(matrice[i][j] == 's')
                        {
                                (*head)=new corps;
                                (*head)->SetPosC(j);
                                (*head)->SetPosL(i);
                                AddCorps();
                                AddCorps();
                                AddCorps();
                        }
                }
        f.close();
}


void SnakeAffichage()
{
        glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

        DessinerNiveau();
        list<corps*>::iterator it=snake.begin();
        while(it!= snake.end())
        {
        (*it)->Dessiner();
        it++;
        }
        food->Dessiner();
        glutSwapBuffers();
}


void SnakeRedim(int x,int y)
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
                                glVertex2d(j, i);
                                glVertex2d(j, i+1);
                                glVertex2d(j+1, i+1);
                                glVertex2d(j+1, i);
                        }
        glEnd();
}


void SnakeClavierSpecial(int key,int x,int y)
{
        switch(key)
        {
        case GLUT_KEY_UP:{
                if((*head)->GetDir()!=bas)
                {
                        SuiviHead();
                        (*head)->SetDir(haut);
                        (*head)->Bouger();
                        Collision();
                }
                                         break;}
        case GLUT_KEY_DOWN:{
                if((*head)->GetDir()!=haut)
                {
                        SuiviHead();
                        (*head)->SetDir(bas);
                        (*head)->Bouger();
                        Collision();
                }
                                          break;}
        case GLUT_KEY_LEFT:{
                if((*head)->GetDir()!=droite)
                {
                        SuiviHead();
                        (*head)->SetDir(gauche);
                        (*head)->Bouger();
                        Collision();
                }
                                          break;}
        case GLUT_KEY_RIGHT:{
                if((*head)->GetDir()!=gauche)
                {
                        SuiviHead();
                        (*head)->SetDir(droite);
                        (*head)->Bouger();
                        Collision();
                }
                                                break;}
        }
        glutPostRedisplay();
}


void SnakeTimer(int value)
{
        SuiviHead();
        (*head)->Bouger();
        Collision();

        glutPostRedisplay();
        glutTimerFunc(TIMER_MILLIS, SnakeTimer, 0);
}


void LibererMemoire()
{
        if(matrice != NULL)
        {
                for(int i=0;i<NbLignes;i++)
                        delete [] matrice[i];
                delete [] matrice;
        }

        list<corps*>::iterator it=snake.begin();
        while(it!= snake.end())
        {
                delete *it;
                it++;
        }
        snake.clear();

        delete food;
}


void AddCorps()
{
        corps* pointeur;
        pointeur=new corps;
        list<corps*>::iterator tail = snake.end();
        tail--;
        pointeur->SetDir((*tail)->GetDir());
        int C=(*tail)->GetPosC();
        int L=(*tail)->GetPosL();

        switch(pointeur->GetDir())
        {
        case haut:{
                pointeur->SetPosC(C);
                pointeur->SetPosL(L+1);

                break;}
        case bas:{
                pointeur->SetPosC(C);
                pointeur->SetPosL(L-1);
                break;}
        case gauche:{
                pointeur->SetPosC(C+1);
                pointeur->SetPosL(L);
                break;}
        case droite:{
                pointeur->SetPosC(C-1);
                pointeur->SetPosL(L);
                break;}
        }
        snake.push_back(pointeur);
}


void SuiviHead()
{
        list<corps*>::iterator it1=snake.end();
        list<corps*>::iterator it2=snake.end();
        it1--;
        while(it1!= snake.begin())                                              //tres important!!! sens invers
        {
                it1--;
                it2--;
                (*it2)->Suivre((*it1));

        }
}


void Collision()
{
        (*head)->TestCollision();
        list<corps*>::iterator it=snake.begin();
        it++;it++;it++;
        while(it!= snake.end())
        {
                (*head)->SeCollision(*it);
                it++;
        }
        if((*head)->GetPosL()==food->GetPosL() && (*head)->GetPosC()==food->GetPosC())
        {
                AddCorps();
                food->ChangePosition();
                Score++;
                TIMER_MILLIS=(TIMER_MILLIS-60)*0.96+60;
                SnakeAffichage();
                system("cls");
                cout<<"Score : "<<Score<<endl;
                if(TIMER_MILLIS>100)
                cout<<"Speed : "<<setprecision(2)<<1000/TIMER_MILLIS<<endl;
                if(TIMER_MILLIS<=100)
                cout<<"Speed : "<<setprecision(3)<<1000/TIMER_MILLIS<<endl;
        }
}


void foods::Dessiner()
{
        glPushMatrix();
        glTranslated(PosC+0.5, PosL+0.5, 0.0);
                glTranslated(-0.125, -0.116, 0.0);
                glColor3d(0.0, 0.7, 0.8);
                glutSolidSphere(0.2,12,12);
                glTranslated(0.25, 0.0, 0.0);
                glColor3d(0.7, 0.7, 0.0);                       //jaune
                glutSolidSphere(0.2,12,12);
                glTranslated(-0.123, 0.33, 0.0);
                glColor3d(0.8, 0.0, 0.6);                               //rose
                glutSolidSphere(0.2,12,12);
        glPopMatrix();

}


void foods::ChangePosition()
{
        bool b;
        do{
                b=false;
                PosC=rand()%NbColonnes;
                PosL=rand()%NbLignes;
                list<corps*>::iterator it=snake.begin();
                while(it!= snake.end())
                {
                if(PosC==(*it)->GetPosC() && PosL==(*it)->GetPosL())
                {
                        b=true;
                        break;
                }
                it++;
                }
        }while(matrice[PosL][PosC]== '0'|| b);
}


void EndOut()
{
        glutExit();
        LibererMemoire();
        int high[4]={0,0,0,0};
        string nom[4];
        for(int i=0;i<4;i++) nom[i]="god";
        ifstream f;
        f.open("HighScore.sav");
        for(int i=0;i<4;i++)
        {
                f>>high[i];
                f>>nom[i];
        }
        f.close();

        cout<<"Game over !!"<<endl;
        cout<<"Your Final Score : "<<Score<<endl;
        if(Score>high[map-1])
        {
                high[map-1]=Score;
                cout<<"Congras! New HighScore ~~~ "<<endl;
                cout<<"Your name : ";
                cin>>nom[map-1];
                ofstream f;
                f.open("HighScore.sav");
                for(int i=0;i<4;i++)
                {
                        f<<high[i]<<endl;
                        f<<nom[i]<<endl;
                }
                f.close();
        }
        cout<<"*********************************"<<endl;
        cout<<"  Map "<<map<<endl;
        cout<<"  High Score : "<<high[map-1]<<endl;
        cout<<"  By : "<<nom[map-1]<<endl;
        cout<<"*********************************"<<endl<<endl;

        //replayCheck();
        system("pause");
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
