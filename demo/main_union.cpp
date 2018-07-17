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
#include "svg.h"

using namespace std;
using namespace clipperlib;
using namespace svglib;

void SaveToSVG(const string filename, int max_width, int max_height, 
  Paths &subj, Paths &clip, Paths &solution,
  FillRule fill_rule, bool show_coords = false)
{
  SVGBuilder svg;
  svg.fill_rule = fill_rule;
  svg.SetCoordsStyle("Verdana", 0xFF0000AA, 9);
  svg.AddPaths(subj, false, 0x1200009C, 0xCCD3D3DA, 0.8, show_coords);
  svg.AddPaths(clip, false, 0x129C0000, 0xCCFFA07A, 0.8, show_coords);
  svg.AddPaths(solution, false, 0x6080ff9C, 0xFF003300, 0.8, show_coords);
  svg.SaveToFile(filename, max_width, max_height, 80);
}

int main(int argc, char* argv[])
{
  int display_width = 800, display_height = 600;
  bool show_cords = false;//true;//  //don't this if there are hundreds or thousands of coords :)


  Paths subject, clip, solution;
  
  ClipType ct = ctIntersection;
  FillRule fr = frNonZero;
  Clipper clipper; 
  time_t time_start = clock();
  /************************************************************************/
  int edge_cnt = 4;
  ct = ctUnion;
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

  Paths subject_open,solution_open;
  SaveToSVG("union.svg", display_width, display_height,
          subject, clip, solution, 
          fr, show_cords);
  system("union.svg");

  double time_elapsed = ((double)clock() - time_start) * 1000 / CLOCKS_PER_SEC;
  cout << "\nFinished in " << time_elapsed << " msecs.\n\n";

  return 0;
}
//---------------------------------------------------------------------------
