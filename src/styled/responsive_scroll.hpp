#ifndef STYLED_RESPONSIVE_GROUP_INCLUDED
#define STYLED_RESPONSIVE_GROUP_INCLUDED

#include "FL/Fl_Scroll.H"

#include "styled/widget.hpp"

namespace styled {

struct ResponsiveScroll : public Widget<Fl_Scroll> {
  int xsep = 0;
  int ysep = 0;

  template<typename... Args>
  ResponsiveScroll(Args... args): Widget<Fl_Scroll>(args...){}

  // Rearrange the children based on new xywh
  void RearrangeChildren(int X, int Y, int W, int H) {
    int nchildren =
        children() - 2; // -2: ignore Fl_Scroll's two child scrollbars
    if (nchildren < 1)
      return;
    int sw = (scrollbar.visible()) ? scrollbar.w() : 0;
    // Figure out how many thumbnails we can arrange horizontally
    int thumb_w = (child(0)->w() +
                   xsep); // overall width of thumbnail, including separation
    int thumb_h = (child(0)->h() +
                   ysep); // overall height of thumbnail, including separation
    int nw =
        (W - sw - xsep) /
        thumb_w; // max # thumbnails we can arrage horizontally before wrapping
    int remain = (W - sw - xsep) % thumb_w; // remainder of division
    if (nw < 2)
      nw = 2;                           // minimum number of thumbs
    int left = X + xsep + (remain / 2); // left edge of thumb arrangement
    int top = Y + ysep;                 // top edge of thumb arrangement
    // Now walk the children, moving them around
    int tx = left;
    int ty = top;
    for (int i = 0; i < nchildren; i++) {
      Fl_Widget *w = child(i);
      w->position(tx, ty);
      if ((i % nw) == (nw - 1)) { // wrap?
        ty += thumb_h;            // advance to next row
        tx = left;                // reset to left
      } else {                    // no wrap?
        tx += thumb_w;            // just advance to next right position
      }
    }
  }
  void resize(int X, int Y, int W, int H) {
    RearrangeChildren(X, Y, W, H); // move children around to fit new size
    Fl_Scroll::resize(X, Y, W, H); // let Fl_Scroll handle the new arrangement
  }
};
}

#endif //STYLED_RESPONSIVE_GROUP_INCLUDED
