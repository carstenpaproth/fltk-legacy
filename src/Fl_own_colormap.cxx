//
// "$Id: Fl_own_colormap.cxx,v 1.7 2002/12/09 04:52:27 spitzak Exp $"
//
// Private colormap support for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// Using the default system colormap can be a bad idea on PseudoColor
// visuals, since typically every application uses the default colormap and
// you can run out of colormap entries easily.
//
// The solution is to always create a new colormap on PseudoColor displays
// and copy the first 16 colors from the default colormap so that we won't
// get huge color changes when switching windows.

#include <fltk/visual.h>
#include <fltk/x.h>
#include <config.h>

#ifdef _WIN32
// There is probably something relevant to do on MSWindows 8-bit displays
// but I don't know what it is

void fltk::own_colormap() {}

#else
// X version

void fltk::own_colormap() {
  open_display();
#if USE_COLORMAP
  switch (xvisual->c_class) {
  case GrayScale :
  case PseudoColor :
  case DirectColor :
    break;
  default:
    return; // don't do anything for non-colormapped visuals
  }
  int i;
  XColor colors[16];
  // Get the first 16 colors from the default colormap...
  for (i = 0; i < 16; i ++) colors[i].pixel = i;
  XQueryColors(xdisplay, xcolormap, colors, 16);
  // Create a new colormap...
  xcolormap = XCreateColormap(xdisplay,
			      RootWindow(xdisplay,xscreen),
			      xvisual->visual, AllocNone);
  // Copy those first 16 colors to our own colormap:
  for (i = 0; i < 16; i ++)
    XAllocColor(xdisplay, xcolormap, colors + i);
#endif
}

#endif

//
// End of "$Id: Fl_own_colormap.cxx,v 1.7 2002/12/09 04:52:27 spitzak Exp $".
//
