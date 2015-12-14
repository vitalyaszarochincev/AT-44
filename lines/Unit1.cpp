#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner){}

const int GRID_FROM = 10;
const int CELL_SIZE = 5;
const int CELL_NUM = 60;
const int FIELD_SIZE = CELL_NUM * CELL_SIZE;
int m[CELL_NUM][CELL_NUM];
const int Color1 = clRed;
const int Color2 = clBlue;
const int Color3 = clYellow;

void drawGrid()
{
    int x = GRID_FROM;
    int y = GRID_FROM;

    for (int i = 0; i <= CELL_NUM; i++)
    {
        Form1->Canvas->MoveTo(x, y);
        Form1->Canvas->LineTo(x, y + FIELD_SIZE);
        x += CELL_SIZE;
    }

    x = GRID_FROM;

    for (int i = 0; i <= CELL_NUM; i++)
    {
        Form1->Canvas->MoveTo(x, y);
        Form1->Canvas->LineTo(x + FIELD_SIZE, y);
        y += CELL_SIZE;
    }
}

void putCircle(int x, int y, int color)
{
    Form1->Canvas->Brush->Color = (TColor)color;

    if (x < 0 || y < 0 || x >= CELL_NUM || y >= CELL_NUM)
        return;

    Form1->Canvas->Ellipse(GRID_FROM + x * CELL_SIZE, GRID_FROM + (CELL_NUM - 1) * CELL_SIZE - y * CELL_SIZE, GRID_FROM + CELL_SIZE + x * CELL_SIZE, GRID_FROM + FIELD_SIZE - y * CELL_SIZE);
    m[x][y] = Color1;
}

void CDA(double fromX, double fromY, double toX, double toY)
{
    double diffX = fabs(toX - fromX);
    double diffY = fabs(toY - fromY);
    double circlesNum = (diffX >= diffY ? diffX : diffY);
    double Dx = (toX - fromX) / circlesNum;
    double Dy = (toY - fromY) / circlesNum;
    double x = fromX + 0.5 * fabs(Dx);
    double y = fromY + 0.5 * fabs(Dy);

    for (double i = 1; i <= circlesNum; i++)
    {
        putCircle(x, y, Color3);
        x += Dx;
        y += Dy;
    }
}

void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void brez(int fromX, int fromY, int toX, int toY)
{
    bool flag = false;
    toX -= fromX;
    int dx = abs(toX);
    toY -= fromY;
    int dy = abs(toY);

    if (dx < dy)
    {
        swap(&dx, &dy);
        flag = true;
    }

    if (!toX && !toY)
        return;

    toX = (toX < 0 ? -1 : 1);
    toY = (toY < 0 ? -1 : 1);

    int e = dy * 2 - dx;

    for(int i = 0; i <= dx + dy; i++)
    {
        putCircle(fromX, fromY, Color2);

        if (e > 0)
        {
            if (flag)
                fromX += toX;
            else
                fromY += toY;

            e -= dx * 2;
        }else
        {
            if (flag)
                fromY += toY;
            else
                fromX += toX;

            e += dy * 2;
        }
    }
}

int LineFill (int x, int y, int dir, int PrevXl, int PrevXr)
{
    int xl = x;
    int xr = x;
    int c;

    do
        c = m[--xl][y];
    while(c != Color1);

    do
        c = m[++xr][y];
    while(c != Color1);

    m[x][y] = Color1;
    xl++;
    xr--;
    brez(xl, y, xr, y);

    for (x = xl; x <= xr; x++)
    {
        c = m[x][y + dir];

        if(c != Color1)
            x = LineFill(x, y + dir, dir, xl, xr);
    }

    for(x = xl; x < PrevXl; x++)
    {
        c = m[x][y - dir];

        if(c != Color1)
            x = LineFill(x, y - dir, -dir, xl, xr);
    }

    for(x = PrevXr; x < xr; x++)
    {
        c = m[x][y - dir];

        if(c != Color1)
            x = LineFill(x, y - dir, -dir, xl, xr);
    }

    return xr;
}

static void circle_okt(int ix, int iy, int x, int y)
{
    if (ix + x >= GRID_FROM || iy + y >= GRID_FROM || ix + x < CELL_SIZE || iy + y < CELL_NUM)
        putCircle(ix+x, iy+y, Color1);

    if (ix + y >= GRID_FROM || iy + x >= GRID_FROM || ix + y < CELL_SIZE || iy + x < CELL_NUM)
        putCircle(ix+y, iy+x, Color1);

    if (ix + y >= GRID_FROM || iy - x >= GRID_FROM || ix + y < CELL_SIZE || iy - x < CELL_NUM)
        putCircle(ix + y, iy - x, Color1);

    if (ix + x >= GRID_FROM || iy - y >= GRID_FROM || ix + x < CELL_SIZE || iy - y < CELL_NUM)
        putCircle(ix + x, iy - y, Color1);

    if (ix - x >= GRID_FROM || iy - y >= GRID_FROM || ix - x < CELL_SIZE || iy - y < CELL_NUM)
        putCircle(ix - x, iy - y, Color1);

    if (ix - y >= GRID_FROM || iy - x >= GRID_FROM || ix - y < CELL_SIZE || iy - x < CELL_NUM)
        putCircle(ix - y, iy - x, Color1);

    if (ix - y >= GRID_FROM || iy + x >= GRID_FROM || ix - y < CELL_SIZE || iy + x < CELL_NUM)
        putCircle(ix - y, iy + x, Color1);

    if (ix - x >= GRID_FROM || iy + y >= GRID_FROM || ix - x < CELL_SIZE || iy + y < CELL_NUM)
        putCircle(ix - x, iy + y, Color1);
}

void circle(int centerX, int centerY, int radius)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y)
    {
        circle_okt(centerX, centerY, x, y);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            --y;
        }

        x++;
    }

    if (x == y)
        circle_okt(centerX, centerY, x, y);
}

void triangle(int ax, int ay, int bx, int by, int cx, int cy)
{
    int Ax;
    int Ay;
    int Bx;
    int By;
    int Cx;
    int Cy;

    if ((ay >= by) && (ay >= cy))
    {
        Ay = ay;
        Ax = ax;

        if (by > cy)
        {
            By = by;
            Cy = cy;
            Bx = bx;
            Cx = cx;
        }else
        {
            By = cy;
            Cy = by;
            Bx = cx;
            Cx = bx;
        }
    }else if ((by >= ay) && (by >= cy))
    {
        Ay = by;
        Ax = bx;

        if (ay > cy)
        {
            By = ay;
            Cy = cy;
            Bx = ax;
            Cx = cx;
        }
        else
        {
            By = cy;
            Cy = ay;
            Bx = cx;
            Cx = ax;
        }
    }else if ((cy >= ay) && (cy >= by))
    {
        Ay = cy;
        Ax = cx;

        if (ay > by)
        {
            By = ay;
            Cy = by;
            Bx = ax;
            Cx = bx;
        }else
        {
            By = by;
            Cy = ay;
            Bx = bx;
            Cx = ax;
        }
    }

    int x1;
    int x2;

    for(int sy = Cy; sy <= Ay; sy++)
    {
        x1 = Ax + (sy - Ay) * (Cx - Ax) / (Cy - Ay);

        if(sy > By)
            x2 = Ax + (sy - Ay) * (Bx - Ax) / (By - Ay);
        else
        {
            if (Cy == By)
                x2 = Bx;
            else
                x2 = Bx + (sy - By) * (Cx - Bx) / (Cy - By);
        }

        if(x1 > x2)
            swap(&x1, &x2);

        brez(x1, sy, x2, sy);
    }
}

void __fastcall TForm1::drawCDA(TObject *Sender)
{
    Form1->Repaint();
    int fromX = StrToFloat(Form1->ax->Text);
    int fromY = StrToFloat(Form1->ay->Text);
    int toX = StrToFloat(Form1->bx->Text);
    int toY = StrToFloat(Form1->by->Text);

    drawGrid();
    CDA(fromX, fromY, toX, toY);
}

void __fastcall TForm1::drawBrez(TObject *Sender)
{
    Form1->Repaint();

    int fromX = StrToFloat(Form1->ax2->Text);
    int fromY = StrToFloat(Form1->ay2->Text);
    int toX = StrToFloat(Form1->bx2->Text);
    int toY = StrToFloat(Form1->by2->Text);

    drawGrid();
    brez(fromX, fromY, toX, toY);
}

void __fastcall TForm1::drawCircle(TObject *Sender)
{
    Form1->Repaint();

    int centerX = StrToFloat(Form1->cx->Text);
    int centerY = StrToFloat(Form1->cy->Text);
    int radius = StrToFloat(Form1->r->Text);

    drawGrid();
    circle(centerX, centerY, radius);
}

void __fastcall TForm1::drawTriangle(TObject *Sender)
{
    Form1->Repaint();

    int firstX = StrToFloat(Form1->axt->Text);
    int firstY = StrToFloat(Form1->ayt->Text);
    int secondX = StrToFloat(Form1->bxt->Text);
    int secondY = StrToFloat(Form1->byt->Text);
    int thirdX = StrToFloat(Form1->cxt->Text);
    int thirdY = StrToFloat(Form1->cyt->Text);

    drawGrid();
    triangle(firstX, firstY, secondX, secondY, thirdX, thirdY);
}

void __fastcall TForm1::drawPicture(TObject *Sender)
{
    Form1->Repaint();
    drawGrid();
    circle(29, 29, 29);
    circle(32, 42, 6);
    CDA(32, 36, 20, 16);
    CDA(20, 16, 44, 16);
    CDA(44, 16, 32, 36);

    CDA(38, 16, 42, 16);
    CDA(42, 16, 38, 10);
    CDA(38, 10, 38, 16);

    CDA(26, 16, 22, 16);
    CDA(22, 16, 26, 10);
    CDA(26, 10, 26, 16);

    putCircle(35, 43, clBlack);
    putCircle(29, 43, clBlack);

    triangle(32, 41, 30, 39, 34, 39);

    LineFill (20, 20, 1, 20, 20);
}

void __fastcall TForm1::clean(TObject *Sender)
{
    Form1->Repaint();

    for (int i = 0; i < CELL_NUM; i++)
        for (int j = 0; j < CELL_NUM; j++)
            m[i][j] = 0;
}

