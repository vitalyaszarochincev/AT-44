#pragma hdrstop

#include <vcl.h>
#include <math.h>
#include "Unit1.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

#define TO_RADIANS(angle) (((angle) * (M_PI)) / (180.0))

TForm1 *Form1;

struct CUBE
{
  	double x;
  	double y;
};

const int PEAK_NUM = 8;
const int PEAKS_IN_ADGE = 4;
const int ADGES = 6;
const int MAX_ANGLE = 360;
const int ROT_SHIFT = 5;
const double SKALE_SHIFT = 0.2;
const double START_SCALE = 2.0;
CUBE pix[PEAK_NUM];
CUBE cube[ADGES][PEAKS_IN_ADGE];

double startXCordinate = ROT_SHIFT;
double startYCordinate = 2ROT_SHIFT;
double startZCordinate = 0;
double vergeLen = 80;

const int NewPix[PEAK_NUM][3] =
{
	{startXCordinate, startYCordinate, startZCordinate},
	{startXCordinate + vergeLen, startYCordinate, startZCordinate},
	{startXCordinate + vergeLen, startYCordinate + vergeLen, startZCordinate},
	{startXCordinate, startYCordinate + vergeLen, startZCordinate},
	{startXCordinate, startYCordinate, startZCordinate + vergeLen},
	{startXCordinate + vergeLen, startYCordinate, startZCordinate + vergeLen},
	{startXCordinate + vergeLen, startYCordinate+vergeLen, startZCordinate + vergeLen},
	{startXCordinate, startYCordinate+vergeLen, startZCordinate+vergeLen}
};
const int verges[ADGES][PEAKS_IN_ADGE] =
{
	{0, 4, 5, 1},
	{0, 1, 2, 3},
	{0, 3, 7, 4},
	{5, 4, 7, 6},
	{1, 5, 6, 2},
	{2, 6, 7, 3}
};

int RotX = 0;
int RotY = 0;
int RotZ = 0;
int ShiftY = 150;
int ShiftX = 150;
double newpix[PEAK_NUM][3];
double Scale = 0;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner){}

int ALG_Roberts(int i)
{
    double summ = 0;
    int k;

    for(int j = 0; j < PEAKS_IN_ADGE; j++)
    {
    	if(j == PEAKS_IN_ADGE - 1)
    		k = 0;
    	else
    		k = j + 1;
        
        ssumm += (cube[i][j].x - cube[i][k].x) * (cube[i][j].y + cube[i][k].y);
    }

    if(summ > 0)
    	summ = 1;
    else
    	summ = 0;

    return summ;
}

void Perspect()
{
	for(int i = 0; i < PEAK_NUM; i++)
	{
		pix[i].x = newpix[i][0] + newpix[i][2] / 2;
		pix[i].y = newpix[i][1] - newpix[i][2] / 2;
	}

	for(int i = 0; i < ADGES; i++)
		for(int j = 0; j < PEAKS_IN_ADGE; j++)
			cube[i][j] = pix[verges[i][j]];
}

void Conversion()
{
	double x = 0;
	double y = 0;
	double z = 0;
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	for (int i = 0; i < PEAK_NUM; i++)
	{
		x = NewPix[i][0];
		y = NewPix[i][1];
		z = NewPix[i][2];

		x1 = x * cos(TO_RADIANS(RotZ)) + y * sin(TO_RADIANS(RotZ));
		y1 = -x * sin(TO_RADIANS(RotZ)) + y * cos(TO_RADIANS(RotZ));
		z1 = z;

		x = x1;
		y = y1 * cos(TO_RADIANS(RotX)) + z1 * sin(TO_RADIANS(RotX));
		z = -y1 * sin(TO_RADIANS(RotX)) + z1 * cos(TO_RADIANS(RotX));

		x1 = x * cos(TO_RADIANS(RotY)) - z * sin(TO_RADIANS(RotY));
		y1 = y;
		z1 = x * sin(TO_RADIANS(RotY)) + z * cos(TO_RADIANS(RotY));

		newpix[i][0] = x1 * Scale + ShiftX;
		newpix[i][1] = y1 * Scale + ShiftY;
		newpix[i][2] = z1 * Scale;
	}
}

void DrawEdge (int fromX, int fromY, int toX, int toY)
{
	Form1->Canvas->MoveTo(cube[fromX][fromY].x, cube[fromX][fromY].y);
	Form1->Canvas->LineTo(cube[toX][toY].x, cube[toX][toY].y);
}

void DrawCube()
{
	int k;
	
	for(int i = 0; i < ADGES; i++)
		for(int j = 0; j < PEAKS_IN_ADGE j++)
			if(ALG_Roberts(i))
			{
		    	if(j == PEAKS_IN_ADGE - 1)
		    		k = 0;
		    	else
		    		k = j + 1;

				DrawEdge(i, j, i, k);
			}
}

void START ()
{
   Form1->Repaint();
   Conversion();
   Perspect();
   DrawCube();
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	RotX = 0;
	RotY = 0; 
	RotZ = 0;
	Scale = START_SCALE;

	START();

	Form1->GroupBox2->Visible = True;
	Form1->GroupBox3->Visible = True;
}

void __fastcall TForm1::S_MaxClick(TObject *Sender)
{
	Scale += SKALE_SHIFT;
	START();
}

void __fastcall TForm1::S_MinClick(TObject *Sender)
{
  if (Scale > 1) 
  	Scale -= SKALE_SHIFT;

  START();
}

void __fastcall TForm1::UpClick(TObject *Sender)
{
	double Step = StrToFloat(Form1->SZ->Text);
	ShiftY -= Step;
	START();
}

void __fastcall TForm1::DownClick(TObject *Sender)
{  
	double Step = StrToFloat(Form1->SZ->Text);
	ShiftY += Step;
	START();
}

void __fastcall TForm1::RightClick(TObject *Sender)
{ 
	double Step = StrToFloat(Form1->SZ->Text);
	ShiftX += Step;
	START();
}

void __fastcall TForm1::LeftClick(TObject *Sender)
{
	double Step = StrToFloat(Form1->SZ->Text);
	ShiftX -= Step;
	START();
}

void __fastcall TForm1::ExitClick(TObject *Sender)
{
  	Close();
}

void __fastcall TForm1::Rotation_XMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(RotX < MAX_ANGLE - ROT_SHIFT)
   {
     if (Button == mbLeft) 
     	RotX += ROT_SHIFT;

     if (Button == mbRight) 
     	RotX -= ROT_SHIFT;
   }else 
   		RotX = 0;

   START();
}

void __fastcall TForm1::Rotation_YMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(RotX < MAX_ANGLE - ROT_SHIFT)
   {
     	if (Button == mbLeft) 
     		RotY += ROT_SHIFT;

     	if (Button == mbRight) 
     		RotY -=ROT_SHIFT;
   }else 
   		RotX = 0;

   START();
}

void __fastcall TForm1::Rotation_ZMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(RotX < MAX_ANGLE - ROT_SHIFT)
   {
    	if (Button == mbLeft) 
     		RotZ += ROT_SHIFT;

    	 if (Button == mbRight) 
     		RotZ -= ROT_SHIFT;
   }else 
   		 RotX = 0;

   START();
}

void __fastcall TForm1::GroupBox3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
  	ShowHint = True;
}
