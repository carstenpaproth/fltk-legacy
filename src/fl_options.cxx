//
// "$Id: fl_options.cxx,v 1.66 2000/07/14 10:09:17 spitzak Exp $"
//
// Scheme and theme option handling code for the Fast Light Tool Kit (FLTK).
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
//                                   Shell No 2

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/conf.h>
#include <FL/fl_load_plugin.H>
#include <FL/Fl_Color.H>
#include <FL/Fl_Font.H>
#include <FL/Fl_Labeltype.H>
#include <FL/Fl_Style.H>
#include <FL/Fl_Widget.H>
#include <config.h>
#if defined(WIN32) || defined(__EMX__)
#  include <windows.h>
#  include <io.h>
extern "C" int access(const char *, int);
#  define F_OK 0
#else
#  include <unistd.h>
#endif /* WIN32 || __EMX__ */

#ifndef R_OK
#define R_OK 4
#endif

#ifndef PATH_MAX
#define PATH_MAX 128
#endif

const char* Fl::scheme_ = 0;
Fl_Color fl_bg_switch = 0; // set by -bg in Fl_arg.cxx

static const char* flconfig = 0;
static char beenhere = 0;
extern void fl_get_system_colors();

static int load_scheme(const char*);

// one-time startup stuff
void fl_startup() {
  beenhere = 1;
  if (!flconfig) {
    const char* p = fl_find_config_file("flconfig");
    if (p) flconfig = strdup(p);
  }
  fl_get_system_colors();
  const char* s = Fl::scheme();
  char temp[PATH_MAX];
  if (!s && !getconf(flconfig, "default/scheme", temp, sizeof(temp))) s = temp;
  load_scheme(s);
  if (fl_bg_switch) fl_background(fl_bg_switch);
}

// After it is opened it can call this to redo everything:
int Fl::reload_scheme() {
  Fl_Style::revert();
  fl_startup();
  return 0;
}

// When we change the scheme we automatically call reload_scheme if needed:
int Fl::scheme(const char* s) {
  if (scheme_ == s) return 0;
  if (s && scheme_ && !strcmp(s,scheme_)) return 0;
  scheme_ = s;
  if (beenhere) reload_scheme();
  return 1;
}

// The rest of this is Carl's config file reader:

static Fl_Color grok_color(const char* cf, const char *colstr) {
  char key[80], val[32];
  const char *p = colstr;
  snprintf(key, sizeof(key), "aliases/%s", colstr);
  if (!getconf(cf, key, val, sizeof(val))) p = val;
  char* q;
  long l = strtoul(p, &q, 0);
  if (!*q) return (Fl_Color)l;
  return fl_rgb(p);
}

static Fl_Font grok_font(const char* cf, const char* fontstr) {
  char key[80], val[80];
  const char *p = fontstr;
  snprintf(key, sizeof(key), "aliases/%s", fontstr);
  if (!getconf(cf, key, val, sizeof(val))) p = val;

  char* q;
  long l = strtoul(p, &q, 0);
  if (!*q) return fl_fonts+l;

  return fl_font(p);
}

static int load_theme(const char*);

static int load_scheme(const char* s) {

  char temp[PATH_MAX];
  strncpy(temp, s, sizeof(temp));
  const char* p = access(temp, R_OK) ? 0 : temp;
  if (!p && !conf_is_path_rooted(s)) {
    snprintf(temp, sizeof(temp), "schemes/%s", s);
    p = fl_find_config_file(temp);
  }

  if (!p) {
    fprintf(stderr, "Cannot find scheme \"%s\"\n", temp);
    return -1;
  }

  char sfile[PATH_MAX];
  strncpy(sfile, p, sizeof(sfile));
  if (!::getconf(sfile, "general/themes", temp, sizeof(temp)))
    for (p = strtok(temp, CONF_WHITESPACE); p; p = strtok(NULL, CONF_WHITESPACE))
      load_theme(p);
  char valstr[80];
  Fl_Color col;

  if (!::getconf(sfile, "global colors/background", valstr, sizeof(valstr))) {
    col = grok_color(sfile, valstr);
    fl_background(fl_get_color(col));
  }

  static struct { const char* key; Fl_Color col; } colors[] = {
    { "DARK1", FL_DARK1 },
    { "DARK2", FL_DARK2 },
    { "DARK3", FL_DARK3 },
    { "LIGHT1", FL_LIGHT1 },
    { "LIGHT2", FL_LIGHT2 },
    { "LIGHT3", FL_LIGHT3 },
    { 0, 0 }
  };

  for (int i = 0; colors[i].key; i++) {
    snprintf(temp, sizeof(temp), "global colors/%s", colors[i].key);
    int res = ::getconf(sfile, temp, valstr, sizeof(valstr));
    if (!res) {
      col = grok_color(sfile, valstr);
      fl_set_color(colors[i].col, col);
    }
  }

  for (Fl_Named_Style* style = Fl_Named_Style::first; style; style = style->next) {
    int namepos = snprintf(temp, sizeof(temp), "widgets/%s/", style->name);
    int namelen = sizeof(temp)-namepos;

    // box type
    Fl_Boxtype boxtype;
    strncpy(temp+namepos, "box", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      if ( (boxtype = Fl_Boxtype_::find(valstr)) ) style->box = boxtype;

    // glyph box type
    strncpy(temp+namepos, "text box", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      if ( (boxtype = Fl_Boxtype_::find(valstr)) ) style->text_box = boxtype;

    // color
    strncpy(temp+namepos, "color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->color = grok_color(sfile, valstr);

    // label color
    strncpy(temp+namepos, "label color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->label_color = grok_color(sfile, valstr);

    // selection color
    strncpy(temp+namepos, "selection color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->selection_color = grok_color(sfile, valstr);

    // selection text color
    strncpy(temp+namepos, "selection text color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->selection_text_color = grok_color(sfile, valstr);

    // off color
    strncpy(temp+namepos, "text background", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->text_background = grok_color(sfile, valstr);

    // highlight color
    strncpy(temp+namepos, "highlight color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->highlight_color = grok_color(sfile, valstr);

    // highlight label color
    strncpy(temp+namepos, "highlight label color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->highlight_label_color = grok_color(sfile, valstr);

    // color
    strncpy(temp+namepos, "text color", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->text_color = grok_color(sfile, valstr);

    Fl_Font font;

    // label font
    strncpy(temp+namepos, "label font", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      if ( (font = grok_font(sfile, valstr)) ) style->label_font = font;

    // text font
    strncpy(temp+namepos, "text font", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      if ( (font = grok_font(sfile, valstr)) ) style->text_font = font;

    // label type
    Fl_Labeltype labeltype;
    strncpy(temp+namepos, "label type", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      if ( (labeltype = Fl_Labeltype_::find(valstr)) ) style->label_type = labeltype;

    // label size
    strncpy(temp+namepos, "label size", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->label_size = (int)strtol(valstr,0,0);

    // text size
    strncpy(temp+namepos, "text size", namelen);
    if (!::getconf(sfile, temp, valstr, sizeof(valstr)))
      style->text_size = (int)strtol(valstr,0,0);

  }

  Fl::redraw();
  return 0;
}

static int load_theme(const char *t) {
// don't try to load themes if not linked to shared libraries
  //#ifdef FL_SHARED
  if (!t) { Fl_Style::revert(); return 0; }
  char temp[PATH_MAX];
  strncpy(temp, t, sizeof(temp));
  if (strlen(temp)<6 || strcasecmp(temp+strlen(temp)-6, ".theme"))
    strncat(temp, ".theme", sizeof(temp)-strlen(temp)-1);
  const char* tfile = access(temp, R_OK) ? 0 : temp;
  if (!tfile && !conf_is_path_rooted(t)) {
    snprintf(temp, sizeof(temp), "themes/%s", t);
    if (strlen(temp)<6 || strcasecmp(temp+strlen(temp)-6, ".theme"))
      strncat(temp, ".theme", sizeof(temp)-strlen(temp)-1);
    tfile = fl_find_config_file(temp);
  }
  if (!tfile) {
    fprintf(stderr, "Cannot find theme \"%s\"\n", temp);
    return -1;
  }

  strncpy(temp, tfile, sizeof(temp));
  int r = fl_load_plugin(temp, "fltk_theme");
  if (r) {
    fprintf(stderr, "Cannot load theme \"%s\": %d\n", temp, r);
    return r;
  }

  Fl::redraw();
  //#endif
  return 0;
}

#ifndef WIN32
#define HOMEVAR "HOME"
#define HOMEFLTKDIR "/.fltk/"
#else
#define HOMEVAR "HOMEPATH"
#define HOMEFLTKDIR "/fltk/"
#endif

#ifndef CONFIGDIR
#define CONFIGDIR "/fltk"
#endif

const char* fl_find_config_file(const char* fn, int cflag) {
  static char path[PATH_MAX];

  if (conf_is_path_rooted(fn)) {
    strcpy(path, fn);
    return (cflag || !access(path, R_OK)) ? path : 0;
  }
  char *cptr = getenv(HOMEVAR);
  if (cptr) {
    snprintf(path, sizeof(path), "%s%s%s", cptr, HOMEFLTKDIR, fn);
    if (cflag || !access(path, R_OK)) return path;
  }
#ifdef WIN32
  cptr = getenv("USERPROFILE");
  if (cptr) {
    snprintf(path, sizeof(path), "%s/Application Data/fltk/%s", cptr, fn);
    if (cflag || !access(path, R_OK)) return path;
  }
#endif

  snprintf(path, sizeof(path), CONFIGDIR "/%s", fn);
  return (cflag || !access(path, R_OK)) ? path : 0;
}

//
// End of "$Id: fl_options.cxx,v 1.66 2000/07/14 10:09:17 spitzak Exp $".
//


