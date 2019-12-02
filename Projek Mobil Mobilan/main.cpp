/**
#Motion select
r = static
t = car
y = bridge



**/

#define sp 10
#define CAR_IN_MOTION 1
#define SCENE_IN_MOTION 2
#define STATIC_SCENE 3

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdio.h>
///problemspe*cificHeaders
#include <vector>
using namespace std;
///My Headers
#include "opengl.h"
double roadMotion = 1, carM=1;
double runz = 0;
int state = STATIC_SCENE;
///Global values
double Angle = 0.0;
double W=700,H=700,persAngle=45.0;
int zNear=10,zFar=10000;
double ccr=.02,ccg=.5,ccb=1,cr,cg,cb;
point3d eye=point3d(0,0,100), lookat=point3d(0,0,0), upvec(0,1,0);
double rx=1,ry=0,rz=0,xa=0,za=0,ya=0;
GLUquadricObj *quadratic;

bool imgLoaded =false;
 point3d p[8];
 color c[6];

point3d car[80];
void initializeCar(){
    car[1] = point3d(-80,0,30);
    car[2] = point3d(-80,0,-30);

    car[3] = point3d(-58,0,-30);
    car[20] = point3d(-58,0,30);

    car[4] = point3d(-58,0,-25);
    car[19] = point3d(-58,0,25);

    car[5] = point3d(-44,0,-25);
    car[18] = point3d(-44,0,25);

    car[6] = point3d(-44,0,-30);
    car[17] = point3d(-44,0,30);
    car[7] = point3d(50,0,-30);
    car[16] = point3d(50,0,30);
    car[8] = point3d(50,0,-25);
    car[15] = point3d(50,0,25);
    car[9] = point3d(64,0,-25);
    car[14] = point3d(64,0,25);
    car[10] = point3d(64,0,-30);
    car[13] = point3d(64,0,30);
    car[11] = point3d(80,0,-30);
    car[12] = point3d(80,0,30);


    car[21] = point3d(-80,14,30);
    car[22] = point3d(-44,20,30);
    car[23] = point3d(-30,34,24);
    car[24] = point3d(50,34,24);
    car[25] = point3d(64,20,30);
    car[26] = point3d(80,20,30);
    car[27] = point3d(64,8,30);
    car[28] = point3d(50,8,30);
    car[29] = point3d(-44,8,30);
    car[30] = point3d(-58,8,30);



    car[31] = point3d(-80,14,-30);
    car[32] = point3d(-44,20,-30);
    car[33] = point3d(-30,34,-24);
    car[34] = point3d(50,34,-24);
    car[35] = point3d(64,20,-30);
    car[36] = point3d(80,20,-30);
    car[37] = point3d(64,8,-30);
    car[38] = point3d(50,8,-30);
    car[39] = point3d(-44,8,-30);
    car[40] = point3d(-58,8,-30);


    /***
    car[22] = point3d(-44,20,30);
    car[23] = point3d(-30,34,24);
    car[24] = point3d(50,34,24);
    car[25] = point3d(64,20,30);
    ***/
    car[41] = point3d(-40,22,29.2);
    car[42] = point3d(-29,32,25);
    car[43] = point3d(0,32,25);
    car[44] = point3d(0,22,29.2);

    car[45] = point3d(2,32,25);
    car[46] = point3d(42,32,25);
    car[47] = point3d(42,22,29.2);
    car[48] = point3d(2,22,29.2);

    car[49] = point3d(44,32,25);
    car[50] = point3d(49,32,25);
    car[51] = point3d(60,22,29.2);
    car[52] = point3d(44,22,29.2);

    car[53] = point3d(-40,22,-29.2);
    car[54] = point3d(-29,32,-25);
    car[55] = point3d(0,32,-25);
    car[56] = point3d(0,22,-29.2);

    car[57] = point3d(2,32,-25);
    car[58] = point3d(42,32,-25);
    car[59] = point3d(42,22,-29.2);
    car[60] = point3d(2,22,-29.2);

    car[61] = point3d(44,32,-25);
    car[62] = point3d(49,32,-25);
    car[63] = point3d(60,22,-29.2);
    car[64] = point3d(44,22,-29.2);

    /***
    car[22] = point3d(-44,20,30);
    car[23] = point3d(-30,34,24);
    car[33] = point3d(-30,34,-24);
    car[32] = point3d(-44,20,-30);
    ***/

    car[65] = point3d(-44.5,20,27);
    car[66] = point3d(-32.5,32,22);
    car[67] = point3d(-32.5,32,-22);
    car[68] = point3d(-44.5,20,-27);

    /***
     car[25] = point3d(64,20,30);
    car[24] = point3d(50,34,24);
     car[34] = point3d(50,34,-24);
    car[35] = point3d(64,20,-30);

    ***/

    car[69] = point3d(64.5,20,27);
    car[70] = point3d(52.5,32,22);
    car[71] = point3d(52.5,32,-22);
    car[72] = point3d(64.5,20,-27);

}


 void initialize(){

     ///backward plane
    p[0]=point3d(-40, 30,-40);
    p[1]=point3d(0,30,-40);
    p[2]=point3d(0,-10,-40);
    p[3]=point3d(-40,-10,-40);

    ///front plane
    p[4]=point3d(-40, 30,0);
    p[5]=point3d(0,30,0);
    p[6]=point3d(0,-10,0);
    p[7]=point3d(-40,-10,0);

    /*p[4]=point3d(-20,10,0);
    p[5]=point3d(20,10,0);
    p[6]=point3d(20,-30,0);
    p[7]=point3d(-20,-30,0);*/


    c[0] = color(1,0,0);
    c[1] = color(139,0,139);
    c[2] = color(0,1,0);
    c[3] = color(1,1,0);
    c[4] = color(34,139,34);
    c[5] = color(135,206,235);

 }









int init(){
    glShadeModel(GL_SMOOTH);
    glClearColor(0,0,0,1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    return TRUE;
}
void resize(GLsizei width, GLsizei height){
    if(height==0) height=1;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(persAngle,W/H,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool isOccupiedByQuad(point3d p[]){

}

void drawDisk(double inDiameter, double outDiameter, int vertSlices, int horizSlices)
{
    GLUquadricObj *disk;
    disk = gluNewQuadric();
    gluDisk(disk, inDiameter, outDiameter, vertSlices, horizSlices);
}

void motion(){
    //const double t = glutGet(GLUT_ELAPSED_TIME);
    //double a = (t%1000)*-1;
    //a = a/10;
    //if(a==-1000) a = 1000;
    glTranslated(0,0,roadMotion);
}

void carmotion(){
    glTranslated(0,0,carM);
}



void frontDesign(){

}


void planeF(){
///planeF
     color3(color(204,0,0));
    //color3(color(0,1,0));
    glBegin(GL_POLYGON);
    glVertex3d(car[22].X,car[22].Y,car[22].Z-4);
    glVertex3d(car[32].X,car[32].Y,car[32].Z+4);
    glVertex3d(car[31].X+4,car[31].Y,car[31].Z+4);
    glVertex3d(car[21].X+4,car[21].Y,car[21].Z-4);
    glEnd();

}

void frontSmoother(){
///frontLight

    glPushMatrix() ;
    glTranslated(car[22].X,car[22].Y-4,car[22].Z-4) ;
    glRotated(-90,0,1,0);
    glRotated(9.462,1,0,0);

    quadratic = gluNewQuadric();
    /*color3(color(227,255,9));
    glutSolidTorus(1.5,1.5,8,8);*/

    color3(color(204,0,0));
    gluCylinder(quadratic,4,4,car[22].X-car[21].X,64,64);
    glutSolidSphere(4,32,32);
    glPopMatrix() ;

    glPushMatrix() ;
    glTranslated(car[32].X,car[32].Y-4,car[31].Z+4) ;
    glRotated(-90,0,1,0);
    glRotated(9.462,1,0,0);
    quadratic = gluNewQuadric();
    color3(color(204,0,0));
    gluCylinder(quadratic,4,4,car[32].X-car[31].X,64,64);
    glutSolidSphere(4,32,32);
    glPopMatrix() ;

    glPushMatrix();
    glTranslated(car[32].X,car[32].Y-4,car[32].Z) ;
    glRotated(-90,0,1,0);
    glRotated(9.462,1,0,0);
    glTranslated(4,0,car[32].X-car[31].X);
    color3(color(227,255,9));
    glutSolidTorus(2,2,8,8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(car[22].X,car[22].Y-4,car[22].Z) ;
    glRotated(-90,0,1,0);
    glRotated(9.462,1,0,0);
    glTranslated(-4,0,car[22].X-car[21].X);
    color3(color(227,255,9));
    glutSolidTorus(2,2,8,8);
    glPopMatrix();


}

void planeA(){
 color3(color(51,0,0));
    glBegin(GL_POLYGON);
    vertex3d(car[1]);
    vertex3d(car[2]);
    vertex3d(car[3]);
    vertex3d(car[20]);

    glEnd();
     glBegin(GL_POLYGON);
    vertex3d(car[4]);
    vertex3d(car[5]);
    vertex3d(car[18]);
    vertex3d(car[19]);

    glEnd();


    glBegin(GL_POLYGON);
    vertex3d(car[5]);
    vertex3d(car[6]);
    vertex3d(car[7]);
    vertex3d(car[8]);
    vertex3d(car[15]);
    vertex3d(car[16]);
    vertex3d(car[17]);
    vertex3d(car[18]);
    glEnd();


    glBegin(GL_POLYGON);
    vertex3d(car[8]);
    vertex3d(car[9]);
    vertex3d(car[14]);
    vertex3d(car[15]);
    glEnd();

    glBegin(GL_POLYGON);
    //vertex3d(car[10]);
    //vertex3d(car[11]);
    glVertex3d(car[10].X,car[11].Y,car[11].Z+3);
    glVertex3d(car[11].X-3,car[11].Y,car[11].Z+3);
    glVertex3d(car[12].X-3,car[12].Y,car[12].Z-3);
    glVertex3d(car[13].X,car[13].Y,car[13].Z-3);
    //vertex3d(car[12]);
    //vertex3d(car[13]);
    glEnd();

}
void planeBGlass(){
     color3(color(0,0,0));
    glBegin(GL_POLYGON);
     vertex3d(car[41]);
     vertex3d(car[42]);
     vertex3d(car[43]);
     vertex3d(car[44]);
     glEnd();

    glBegin(GL_POLYGON);
     vertex3d(car[45]);
     vertex3d(car[46]);
     vertex3d(car[47]);
     vertex3d(car[48]);
     glEnd();

     glBegin(GL_POLYGON);
     vertex3d(car[49]);
     vertex3d(car[50]);
     vertex3d(car[51]);
     vertex3d(car[52]);
     glEnd();

     color3(color(125,125,125));
     glBegin(GL_POLYGON);
     vertex3d(car[22]);
     vertex3d(car[23]);
     vertex3d(car[24]);
     vertex3d(car[25]);
     glEnd();

}
void fixAWheelHole(int a, int b){
    glBegin(GL_POLYGON);
    vertex3d(car[a]);
    glVertex3d(car[a].X+3,car[a].Y,car[a].Z);
    glVertex3d(car[a].X,car[a].Y-3,car[a].Z);
    glEnd();
    glBegin(GL_POLYGON);
    vertex3d(car[b]);
    glVertex3d(car[b].X-3,car[b].Y,car[b].Z);
    glVertex3d(car[b].X,car[b].Y-3,car[b].Z);
    glEnd();
}

void fixWheelWhole(){
    fixAWheelHole(30,29);
    fixAWheelHole(28,27);
    fixAWheelHole(40,39);
    fixAWheelHole(38,37);

}

void planeB(){
 color3(color(204,0,0));
    glBegin(GL_POLYGON);
    vertex3d(car[30]);
    vertex3d(car[20]);
    vertex3d(car[1]);
    glVertex3d(car[21].X,car[21].Y-4,car[21].Z);
    glVertex3d(car[22].X,car[22].Y-4,car[22].Z);
    //vertex3d(car[22]);
    glEnd();









    glBegin(GL_POLYGON);///changed
    vertex3d(car[16]);
    vertex3d(car[17]);
    vertex3d(car[29]);
    vertex3d(car[28]);
    glEnd();
    glBegin(GL_POLYGON);///changed
    vertex3d(car[30]);
    vertex3d(car[22]);
    vertex3d(car[25]);
    vertex3d(car[27]);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d(car[25].X,car[25].Y-3,car[25].Z);
    glVertex3d(car[26].X-3,car[26].Y-3,car[26].Z);
    glVertex3d(car[12].X-3,car[12].Y+3,car[12].Z);
    glVertex3d(car[13].X,car[13].Y+3,car[13].Z);
    glEnd();
}

void planeCGlass(){
color3(color(0,0,0));
    glBegin(GL_POLYGON);
     vertex3d(car[53]);
     vertex3d(car[54]);
     vertex3d(car[55]);
     vertex3d(car[56]);
     glEnd();

    glBegin(GL_POLYGON);
     vertex3d(car[57]);
     vertex3d(car[58]);
     vertex3d(car[59]);
     vertex3d(car[60]);
     glEnd();

     glBegin(GL_POLYGON);
     vertex3d(car[61]);
     vertex3d(car[62]);
     vertex3d(car[63]);
     vertex3d(car[64]);
     glEnd();

     color3(color(125,125,125));
     glBegin(GL_POLYGON);
     vertex3d(car[32]);
     vertex3d(car[33]);
     vertex3d(car[34]);
     vertex3d(car[35]);
     glEnd();

}

void planeC(){
 color3(color(204,0,0));
     glBegin(GL_POLYGON);
    vertex3d(car[40]);
    vertex3d(car[3]);
    vertex3d(car[2]);
    glVertex3d(car[31].X,car[31].Y-4,car[31].Z);
    glVertex3d(car[32].X,car[32].Y-4,car[32].Z);
    glEnd();
    glBegin(GL_POLYGON);///changed
    vertex3d(car[7]);
    vertex3d(car[6]);
    vertex3d(car[39]);
    vertex3d(car[38]);
    glEnd();
     glBegin(GL_POLYGON);///changed
    vertex3d(car[40]);
    vertex3d(car[32]);
    vertex3d(car[35]);
    vertex3d(car[37]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3d(car[35].X,car[35].Y-3,car[35].Z);
    glVertex3d(car[36].X-3,car[36].Y-3,car[36].Z);
    glVertex3d(car[11].X-3,car[11].Y+3,car[11].Z);
    glVertex3d(car[10].X,car[10].Y+3,car[10].Z);
    glEnd();

}

void drawLight(){
   

    glPushMatrix();
    glTranslated(car[12].X-4,car[12].Y+15,car[12].Z-2);
    //glRotated(-90,1,0,0);
    //quadratic = gluNewQuadric();
    color3(color(1,1,0));
    //gluCylinder(quadratic,3,3,8,64,64);
    glutSolidSphere(3,16,16);
    glTranslated(0,3,0);
     glutSolidSphere(3,16,16);
    glPopMatrix();








    glPushMatrix();
    glTranslated(car[11].X-2,car[12].Y+6,car[11].Z+2);
    glRotated(-90,1,0,0);
    quadratic = gluNewQuadric();
    color3(color(0,1,0));
    gluCylinder(quadratic,3,3,3,64,64);
    glPopMatrix();
    glPushMatrix();
    glTranslated(car[11].X-2,car[11].Y+9,car[11].Z+2);
    glRotated(-90,1,0,0);
    quadratic = gluNewQuadric();
    color3(color(0.3,0,0));
    gluCylinder(quadratic,3,3,3,64,64);
    glPopMatrix();
    glPushMatrix();
    glTranslated(car[11].X-2,car[11].Y+12,car[11].Z+2);
    glRotated(-90,1,0,0);
    quadratic = gluNewQuadric();
    color3(color(1,1,0));
    gluCylinder(quadratic,3,3,3,64,64);
    glPopMatrix();

}




void backSmoother(){
 glPushMatrix() ;
    glTranslated(car[36].X-3,car[36].Y-3,car[36].Z+3) ;
    quadratic = gluNewQuadric();
    color3(color(204,0,0));
    gluCylinder(quadratic,3,3,car[26].Z-car[36].Z-6,64,64);
    glutSolidSphere(3,16,16);

    glPushMatrix();
        quadratic = gluNewQuadric();
        glRotated(90,1,0,0);
        gluCylinder(quadratic,3,3,car[36].Y-car[11].Y-6,64,64);

        GLUquadricObj *quadratic2 = gluNewQuadric();
        glRotated(-90,0,1,0);
        gluCylinder(quadratic2,3,3,car[36].X-car[35].X,64,64);
        glPushMatrix();

        glTranslated(0,0,car[36].X-car[35].X);
         glutSolidSphere(3,16,16);
        glPopMatrix();
    glPopMatrix();
glPopMatrix() ;


glPushMatrix();
    glTranslated(car[26].X-3,car[26].Y-3,car[26].Z-3);
     glutSolidSphere(3,16,16);

    glPushMatrix();
       quadratic = gluNewQuadric();
        glRotated(90,1,0,0);
        gluCylinder(quadratic,3,3,car[26].Y-car[12].Y-6,64,64);

        quadratic2 = gluNewQuadric();
        glRotated(-90,0,1,0);
        gluCylinder(quadratic2,3,3,car[26].X-car[25].X,64,64);
         glTranslated(0,0,car[36].X-car[35].X);
         glutSolidSphere(3,16,16);
        glPopMatrix();
    glPopMatrix();

glPopMatrix();


 glPushMatrix() ;
    glTranslated(car[11].X-3,car[11].Y+3,car[11].Z+3) ;
    quadratic = gluNewQuadric();
    color3(color(204,0,0));
    gluCylinder(quadratic,3,3,car[26].Z-car[36].Z-6,64,64);
    glutSolidSphere(3,16,16);
    glPushMatrix();
       /* quadratic = gluNewQuadric();
        glRotated(90,1,0,0);
        gluCylinder(quadratic,3,3,car[36].Y-car[11].Y-6,64,64);*/

        quadratic2 = gluNewQuadric();
        glRotated(-90,0,1,0);
        gluCylinder(quadratic2,3,3,car[36].X-car[35].X-4.0,64,64);

    glPopMatrix();
glPopMatrix();
glPushMatrix();
    glTranslated(car[12].X-3,car[12].Y+3,car[12].Z-3);
    glutSolidSphere(3,16,16);
    glPushMatrix();
        quadratic2 = gluNewQuadric();
        glRotated(-90,0,1,0);
        gluCylinder(quadratic2,3,3,car[26].X-car[25].X-4,64,64);
    glPopMatrix();
glPopMatrix();

/*glPushMatrix() ;
    glTranslated(car[11].X-3,car[11].Y+6,car[11].Z+.01) ;
    quadratic = gluNewQuadric();
    color3(color(204,0,0));
    gluCylinder(quadratic,3,3,car[12].Z-car[11].Z,64,64);
    glPopMatrix() ;

glPushMatrix();
    glTranslated(car[11].X,car[11].Y,car[11].Z);
    quadratic2 = gluNewQuadric();
    gluCylinder(quadratic2,3,3,car[11].Z-car[12].Z-6,64,64);
glPopMatrix();*/


    /*glPushMatrix() ;
    glTranslated(car[36].X-6,car[36].Y-6,car[36].Z*-1) ;
    //drawDisk(0,6.1,16,16);
    glPopMatrix() ;
    */
    /*glPushMatrix() ;
    glTranslated(car[11].X-6,car[11].Y+6,car[11].Z+.01) ;
    quadratic = gluNewQuadric();
    color3(color(204,0,0));
    gluCylinder(quadratic,6,6,car[12].Z-car[11].Z,64,64);
    drawDisk(0,6.1,16,16);
    glPopMatrix() ;*/
    /*
     glPushMatrix() ;
    //glTranslated(car[11].X-6,car[11].Y+6,car[11].Z*-1-.01) ;
    //drawDisk(0,6.1,16,16);
    glPopMatrix() ;
    //drawLight();
    glPushMatrix();*/
}


void frontSide(){
 ///planeD
    color3(color(204,0,0));
    glBegin(GL_POLYGON);
    vertex3d(car[2]);
    glVertex3d(car[31].X,car[31].Y-4,car[31].Z);
    glVertex3d(car[21].X,car[21].Y-4,car[21].Z);
    vertex3d(car[1]);
    glEnd();
    glPushMatrix();
    glTranslated(car[31].X+4,car[31].Y-4,car[31].Z+3) ;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,4,4,car[21].Z-car[31].Z-6,64,64);
    glPopMatrix();
    ///added 13 may
    glPushMatrix();
    color3(color(0,0,0));
    //drawLine3d(point3d(car[31].X-2,car[31].Y-8,car[31].Z+10),point3d(car[21].X-2,car[21].Y-8,car[21].Z-10));
    glBegin(GL_POLYGON);
    vertex3d(point3d(car[31].X-.001,car[31].Y-4,car[31].Z+10));
    vertex3d(point3d(car[21].X-.001,car[21].Y-4,car[21].Z-10));
    vertex3d(point3d(car[1].X-.001,car[1].Y+4,car[1].Z-10));
    vertex3d(point3d(car[2].X-.001,car[2].Y+4,car[2].Z+10));

    glEnd();
   // glPointSize(10);
    /*for(double i =0;i<car[21].Z-10;i+=1.2){
        glBegin(GL_LINES);
        vertex3d(point3d(car[31].X-.01,car[31].Y-6,car[31].Z+10+i));
        vertex3d(point3d(car[2].X-.01,car[31].Y-11,car[2].Z+10+i));
        //vertex3d(point3d(car[21].X-.001,car[21].Y-6-i,car[21].Z-10));
        glEnd();
        glPopMatrix();

    }
     for(double i =0;i<5;i+=1.2){
        glBegin(GL_LINES);
        vertex3d(point3d(car[31].X-.01,car[31].Y-6-i,car[31].Z+10));
        vertex3d(point3d(car[21].X-.01,car[21].Y-6-i,car[21].Z-10));
        glEnd();
        glPopMatrix();

    }*/


    ///end

}


void leftLight(){
    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 0.0f, 1000.0f, 1000.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.0f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 0.5f, 0.5f, 0.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    ///glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

void planeE(){
    color3(color(204,0,0));
    glBegin(GL_POLYGON);
    glVertex3d(car[11].X,car[11].Y+3,car[11].Z+3);
    glVertex3d(car[12].X,car[12].Y+3,car[12].Z-3);
    glVertex3d(car[26].X,car[26].Y-3,car[26].Z-3);
    glVertex3d(car[36].X,car[36].Y-3,car[36].Z+3);
    glEnd();
}
void planeG(){
    color3(color(0,0,0));
    glBegin(GL_POLYGON);
     vertex3d(car[65]);
     vertex3d(car[66]);
     vertex3d(car[67]);
     vertex3d(car[68]);
    glEnd();


    color3(color(105,105,105));
    glBegin(GL_POLYGON);
    vertex3d(car[22]);
    vertex3d(car[23]);
    vertex3d(car[33]);
    vertex3d(car[32]);
    glEnd();
}

void wheels(){
    ///wheels
    //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double t = glutGet(GLUT_ELAPSED_TIME);
    double a = t;
    a = a/2;
    if(a==100000) a = 0;
    if(state==STATIC_SCENE) a = 0;
    color3(color(0,0,0));
    glPushMatrix();
    glTranslated(-51,0,27);
    glRotated(a,0,0,1);
    color3(color(176,196,222));
    glutSolidTorus(3,2,6,6);
    color3(color(0,0,0));
    glutSolidTorus(2.5,5.5,16,16);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-51,0,-27);
    glRotated(a,0,0,1);
    color3(color(176,196,222));
    glutSolidTorus(3,2,6,6);
    color3(color(0,0,0));
    glutSolidTorus(2.5,5.5,16,16);
    glPopMatrix();
    glPushMatrix();
    glTranslated(57,0,27);
    glRotated(a,0,0,1);
    color3(color(176,196,222));
    glutSolidTorus(3,2,6,6);
    color3(color(0,0,0));
    glutSolidTorus(2.5,5.5,16,16);
    glPopMatrix();
    glPushMatrix();
    glTranslated(57,0,-27);
    glRotated(a,0,0,1);
    color3(color(176,196,222));
    glutSolidTorus(3,2,6,6);
    color3(color(0,0,0));
    glutSolidTorus(2.5,5.5,16,16);
    glPopMatrix();

}

void planeI(){
    color3(color(0,0,0));
    glBegin(GL_POLYGON);
     vertex3d(car[69]);
     vertex3d(car[70]);
     vertex3d(car[71]);
     vertex3d(car[72]);
    glEnd();

    color3(color(105,105,105));
    glBegin(GL_POLYGON);
    vertex3d(car[24]);
    vertex3d(car[25]);
    vertex3d(car[35]);
    vertex3d(car[34]);
    glEnd();

}
void planeJ(){
    //color3(color(230,230,250));
     color3(color(204,0,0));
    glBegin(GL_POLYGON);
    glVertex3d(car[25].X,car[25].Y,car[25].Z-3);
    glVertex3d(car[26].X-3,car[26].Y,car[26].Z-3);
    glVertex3d(car[36].X-3,car[36].Y,car[36].Z+3);
    glVertex3d(car[35].X,car[35].Y,car[35].Z+3);
    glEnd();


    glPushMatrix();
    glTranslated(car[35].X,car[35].Y-3,car[35].Z+3);
    glRotated(90,0,1,0);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,3,3,car[26].X-car[25].X-6,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslated(car[25].X,car[25].Y-3,car[25].Z-3);
    glRotated(90,0,1,0);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,3,3,car[26].X-car[25].X-6,32,32);
    glPopMatrix();
}

void planeH(){
     color3(color(255,228,181));
    glBegin(GL_POLYGON);
    vertex3d(car[23]);
    vertex3d(car[24]);
    vertex3d(car[34]);
    vertex3d(car[33]);
    glEnd();
}

void drawDoors(){

}



 void drawCar(){
    glPushMatrix();
    if(state==CAR_IN_MOTION) carmotion();
    glPushMatrix();


    glRotated(90,0,1,0);

    leftLight();
    planeA();
    planeBGlass();
    planeB();
    planeCGlass();
    planeC();
    frontSide();
    planeE();
    planeF();
    planeG();
    planeH();
    planeI();
    planeJ();
    wheels();
    frontSmoother();
    backSmoother();
    drawDoors();
    fixWheelWhole();
    glPopMatrix();
    glPopMatrix();
 }

imageInfo *img, img2;
linearImage *linImg;
static GLuint texName[1];


void callOnce(){
    if(!loadImage("street.bmp",img))
	{
		printf("\n4File Error\n");
	}

	linImg = getLinearImage(img);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glGenTextures(1, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, (*img).imageWidth, (*img).imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,(*linImg).ar);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(255,255,255,1);
    glLoadIdentity();
    gluLookAt(eye.X,eye.Y,eye.Z,eye.X,eye.Y,eye.Z-100,upvec.X,upvec.Y,upvec.Z);
    glTranslated(0,0,-200);


    glPushMatrix();
    glRotated(xa,1,0,0);
    glRotated(ya,0,1,0);
    glRotated(za,0,0,1);
    glRotated(-90,0,1,0);
    drawCar();
//    drawRoad();
    glPopMatrix();
    glutSwapBuffers();
}

void keypressSpecial (int key, int x, int y)
{	glutSetKeyRepeat(0);
switch (key)
    {
        case GLUT_KEY_UP:
            eye.Y-=sp;
            //runz--;
        break;
        case GLUT_KEY_DOWN:
            //runz++;
            eye.Y+=sp;
        break;
        case GLUT_KEY_LEFT:
            eye.X+=sp;
        break;
        case GLUT_KEY_RIGHT:
            eye.X-=sp;
        break;
        case GLUT_KEY_F10:
            eye.Z+=sp;
        break;
        case GLUT_KEY_F11:
            eye.Z-=sp;
            break;
        case GLUT_KEY_F9:
            eye=point3d(0,0,100);
    }

    glutPostRedisplay();

}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
            exit(0);
            break;
        case 'x':
            xa+=1;
            if(xa==360) xa=0;
        break;
        case 's':
            xa-=1;
            if(xa==-1) xa=359;
        break;
        case 'z':
            za+=1;
            if(za==360) za=0;
        break;
        case 'a':
            za-=1;
            if(za==-1) za=359;
        break;
         case 'c':
            ya+=1;
            if(ya==360) ya=0;
        break;
        case 'd':
            ya-=1;
            if(ya==-1) ya=359;
        break;

        case 'r':
           state = STATIC_SCENE;
           roadMotion = 0;
           carM = 0;
        break;

        case 't':
            state = CAR_IN_MOTION;
            roadMotion = 0;
        break;

        case 'y':
            state = SCENE_IN_MOTION;
            carM = 0;
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}
void update(int value)
{
    if(state== SCENE_IN_MOTION)roadMotion-=4;
    else  if(state == CAR_IN_MOTION && carM<9900) carM+=4;
    if(roadMotion<-1000) roadMotion = 1000;

    Angle += 2.0f ;
    if(Angle > 360)
    {
        Angle -= 360 ;
    }
    glutPostRedisplay() ;
    glutTimerFunc(10 , update , 0) ;
}





int main(int argc, char *argv[]){
    initializeCar();
    callOnce();
    glutInit(&argc,argv);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("Gambar Mobil");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(keypressSpecial);
    glutTimerFunc(10, update , 0) ;
    glutIdleFunc(idle);



    glutMainLoop();
    return 0;
}
