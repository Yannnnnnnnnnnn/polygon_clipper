/*******************************************************************************
* Author    :  Angus Johnson                                                   *
* Date      :  10 November 2017                                                *
* Website   :  http://www.angusj.com                                           *
* Copyright :  Angus Johnson 2010-2017                                         *
*                                                                              *
* License   : http://www.boost.org/LICENSE_1_0.txt                             *
*******************************************************************************/

#ifndef svglib_h
#define svglib_h

#include <cstdlib>
#include <string>
#include "clipper.h"

namespace svglib {

  //---------------------------------------------------------------------------
  // SVGBuilder: a very simple class that creates an SVG image file
  //---------------------------------------------------------------------------

  class SVGBuilder
  {
    class CoordsStyle {
    public:
      std::string font_name;
      unsigned font_color;
      unsigned font_size;
    };

    class CaptionInfo {
    public:
      std::string caption;
      unsigned font_color;
      unsigned font_size;
      int x;
      int y;
    };

    class PathInfo {
    private:
      unsigned brush_color_;
      unsigned pen_color_;
      double pen_width_;
      bool show_coords_;
      clipperlib::Paths paths_;
      bool is_open_path;
    public:
      PathInfo(const clipperlib::Paths &paths, bool is_open, 
        unsigned brush_clr, unsigned pen_clr, double pen_width, bool show_coords) :
        paths_(paths), is_open_path(is_open), brush_color_(brush_clr), 
        pen_color_(pen_clr), pen_width_(pen_width), show_coords_(show_coords) {};
      friend class SVGBuilder;
    };

    typedef std::vector< PathInfo* > PathInfoList;
  private:
    CoordsStyle coords_style;
    CaptionInfo caption_info_;
    PathInfoList path_info_list_;
  public:
    SVGBuilder() { fill_rule = clipperlib::frEvenOdd; coords_style.font_name = "Verdana"; 
      coords_style.font_color = 0xFF000000; coords_style.font_size = 11; };
    ~SVGBuilder() { Clear(); };
    clipperlib::FillRule fill_rule;
    void Clear();
    void SetCoordsStyle(std::string font_name, unsigned font_color, unsigned font_size);
    void AddCaption(const std::string caption, unsigned font_color, unsigned font_size, int x, int y);    
    void AddPath(const clipperlib::Path &path, bool is_open, unsigned brush_color,
      unsigned pen_color, double pen_width, bool show_coords);    
    void AddPaths(const clipperlib::Paths &paths, bool is_open, unsigned brush_color, 
      unsigned pen_color, double pen_width, bool show_coords);
    bool SaveToFile(const std::string &filename, int max_width, int max_height, int margin);
  }; //class

} //namespace

#endif //svglib_h
