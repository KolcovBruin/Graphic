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
float Brz_L[2][3];
float Line_std[2][3];
float MTX[Row_Line][Colm_Line];    //??
float Mod[Row_cnv][Colm_cnv];

float swop;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void start_Brez_L()
{
	Brz_L[0][0]=100.0;
	Brz_L[0][1]=100.0;
	Brz_L[0][2]=1.0;
	Brz_L[1][0]=215.0;
	Brz_L[1][1]=215.0;
	Brz_L[1][2]=1.0;
}
void start_Line()
{
	Line_std[0][0]=105.0;
	Line_std[0][1]=100.0;
	Line_std[0][2]=1.0;
	Line_std[1][0]=220.0;
	Line_std[1][1]=215.0;
	Line_std[1][2]=1.0;

}
//---------------------------------------------------------------------------
void alg_Brez (float x0, float x1, float y0, float y1, TColor color_L)
{
  float dx = (abs(x1-x0));
	float dy = (abs(y1-y0));
	float err = 0.0; //Bretzenheim error
	float derr = dy/dx;
	int x, y;
	if (dx > dy)//(dx>dy)
		{
			if ((x1-x0)<0) // without only 180
			{
				 swop = x0; x0 = x1; x1 = swop;
				 swop = y0; y0 = y1; y1 = swop;
			}
			if ((y1-y0)>=0)
			{
			 y = floor(y0);
			 for(x = floor(x0) ; x < ceil(x1); ++x) // considers +1
			 {                                      // floor to min ceil to max
				Form1->Canvas->Pixels[x][y] = color_L;
				err += derr;
				if (err >= 0.5)
				{
					++y;
					err = err - 1.0;
				}
			 }
			}
			else
			{
			 y = floor(y0);
			 for(x = floor(x0) ; x < ceil(x1); ++x)
			 {
				Form1->Canvas->Pixels[x][y] = color_L;
				err += derr;
				if (err >= 0.5)
				{
					--y;
					err = err - 1.0;
				}
			 }
			}
		}
		else
		{
			if ((y1-y0)<0) // without only 180
			{
				 swop = x0; x0 = x1; x1 = swop;
				 swop = y0; y0 = y1; y1 = swop;
			}
			derr = dx/dy;
			if ((x1-x0)>=0)
			{
			 x = floor(x0);
			 for(y = floor(y0); y < ceil(y1); ++y)
			 {
				Form1->Canvas->Pixels[x][y] = color_L;
				err += derr;
				if (err >= 0.5)
				{
					++x;
					err = err - 1.0;
				}
			 }
			}
			else
			{
			 x = floor(x0);
			 for(y = floor(y0); y < ceil(y1); ++y)
			 {
				Form1->Canvas->Pixels[x][y] = color_L;
				err += derr;
				if (err >= 0.5)
				{
					--x;
					err = err - 1.0;
				}
			 }
			}

		}
}
//---------------------------------------------------------------------------
void refresh()
{
	Form1->Canvas->Brush->Color = clBtnFace;
	Form1->Canvas->FillRect(Form1->Canvas->ClipRect);
if (enable_std)
	{
		Form1->Canvas->Pen->Color=clRed; //Изменяем цвет пера на красный
		Form1->Canvas->MoveTo(round(Line_std[0][0]),round(Line_std[0][1]));
		Form1->Canvas->LineTo(round(Line_std[1][0]),round(Line_std[1][1]));

	}
if (enable_Br)
	{
		alg_Brez(Brz_L[0][0], Brz_L[1][0], Brz_L[0][1], Brz_L[1][1], clBlue);
	}
}
//---------------------------------------------------------------------------
  void mull(int M, int N, int K, const float * A, const float * F, float * C)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			C[i*N + j] = 0;
			for (int k = 0; k < K; ++k)
				C[i*N + j] += A[i*K + k] * F[k*N + j];
		}
	}
}


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
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Canvas->Brush->Color = clBtnFace;
Canvas->FillRect(Canvas->ClipRect);

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
  Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=5.0; Mod[2][1]=0.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=-5.0; Mod[2][1]=0.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=0.0; Mod[2][1]=-5.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=0.0; Mod[2][1]=5.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Mod[0][0]=cos(5*PI/180); Mod[0][1]=+sin(5*PI/180); Mod[0][2]=0.0;
	Mod[1][0]=-sin(5*PI/180); Mod[1][1]=cos(5*PI/180); Mod[1][2]=0.0;
	Mod[2][0]=((Line_std[0][0]+Line_std[1][0])/2)*(1-cos(5*PI/180))+((Line_std[0][1]+Line_std[1][1])/2)*sin(5*PI/180);
	Mod[2][1]=((Line_std[0][1]+Line_std[1][1])/2)*(1-cos(5*PI/180))-((Line_std[0][0]+Line_std[1][0])/2)*sin(5*PI/180);
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{
	Mod[0][0]=1.05; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.05; Mod[1][2]=0.0;
	Mod[2][0]=((Line_std[0][0]+Line_std[1][0])/2)-(1.05*((Line_std[0][0]+Line_std[1][0])/2));
	Mod[2][1]=((Line_std[0][1]+Line_std[1][1])/2)-(1.05*((Line_std[0][1]+Line_std[1][1])/2));
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	Mod[0][0]=0.95; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=0.95; Mod[1][2]=0.0;
	Mod[2][0]=((Line_std[0][0]+Line_std[1][0])/2)-(0.95*((Line_std[0][0]+Line_std[1][0])/2));
	Mod[2][1]=((Line_std[0][1]+Line_std[1][1])/2)-(0.95*((Line_std[0][1]+Line_std[1][1])/2));
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button23Click(TObject *Sender)
{
if (enable_Br == 0)
{
	enable_Br = 1;
	start_Brez_L();
}
else
{
	enable_Br = 0;
}
refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button22Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=5.0; Mod[2][1]=0.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender)
{
Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=-5.0; Mod[2][1]=0.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=0.0; Mod[2][1]=-5.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
	Mod[0][0]=1.0; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.0; Mod[1][2]=0.0;
	Mod[2][0]=0.0; Mod[2][1]=5.0; Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
	Mod[0][0]=cos(5*PI/180); Mod[0][1]=+sin(5*PI/180); Mod[0][2]=0.0;
	Mod[1][0]=-sin(5*PI/180); Mod[1][1]=cos(5*PI/180); Mod[1][2]=0.0;
	Mod[2][0]=((Brz_L[0][0]+Brz_L[1][0])/2)*(1-cos(5*PI/180))+((Brz_L[0][1]+Brz_L[1][1])/2)*sin(5*PI/180);
	Mod[2][1]=((Brz_L[0][1]+Brz_L[1][1])/2)*(1-cos(5*PI/180))-((Brz_L[0][0]+Brz_L[1][0])/2)*sin(5*PI/180);
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
	Mod[0][0]=cos(-5*PI/180); Mod[0][1]=+sin(-5*PI/180); Mod[0][2]=0.0;
	Mod[1][0]=-sin(-5*PI/180); Mod[1][1]=cos(-5*PI/180); Mod[1][2]=0.0;
	Mod[2][0]=((Brz_L[0][0]+Brz_L[1][0])/2)*(1-cos(-5*PI/180))+((Brz_L[0][1]+Brz_L[1][1])/2)*sin(-5*PI/180);
	Mod[2][1]=((Brz_L[0][1]+Brz_L[1][1])/2)*(1-cos(-5*PI/180))-((Brz_L[0][0]+Brz_L[1][0])/2)*sin(-5*PI/180);
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
	Mod[0][0]=1.05; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=1.05; Mod[1][2]=0.0;
	Mod[2][0]=((Brz_L[0][0]+Brz_L[1][0])/2)-(1.05*((Brz_L[0][0]+Brz_L[1][0])/2));
	Mod[2][1]=((Brz_L[0][1]+Brz_L[1][1])/2)-(1.05*((Brz_L[0][1]+Brz_L[1][1])/2));
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
	Mod[0][0]=0.95; Mod[0][1]=0.0; Mod[0][2]=0.0;
	Mod[1][0]=0.0; Mod[1][1]=0.95; Mod[1][2]=0.0;
	Mod[2][0]=((Brz_L[0][0]+Brz_L[1][0])/2)-(0.95*((Brz_L[0][0]+Brz_L[1][0])/2));
	Mod[2][1]=((Brz_L[0][1]+Brz_L[1][1])/2)-(0.95*((Brz_L[0][1]+Brz_L[1][1])/2));
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Brz_L, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Brz_L[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
 Mod[0][0]=cos(-5*PI/180); Mod[0][1]=+sin(-5*PI/180); Mod[0][2]=0.0;
	Mod[1][0]=-sin(-5*PI/180); Mod[1][1]=cos(-5*PI/180); Mod[1][2]=0.0;
	Mod[2][0]=((Line_std[0][0]+Line_std[1][0])/2)*(1-cos(-5*PI/180))+((Line_std[0][1]+Line_std[1][1])/2)*sin(-5*PI/180);
	Mod[2][1]=((Line_std[0][1]+Line_std[1][1])/2)*(1-cos(-5*PI/180))-((Line_std[0][0]+Line_std[1][0])/2)*sin(-5*PI/180);
	Mod[2][2]=1.0;
	mull(2, 3, 3, *Line_std, *Mod,*MTX);
	for (int i = 0; i < 2;i++)
	  for (int j = 0; j < 3; j++)
		Line_std[i][j]=MTX[i][j];
	refresh();
}
//---------------------------------------------------------------------------

