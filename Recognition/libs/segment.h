//---------------------------------------------------------------------------

#ifndef segmentH
#define segmentH

#include <vcl.h>
#include <stack>
#include <queue>

using namespace std;

void setColors(TColor fc, TColor rc);
void SetImage(TImage* img);
void BFS(int x, int y);
void BFS(int& minX, int& minY, int& maxX, int& maxY);
void DFS(int x, int y);
void DFS(int& minX, int& minY, int& maxX, int& maxY);

void BFS4(int x, int y);
void DFS4(int x, int y);
#endif
