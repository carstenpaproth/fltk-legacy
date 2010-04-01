//
// "$Id: DoubleBufferWindow.h 7365 2010-03-30 15:18:29Z matt $"
//
// Double-buffered window header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
   DoubleBufferWindow widget . */

#ifndef Fltk3_Double_Window_H
#define Fltk3_Double_Window_H

#include "Window.h"

class Fl_Double_Window;

namespace fltk3 {

/**
  The fltk3::DoubleBufferWindow provides a double-buffered window.
  If possible this will use the X double buffering extension (Xdbe).  If
  not, it will draw the window data into an off-screen pixmap, and then
  copy it to the on-screen window.
  <P>It is highly recommended that you put the following code before the
  first show() of <I>any</I> window in your program: </P>
  \code
  fltk3::visual(FL_DOUBLE|FL_INDEX)
  \endcode
  This makes sure you can use Xdbe on servers where double buffering
  does not exist for every visual.
*/
class FL_EXPORT DoubleBufferWindow : public Window {
  friend class ::Fl_Double_Window;
protected:
  void flush(int eraseoverlay);
  /**
    Force double buffering, even if the OS already buffers windows
    (overlays need that on MacOS and Windows2000)
  */
  char force_doublebuffering_;
public:
  void show();
  void show(int a, char **b) {Window::show(a,b);}
  void flush();
  void resize(int,int,int,int);
  void hide();
  ~DoubleBufferWindow();
  /**
    Creates a new fltk3::DoubleBufferWindow widget using the given
    position, size, and label (title) string.
  */
  DoubleBufferWindow(int W, int H, const char *l = 0) 
  : Window(W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
   /**
    See  fltk3::DoubleBufferWindow::fltk3::DoubleBufferWindow(int w, int h, const char *label = 0)
  */
  DoubleBufferWindow(int X, int Y, int W, int H, const char *l = 0)
  : Window(X,Y,W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
};

} // namespace fltk3
  
#endif

//
// End of "$Id: DoubleBufferWindow.h 7365 2010-03-30 15:18:29Z matt $".
//