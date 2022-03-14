// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "template_panel.h"
// Code for //\n// "$Id$"\n//\n// FLUID template support for ...
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fltk/string.h>
#include <fltk/events.h>
#include <fltk/filename.h>
#include <fltk/ask.h>
#include <fltk/SharedImage.h>
#include "PrefsData.h"
#if defined(WIN32) && !defined(__CYGWIN__)
#include <io.h>
#else
#include <unistd.h>
#endif // WIN32 && !__CYGWIN__

fltk::DoubleBufferWindow *template_panel=(fltk::DoubleBufferWindow *)0;

static void cb_template_panel(fltk::DoubleBufferWindow*, void*) {
  fltk::SharedImage *img = (fltk::SharedImage *)template_preview->image();
  if (img) img->remove();
  template_preview->image((fltk::Symbol*)0);
  
  template_browser->deselect();
  template_name->value("");
  template_instance->value("");
  template_panel->hide();
}

fltk::Browser *template_browser=(fltk::Browser *)0;

fltk::InvisibleBox *template_preview=(fltk::InvisibleBox *)0;

fltk::Input *template_name=(fltk::Input *)0;

static void cb_template_name(fltk::Input*, void*) {
  if (strlen(template_name->value())) {
    template_submit->activate();
    if (fltk::event_key() == fltk::KeypadEnter || fltk::event_key() == fltk::ReturnKey) template_panel->hide();
  } else template_submit->deactivate();
}

fltk::Input *template_instance=(fltk::Input *)0;

fltk::Button *template_delete=(fltk::Button *)0;

static void cb_Cancel(fltk::Button*, void*) {
  fltk::SharedImage *img = (fltk::SharedImage *)template_preview->image();
  if (img) img->remove();
  template_preview->image((fltk::Symbol*)0);
  
  template_browser->deselect();
  template_name->value("");
  template_instance->value("");
  template_panel->hide();
}

fltk::ReturnButton *template_submit=(fltk::ReturnButton *)0;

static void cb_template_submit(fltk::ReturnButton*, void*) {
  fltk::SharedImage *img = 
  	 (fltk::SharedImage *)template_preview->image();
  if (img) img->remove();
  template_preview->image((fltk::Symbol*)0);
  
  template_panel->hide();
}

fltk::DoubleBufferWindow* make_template_panel() {
  fltk::DoubleBufferWindow* w;
   {fltk::DoubleBufferWindow* o = template_panel = new fltk::DoubleBufferWindow(460, 355, "New/Save Template");
    w = o;
    o->type(241);
    o->shortcut(0xff1b);
    o->callback((fltk::Callback*)cb_template_panel);
    o->begin();
     {fltk::Browser* o = template_browser = new fltk::Browser(10, 28, 180, 250, "Available Templates:");
      o->set_vertical();
      o->labelfont(fltk::HELVETICA_BOLD);
      o->callback((fltk::Callback*)template_browser_cb);
      o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
     {fltk::InvisibleBox* o = template_preview = new fltk::InvisibleBox(200, 28, 250, 250);
      o->box(fltk::THIN_DOWN_BOX);
      o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER|fltk::ALIGN_CLIP);
      fltk::Group::current()->resizable(o);
    }
     {fltk::Input* o = template_name = new fltk::Input(124, 288, 326, 25, "Template Name:");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->textfont(fltk::COURIER);
      o->callback((fltk::Callback*)cb_template_name);
      o->when(fltk::WHEN_NEVER);
    }
     {fltk::Input* o = template_instance = new fltk::Input(124, 288, 326, 25, "Instance Name:");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->textfont(fltk::COURIER);
      o->hide();
    }
     {fltk::Group* o = new fltk::Group(10, 323, 440, 25);
      o->begin();
       {fltk::Button* o = template_delete = new fltk::Button(0, 0, 133, 25, "Delete Template");
        o->callback((fltk::Callback*)template_delete_cb);
      }
       {fltk::InvisibleBox* o = new fltk::InvisibleBox(143, 0, 126, 25);
        fltk::Group::current()->resizable(o);
      }
       {fltk::Button* o = new fltk::Button(279, 0, 72, 25, "Cancel");
        o->callback((fltk::Callback*)cb_Cancel);
      }
       {fltk::ReturnButton* o = template_submit = new fltk::ReturnButton(361, 0, 79, 25, "Save");
        o->shortcut(0xff0d);
        o->callback((fltk::Callback*)cb_template_submit);
      }
      o->end();
    }
    o->end();
    o->set_modal();
  }
  return  w;
}

void template_clear() {
  // in fltk2 no need to delete label because they have the COPIED 
  // internal flags set so that it will delete automatically on destruction
  template_browser->deselect();
  template_browser->clear();
}

void template_load() {
  int i;
  char name[1024], filename[2048], path[1024], *ptr;
  struct dirent **files;
  int num_files;
  
  prefs.getUserdataPath(path, sizeof(path));
  strlcat(path, "templates", sizeof(path));
  
  num_files = fltk::filename_list(path, &files);
  
  for (i = 0; i < num_files; i ++) {
    if (fltk::filename_match(files[i]->d_name, "*.fl")) {
      // Format the name as the filename with "_" replaced with " "
      // and without the trailing ".fl"...
      strlcpy(name, files[i]->d_name, sizeof(name));
      *strstr(name, ".fl") = '\0';
  
      for (ptr = name; *ptr; ptr ++) {
        if (*ptr == '_') *ptr = ' ';
      }
  
      // Add the template to the browser...
      snprintf(filename, sizeof(filename), "%s/%s", path, files[i]->d_name);
      template_browser->add(name, strdup(filename));
    }
  
    free(files[i]);
  }
  
  if (num_files > 0) free(files);
}
// Code for //\n// End of "$Id$".\n//
