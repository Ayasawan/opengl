
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library

#include <fstream>
#include"texture.h"
#include <cmath>
#include "heightMap.h"
#include "Model_3ds.h"
#include "3DTexture.h"
#include <camera.h>
#include "tgaLoader.h"


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

Camera MyCamera;
float speed=1;
int mouseX=0,mouseY=0;
bool isClicked=0,isRClicked=0,ckeck_move=0;

bool check_hit=false,check_pointer;
bool check_hitt=false;
bool check_hittt=false;
double Xa,Xb,Ya,Yb,Za,Zb;
double Xant=28,Yant=0.1,Zant=55;
double Xantt=15,Yantt=18.3,Zantt=60;
double Xanttt=10,Yanttt=18.3,Zanttt=70;
double antscale=300;
double anttscale=300;
double antttscale=300;
double Px=35,Py=30,Pz;
int case_back,case_front,case_left,case_right,case_top,case_down,case_inner;
int back, front, left, right, top;
int black,key_bord,motherboard,power,ramf,ramb,fan,graphics,circuit,processor,usb,ioi,key_bordp;
int table,full,abstrac,gcir,npart,circuitd;
int google,mainp,vc,disctop,off,display,runp;
int scene_num=1;
int collor_grey,collor_orang;
 Model_3DS *antred;
 
	

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	MyCamera = Camera();
	MyCamera.Position.x = 30;
	MyCamera.Position.y = 25;
	MyCamera.Position.z = 5;
	MyCamera.RotateY(180.0);
	
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);

	//collor
	black= LoadTexture("parts/black.bmp");
	collor_grey= LoadTexture("collor/grey.bmp");
	collor_orang=LoadTexture("collor/orang.bmp");
	//room
	back = LoadTexture("room/wall.bmp");
	front = LoadTexture("room/wall.bmp");
	left = LoadTexture("room/wall.bmp");
	right = LoadTexture("room/wall.bmp");
	top = LoadTexture("room/wall.bmp");

	//table
	table = LoadTexture("table/table.bmp");

	//case
	case_back = LoadTexture("case/back.bmp");
	case_front = LoadTexture("case/front.bmp");
	case_left = LoadTexture("case/left.bmp");
	case_right = LoadTexture("case/right.bmp");
	case_top = LoadTexture("case/top.bmp");
	case_down = LoadTexture("case/dwon.bmp");
	case_inner = LoadTexture("case/inner.bmp");
	//Parts
	power= LoadTexture("parts/power.bmp");
	ramf=LoadTexture("parts/ramF.bmp");
	ramb=LoadTexture("parts/ramB.bmp");
	fan=LoadTexture("parts/fan.bmp");
	graphics=LoadTexture("parts/NVIDIA.bmp");
	circuit=LoadTexture("parts/dr.bmp");
	circuitd=LoadTexture("parts/ddr.bmp");
	processor=LoadTexture("parts/processor.bmp");
	usb=LoadTexture("parts/usb.bmp");
	ioi=LoadTexture("parts/ioi.bmp");
	key_bordp=LoadTexture("parts/keybordp.bmp");
	
	//parta
	full=LoadTexture("parta/full.bmp");
	abstrac=LoadTexture("parta/mBground.bmp");
	gcir=LoadTexture("parta/n.bmp");
	npart=LoadTexture("parta/wg.bmp");
	//motherboard
	motherboard= LoadTexture("parts/motherboard.bmp");
	//keybord
	key_bord = LoadTexture("parts/keybord.bmp");
	//LG
	off = LoadTexture("display/off.bmp");
	google = LoadTexture("display/google.bmp");
	mainp = LoadTexture("display/main.bmp");
	vc = LoadTexture("display/vc.bmp");
	disctop = LoadTexture("display/disctop.bmp");
	runp = LoadTexture("display/runp.bmp");
	display=off;
	
	 glEnable(GL_TEXTURE);
		antred = new Model_3DS();
		antred->Load("ANT_BLK.3DS");

		GLTexture blk,blkt;
		blk.LoadBMP("ANT_BLK.bmp");
		blkt.LoadBMP("ANT_BLKt.bmp");	
			antred->Materials[0].tex=blkt;
			antred->Materials[1].tex=blk;

	return TRUE;										// Initialization Went OK
}
GLUquadric* quadric = gluNewQuadric();
void colliderz(float dx,float dy,float px,float py,float pz){
	
	double Xc=MyCamera.Position.x;
	double Yc=MyCamera.Position.y;
	double Zc=MyCamera.Position.z;
	if(Zc<=pz+1&&Zc>=pz-1 && Xc>=px&&Xc<=px+dx && Yc>=py&&Yc<=py+dy)
	{

		if(Zc<pz)
		MyCamera.Position.z=pz-1;
		if(Zc>=pz)
		MyCamera.Position.z=pz+1;
		
	}
}
void colliderx(float dz,float dy,float px,float py,float pz){
	
	double Xc=MyCamera.Position.x;
	double Yc=MyCamera.Position.y;
	double Zc=MyCamera.Position.z;
	if(Xc<=px+1&&Xc>=px-1 &&Zc>=pz&&Zc<=pz+dz && Yc>=py&&Yc<=py+dy)
	{

		if(Xc<px)
		MyCamera.Position.x=px-1.2;
		if(Xc>=px)
		MyCamera.Position.x=px+1.2;
		
	}
}
void colliderineer(float dx,float dy,float dz,float px,float py,float pz){
	
	double Xc=MyCamera.Position.x;
	double Yc=MyCamera.Position.y;
	double Zc=MyCamera.Position.z;

	if(Xc<=px)MyCamera.Position.x=px+0.5;
	if(Xc>=dx)MyCamera.Position.x=dx-0.5;

	if(Yc<=py)MyCamera.Position.y=py+0.5;
	if(Yc>=dy)MyCamera.Position.y=dy-0.5;

	if(Zc<=pz)MyCamera.Position.z=pz+0.5;
	if(Zc>=dz)MyCamera.Position.z=dz-0.5;


}


void colliderScene(float dx,float dy,float px,float py,float pz,int scene )
{
	double Xc=MyCamera.Position.x;
	double Yc=MyCamera.Position.y;
	double Zc=MyCamera.Position.z;
	if(Xc>=px&&Xc<=dx && Yc>=py&&Yc<=dy && Zc>=pz-2&&Zc<=pz)scene_num=scene;



}
void keybord()
{
	
	if (keys['H']){
		scene_num=1;
		MyCamera.Position.x=30;
		MyCamera.Position.y=25;
		MyCamera.Position.z=5;
		
	}
	if (keys['C'])speed=0.1;
	if (keys['V'])speed=0.5;
	if (keys['B'])speed=1;
	if (keys[VK_LEFT])			MyCamera.RotateY(speed+1);
	if (keys[VK_RIGHT])		    MyCamera.RotateY(-(speed+1));
	if (keys['Z'])	    MyCamera.RotateX(-speed);
	if (keys['X'])		    MyCamera.RotateX(speed);
	if (keys['S'])      MyCamera.MoveForward(-speed);
	if (keys['W'])      MyCamera.MoveForward(speed);
	if (keys['A'])	    MyCamera.MoveRight(-speed);
	if (keys['D'])		MyCamera.MoveRight(speed);
	if (keys[VK_UP])    	MyCamera.MoveUpward(speed);
	if (keys[VK_DOWN])		MyCamera.MoveUpward(-speed);
	
}

void test (){
	glPushMatrix();
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex3f(-30,0,0);
	glVertex3f(30,0,0);
	glColor3ub(0,255,0);
	glVertex3f(0,-30,0);
	glVertex3f(0,30,0);
	glColor3ub(0,0,255);
	glVertex3f(0,0,-30);
	glVertex3f(0,0,30);
	glEnd();

	for(int i=0;i<=30;i++){

			glBegin(GL_LINES);
			glColor3ub(255,255,255);
			glVertex3f(0,0,i);
			glVertex3f(30,0,i);
			glEnd();
	
	}
	glPopMatrix();
}
void shoot(){
	glPushMatrix();
	glColor3ub(255,255,255);
	glLineWidth(3);
	glTranslated(0,0,-0.1);
	glBegin(GL_LINES);
		
		glVertex3f(-0.004,0,0);
		glVertex3f(-0.0015,0,0);

		glVertex3f(0.0015,0,0);
		glVertex3f(0.004,0,0);

		glVertex3f(0,-0.004,0);
		glVertex3f(0,-0.0015,0);

		glVertex3f(0,0.0015,0);
		glVertex3f(0,0.004,0);

	glEnd();
		glTranslated(0,0,-0.1);
		if(keys['F']){
		//	glLineWidth(5);
			glBegin(GL_LINES);
				glColor3ub(255,0,0);

				glVertex3f(-4,-4,0);
				glVertex3f(0,0,0);
			glEnd();
		}
	glPopMatrix();
					
}
void hit(){
	
	if(check_hit){
		if(antscale>=0)
			antscale-=40;
		else
		{
			check_hit=false;
		}
	}
	if(check_hitt){
		if(anttscale>=0)
			anttscale-=40;
		else
		{
			check_hitt=false;
		}
	}
	if(check_hittt){
		if(antttscale>=0)
			antttscale-=40;
		else
		{
			check_hittt=false;
		}
	}

}
void fire(){
	glPushMatrix();
		if(keys['F']){
				Xa=MyCamera.Position.x;
				Ya=MyCamera.Position.y;
				Za=MyCamera.Position.z;
				for (int i=0;i<300;i++){
				 MyCamera.MoveForward(0.5);
					  Xb=MyCamera.Position.x;
					  Yb=MyCamera.Position.y;
					  Zb=MyCamera.Position.z;
					 
					   if((Xant-Xb)*(Xant-Xb) + (Yant-Yb)*(Yant-Yb) + (Zant-Zb)*(Zant-Zb) <=1)
						  check_hit=true;
					    if((Xantt-Xb)*(Xantt-Xb) + (Yantt-Yb)*(Yantt-Yb) + (Zantt-Zb)*(Zantt-Zb) <=1)
						  check_hitt=true;
					    if((Xanttt-Xb)*(Xanttt-Xb) + (Yanttt-Yb)*(Yanttt-Yb) + (Zanttt-Zb)*(Zanttt-Zb) <=1)
						  check_hittt=true;

				} 
					MyCamera.Position.x=Xa;
					  MyCamera.Position.y=Ya;
					  MyCamera.Position.z=Za;
						 
		}
			
	glPopMatrix();

}

void ant(){
			glColor3ub(255,10,10);
	antred->pos.x=Xant;
	antred->pos.y=Yant;
	antred->pos.z=Zant;
	antred->scale=antscale;
	
	antred->Draw();
	antred->pos.x=Xantt;
	antred->pos.y=Yantt;
	antred->pos.z=Zantt;
	antred->scale=anttscale;
	
	antred->Draw();
		antred->Draw();
	antred->pos.x=Xanttt;
	antred->pos.y=Yanttt;
	antred->pos.z=Zanttt;
	antred->scale=antttscale;
	
	antred->Draw();
	glColor3ub(255,255,255);
}
void pointer(){
	if(display==off)glColor3ub(0,0,0);
	else glColor3ub(255,255,255);
	glPushMatrix();
	
		glTranslated(Px,Py,54);
		glRotated(-45,0,0,1);
		glBegin(GL_POLYGON);
			glVertex3f(-0.05,0,0);
			glVertex3f(-0.05,0.2,0);
			glVertex3f(0.05,0.2,0);
			glVertex3f(0.05,0,0);
			glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-0.2,0.2,0);
			glVertex3f(0.2,0.2,0);
			glVertex3f(0,0.45,0);

			glEnd();
		glPopMatrix();
		 glColor3ub(255,255,255);
}
void movepointer(){

	if (keys['I'])     Py+=0.3;
	if (keys['K'])     Py-=0.3;
	if (keys['J'])	   Px+=0.3;
	if (keys['L'])		Px-=0.3;
	if(Px>42.5)Px=42.5;
	if(Px<27.2)Px=27.2;
	if(Py>34.5)Py=34.5;
	if(Py<24.1)Py=24.1;
}
void clickpointer(){
	if (keys['O']){
		if(Px>=27.2 && Px<=27.5 && Py>=33.5 && Py<=34.5)display=google;
		if(Px>=27.2 && Px<=27.5 && Py>=32 && Py<=33)display=disctop;
		if(Px>=27.2 && Px<=27.5 && Py>=25 && Py<=26)display=vc;
			
	}
	
	if (keys['R'] && display==vc)display=runp;
	if (keys['M'] )display=mainp;
	if (keys['Q'] )display=off;
}
void LG(){
		glPushMatrix();
	glTranslated(35,21.1,56);
	glRotated(-90,1,0,0);
	
	glColor3ub(20,20,20);
	gluCylinder(quadric, 4.5, 3.5, 1, 32, 70);
	gluDisk(quadric, 0, 4.5, 32, 32);
	glTranslatef(0, 0,1);
	gluDisk(quadric, 0, 3.5, 32, 32);

	gluCylinder(quadric, 1.5, 1.55, 2.5, 32, 70);
	glTranslatef(0, 0,2.5);
	gluDisk(quadric, 0, 1.55, 32, 32);
	
	glPopMatrix();
	

	
}
void transistor(float x,float y,float z)
{
		glPushMatrix();
			glTranslated(x,y,z);
			glRotated(-90,1,0,0);
	
			glColor3ub(20,20,20);
			gluCylinder(quadric, 2, 2, 2, 32, 70);
			gluDisk(quadric, 0, 2, 32, 32);
			glTranslatef(0, 0,2);
			gluDisk(quadric, 0, 2, 32, 32);
	
	glPopMatrix();
	
}

void socket(float x1,float y1,float z1,float x2,float y2,float z2){
	//create_box(3,14,0.2,1.5,19,23.8,8,-1,-1,-1,-1,-1,-1);
	glPushMatrix();
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);


	glEnd();
	glPopMatrix();
}
void create_box(float dx,float dy,float dz,float px,float py,float pz,int check_face,
				int img_front,int img_back,int img_right,
				int img_left,int img_down,int img_top)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

		if (check_face == 1||check_face == 7||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_front);
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0);glVertex3f(px+dx,py,pz);
		
		glTexCoord2d(1, 0);glVertex3f(px,py,pz);
		
		glTexCoord2d(1, 1);glVertex3f(px,py+dy,pz);
		
		glTexCoord2d(0, 1);glVertex3f(px+dx,py+dy,pz);
		
		glEnd();
		}

		if (check_face == 2||check_face == 7||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_back);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);
			glVertex3f(px,py,pz+dz);
			glTexCoord2d(1, 0);
			glVertex3f(px+dx,py,pz+dz);
			glTexCoord2d(1,1);
			glVertex3f(px+dx,py+dy,pz+dz);
			glTexCoord2d(0, 1);
			glVertex3f(px,py+dy,pz+dz);
		glEnd();
		}


		if (check_face == 3||check_face == 7||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_right);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);
			glVertex3f(px,py,pz);
			glTexCoord2d(1, 0);
			glVertex3f(px,py,pz+dz);
			glTexCoord2d(1, 1);
			glVertex3f(px,py+dy,pz+dz);
			glTexCoord2d(0, 1);
			glVertex3f(px,py+dy,pz);
		glEnd();
		}

		if (check_face == 4||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_left);
			glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);glVertex3f(px+dx,py,pz+dz);
			
			glTexCoord2d(1, 0);glVertex3f(px+dx,py,pz);
			
			glTexCoord2d(1, 1);	glVertex3f(px+dx,py+dy,pz);
			
			glTexCoord2d(0, 1);glVertex3f(px+dx,py+dy,pz+dz);
		
		glEnd();}


		if (check_face == 5||check_face == 7||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_down);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);
			glVertex3f(px,py,pz);
			glTexCoord2d(1, 0);
			glVertex3f(px+dx,py,pz);
			glTexCoord2d(1, 1);
			glVertex3f(px+dx,py,pz+dz);
			glTexCoord2d(0, 1);
			glVertex3f(px,py,pz+dz);
		glEnd();
		}


		if (check_face == 6||check_face == 7||check_face == 8){
		glBindTexture(GL_TEXTURE_2D, img_top);
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0);glVertex3f(px+dx,py+dy,pz);
		
		glTexCoord2d(1, 0);glVertex3f(px,py+dy,pz);
		
		glTexCoord2d(1, 1);glVertex3f(px,py+dy,pz+dz);
		
		glTexCoord2d(0, 1);glVertex3f(px+dx,py+dy,pz+dz);
		
		glEnd();
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		//1 front
		//2 back
		//3 right
		//4 lift
		//5 down
		//6 top
		//7 back right lift down top
		//8 cube
}
void cir(){
	create_box(10,5,10,30,0.1,10,8,abstrac,abstrac,abstrac,abstrac,abstrac,abstrac);
	glPushMatrix();
	glColor3ub(255,25,25);
	glLineWidth(3);

	glBegin(GL_LINES);
		
	for (int i = 0; i < 9; i++)
	{
		glVertex3f(30,5,i+11);
		glVertex3f(27,0.1,i+11);

		glVertex3f(40,5,i+11);
		glVertex3f(43,0.1,i+11);
	}
		

	

	glEnd();
}
void cabl(){
	glBegin(GL_LINES);
		glColor3ub(255,0,0);

		glVertex3f(10,10,0.1);
		glVertex3f(15,15,15);

		glVertex3f(15,15,15);
		glVertex3f(60,33,0.1);

		glColor3ub(0,255,0);

		glVertex3f(10,12,0.1);
		glVertex3f(15,15,15);

		glVertex3f(15,15,15);
		glVertex3f(60,36,0.1);

		glColor3ub(0,0,255);
		
		glVertex3f(16,16,0.1);
		glVertex3f(15,15,15);

		glVertex3f(15,15,15);
		glVertex3f(66,40,0.1);

	glEnd();
	glColor3ub(255,255,255);
}
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glColor3ub(255,255,255);
	shoot();
	MyCamera.Render();
	
	keybord();
	hit();
	fire();
	glColor3ub(255,255,255);
	

	//--------------------Scene 1 -------Room
	if(scene_num==1){
		
		colliderScene(41,25.5,40,25,56,2);//Monitor
		colliderScene(24.5,25.5,22,24.5,45,3);//case
		colliderScene(32.5,21.5,32,21.1,44.5,4);//keybord

		movepointer();
		clickpointer();
		pointer();
		//room
		colliderineer(70,70,70,0,0,0);
		glColor3ub(255,255,255);
		create_box(70,70,70,0,0,0,8,front,back,right,left,top,top);
		//table
		create_box(3,20,3,50,0,40,8,table,table,table,table,table,table);
		create_box(3,20,3,20,0,40,8,table,table,table,table,table,table);
		create_box(3,20,3,50,0,60,8,table,table,table,table,table,table);
		create_box(3,20,3,20,0,60,8,table,table,table,table,table,table);
		create_box(40,1,30,15,20,40,8,table,table,table,table,table,table);
		//case
		colliderz(5,10,20,21.1,45);
		colliderz(5,10,20,21.1,45);
		colliderx(10,10,20,21.1,45);
		colliderx(10,10,25,21.1,45);
		create_box(5,10,10,20,21.1,45,8,case_front,case_back,case_right,case_left,case_right,case_right);
		//keybord
		colliderz(12,0.4,30,21.1,45);
		colliderz(12,0.4,30,21.1,49);
		colliderx(4,0.4,30,21.1,45);
		colliderx(4,0.4,42,21.1,45);
		create_box(12,0.4,4,30,21.1,45,8,black,black,black,black,black,key_bord);
		create_box(0.5,0.2,0.5,32,21.2,44.93,8,usb,black,black,black,black,black);

		//LG
		colliderz(17,12,26.5,23.5,54.4);
		colliderz(17,12,26.5,23.5,55.4);
		colliderx(1,12,26.5,23.5,54.4);
		colliderx(1,12,43.5,23.5,54.4);
		LG();
		create_box(17,12,1,26.5,23.5,54.4,8,-1,-1,-1,-1,-1,-1);
		glColor3ub(255,255,255);
		create_box(1,0.4,0.2,40,25,55.4,8,black,ioi,black,black,black,black);
		//play
		glColor3ub(255,255,255);
		create_box(16,11,1,27,24,54.3,1,display,-1,-1,-1,-1,-1);



				} //End Scene 1
		//_________________________________________________________________________
	   //--------------------Scene 2 -------Monitor
	if(scene_num==2){
		 Xant=30,Yant=0.1,Zant=10;
		 Xantt=15,Yantt=0.1,Zantt=15;
		 Xanttt=60,Yanttt=0.1,Zanttt=12;
		 ant();
		colliderineer(80,60,30,0,0,0);
		create_box(80,60,30,0,0,0,8,black,black,black,black,black,black);

		create_box(78,57,0.3,5,5,29,8,abstrac,black,black,black,black,black);

		create_box(40,30,0.3,5,5,0.1,8,black,circuitd,black,black,black,black);
		create_box(30,20,0.3,48,25,0.1,8,black,circuit,black,black,black,black);
		cabl();

	
		}//End Scene 2

	//--------------------Scene 3 -------Case
	if(scene_num==3){
		 Xant=28,Yant=0.1,Zant=55;
		 Xantt=15,Yantt=18.3,Zantt=60;
		 Xanttt=10,Yanttt=18.3,Zanttt=70;
		 ant();
		colliderineer(40,80,80,0,0,0);
		//case
		create_box(40,80,80,0,0,0,8,black,case_back,case_inner,case_left,black,black);
		//power
		colliderz(38,20,1,60,55);
		create_box(38,20,25,1,60,55,8,power,collor_grey,collor_grey,collor_grey,collor_grey,collor_grey);
		//Motherboard
		create_box(1.5,55,57,1,1,20,8,collor_grey,collor_grey,collor_grey,motherboard,collor_grey,collor_grey);

		//RAM
		create_box(6,32,0.5,1.5,20,31,8,ramf,ramb,black,black,black,black);
		create_box(6,32,0.5,1.5,20,33.2,8,ramf,ramb,black,black,black,black);

		//FAN
		create_box(5,10,10,1.5,25,40,8,black,black,black,fan,black,black);

		//socket
		glColor3ub(30,100,170);
		create_box(1,14,2.2,1.5,19,23.8,8,-1,-1,-1,-1,-1,-1);
		glColor3ub(110,180,230);
		create_box(3,14,0.2,1.5,19,26,8,-1,-1,-1,-1,-1,-1);
		create_box(3,14,0.2,1.5,19,23.8,8,-1,-1,-1,-1,-1,-1);
		
		glColor3ub(190,200,0);
		for (int i = 0; i < 13; i++)
		{
			socket(1,20+i,24.5,4,20+i,24.5);
			socket(1,20+i,25.6,4,20+i,25.6);
		}
		glColor3ub(255,255,255);

		//NVIDIA
		create_box(17,0.3,35,1.5,18,40,8,circuit,circuit,circuit,circuit,circuit,graphics);

		//Processor
		create_box(5,13,10,1.5,22,56,8,collor_orang,collor_orang,collor_orang,processor,collor_orang,collor_orang);


		//test();
		} //End Scene 3
	//_________________________________________________________________________
	 //--------------------Scene 4 -------keybord
	if(scene_num==4){
		

		colliderineer(80,20,60,0,0,0);
		create_box(80,20,60,0,0,0,8,black,black,black,black,black,key_bordp);
		//circuit
		create_box(78,0.2,58,1,0.1,1,8,black,black,black,black,black,circuit);
		cir();
		

		for (int i = 0; i < 5; i++){
		for (int j = 0; j < 15; j++)
				{
				transistor(10+5*j,18,10+5*i);
					}}
			
		

		}//End Scene 4

	
	

	


		glFlush();										

    //DO NOT REMOVE THIS
	SwapBuffers(hDC);			
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}


 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{

		case WM_MOUSEMOVE: 
			{ mouseX = (int)LOWORD(lParam);
				mouseY = (int)HIWORD(lParam); isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
				isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false; break;
			} 

			 case WM_LBUTTONUP: isClicked = false; break;
			 case WM_RBUTTONUP: isRClicked = false;break;
			 case WM_LBUTTONDOWN: isClicked = true;break;
			 case WM_RBUTTONDOWN: isRClicked = true; break;

		case WM_PAINT: 
			DrawGLScene();
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;
	
		case WM_TIMER:
			DrawGLScene();
			return 0;

		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Madhat NeHe Template",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer=SetTimer(hWnd,0,50,(TIMERPROC) NULL);

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
	}

	return 0;

}



