//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Lab_1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <stdlib.h>
#include <stdio.h>
#define Row_Line 2 // number of matrix line rows
#define Colm_Line 3 // number of matrix line columns
#define Row_cnv 3 // number of conversion matrix rows
#define Colm_cnv 3 // number of conversion matrix columns
#define PI 3.14159265
int enable_Br = 0;
int enable_std = 0;
float Brz_L[Row_Line][Colm_Line];
float Line_std[3][3];

float MTX[Row_Line][Colm_Line];    //??
float Mod[Row_cnv][Colm_cnv];
float max_x=0;
float max_y=0;
float min_x=0;
float min_y=0;
float swop;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void pokras()
{
   float q1;
   float q2;
   float q3;
	for (int x = min_x; x <max_x ; x++) {
		 for (int y = min_y; y <max_y; y++) {
			q1=x*(Line_std[1][1]-Line_std[0][1])+y*(Line_std[0][0]-Line_std[1][0])+Line_std[0][1]*Line_std[1][0]-Line_std[0][0]*Line_std[1][1];
			q2=x*(Line_std[2][1]-Line_std[1][1])+y*(Line_std[1][0]-Line_std[2][0])+Line_std[1][1]*Line_std[2][0]-Line_std[1][0]*Line_std[2][1];
			q3=x*(Line_std[0][1]-Line_std[2][1])+y*(Line_std[2][0]-Line_std[0][0])+Line_std[2][1]*Line_std[0][0]-Line_std[2][0]*Line_std[0][1];

			if ((((q1 >= 0) and (q2 >= 0) and (q3 >= 0)) or ((q1 < 0) and (q2 < 0) and (q3 < 0))) and (Form1->Canvas->Pixels[x][y] != clRed))
			{

			 Form1->Canvas->Pixels[x][y] = clGreen;

			}

		 }
	}
}


void max_min()
{
	max_x=0;
	max_y=0;
	min_x=100000;
	min_y=100000;
	for (int i = 0; i < 3; i++) {

			if (Line_std[i][0]>max_x) {
				max_x=Line_std[i][0];
			}
			if (Line_std[i][1]>max_y) {
				max_y=Line_std[i][1];
			}
			if (Line_std[i][0]<min_x) {
				min_x=Line_std[i][0];
			}
			if (Line_std[i][1]<min_y) {
				min_y=Line_std[i][1];
			}


	}
}



void start_Line()
{
	Line_std[0][0]=105.0;
	Line_std[0][1]=100.0;
	Line_std[0][2]=1.0;
	Line_std[1][0]=220.0;
	Line_std[1][1]=215.0;
	Line_std[1][2]=1.0;
	Line_std[2][0]=105.0;
	Line_std[2][1]=215.0;
	Line_std[2][2]=1.0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void refresh()
{
	Form1->Canvas->Brush->Color = clBtnFace;
	Form1->Canvas->FillRect(Form1->Canvas->ClipRect);
if (enable_std)
	{
		Form1->Canvas->Pen->Color=clRed; //Изменяем цвет пера на красный
		Form1->Canvas->MoveTo(round(Line_std[0][0]),round(Line_std[0][1]));
        Form1->Canvas->Pixels[round(Line_std[0][0])][round(Line_std[0][1])]=clBtnFace;
		Form1->Canvas->LineTo(round(Line_std[1][0]),round(Line_std[1][1]));
		Form1->Canvas->LineTo(round(Line_std[2][0]),round(Line_std[2][1]));
		Form1->Canvas->LineTo(round(Line_std[0][0]),round(Line_std[0][1]));
	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 void mull_mtx(double MOD[3][3])
{
float New_fig[3][3]={0,0,0};
   for (int k = 0; k < 3; k++) {
	   for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
			  New_fig[k][i]+=Line_std[k][j]*MOD[j][i];
			}
	   }
  }
  for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			Line_std[k][i] = New_fig[k][i];
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if (enable_std == 0)
{
	enable_std = 1;
	start_Line();
}
else
{
	enable_std = 0;
}
refresh();
}





//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	double x_n=0, y_n=0;
	for (int i = 0; i < 3; i++) {
		 x_n+=Line_std[i][0] ;
		 y_n+=Line_std[i][1];
	}
	x_n=x_n/3;
	y_n=y_n/3;
	double Mods[3][3]={{cos(5*PI/180), sin(5*PI/180), 0},{ -sin(5*PI/180), cos(5*PI/180), 0},{x_n * (1 - cos(5*PI/180)) + y_n * sin(5*PI/180), y_n * (1 - cos(5*PI/180)) - x_n * sin(5*PI/180), 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
Canvas->Brush->Color = clBtnFace;
Canvas->FillRect(Canvas->ClipRect);
}
//---------------------------------------------------------------------------











void __fastcall TForm1::Button23Click(TObject *Sender)
{
/////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
////
double Mods[3][3]={{1, 0, 0},{ 0, 1, 0},{0, -5, 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  //////
  double Mods[3][3]={{1, 0, 0},{ 0, 1, 0},{5, 0, 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
   ////
   double Mods[3][3]={{1, 0, 0},{ 0, 1, 0},{0, 5, 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{

double Mods[3][3]={{1, 0, 0},{ 0, 1, 0},{-5, 0, 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{
//////
double x_n=0, y_n=0;
	for (int i = 0; i < 3; i++) {
		 x_n+=Line_std[i][0] ;
		 y_n+=Line_std[i][1];
	}
	x_n=x_n/3;
	y_n=y_n/3;
double Mods[3][3]={{0.95, 0, 0},{ 0, 0.95, 0},{x_n*(1-0.95), y_n*(1-0.95), 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
///////
double x_n=0, y_n=0;
	for (int i = 0; i < 3; i++) {
		 x_n+=Line_std[i][0] ;
		 y_n+=Line_std[i][1];
	}
	x_n=x_n/3;
	y_n=y_n/3;
double Mods[3][3]={{1.05, 0, 0},{ 0, 1.05, 0},{x_n*(1-1.05), y_n*(1-1.05), 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
/////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
//////////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
/////////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
////////0
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
//////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{
//////
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::Button21Click(TObject *Sender)
{
//////
}
void __fastcall TForm1::Button22Click(TObject *Sender)
{
//////
}


void __fastcall TForm1::Button6Click(TObject *Sender)
{
/////
 double x_n=0, y_n=0;
	for (int i = 0; i < 3; i++) {
		 x_n+=Line_std[i][0] ;
		 y_n+=Line_std[i][1];
	}
	x_n=x_n/3;
	y_n=y_n/3;
	double Mods[3][3]={{cos(-5*PI/180), sin(-5*PI/180), 0},{ -sin(-5*PI/180), cos(-5*PI/180), 0},{x_n * (1 - cos(-5*PI/180)) + y_n * sin(-5*PI/180), y_n * (1 - cos(-5*PI/180)) - x_n * sin(-5*PI/180), 1}}  ;
	mull_mtx(Mods);

	refresh();
}
//---------------------------------------------------------------------------

