#include <vcl.h>
#include <math.h>
#include "Unit1.h"

#pragma resource "*.dfm"

TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

struct Cube
{
    double x;
    double y;
};

const double ZOOM_OFFSET = 0.2;
const double MIN_ZOOM = 0.4;
const double MAX_ZOOM = 3.0;
const int COORDINATE_OFFSET = 20;
const int MAX_ANGLE = 357;
const int ANGLE_OFFSET = 3;
const int NUM_OF_POINTS = 8;
const int NUM_OF_VERTEGES = 6;
const int POINTS_IN_VERTEGE = 4;
const int NUM_OF_COORDINATES = 3;

double zoom = 1;
int angle_x, angle_y, angle_z = 0;
int center_x = 300, center_y = 220;

const int point[NUM_OF_POINTS][NUM_OF_COORDINATES] = {{-30,-30,-30},
                                                      { 30,-30,-30},
                                                      { 30, 30,-30},
                                                      {-30, 30,-30},
                                                      {-30,-30, 30},
                                                      { 30,-30, 30},
                                                      { 30, 30, 30},
                                                      {-30, 30, 30}};

const int verges[NUM_OF_VERTEGES][POINTS_IN_VERTEGE] = {{0,4,5,1},
                                                        {0,1,2,3},
                                                        {0,3,7,4},
                                                        {5,4,7,6},
                                                        {1,5,6,2},
                                                        {2,6,7,3}};

double newpoint[NUM_OF_POINTS][NUM_OF_COORDINATES];
Cube points[NUM_OF_POINTS];
Cube cube[NUM_OF_VERTEGES][POINTS_IN_VERTEGE];

bool visible_roberts(int i)
{
    double s = 0;

    for(int j = 0; j < 4; j++)
    {
        int k = (j == 3) ? 0 : j + 1;
        s += (cube[i][j].x - cube[i][k].x) * (cube[i][j].y + cube[i][k].y);
    }

    return ((s > 0) ? true : false);
}

void projection()
{
    for(int i = 0; i < NUM_OF_POINTS; i++)
    {
        points[i].x = newpoint[i][0] + newpoint[i][2] / 2;
        points[i].y = newpoint[i][1] - newpoint[i][2] / 2;
    }

    for(int i = 0; i < NUM_OF_VERTEGES; i++)
    {
        for(int j = 0; j < POINTS_IN_VERTEGE; j++)
        {
            cube[i][j] = points[verges[i][j]];
        }
    }
}

double to_radians(double x)
{
    return (x * (M_PI / 180));
}

void transparent()
{
    double sinx = sin(to_radians(angle_x)),
           siny = sin(to_radians(angle_y)),
           sinz = sin(to_radians(angle_z)),
           cosx = cos(to_radians(angle_x)),
           cosy = cos(to_radians(angle_y)),
           cosz = cos(to_radians(angle_z));

    double x,y,z,x1,y1,z1;

    for (int i = 0; i < NUM_OF_POINTS; i++)
    {
        x = point[i][0];
        y = point[i][1];
        z = point[i][2];

        x1 = x * cosz + y * sinz;
        y1 = -x * sinz + y * cosz;
        z1 = z;

        x = x1;
        y = y1 * cosx + z1 * sinx;
        z = -y1 * sinx + z1 * cosx;

        x1 = x * cosy - z * siny;
        y1 = y;
        z1 = x * siny + z * cosy;

    	newpoint[i][0] = (x1 * zoom);
	    newpoint[i][1] = (y1 * zoom);
	    newpoint[i][2] = (z1 * zoom);

	    newpoint[i][0] += center_x;
	    newpoint[i][1] += center_y;
    }
}

void line(int i, int j, int i1, int j1)
{
        Form1->PaintBox1->Canvas->MoveTo(cube[i][j].x, cube[i][j].y);
        Form1->PaintBox1->Canvas->LineTo(cube[i1][j1].x, cube[i1][j1].y);
}

void draw()
{
    for(int i = 0; i < NUM_OF_VERTEGES; i++)
    {
        for(int j = 0; j < POINTS_IN_VERTEGE; j++)
        {
            if(visible_roberts(i))
            {
                int k = (j == 3) ? 0 : j + 1;
                line(i,j,i,k);
            }
        }
    }
}

void repaint()
{
    Form1->PaintBox1->Repaint();

    transparent();
    projection();
    draw();
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    repaint();

    Form1->GroupBox3->Visible = true;
    Form1->GroupBox4->Visible = true;
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
    if(zoom > MIN_ZOOM) zoom -= ZOOM_OFFSET;
    repaint();
}

void __fastcall TForm1::Button7Click(TObject *Sender)
{
    if(zoom < MAX_ZOOM) zoom += ZOOM_OFFSET;
    repaint();
}

void __fastcall TForm1::Button9Click(TObject *Sender)
{
    if(angle_x < MAX_ANGLE)
        angle_x += ANGLE_OFFSET;
    else
        angle_x = 0;

    repaint();
}

void __fastcall TForm1::Button8Click(TObject *Sender)
{
    if(angle_y < MAX_ANGLE)
        angle_y += ANGLE_OFFSET;
    else
        angle_y = 0;

    repaint();
}

void __fastcall TForm1::Button10Click(TObject *Sender)
{
    if(angle_z < MAX_ANGLE)
        angle_z += ANGLE_OFFSET;
    else
        angle_z = 0;
        
    repaint();
}

int new_center_y = 6;
int new_center_x = 10;

void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
    int center_pos = Form1->UpDown1->Position;

    if(new_center_y > center_pos)
        center_y += COORDINATE_OFFSET;
    else
        center_y -= COORDINATE_OFFSET;

    repaint();
    new_center_y = center_pos;
}

void __fastcall TForm1::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
    int center_pos = Form1->UpDown2->Position;

    if(new_center_x > center_pos)
        center_x -= COORDINATE_OFFSET;
    else
        center_x += COORDINATE_OFFSET;

    repaint();
    new_center_x = center_pos;
}


