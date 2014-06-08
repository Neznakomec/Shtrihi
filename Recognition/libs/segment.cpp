//---------------------------------------------------------------------------


#pragma hdrstop

#include "segment.h"

TImage* Image1;

TColor FindColor;
TColor ReplaceColor;

void setColors(TColor fc, TColor rc)
{
FindColor = fc;
ReplaceColor = rc;
}

void SetImage(TImage* img)
{
Image1 = img;
}
//---------------------------------------------------------------------------
//
//      œŒ»—  ¬ ÿ»–»Õ”
//
//
//---------------------------------------------------------------------------
void BFS(int x, int y)
{
TPoint P;
queue<TPoint> Q;

Q.push(TPoint(x, y));
Image1->Canvas->Pixels[x][y] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.front();
   Q.pop();

   for (int i=P.x - 1; i <= P.x + 1; i++)
    for (int j=P.y - 1; j <= P.y + 1; j++)
     {
       if (Image1->Canvas->Pixels[i][j] == FindColor)
        {
          Image1->Canvas->Pixels[i][j] = ReplaceColor;
          Q.push(TPoint(i,j));
        }
     }

 }
}
//---------------------------------------------------------------------------

void BFS(int& minX, int& minY, int& maxX, int& maxY)
{
TPoint P;
queue<TPoint> Q;

Q.push(TPoint(minX, minY));
Image1->Canvas->Pixels[minX][minY] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.front();
   Q.pop();

   //Image1->Repaint();
   //Sleep(1);

   if (P.x < minX) minX = P.x;
   if (P.x > maxX) maxX = P.x;
   if (P.y < minY) minY = P.y;
   if (P.y > maxY) maxY = P.y;

   for (int i=P.x - 1; i <= P.x + 1; i++)
    for (int j=P.y - 1; j <= P.y + 1; j++)
     {
       if (Image1->Canvas->Pixels[i][j] == FindColor)
        {
          Image1->Canvas->Pixels[i][j] = ReplaceColor;
          Q.push(TPoint(i,j));
        }
     }

 }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void BFS4(int x, int y)
{
TPoint P;
queue<TPoint> Q;

Q.push(TPoint(x, y));
Image1->Canvas->Pixels[x][y] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.front();
   Q.pop();

   int j1=P.y;
   for (int i=P.x - 1; i <= P.x + 1; i++)
   if (Image1->Canvas->Pixels[i][j1] == FindColor)
        {
          Image1->Canvas->Pixels[i][j1] = ReplaceColor;
          Q.push(TPoint(i,j1));
        }

   int i1 = P.x;
   for (int j=P.y - 1; j <= P.y + 1; j++)
      if (Image1->Canvas->Pixels[i1][j] == FindColor)
       {
         Image1->Canvas->Pixels[i1][j] = ReplaceColor;
         Q.push(TPoint(i1,j));
       }
 } //end while
}
//---------------------------------------------------------------------------
//
//      œŒ»—  ¬ √À”¡»Õ”
//
//
//---------------------------------------------------------------------------
void DFS(int x, int y)
{
TPoint P;
stack<TPoint> Q;

Q.push(TPoint(x, y));
Image1->Canvas->Pixels[x][y] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.top();
   Q.pop();

   for (int i=P.x - 1; i <= P.x + 1; i++)
    for (int j=P.y - 1; j <= P.y + 1; j++)
     {
       if (Image1->Canvas->Pixels[i][j] == FindColor)
        {
          Image1->Canvas->Pixels[i][j] = ReplaceColor;
          Q.push(TPoint(i,j));
        }
     }

 }
}
//---------------------------------------------------------------------------

void DFS(int& minX, int& minY, int& maxX, int& maxY)
{
TPoint P;
stack<TPoint> Q;

Q.push(TPoint(minX, minY));
Image1->Canvas->Pixels[minX][minY] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.top();
   Q.pop();

   if (P.x < minX) minX = P.x;
   if (P.x > maxX) maxX = P.x;
   if (P.y < minY) minY = P.y;
   if (P.y > maxY) maxY = P.y;

   for (int i=P.x - 1; i <= P.x + 1; i++)
    for (int j=P.y - 1; j <= P.y + 1; j++)
     {
       if (Image1->Canvas->Pixels[i][j] == FindColor)
        {
          Image1->Canvas->Pixels[i][j] = ReplaceColor;
          Q.push(TPoint(i,j));
        }
     }

 }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void DFS4(int x, int y)
{
TPoint P;
stack<TPoint> Q;

Q.push(TPoint(x, y));
Image1->Canvas->Pixels[x][y] = ReplaceColor;

while (!Q.empty())
 {
   P = Q.top();
   Q.pop();

   int j1=P.y;
   for (int i=P.x - 1; i <= P.x + 1; i++)
   if (Image1->Canvas->Pixels[i][j1] == FindColor)
    {
      Image1->Canvas->Pixels[i][j1] = ReplaceColor;
      Q.push(TPoint(i,j1));
    }

   int i1 = P.x;
   for (int j=P.y - 1; j <= P.y + 1; j++)
    if (Image1->Canvas->Pixels[i1][j] == FindColor)
      {
        Image1->Canvas->Pixels[i1][j] = ReplaceColor;
        Q.push(TPoint(i1,j));
      }

 }
}
#pragma package(smart_init)
