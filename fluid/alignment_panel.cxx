// generated by Fast Light User Interface Designer (fluid) version 2.0001

#include "alignment_panel.h"

Fl_Window *alignment_window=(Fl_Window *)0;

Fl_Input *horizontal_input=(Fl_Input *)0;

Fl_Input *vertical_input=(Fl_Input *)0;

Fl_Input *snap_input=(Fl_Input *)0;

Fl_Input *header_file_input=(Fl_Input *)0;

Fl_Input *code_file_input=(Fl_Input *)0;

Fl_Light_Button *include_H_from_C_button=(Fl_Light_Button *)0;

static void cb_Close(Fl_Button*, void*) {
  alignment_window->hide();
}

Fl_Window* make_alignment_window() {
  Fl_Window* w;
  { Fl_Window* o = alignment_window = new Fl_Window(210, 310, "fluid Preferences");
    w = o;
    { Fl_Group* o = new Fl_Group(10, 20, 190, 100, "Alignment:");
      o->box(FL_ENGRAVED_BOX);
      o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
      { Fl_Input* o = horizontal_input = new Fl_Input(80, 10, 100, 20, "Horizontal:");
        o->callback((Fl_Callback*)alignment_cb, (void*)(1));
        o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
      }
      { Fl_Input* o = vertical_input = new Fl_Input(80, 40, 100, 20, "Vertical:");
        o->callback((Fl_Callback*)alignment_cb, (void*)(2));
        o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
      }
      { Fl_Input* o = snap_input = new Fl_Input(80, 70, 100, 20, "Snap:");
        o->callback((Fl_Callback*)alignment_cb, (void*)(3));
        o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(10, 140, 190, 130, "Output File Names:");
      o->box(FL_ENGRAVED_BOX);
      o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
      { Fl_Box* o = new Fl_Box(10, 10, 170, 30, "Use \"name.ext\" to set name or just \".ext\" to set only extension.");
        o->label_size(10);
        o->align(132|FL_ALIGN_INSIDE);
      }
      { Fl_Input* o = header_file_input = new Fl_Input(90, 40, 90, 20, "Header File:");
        o->callback((Fl_Callback*)header_input_cb, (void*)(1));
        o->when(FL_WHEN_CHANGED);
      }
      { Fl_Input* o = code_file_input = new Fl_Input(90, 70, 90, 20, "Code File:");
        o->callback((Fl_Callback*)code_input_cb, (void*)(1));
        o->when(FL_WHEN_CHANGED);
      }
      { Fl_Light_Button* o = include_H_from_C_button = new Fl_Light_Button(10, 100, 170, 20, "Include Header from Code");
        o->value(1);
        o->callback((Fl_Callback*)include_H_from_C_button_cb);
      }
      o->end();
    }
    { Fl_Button* o = new Fl_Button(140, 280, 60, 20, "Close");
      o->callback((Fl_Callback*)cb_Close);
    }
    o->end();
  }
  return w;
}
