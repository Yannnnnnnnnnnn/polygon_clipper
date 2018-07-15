#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "clipper.h"
#include "clipper_offset.h"

using namespace std;
using namespace clipperlib;


int main(int argc, char* argv[])
{
  Paths subject, clip, solution;
  
  ClipType ct = ctIntersection;
  FillRule fr = frNonZero;
  Clipper clipper; 
  time_t time_start = clock();
  /************************************************************************/
  int edge_cnt = 4;
  ct = ctIntersection;//ctUnion;//
  fr = frEvenOdd;//frNonZero;//
  /************************************************************************/
  subject.resize(1);
  subject[0].resize(edge_cnt);
  subject[0][0].x = 0;   subject[0][0].y = 0;
  subject[0][1].x = 100; subject[0][1].y = 0;
  subject[0][2].x = 100; subject[0][2].y = 100;
  subject[0][3].x = 0;   subject[0][3].y = 100;

  clip.resize(1);
  clip[0].resize(edge_cnt);
  clip[0][0].x = 50;   clip[0][0].y = 0;
  clip[0][1].x = 150;  clip[0][1].y = 0;
  clip[0][2].x = 150;  clip[0][2].y = 150;
  clip[0][3].x = 50;   clip[0][3].y = 150;
  
  clipper.Clear();
  clipper.AddPaths(subject, ptSubject);
  clipper.AddPaths(clip, ptClip);
  clipper.Execute(ct, solution, fr);
  
  // Output the result
  std::cout<<"Result Polygon Size:"<<solution.size()<<std::endl;
  for(int i=0;i<solution.size();i++)
  {
    std::cout<<"Polygon: "<<i+1<<std::endl;
    std::cout<<"Point Number: "<<solution[i].size()<<std::endl;
    std::cout<<"x\ty"<<std::endl;
    for(int j=0;j<solution[i].size();j++)
    {
      std::cout<<solution[i][j].x<<"\t"<<solution[i][j].y<<std::endl;
    }
  }


  double time_elapsed = ((double)clock() - time_start) * 1000 / CLOCKS_PER_SEC;
  cout << "\nFinished in " << time_elapsed << " msecs.\n\n";

  return 0;
}
//---------------------------------------------------------------------------
